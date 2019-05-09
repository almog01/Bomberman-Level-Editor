#include "Board.h"
#include "Globals.h"
#include <iostream>

using std::cout;
using std::cin;

const unsigned MAX_BOARD_SIZE = 60;

Board::Board() : m_isRobotPlaced(false), m_isDoorPlaced(false), m_isTileHighlighted(false)
{
}

Board::~Board()
{
}

bool Board::loadBoard(fstream & file, const vector<Texture> &textures)
{
	file.seekg(0, std::ios::beg);	// put the reading cursor at the beggining of the file
	file >> m_rows >> m_cols;
	if (file.eof())	// if the existing file was empty
		return false;

	initializeBoard();
	file.get();		// workaround to throw away '\n'
	Char_t c;
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			c = (Char_t)file.get();
			switch (c)
			{
			case C_ROBOT:
				if (!m_isRobotPlaced)	// if a robot was read from the file, save his position.
				{
					m_isRobotPlaced = true;
					m_robotTilePos.x = i;
					m_robotTilePos.y = j;
					m_board[i][j].setObject(O_ROBOT, textures[O_ROBOT]);
				}
				break;
			case C_WALL:
				m_board[i][j].setObject(O_WALL, textures[O_WALL]);
				break;
			case C_GUARD:
				m_board[i][j].setObject(O_GUARD, textures[O_GUARD]);
				break;
			case C_DOOR:
				if (!m_isDoorPlaced)	// if a door was read from the file, save his position.
				{
					m_isDoorPlaced = true;
					m_doorTilePos.x = i;
					m_doorTilePos.y = j;
					m_board[i][j].setObject(O_DOOR, textures[O_DOOR]);
				}
				break;
			case C_ROCK:
				m_board[i][j].setObject(O_ROCK, textures[O_ROCK]);
				break;
			default:
				break;
			}
		}
		file.get();		// to throw away '\n'
	}

	return true;
}

void Board::createNewBoard()
{
	cout << "Please enter board dimenstions (between 1 and 60)\n";
	cin >> m_rows >> m_cols;
	while (m_rows <= 0 || m_rows > MAX_BOARD_SIZE || m_cols <= 0 || m_cols > MAX_BOARD_SIZE)
	{
		cout << "Invalid board dimensions\n";
		cout << "Please enter new dimenstions (between 1 and 60)\n";
		cin >> m_rows >> m_cols;
	}
	initializeBoard();
}

void Board::setTilesTexture(const Texture &texture)
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j].setTexture(texture);
		}
	}
}

unsigned Board::getRows() const 
{
	return m_rows;
}

unsigned Board::getCols() const 
{
	return m_cols;
}

void Board::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j].draw(window);
		}
	}
}

void Board::highlightTile(const Vector2f & pos)
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
		{
			if (m_board[i][j].contains(pos))
			{
				if (!m_isTileHighlighted)	// if there isn't any tile highlighted yet
				{
					m_isTileHighlighted = true;
					m_board[i][j].highlight();
					m_highlightedTile.x = i;
					m_highlightedTile.y = j;
					return;
				}
				else if (i != m_highlightedTile.x || j != m_highlightedTile.y)	// if the tile isn't already highlighted
				{
					m_board[i][j].highlight();
					m_board[m_highlightedTile.x][m_highlightedTile.y].unhighlight();
					m_highlightedTile.x = i;
					m_highlightedTile.y = j;
					return;
				}
			}
		}
}

void Board::unhighlightTile()
{
	if (m_isTileHighlighted)
		m_board[m_highlightedTile.x][m_highlightedTile.y].unhighlight();

	m_isTileHighlighted = false;
}

void Board::setObject(const Vector2f & pos, const Object_t & obj, const vector<Texture> &textures)
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
		{
			if (m_board[i][j].contains(pos))
			{
				if (obj == O_ROBOT)
				{
					if (!m_isRobotPlaced)	// if there is not any robot on the board yet
					{
						m_isRobotPlaced = true;
						m_robotTilePos.x = i;
						m_robotTilePos.y = j;
						m_board[i][j].setObject(obj, textures[obj]);
					}
					else	// if a robot was placed already we transfer his position
					{
						m_board[m_robotTilePos.x][m_robotTilePos.y].deleteObject();	// delete old robot
						m_robotTilePos.x = i;
						m_robotTilePos.y = j;
						m_board[i][j].setObject(obj, textures[obj]);				// and put it on the new tile
					}
				}
				else if (obj == O_DOOR)
				{
					if (!m_isDoorPlaced)	// if there is not any door on the board
					{
						m_isDoorPlaced = true;
						m_doorTilePos.x = i;
						m_doorTilePos.y = j;
						m_board[i][j].setObject(obj, textures[obj]);
					}
					else	// if a door was placed already we transfer its position
					{
						m_board[m_doorTilePos.x][m_doorTilePos.y].deleteObject();	// delete old door
						m_doorTilePos.x = i;
						m_doorTilePos.y = j;
						m_board[i][j].setObject(obj, textures[obj]);				// and put it on the new tile
					}
				}
				else
				{
					if (i == m_robotTilePos.x && j == m_robotTilePos.y)	// if the new object was placed on the robot
					{
						m_board[i][j].setObject(obj, textures[obj]);
						m_isRobotPlaced = false;
					}
					else if (i == m_doorTilePos.x && j == m_doorTilePos.y)	// if the new object was placed on the door
					{
						m_board[i][j].setObject(obj, textures[obj]);
						m_isDoorPlaced = false;
					}
					else
						m_board[i][j].setObject(obj, textures[obj]);
				}
				break;
			}
		}
}

void Board::saveBoard(fstream & file)
{
	file.seekp(0, std::ios::beg);	// put the reading cursor at the beggining of the file
	file << m_rows << " " << m_cols << "\n";

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			file << (char)m_board[i][j].getObject();
		}
		file << "\n";
	}
	file.flush();
	cout << "Board saved!\n";
	system("pause");	// pause the program to let the user know the file was saved
}

void Board::clearBoard()
{
	m_board.clear();
	m_rows = m_cols = 0;
	m_isRobotPlaced = false;
	m_isDoorPlaced = false;
	unhighlightTile();
}

void Board::initializeBoard()
{
	m_board.resize(m_rows);
	for (size_t i = 0; i < m_board.size(); i++)
	{
		m_board[i].resize(m_cols);
	}

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			// the position of each tile will be in the middle of it (TILE_SIZE / 2), where its origin is located.
			// in addition, the first TILE_SIZE in the Y-axis is saved for the toolbar (hence the 1.5*TILE_SIZE).
			m_board[i][j].setPos(Vector2f((float)(j*TILE_SIZE + (TILE_SIZE / 2)), (float)(i*TILE_SIZE + (1.5*TILE_SIZE))));
		}
	}
}