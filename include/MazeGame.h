#ifndef MAZEGAME_H
#define MAZEGAME_H

#include "database.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 40;
const int MAZE_ROWS = SCREEN_HEIGHT / CELL_SIZE;
const int MAZE_COLS = SCREEN_WIDTH / CELL_SIZE;
const int BLOCK_WIDTH = 65;
const int BLOCK_HEIGHT = 65;
const int NUM_BLOCKS = 5;
const int MENU_HEIGHT = 400; // Height of the menu bar
const std::vector<int> BLOCK_POINTS={0,10,15,25,35,50};

class Button {
public:
    Button(const std::string& text, int x, int y, int width, int height);

    void render(SDL_Renderer* renderer, TTF_Font* font) const;

    bool isClicked(int mouseX, int mouseY) const;

public:
    std::string text;
    int x, y, width, height;
};

class MazeGame {
public:
    enum class CellType { EMPTY, WALL, START, TARGET, P1, P2, P3, P4, P5, VISITED };
    enum class GameState { HOME,MENU, PLAYING, GAME_OVER, GAME_LOST, GAME_SCORE };

    MazeGame();
    ~MazeGame();

    void run();

private:
    Database database;
    std::string playerName;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    int playerRow, playerCol;
    int points;
    int currentLevel;
    int levelPoints;
    GameState gameState;
    std::vector<std::vector<CellType>> maze;
    std::vector<Button> buttons;
    std::vector<std::pair<int, int>> blockPositions;
    Database highScore;

    void initializeBlocks();
    void initializeMaze();
    void generateMaze(int row, int col);
    void initializePlayer();
    void initializeSDL();
    void initializeButtons();
    void movePlayer(int rowOffset, int colOffset);
    void handleInput();
    void handleButtonClick(const Button& button);
    void update();
    void render();
    void renderButtons();
    void renderPlayText(const std::string& text, int x, int y);
    void renderHomeScreen();
    void renderMenu();
    void renderHighScoreScreen();
    void renderGameOverScreen();
    void renderGameLostScreen();
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    void renderMaze();
    void renderPlayer();
    void renderCustomSizeText(const std::string& text, int x, int y, SDL_Color color,int fontSize);
    void initializeMenu();
};

#endif // MAZEGAME_H
