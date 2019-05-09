#pragma once
#include <vector>
#include "Container.h"
#include <fstream>
#include <SFML/Graphics.hpp>

using std::vector;
using std::fstream;
using sf::Vector2f;
using sf::Texture;

// A struct to hold indexes of a matrix.
struct MatrixIndex
{
	unsigned x;	// Row index.
	unsigned y;	// Column index.
};

class Board
{
public:
	Board();	// c-tor
	~Board();	// d-tor

	// Loads a board from a file.
	bool loadBoard(fstream & file,						// file - The file to read from.
					const vector<Texture> &textures);	// textures - The textures that will be set for the objects.

	// Gets an input for the board dimensions, and creates a new board based on it.
	void createNewBoard();

	// Sets the textures of the tiles background.
	void setTilesTexture(const Texture &texture);	// texture - The texture that will be set for the tiles background.

	// Returns the number of rows existing in the board.
	unsigned getRows() const;
	
	// Returns the number of columns existing in the board.
	unsigned getCols() const;

	// Draws the board on a window.
	void draw(sf::RenderWindow & window);	// window - The window to draw on.

	// Highlights the tile in the given position.
	void highlightTile(const Vector2f & pos);	// pos - The position of the tile to highlight.

	// Unhighlights the last tile that was highlighted.
	void unhighlightTile();

	// Sets an object on a tile in the given position.
	void setObject(const Vector2f & pos,				// pos - The position of the tile.
					const Object_t & obj,				// obj - The object to put on the tile.
					const vector<Texture> &textures);	// textures - The textures that will be set for the objects.

	// Saves the board into a file.
	void saveBoard(fstream & file);	// file - The file to save into.
	
	// Clears the board.
	void clearBoard();

private:
	// Sets the board (matrix of containers) with size and position.
	void initializeBoard();

	// Members:
	vector<vector<Container>> m_board;	// The board - matrix of containers
	int m_rows;							// Board's number of rows
	int m_cols;							// Board's number of columns
	bool m_isTileHighlighted;			// True if any tile is highlighted.
	MatrixIndex m_highlightedTile;		// The highlighted tile indexes in the matrix.
	bool m_isRobotPlaced;				// True if any robot is placed on the board already.
	MatrixIndex m_robotTilePos;			// The robot tile indexes in the matrix.
	bool m_isDoorPlaced;				// True if any door is placed on the board already.
	MatrixIndex m_doorTilePos;			// The door tile indexes in the matrix.
};

