#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <map>

class Database {
private:
    const std::string fileName = "./Database/high_scores.txt"; // Change the filename as needed

public:
    Database();

    ~Database();
    std::map<std::string, int> highScores;

    void addHighScore(const std::string& playerName, int score);

    void displayHighScores() const;

    int getScore(const std::string& playerName) const;

    void saveHighScores() const;
private:

    void loadHighScores();
};

#endif // DATABASE_H
