#include <iostream>

int main() {
    int maxCalories = 0;    // Largest calorie value among the Elves
    int maxCalorieElf = 0;  // Elf ID with the largest calorie value
    int currentElf = 1;     // Current Elf ID
    bool done = false;      // Done reading Elf data
    char ch{};              // Buffer character to read separation byte

    while (!done) {
        int calorieSum = 0;  // Current Elf's calorie sum
        int calorie;         // Current calories value

        // Grab calories until the blank line is spotted
        while (std::cin && std::cin.peek() != '\n') {
            std::cin >> calorie;  // Extract integer from input
            std::cin.ignore();    // Remove newline after integer from input

            calorieSum += calorie;
        }

        if (calorieSum > maxCalories) {
            maxCalories = calorieSum;
            maxCalorieElf = currentElf;
        }

        ++currentElf;

        std::cin.get(ch);
        if (std::cin.eof()) {
            done = true;
        }
    }

    // Results
    printf("The Elf with the largest calorie count is %d.\n", maxCalorieElf);
    printf("They had %d calories.\n", maxCalories);

    return 0;
}
