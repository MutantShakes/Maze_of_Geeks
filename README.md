# Maze_of_Geeks

Welcome to the Maze Game! This is a simple console-based maze game implemented in C++ using the SDL2 library. Navigate through the maze, avoiding penalties, and reach the target to advance to the next level. Be cautious of penalties associated with certain blocks, and try to achieve the highest score possible!

## Installation

To play the Maze Game, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/MutantShakes/Maze_of_Geeks.git
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

1. **Points and Penalties:** Each level features green, purple, and red blocks. These blocks carry penalties, and your task is to avoid them to prevent point deductions. The penalty for each block type is as follows:
   - Green Block (P1): 10 points
   - Dark Green Block (P2): 15 points
   - Purple Block (P3): 25 points
   - Dark Purple Block (P4): 35 points
   - Red Block (P5): 50 points

2. **Points System:** Your initial set of points is 400. Throughout the game, points are deducted based on the encountered blocks. Avoid penalties to preserve your score.

3. **Level Advancement:** Successfully completing a level adds a bonus of 10 points to your score. Keep advancing through the levels to accumulate points.

4. **Game Over Conditions:**
   - Points Below 0: If, at any point, your points go below 0, you lose the game.
   - Level 8 Completion: Upon completing the eighth level, your final score is calculated, including bonus points. The game concludes, and your remaining points determine your overall performance.

5. **Bonus Points:** You receive a bonus of 10 points each time you successfully complete a level. Strategically clear each maze to maximize your score.

6. **Challenge:** The difficulty increases with each level. Navigate the mazes wisely to overcome obstacles, avoid penalties, and secure a high score.

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

### Links
- [Video Demo Link](https://youtu.be/nCwCKKjyVCs)
- [SDL Documentation](https://www.libsdl.org/release/SDL-1.2.15/docs/html/reference.html)

Have fun playing the Maze Game! If you encounter any issues or have suggestions, feel free to contribute or reach out.
