#include "MazeGame.h"
#include "database.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <algorithm>

// Implement the Button class methods

Button::Button(const std::string& text, int x, int y, int width, int height)
    : text(text), x(x), y(y), width(width), height(height) {}

void Button::render(SDL_Renderer* renderer, TTF_Font* font) const {
    SDL_Color textColor = {48, 0, 48, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {x + (width - textSurface->w) / 2, y + (height - textSurface->h) / 2,
                             textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    SDL_SetRenderDrawColor(renderer, 48, 0, 48, 255);
    SDL_Rect buttonRect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &buttonRect);
}

bool Button::isClicked(int mouseX, int mouseY) const {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

// Implement the MazeGame class methods

MazeGame::MazeGame() {
    initializeMenu();
    initializeMaze();
    initializeSDL();
    initializePlayer();
    initializeButtons();
    initializeBlocks();
    // gameState = GameState::HOME;
}

MazeGame::~MazeGame() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    database.~Database();
}

void MazeGame::run() {
    while (true) {
        handleInput();
        update();
        render();
        SDL_Delay(16);
    }
    
}

void MazeGame::initializeBlocks() {
    for (int i = 0; i < NUM_BLOCKS; ++i) {
        blockPositions.push_back({SCREEN_WIDTH / 2 - BLOCK_WIDTH / 2, i * BLOCK_HEIGHT});
    }
}




void MazeGame::initializeMaze() {
    maze.resize(MAZE_ROWS, std::vector<CellType>(MAZE_COLS, CellType::EMPTY));

    srand(static_cast<unsigned>(time(nullptr)));
    generateMaze(0, 0);

    playerRow = 0;
    playerCol = 0;

    maze[MAZE_ROWS - 1][MAZE_COLS - 1] = CellType::TARGET;

    std::map<std::pair<int,int>,int> mp;

    for(int j=1;j<=5;j++){
        for (int i = 0; i < currentLevel+30; ++i) {
            int pointRow, pointCol;
            do {
                pointRow = rand() % MAZE_ROWS;
                pointCol = rand() % MAZE_COLS;
            } while (maze[pointRow][pointCol] != CellType::EMPTY && mp.find(std::make_pair(pointRow,pointCol))==mp.end());

            mp[std::make_pair(pointRow,pointCol)]++;
            if(j==1) maze[pointRow][pointCol] = CellType::P1;
            if(j==2) maze[pointRow][pointCol] = CellType::P2;
            if(j==3) maze[pointRow][pointCol] = CellType::P3;
            if(j==4) maze[pointRow][pointCol] = CellType::P4;
            if(j==5) maze[pointRow][pointCol] = CellType::P5;
        }
    }
}

void MazeGame::generateMaze(int row, int col) {
    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            maze[i][j] = CellType::EMPTY;
        }
    }
    maze[MAZE_ROWS - 1][MAZE_COLS - 1] = CellType::TARGET;
}

void MazeGame::initializePlayer() {
    currentLevel = 1;
    levelPoints=10;
    points = 300;

}

void MazeGame::initializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init() failed: " << TTF_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    font = TTF_OpenFont("./fonts/OpenSans-ExtraBoldItalic.ttf", 24);
    if (!font) {
        std::cerr << "TTF_OpenFont() failed: " << TTF_GetError() << std::endl;
    }

    

}

void MazeGame::initializeButtons() {
    buttons.emplace_back("Restart", 55, 8, 100, 30);
    buttons.emplace_back("Home", 210, 8, 100, 30);
}

void MazeGame::movePlayer(int rowOffset, int colOffset) {
    int newRow = playerRow + rowOffset;
    int newCol = playerCol + colOffset;

    if (newRow >= 0 && newRow < MAZE_ROWS && newCol >= 0 && newCol < MAZE_COLS &&
        maze[newRow][newCol] != CellType::WALL && maze[newRow][newCol]!=CellType::VISITED) {
        playerRow = newRow;
        playerCol = newCol;

        switch(maze[playerRow][playerCol]){
            case CellType::P1:
                points-=BLOCK_POINTS[1];
                break;
            case CellType::P2:
                points-=BLOCK_POINTS[2];
                break;
            case CellType::P3:
                points-=BLOCK_POINTS[3];
                break;
            case CellType::P4:
                points-=BLOCK_POINTS[4];
                break;
            case CellType::P5:
                points-=BLOCK_POINTS[5];
                break;
        }

        if(maze[playerRow][playerCol]!=CellType::TARGET) maze[playerRow][playerCol]=CellType::VISITED;

        if(maze[playerRow][playerCol] == CellType::TARGET){
            if (points >= 0) {
                // levelPoints+=15;
                std::cout << "Level " << currentLevel << " completed!" << std::endl;
                currentLevel++;
                if(currentLevel > 8) gameState = GameState::GAME_OVER;
                else{
                    initializeMaze();
                    playerCol=0;
                    playerRow=0;
                    points+=levelPoints;
                }
            }
            else{
                std::cout<< "Not Enough Points! You Lose"<<std::endl;
                gameState = GameState::GAME_LOST;
            }
        }
        else{
            int l=std::max(0,playerCol-1);
            int r=std::min(MAZE_COLS-1,playerCol+1);
            int u=std::max(0,playerRow-1);
            int d=std::min(MAZE_ROWS-1,playerRow+1);

            std::vector<int> rows={u,d,playerRow};
            std::vector<int> cols={l,r,playerCol};

            bool flag=true;
            for(auto i:rows){
                for(auto j:cols){
                    if(maze[i][j]!=CellType::VISITED) {
                        flag=false;
                        break;
                    }
                }
                if(!flag) break;
            }

            if(flag || points < 0) gameState = GameState::GAME_LOST;
        }
    }
}


