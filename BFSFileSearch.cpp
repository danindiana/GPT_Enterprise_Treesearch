#include <iostream>
#include <filesystem>
#include <deque>
#include <string>

namespace fs = std::filesystem;

// Structure to hold directory path and current depth
struct DirInfo {
    std::string path;
    int depth;
};

void bfs_file_search(const std::string& root_path, const std::string& target_filename, int max_depth) {
    std::deque<DirInfo> bfs_queue;   // Use a queue to perform BFS
    bfs_queue.push_back({root_path, 0});

    while (!bfs_queue.empty()) {
        DirInfo current_dir = bfs_queue.front();
        bfs_queue.pop_front();

        try {
            for (const auto& entry : fs::directory_iterator(current_dir.path)) {
                if (entry.is_regular_file() && entry.path().filename() == target_filename) {
                    std::cout << "Found target file at: " << entry.path() << '\n';
                } 
                else if (entry.is_directory() && current_dir.depth < max_depth) {
                    bfs_queue.push_back({entry.path().string(), current_dir.depth + 1});
                }
            }
        }
        catch (std::exception& e) {
            std::cerr << "Exception caught while accessing directory " << current_dir.path << ": " << e.what() << '\n';
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <root_path> <target_filename> <max_search_depth>\n";
        return 1;
    }

    bfs_file_search(argv[1], argv[2], std::stoi(argv[3]));
    return 0;
}
