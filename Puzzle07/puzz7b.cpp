#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

// Helper struct to simulate a file system directory
struct directory {
    std::string dirName{};                    // Name of directory element
    std::list<directory>::iterator parent{};  // Iterator to parent directory
    std::list<directory> children{};          // Collection of child directories
};

// Helper struct to hold the directory listing and map of directory sizes
struct directoryTree {
    std::list<directory> tree;                    // Simulate a file system tree
    std::unordered_map<std::string, size_t> map;  // Map a directory to its size
};

/// @brief Handles all input, including commands and file/directory information.
///
/// @tparam dirIter : Directory iterator type (for simplifying parameter type).
///
/// @param direct : An iterator to the current directory.
/// @param dt : Reference to helper struct with file system information.

template <class dirIter>
void handleCommands(dirIter direct, directoryTree& dt);

int main() {
    directoryTree dt;  // Struct containing information about the file system

    // Process input regarding the file system
    handleCommands(dt.tree.begin(), dt);

    // Minimum amount of space required to be cleared
    const size_t missingSpace = 30'000'000 - (70'000'000 - dt.map["/"]);
    // Holds candidate directory sizes that would clear up the required space
    std::vector<size_t> dirSizes;

    for (auto& [key, value] : dt.map) {
        if (key.back() == '/' && value >= missingSpace) {
            dirSizes.push_back(value);
        }
    }

    // Find smallest entry
    size_t smallest = dirSizes.front();
    for (auto val : dirSizes) {
        if (val < smallest) {
            smallest = val;
        }
    }

    printf("Size of Directory To Be Deleted: %ld\n", smallest);

    return 0;
}

template <class dirIter>
void handleCommands(dirIter direct, directoryTree& dt) {
    std::string label;  // Command ("cd", "ls") or "dir" string from input
    std::string info;   // Directory or file name from input
    size_t fileSize;    // File size from input

    // Command identifier located
    if (std::cin.peek() == '$') {
        std::cin.ignore(2);  // Get rid of command identifier
        std::cin >> label;   // Read command to process

        // List directory contents
        if (label == "ls") {
            std::cin.ignore();           // Get rid of trailing newline
            handleCommands(direct, dt);  // Handle directory contents
        // Change directory
        } else if (label == "cd") {
            std::cin >> info;   // Read directory to change to
            std::cin.ignore();  // Get rid of trailing newline

            // Change to root directory
            if (info == "/") {
                if (!dt.map.count("/")) {
                    dt.map[info] = 0;
                    dt.tree.push_front({
                        "/",
                        dirIter{},
                        {}
                    });
                }

                // Handle commands from context of root directory
                handleCommands(dt.tree.begin(), dt);
            // Change to parent directory
            } else if (info == "..") {
                // Handle commands from context of parent directory
                handleCommands(direct->parent, dt);
            // Change to some child directory
            } else {
                auto newDirect = direct->children.begin();
                bool found = false;
                while (!found && newDirect != direct->children.end()) {
                    if (newDirect->dirName != direct->dirName + info + "/") {
                        ++newDirect;
                    } else {
                        found = true;
                    }
                }

                if (newDirect != dirIter{}) {
                    // Handle commands from context of child directory
                    handleCommands(newDirect, dt);
                }
            }
        }
    // Directory listing found
    } else if (std::cin.peek() == 'd') {
        std::cin.ignore(4);  // Ignore 'dir' label
        std::cin >> info;    // Read in directory name
        std::cin.ignore();   // Get rid of trailing newline

        // Initialize directory size in map
        dt.map[direct->dirName + info + "/"] = 0;

        // Set up directory in tree
        direct->children.push_back({
            direct->dirName + info + "/",
            direct,
            {}
        });

        // Continue handling commands from context of current directory
        handleCommands(direct, dt);
    // File listing found
    } else if (std::cin.peek() >= '0' && std::cin.peek() <= '9') {
        std::cin >> fileSize;  // Read in file size
        std::cin >> info;      // Read in file name
        std::cin.ignore();     // Get rid of trailing newline

        // Initialize file size in map
        dt.map[direct->dirName + info] = fileSize;

        // Update current directory size
        dt.map[direct->dirName] += fileSize;

        // Update parent directory sizes all the way back to the root
        auto parentDir = direct->parent;
        while (parentDir != dirIter{}) {
            dt.map[parentDir->dirName] += fileSize;
            parentDir = parentDir->parent;
        }

        // Set up file in tree
        direct->children.push_back({
            direct->dirName + info,
            direct,
            {}
        });
        
        // Continue to handle commands from context of current directory
        handleCommands(direct, dt);
    // Out of commands to process
    } else {
        return;
    }
}
