# Tic-Tac-Toe Game with OpenGL in C++

This is a simple Tic-Tac-Toe game implemented in C++ using OpenGL. The game is built using the Model-View-Controller (MVC) architecture.

## Features

- Graphical rendering with OpenGL.
- Basic Tic-Tac-Toe game logic.

### MVC Architecture

- **Model**: (`ModelGL`) Handles the game state, including the board, player turns, and win conditions.
- **View**: (`ViewGL`) Manages the rendering of the game using OpenGL (RC and DC manipulations)
- **Controller**: (`ControllerGL`) Manages user input and updates the model accordingly.

## Future Plans

This project is part of my Master's thesis and will be developed further with the following enhancements:

- **AI Opponent**: 
  - Implement a basic AI using the **Minimax algorithm** with alpha-beta pruning.
  - Develop a more advanced AI opponent based on **Monte Carlo Tree Search (MCTS)**.
- **Hashing and Game State Optimization**:
  - Use **Zobrist Hashing** to efficiently handle game states and improve AI performance.
- **Improved UI/UX**:
  - Enhance the graphical user interface and provide additional features for a better user experience.
