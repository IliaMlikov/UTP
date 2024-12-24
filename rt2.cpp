#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

void printUsage() {
    std::cout << "Пожалуйста, укажите директорию и расширение файлов." << std::endl;
}

void findFiles(const std::string& directory, const std::string& extension) {
    if (!fs::exists(directory)) {
        std::cout << "Директория не найдена." << std::endl;
        return;
    }

    std::vector<std::string> foundFiles;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ("." + extension)) {
            foundFiles.push_back(entry.path().string());
        }
    }

    if (foundFiles.empty()) {
        std::cout << "Файлы с расширением " << extension << " не найдены." << std::endl;
    } else {
        std::cout << "Найденные файлы с расширением " << extension << ":" << std::endl;
        for (const auto& file : foundFiles) {
            std::cout << file << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage();
        return 1;
    }

    std::string directory = argv[1];
    std::string extension = argv[2];

    findFiles(directory, extension);

    return 0;
}
