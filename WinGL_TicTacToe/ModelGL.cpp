#include "ModelGL.h"
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>



ModelGL::ModelGL() : hoverCellX(-1), hoverCellY(-1), m_leftButtonDown(false), m_rightButtonDown(false), movePlayed(0)
{
	resetGame();
}

ModelGL::~ModelGL()
{
}

void ModelGL::init()
{
	glClearColor(0, 0, 0, 0);                       // background color
}

void ModelGL::centerBoard(int width, int height)
{
	int halfGrid = cellSize + (cellSize >> 1);

	offsX = (width >> 1) - halfGrid;
	offsY = (height >> 1) - halfGrid;
}

void ModelGL::setViewport(int width, int height)
{
	// Set up the OpenGL viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);

	centerBoard(width, height);
}

void ModelGL::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix(); // Save the current transformation matrix

	glTranslatef(offsX, offsY, 0.0f);

	// color hovered cell
	if (hoverCellX >= 0)
	{
		glColor3f(0.1f, 0.1f, 0.1f); // Gray hover color
		glBegin(GL_QUADS);
		glVertex2f(hoverCellX * cellSize, hoverCellY * cellSize);   // Specify the vertex coordinates
		glVertex2f(hoverCellX * cellSize + cellSize, hoverCellY * cellSize);
		glVertex2f(hoverCellX * cellSize + cellSize, hoverCellY * cellSize + cellSize);
		glVertex2f(hoverCellX * cellSize, hoverCellY * cellSize + cellSize);
		glEnd();
	}
	// draw players
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (m_board[x][y] != 0)
			{
				if (m_board[x][y] == 1)
					glColor3f(1.0f, 0.2f, 0.2f);  // Set the drawing color to red
				else
					glColor3f(0.2f, 0.2f, 1.0f);  // Set the drawing color to blue

				glBegin(GL_QUADS);  // Start drawing quadrilaterals
				glVertex2f(x * cellSize,			y * cellSize);   // Specify the vertex coordinates
				glVertex2f(x * cellSize + cellSize, y * cellSize);
				glVertex2f(x * cellSize + cellSize, y * cellSize + cellSize);
				glVertex2f(x * cellSize,			y * cellSize + cellSize);
				glEnd();            // End drawing quadrilaterals
			}
		}
	}

	// Draw TicTacToe grid
	glColor3f(1.0f, 1.0f, 1.0f); // White color for grid
	glBegin(GL_LINES);
	for (int i = 0; i <= 3; i++) // horizontal
	{
		glVertex2f(0, i * cellSize);
		glVertex2f(3 * cellSize, i * cellSize);
	}
	for (int i = 0; i <= 3; i++) // vertical
	{
		glVertex2f(i * cellSize, 0);
		glVertex2f(i * cellSize, 3 * cellSize);
	}
	glEnd();



	glPopMatrix(); // Save the current transformation matrix
	glFlush(); // Ensure everything is drawn
}

void ModelGL::setMousePosition(int x, int y)
{
	m_mX = x;
	m_mY = y;

	int cellX = (x - offsX) / cellSize;
	int cellY = (y - offsY) / cellSize;

	if (cellX >= 0 && cellY >= 0 && cellX < 3 && cellY < 3)
	{
		hoverCellX = cellX;
		hoverCellY = cellY;
	}
	else
	{
		hoverCellX = -1;
		hoverCellY = -1;
	}
}

void ModelGL::resetGame()
{
	// Clear the board
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m_board[i][j] = 0;
		}
	}
	currentPlayer = 1;  // Player 1 starts
	movePlayed = 0;
}

bool ModelGL::makeMove(int x, int y, int player)
{
	if (x >= 0 && m_board[x][y]==0)
	{
		m_board[x][y] = player;
		currentPlayer = (player == 1) ? 2 : 1; // Switch player
		movePlayed++;
		return true;
	}
	return false;
}

int ModelGL::checkWinner()
{
	if (movePlayed >= 9) return 3; // draw
	// row & columns
	for (int i = 0; i < 3; ++i) {
		if (m_board[i][0] != 0 && m_board[i][0] == m_board[i][1] && m_board[i][0] == m_board[i][2])
			return m_board[i][0]; // row winner 
		if (m_board[0][i] != 0 && m_board[0][i] == m_board[1][i] && m_board[0][i] == m_board[2][i])
			return m_board[0][i]; // col winner
	}

	// diag
	if (m_board[0][0] != 0 && m_board[0][0] == m_board[1][1] && m_board[0][0] == m_board[2][2])
		return m_board[0][0]; // diag1 winner
	if (m_board[0][2] != 0 && m_board[0][2] == m_board[1][1] && m_board[0][2] == m_board[2][0])
		return m_board[0][2]; // diag1 winner


	return 0; // Continue
}
