#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;
using namespace cv;

// Función para ejecutar tu script 'resize_image'
void runImageProcessingScript(const std::string& inputFolderPath, const std::string& outputFolderPath) {
    std::string command = "./resize_image " + inputFolderPath + " " + outputFolderPath;
    system(command.c_str());  // Ejecuta el script como un comando del sistema
}

// Función para verificar si la imagen ha sido redimensionada correctamente
bool isImageProcessedCorrectly(const std::string& imagePath, int targetWidth, int targetHeight) {
    Mat image = imread(imagePath, IMREAD_COLOR);
    if (image.empty()) {
        return false;
    }
    return image.cols == targetWidth && image.rows == targetHeight;
}

int main() {
    std::string sourceDir = "images"; // Cambia esto a la ruta de las imágenes de prueba
    std::string destDir = "previews";       // Cambia esto a la ruta de salida

    // Ejecuta el script de procesamiento de imágenes
    runImageProcessingScript(sourceDir, destDir);

    // Verifica que todas las imágenes se han procesado correctamente
    bool allImagesProcessed = true;
    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        std::string outputImagePath = destDir + "/" + entry.path().filename().string();
        if (!isImageProcessedCorrectly(outputImagePath, 2000, 2000)) {
            std::cerr << "Test de aceptación fallido para la imagen: " << entry.path() << std::endl;
            allImagesProcessed = false;
            break; // Sal del bucle si una imagen falla
        }
    }

    if (allImagesProcessed) {
        std::cout << "Test de aceptación superado con éxito." << std::endl;
        return 0;
    } else {
        std::cerr << "Test de aceptación fallido." << std::endl;
        return 1;
    }
}
