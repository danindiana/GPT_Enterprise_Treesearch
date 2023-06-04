#include <iostream>
#include <string>
#include <filesystem>
#include <thread>
#include <vector>

// Recursive function to perform IDDFS
void DLS(const std::filesystem::path& currentPath, const std::string& target, int depth) {
    try {
        if (depth >= 0) {
            std::vector<std::thread> threads;
            for (const auto& dirEntry : std::filesystem::directory_iterator(currentPath)) {
                if (depth == 0 && dirEntry.path().extension() == target) {
                    std::cout << "Found file: " << dirEntry.path() << std::endl;
                }
                else if (dirEntry.is_directory()) {
                    threads.emplace_back(DLS, dirEntry.path(), target, depth - 1);
                }
            }
            for(auto &th : threads) {
                th.join();
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error reading directory '" << currentPath << "': " << e.what() << std::endl;
    }
}

// Function to perform IDDFS up to a maximum depth
void IDDFS(const std::filesystem::path& rootPath, const std::string& target, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        DLS(rootPath, target, depth);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        std::cout << "Usage: ./program [targetExtension] [rootPath] [maxDepth]" << std::endl;
        return 1;
    }

    std::string targetExtension = argv[1]; // Your target extension
    std::filesystem::path rootPath = argv[2]; // Your root path
    int maxDepth = std::stoi(argv[3]); // Your max depth

    IDDFS(rootPath, targetExtension, maxDepth);

    return 0;
}
