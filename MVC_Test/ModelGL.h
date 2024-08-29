#pragma once
class ModelGL
{
private:
    bool m_leftButtonDown;
    bool m_rightButtonDown;
    int m_mX;
    int m_mY;    

    int m_board[3][3];   // 3x3 TicTacToe board (0: empty, 1: player1, 2: player2)
    
public:
    int cellSize = 100;
    int offsX = 400;
    int offsY = 400;

    int hoverCellX;
    int hoverCellY;

    int currentPlayer; // 1 for player 1, 2 for player 2
    int movePlayed;
public:
    ModelGL();
    ~ModelGL();

    void init();
    void setViewport(int width, int height);
    void centerBoard(int width, int height);
    void draw();

    void setMouseLeft(bool flag) { m_leftButtonDown = flag; };
    void setMouseRight(bool flag) { m_rightButtonDown = flag; };
    void setMousePosition(int x, int y);

    // Game funcions
    void resetGame();
    bool makeMove(int x, int y, int player);  // Returns true if move is valid
    int checkWinner(); // 0: no winner, 1: player 1 wins, 2: player 2 wins, 3: draw
};

