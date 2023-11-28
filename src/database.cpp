#include "database.h"

Database::Database() {
    loadHighScores(); // Load high scores from file when the object is created
}

Database::~Database() {
    saveHighScores(); // Save high scores to file when the object is destroyed
}

void Database::addHighScore(const std::string& playerName, int score) {
    if(highScores[playerName] < score) highScores[playerName] = score;
    saveHighScores(); // Save high scores after adding a new score
}

void Database::displayHighScores() const {
    std::cout << "High Scores:\n";
    for (const auto& entry : highScores) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}

int Database::getScore(const std::string& playerName) const {
    auto it = highScores.find(playerName);
    if (it != highScores.end()) {
        return it->second;
    } else {
        std::cout << "Player not found.\n";
        return -1; 
    }
}

void Database::saveHighScores() const {
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto& entry : highScores) {
            outFile << entry.first << " " << entry.second << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << fileName << std::endl;
    }
}

void Database::loadHighScores() {
    std::ifstream inFile(fileName);
    if (inFile.is_open()) {
        std::string playerName;
        int score;
        while (inFile >> playerName >> score) {
            highScores[playerName] = score;
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading: " << fileName << std::endl;
    }
}
