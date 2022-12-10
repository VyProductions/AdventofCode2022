#include <iostream>
#include <unordered_map>

// How large the "window" is
const unsigned BUFFER_SIZE = 14;

int main() {
    // Moving buffer "window" to look at groups of characters
    char chars[BUFFER_SIZE] {};
    // Map a character to how many times it exists in the "window"
    std::unordered_map<char, int> charMap;
    // How many characters in the window are unique
    int char_count = 0;

    int char_length = 0;  // Length of signal read when buffer was all unique
    char ch;              // Individual character read in from signal string

    while (char_count != BUFFER_SIZE && std::cin >> ch) {
        ++char_length;

        // Decrease amount of times first character in "window" appears
        if (chars[0] != '\0') {
            charMap[chars[0]]--;
            char_count -= !charMap[chars[0]];
        }

        // Shift "window" over by one character
        for (unsigned i = 0; i < BUFFER_SIZE - 1; ++i) {
            chars[i] = chars[i+1];
        }
        // Place in new character at end of "window"
        chars[BUFFER_SIZE - 1] = ch;
        
        char_count += !charMap[ch];

        charMap[ch]++;
    }

    printf("Signal Length: %d\n", char_length);

    return 0;
}
