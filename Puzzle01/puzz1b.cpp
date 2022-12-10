#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> calorieTotals;
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

        calorieTotals.push_back(calorieSum);

        std::cin.get(ch);
        if (std::cin.eof()) {
            done = true;
        }
    }

    std::sort(calorieTotals.begin(), calorieTotals.end(), std::greater<int>());

    // Results

    if (calorieTotals.size() >= 3) {
        int& first  = calorieTotals.at(0);
        int& second = calorieTotals.at(1);
        int& third  = calorieTotals.at(2);

        printf("Top three calorie totals: %d %d %d\n", first, second, third);
        printf("Sum of top three: %d\n", first + second + third);
    } else {
        printf("Not enough Elves to get top three.\n");
    }

    return 0;
}
