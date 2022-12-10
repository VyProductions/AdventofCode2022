#include <iostream>
#include <string>
#include <unordered_map>

struct wl {
    char wins;
    char loses;
};

// Maps a choice to the two moves it (1) wins against and (2) loses against

std::unordered_map<char, wl> priorityMap = {
    {'A', {'C', 'B'}}, {'B', {'A', 'C'}}, {'C', {'B', 'A'}}
};

// Maps a choice to how many points that choice yields

std::unordered_map<char, int> choiceScores = {
    {'A', 1}, {'B', 2}, {'C', 3}
};

// Maps a round result to how many points are gained for that result

std::unordered_map<std::string, int> roundScores = {
    {"LOSS", 0}, {"DRAW", 3}, {"WIN", 6}
};

int main() {
    int totalScore = 0;    // Scored total of all rounds
    char opponentChoice;   // Which move your opponent will make
    char directedOutcome;  // Which outcome you are told you should create

    while (std::cin >> opponentChoice >> directedOutcome) {
        // Told to lose
        if (directedOutcome == 'X') {
            // Determine what move you should make based on the outcome
            char shouldChoose = priorityMap[opponentChoice].wins;

            totalScore += choiceScores[shouldChoose] + roundScores["LOSS"];
        // Told to draw
        } else if (directedOutcome == 'Y') {
            totalScore += choiceScores[opponentChoice] + roundScores["DRAW"];
        // Told to win
        } else if (directedOutcome == 'Z') {
            // Determine what move you should make based on the outcome
            char shouldChoose = priorityMap[opponentChoice].loses;

            totalScore += choiceScores[shouldChoose] + roundScores["WIN"];
        }
    }

    printf("Final Score: %d\n", totalScore);

    return 0;
}
