#include <iostream>
#include <string>
#include <filesystem>
#include <stack>
#include <vector>

// Recursive function to perform IDDFS
bool DLS(const std::filesystem::path& currentPath, const std::string& target, int depth) {
    try {
        if (depth >= 0) {
            for (const auto& dirEntry : std::filesystem::directory_iterator(currentPath)) {
                if (depth == 0 && dirEntry.path().filename() == target) {
                    std::cout << "Found file: " << dirEntry.path() << std::endl;
                    return true;
                }
                else if (dirEntry.is_directory()) {
                    if (DLS(dirEntry.path(), target, depth - 1)) {
                        return true;
                    }
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error reading directory '" << currentPath << "': " << e.what() << std::endl;
    }
    return false;
}

// Function to perform IDDFS up to a maximum depth
void IDDFS(const std::filesystem::path& rootPath, const std::string& target, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        if (DLS(rootPath, target, depth)) {
            return;
        }
    }
    std::cout << "File not found within depth " << maxDepth << std::endl;
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        std::cout << "Usage: ./program [targetFile] [rootPath] [maxDepth]" << std::endl;
        return 1;
    }

    std::string targetFile = argv[1]; // Your target file
    std::filesystem::path rootPath = argv[2]; // Your root path
    int maxDepth = std::stoi(argv[3]); // Your max depth

    IDDFS(rootPath, targetFile, maxDepth);

    return 0;
}
