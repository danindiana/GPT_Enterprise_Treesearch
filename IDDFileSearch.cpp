#include <iostream>
#include <string>
#include <filesystem>
#include <stack>
#include <vector>

// Recursive function to perform IDDFS
bool DLS(const std::filesystem::path& currentPath, const std::string& target, int depth) {
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

int main() {
    std::string targetFile = "target.txt"; // Your target file
    std::filesystem::path rootPath = "/"; // Your root path
    int maxDepth = 5; // Your max depth

    IDDFS(rootPath, targetFile, maxDepth);

    return 0;
}