void MazeGame::initializeMenu() {
        gameState = GameState::MENU;
        playerName = "";
}

void MazeGame::renderMenu() {

    renderCustomSizeText("MAZE OF GEEKS", SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 8, {130, 0, 130},60);
    renderText("Enter Your Name:", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 3 - 15, {255, 255, 255});
    renderText(playerName.c_str(), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 3 + 20, {255, 255, 255});
     
}



void MazeGame::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            std::cout << "Quitting the game." << std::endl;
            exit(0);
        } else if (e.type == SDL_KEYDOWN) {
            if(gameState == GameState::MENU){
                 if (e.key.keysym.sym == SDLK_RETURN && !playerName.empty()) {
                gameState = GameState::HOME;
            } else if (e.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty()) {
                playerName.pop_back();
            } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "Quitting the game." << std::endl;
                exit(0);
            }
            }
            else{

            switch (e.key.keysym.sym) {
                case SDLK_w:
                    movePlayer(-1, 0);
                    break;
                case SDLK_s:
                    movePlayer(1, 0);
                    break;
                case SDLK_a:
                    movePlayer(0, -1);
                    break;
                case SDLK_d:
                    movePlayer(0, 1);
                    break;
                case SDLK_SPACE:
                    if (gameState != GameState::PLAYING) {
                        initializePlayer();
                        initializeMaze();
                        gameState = GameState::PLAYING;
                    }
                    break;
                case SDLK_ESCAPE:
                    if(gameState != GameState::HOME){
                        gameState = GameState::HOME;
                    }
                    else{
                        std::cout << "Quitting the game." << std::endl;
                        exit(0);
                    }
                    break;
                case SDLK_h:
                    if(gameState != GameState::PLAYING){
                        gameState = GameState::GAME_SCORE;
                    }
                    break;
            }
            }
        }else if (e.type == SDL_TEXTINPUT && gameState==GameState::MENU) {
            playerName += e.text.text;
        } 
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            for (const auto& button : buttons) {
                if (button.isClicked(mouseX, mouseY)) {
                    handleButtonClick(button);
                    break;
                }
            }
        }
    }
}

void MazeGame::handleButtonClick(const Button& button) {
    if (button.text == "Restart") {
        initializeMaze();
        initializePlayer();
    } else if (button.text == "Home") {
        gameState = GameState::HOME;
    }
}

void MazeGame::update() {
    if (gameState == GameState::PLAYING) {
        // Additional game logic can be added here
    }
}

void MazeGame::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (gameState == GameState::HOME) {
        renderHomeScreen();
    } else if (gameState == GameState::PLAYING) {
        renderMaze();
        renderPlayer();
        renderPlayText("Level: " + std::to_string(currentLevel) + " Points: " + std::to_string(points),
               (SCREEN_WIDTH + 200) / 2, 8);
        renderButtons();
    } else if (gameState == GameState::GAME_OVER) {
        renderGameOverScreen();
    } else if(gameState == GameState::GAME_LOST){
        renderGameLostScreen();
    } else if(gameState == GameState::GAME_SCORE){
        renderHighScoreScreen();
    } else if(gameState == GameState::MENU){
        renderMenu();
    }

    SDL_RenderPresent(renderer);
}

void MazeGame::renderButtons(){
    for (const auto& button : buttons) {
        button.render(renderer, font);
    }
}

