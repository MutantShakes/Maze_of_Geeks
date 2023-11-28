# Maze_of_Geeks

Welcome to the Maze Game! This is a simple console-based maze game implemented in C++ using the SDL2 library. Navigate through the maze, avoiding penalties, and reach the target to advance to the next level. Be cautious of penalties associated with certain blocks, and try to achieve the highest score possible!

## Installation

To play the Maze Game, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your_username/maze-game.git
   ```

2. **Install SDL2:**
   Ensure that SDL2 is installed on your system. You can follow the [official SDL installation guide](https://wiki.libsdl.org/Installation) for instructions. All the required dependencies are listed in the [Dependencies](#dependencies) section at the end. 

4. **Compile the Code: Run the below command in root directory**
   ```bash
   make
   ```

5. **Run the Game:**
   ```bash
   ./bin/maze_game
   ```

## How to Play

- Use the `W`, `A`, `S`, and `D` keys to navigate through the maze.
- Press the `SPACE` key to start the game in the main menu.
- Press `ESCAPE` to go back or quit when in main menu.
- Press `H` to view the high scores.
- Enjoy the game and aim for the highest score!

## Gameplay

- **Green, Dark Green, Purple, Dark Purple, Red Blocks :** These block carry penalities in increasing order as mentioned in the main menu.
- **Yellow Block (TARGET):** Reach this block to complete the level and advance.
- **Gray Block (VISITED):** Indicates areas visited in the maze and cannot be visited again.
- **Black Block:** Indicates the player position and block to be moved by pressing appropriate keys.

## Menu

- **Enter Your Name:** Type your name and press `ENTER` to start the game.
- **Restart Button:** Click to restart the game.
- **Home Button:** Click to return to the home screen.

## High Scores

Check out the top scores achieved by players! Press `H` in the main menu to view the high scores.

## Notes

- Adjust the maze size, block positions, and other parameters in the code as needed.
- This game uses the SDL2 library, so ensure it is properly installed on your system.

## Dependencies

The Maze Game relies on the SDL2 library for graphics and input handling. Make sure to have the following SDL2 components installed on your system:

- [SDL2](https://libsdl.org/download-2.0.php): Simple DirectMedia Layer is a cross-platform development library designed to provide low-level access to audio, keyboard, mouse, and display.

- [SDL2_ttf](https://libsdl.org/projects/SDL_ttf/): SDL2_ttf is an SDL2 library extension that allows you to use TrueType fonts in your SDL applications.

- [SDL2_gfx](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/): SDL2_gfx is a library containing various drawing primitives such as lines, circles, and polygons for SDL2.

### Installation Guide

Follow the official SDL installation guides for each component to ensure they are correctly installed on your system.

- [SDL Installation Guide](https://wiki.libsdl.org/Installation)
- [SDL_ttf Installation Guide](https://libsdl.org/projects/SDL_ttf/)
- [SDL2_gfx Installation Guide](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/)

Have fun playing the Maze Game! If you encounter any issues or have suggestions, feel free to contribute or reach out.
