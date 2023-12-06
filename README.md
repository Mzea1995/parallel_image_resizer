# Parallel Image Resizer Readme

## Description
Parallel Image Resizer is a C++ script designed to efficiently resize a set of images. Using multithreading, the script processes multiple images in parallel, improving performance on multi-core systems. Each image is resized to a fixed size of 2000x2000 pixels, and appropriate permissions are set for the output files.

## Features
- **Parallel Image Processing:** Utilizes multiple threads to process images simultaneously.
- **Standardized Resizing:** Resizes all images to 2000x2000 pixels.
- **File Permission Setting:** Configures permissions for resulting image files to ensure proper accessibility.
- **Performance Metrics:** Records total processing time, peak memory usage, and CPU usage percentage.

## Requirements
- C++ compiler with C++17 standard support.
- OpenCV installed and configured on your system.
- UNIX-based operating system (Linux, macOS) for full functionality, including file permission setting.

## Usage
### Compilation
Use the `make` command to compile the script. Make sure your environment has access to OpenCV and a compatible C++ compiler.

### Execution
Run the compiled script by providing the paths to the source and destination image folders.

