#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // Map an item to its priority number
    std::unordered_map<char, int> itemPriorities;
    std::string rucksack1;  // Characters representing items in rucksack 1
    std::string rucksack2;  // Characters representing items in rucksack 2
    std::string rucksack3;  // Characters representing items in rucksack 3
    int prioritySum = 0;    // Sum of the priorities of each duplicated item

    // Initialize priorities
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        itemPriorities[ch] = (int)(ch - 38);
    }
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        itemPriorities[ch] = (int)(ch - 96);
    }

    // Loop over rucksacks
    while (std::cin >> rucksack1 >> rucksack2 >> rucksack3) {
        // Map a character to if it is in rucksack1
        std::unordered_map<char, bool> seen1;

        for (char& ch : rucksack1) {
            seen1[ch] = true;
        }

        // Map a character to if it is in both rucksack1 and rucksack2
        std::unordered_map<char, bool> seen2;

        for (char& ch : rucksack2) {
            if (seen1[ch]) {
                seen2[ch] = true;
            }
        }

        // Check rucksack3 for if any of its characters appear in rs1 and rs2
        for (char& ch : rucksack3) {
            if (seen2[ch]) {
                prioritySum += itemPriorities[ch];
                break;
            }
        }
    }

    printf("Total priority sum (triplet): %d\n", prioritySum);

    return 0;
}