void MazeGame::renderPlayText(const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 87, 51, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void MazeGame::renderHomeScreen() {
    // Render HOME screen content here
      
        // For simplicity, let's render a message
        renderText("Press SPACE to start", (SCREEN_WIDTH + 50) / 3, (SCREEN_HEIGHT+200) / 2,{255, 255, 255} );
        renderText("Press H for High Scores: ", (SCREEN_WIDTH + 50) / 3, (SCREEN_HEIGHT+300) / 2,{255, 255, 0} );


        // Render blocks
        // std::vector<SDL_Color> block_color (NUM_BLOCKS);
        std::vector<std::vector<Uint8>> block_color(NUM_BLOCKS,std::vector<Uint8>(4));

        block_color[0]={0, 255, 0,255};
        block_color[1]={0, 128, 0,255};
        block_color[2]={128, 0, 128,255};
        block_color[3]={64, 0, 64,255};
        block_color[4]={255, 0, 0,255};
        for (int i = 0; i < NUM_BLOCKS; ++i) {
            SDL_Rect blockRect = {blockPositions[i].first -100, blockPositions[i].second+ ((i+1)*5), BLOCK_WIDTH, BLOCK_HEIGHT};
            SDL_SetRenderDrawColor(renderer, block_color[i][0],block_color[i][1],block_color[i][2],block_color[i][3]);
            SDL_RenderFillRect(renderer, &blockRect);

            // Render points
            std::string st="Points Penalty: ";
            st.append(std::to_string(BLOCK_POINTS[i+1]));
            renderText(st, blockPositions[i].first + BLOCK_WIDTH / 2, blockPositions[i].second+((i+1)*5) + BLOCK_HEIGHT / 3, {255,255,255});
        }

}

void MazeGame::renderHighScoreScreen() {
        std::vector<std::pair<int,std::string>> sc_pair;
        for(const auto& entry: database.highScores){
            sc_pair.push_back(std::make_pair(entry.second,entry.first));
        }
        std::sort(sc_pair.begin(),sc_pair.end());
        std::reverse(sc_pair.begin(),sc_pair.end());
       int j=1;
       for (auto entry: sc_pair) {
        std::string score = std::to_string(j);
        score.append(". ");
        score.append(entry.second);
        score.append("  --  ");
        score.append(std::to_string(entry.first));

        renderText(score, (SCREEN_WIDTH + 50) / 3, (SCREEN_HEIGHT-200+(j*100)) / 3,{255, 255, 255} );
        j++;
        if(j > 7) break;
    }
}

void MazeGame::renderGameOverScreen() {
        std::string pl_score=playerName;
        
        database.addHighScore(pl_score,points);
        // Render game over screen content here
      
        std::string st="Your Score: ";
        st.append(std::to_string(points));
        renderText(st,(SCREEN_WIDTH + 400) / 4, (SCREEN_HEIGHT) / 3, {255, 0, 0});
        renderText("Game Over. Press SPACE to restart", SCREEN_WIDTH / 4, (SCREEN_HEIGHT+100) / 3, {255, 255, 255});
        // renderText("Press H for High Scores: ", (SCREEN_WIDTH + 50) / 3, (SCREEN_HEIGHT+300) / 3,{255, 255, 0} );
}

void MazeGame::renderGameLostScreen(){
    // Render game over screen content here
        // For simplicity, let's render a message
        renderText("Game Lost !! . Press SPACE to restart", SCREEN_WIDTH / 4, (SCREEN_HEIGHT+100) / 3, {255, 255, 255});
}

void MazeGame::renderCustomSizeText(const std::string& text, int x, int y, SDL_Color color, int fontSize){
    // Load a font with the specified size
    TTF_Font* font_cus = TTF_OpenFont("./fonts/OpenSans-ExtraBoldItalic.ttf", fontSize); // Replace "your_font_file.ttf" with your font file

    if (!font_cus) {
        // Handle font loading error
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = color;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font_cus, text.c_str(), textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int textWidth, textHeight;
    SDL_QueryTexture(message, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect textRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, message, NULL, &textRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    TTF_CloseFont(font_cus); // Close the font after use
}

void MazeGame::renderText(const std::string& text, int x, int y, SDL_Color color) {
     // For simplicity, let's render text in white
        SDL_Color textColor = color;
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), textColor);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        int textWidth, textHeight;
        SDL_QueryTexture(message, NULL, NULL, &textWidth, &textHeight);

        SDL_Rect textRect = {x, y, textWidth, textHeight};
        SDL_RenderCopy(renderer, message, NULL, &textRect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
}

void MazeGame::renderMaze() {
    // Render maze
        for (int i = 0; i < MAZE_ROWS; ++i) {
            for (int j = 0; j < MAZE_COLS; ++j) {
                 // Draw black border
            SDL_Rect borderRect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &borderRect);

                // Fill inner part based on cell type
            SDL_Rect cellRect = {j * CELL_SIZE + 1, i * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2};
                switch (maze[i][j]) {
                    case CellType::EMPTY:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        break;
                    case CellType::WALL:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        break;
                    case CellType::START:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case CellType::TARGET:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
                        break;
                    case CellType::P1:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
                        break;
                    case CellType::P2:
                        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Dark Green
                        break;
                    case CellType::P3:
                        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // Purple
                        break;
                    case CellType::P4:
                        SDL_SetRenderDrawColor(renderer, 64, 0, 64, 255); // Dark Purple
                        break;
                    case CellType::P5:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
                        break;
                    case CellType::VISITED:
                        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); //silver
                        break;
                }
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
}

void MazeGame::renderPlayer() {
        // Render player
        SDL_Rect playerRect = {playerCol * CELL_SIZE + 1, playerRow * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &playerRect);
}
