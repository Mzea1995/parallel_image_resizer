#include <opencv2/opencv.hpp>
#include <filesystem>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <sys/resource.h>
#include <sys/stat.h>

namespace fs = std::filesystem;
using namespace cv;
using namespace std::chrono;

void processImage(const std::string& filePath, const std::string& outputFolderPath) {
    Mat originalImage = imread(filePath, IMREAD_COLOR);

    if (!originalImage.empty()) {
        Mat resizedImage;
        resize(originalImage, resizedImage, Size(2000, 2000));

        std::string newFileName = outputFolderPath + "/" + fs::path(filePath).filename().string();
        if (imwrite(newFileName, resizedImage)) {
            // Establecer los permisos de archivo usando chmod
            int result = chmod(newFileName.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (result != 0) {
                std::cerr << "Error al establecer los permisos para " << newFileName << std::endl;
            }
        } else {
            std::cerr << "Error al guardar la imagen " << newFileName << std::endl;
        }
    }
}

int main() {
    std::string inputFolderPath = "images"; // Cambiar a la ruta correcta
    std::string outputFolderPath = "previews"; // Cambiar a la ruta correcta

    const int MAX_THREADS = 5;

    auto totalStartTime = high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (const auto& entry : fs::directory_iterator(inputFolderPath)) {
        if (threads.size() >= MAX_THREADS) {
            threads.front().join();
            threads.erase(threads.begin());
        }

        if (fs::is_regular_file(entry.status())) {
            threads.emplace_back(processImage, entry.path().string(), outputFolderPath);
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    auto totalStopTime = high_resolution_clock::now();
    auto totalDuration = duration_cast<microseconds>(totalStopTime - totalStartTime);

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    auto cpuTime = duration_cast<microseconds>(
        microseconds(usage.ru_utime.tv_sec * 1000000L + usage.ru_utime.tv_usec) +
        microseconds(usage.ru_stime.tv_sec * 1000000L + usage.ru_stime.tv_usec)
    );

    double cpuUsagePercent = 100.0 * cpuTime.count() / totalDuration.count();

    std::cout << "Total time to process all images: " << duration_cast<milliseconds>(totalDuration).count() << " milliseconds." << std::endl;
    std::cout << "Peak memory usage: " << usage.ru_maxrss << " KB" << std::endl;
    std::cout << "CPU Usage Percentage: " << cpuUsagePercent << "%" << std::endl;

    return 0;
}
