#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // Map an item to its priority number
    std::unordered_map<char, int> itemPriorities;
    std::string rucksack;  // Characters representing items in the rucksack
    int prioritySum = 0;   // Sum of the priorities of each duplicated item

    // Initialize priorities
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        itemPriorities[ch] = (int)(ch - 38);
    }
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        itemPriorities[ch] = (int)(ch - 96);
    }

    // Loop over rucksacks
    while (std::cin >> rucksack) {
        // Map a character to if it has been seen in the right compartment
        std::unordered_map<char, bool> seenRight;
        // See which elements exist in the right compartment
        for (char& ch : rucksack.substr(rucksack.size() / 2, rucksack.size())) {
            seenRight[ch] = true;
        }
        // See which elements match an existing element in the left compartment
        for (char& ch : rucksack.substr(0, rucksack.size() / 2)) {
            if (seenRight[ch]) {
                prioritySum += itemPriorities[ch];
                break;
            }
        }
    }

    printf("Total priority sum (single): %d\n", prioritySum);

    return 0;
}
