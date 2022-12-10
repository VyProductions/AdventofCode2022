#include <iostream>
#include <string>
#include <unordered_map>

struct wl {
    char wins;
    char loses;
};

// Maps a choice to the two moves it (1) wins against and (2) loses against

std::unordered_map<char, wl> priorityMap = {
    {'X', {'C', 'B'}}, {'Y', {'A', 'C'}}, {'Z', {'B', 'A'}}
};

// Maps a choice to how many points that choice yields

std::unordered_map<char, int> choiceScores = {
    {'X', 1}, {'Y', 2}, {'Z', 3}
};

// Maps a round result to how many points are gained for that result

std::unordered_map<std::string, int> roundScores = {
    {"LOSS", 0}, {"DRAW", 3}, {"WIN", 6}
};

int main() {
    int totalScore = 0;   // Scored total of all rounds
    char opponentChoice;  // Which move your opponent will make
    char directedChoice;  // Which move you are told to make

    while (std::cin >> opponentChoice >> directedChoice) {
        if (priorityMap[directedChoice].wins == opponentChoice) {
            totalScore += choiceScores[directedChoice] + roundScores["WIN"];
        } else if (priorityMap[directedChoice].loses == opponentChoice) {
            totalScore += choiceScores[directedChoice] + roundScores["LOSS"];
        } else {
            totalScore += choiceScores[directedChoice] + roundScores["DRAW"];
        }
    }

    printf("Final Score: %d\n", totalScore);

    return 0;
}
