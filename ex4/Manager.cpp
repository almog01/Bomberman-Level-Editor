#include "Manager.h"
#include "Globals.h"

using sf::Event;
using sf::Vector2f;

const char APP_NAME[] = "Stage Editor";
const char FILE_NAME[] = "board.bomb.txt";
const unsigned NUM_OF_BUTTONS = 8;

Manager::Manager()
	: m_toolbar(NUM_OF_BUTTONS)
{
	loadTextures();
	m_toolbar.setBtnTextures(m_textures);

	if (!openFile())	// if file doesn't exist
	{
		createNewFile();
		m_board.createNewBoard();
	}
	else if (!m_board.loadBoard(m_file, m_textures))	// if reading the existing file failed
	{
		createNewFile();
		m_board.createNewBoard();
	}

	m_board.setTilesTexture(m_textures[O_TILE]);
	createWindow();
}

Manager::~Manager()
{
	if (m_file.is_open())
		m_file.close();
}

void Manager::loadTextures()
{
	m_textures.resize(NUM_OF_BUTTONS + 1);	// Texture for each button, +1 for the tile texture
	m_textures[O_DELETE].loadFromFile("Icons/delete.png");
	m_textures[O_ROBOT].loadFromFile("Icons/robot.png");
	m_textures[O_GUARD].loadFromFile("Icons/guard.png");
	m_textures[O_WALL].loadFromFile("Icons/wall.png");
	m_textures[O_ROCK].loadFromFile("Icons/rock.png");
	m_textures[O_DOOR].loadFromFile("Icons/door.png");
	m_textures[O_CLEAN].loadFromFile("Icons/clean.png");
	m_textures[O_SAVE].loadFromFile("Icons/save.png");
	m_textures[O_TILE].loadFromFile("Icons/tile.png");
}

void Manager::run()
{
	while (m_window.isOpen())
	{
		draw();
		HandleEvents();
	}
}

bool Manager::openFile()
{
	m_file.open(FILE_NAME, fstream::out | fstream::in);
	if (!m_file.is_open())	// if file doesn't exist
		return false;
	return true;
}

void Manager::createNewFile()
{
	if (m_file.is_open())
		m_file.close();
	m_file.open(FILE_NAME, fstream::out);
}

void Manager::createWindow()
{
	if (m_board.getCols() < NUM_OF_BUTTONS)	// Workaround so that all buttons will be displayed
		m_window.create(sf::VideoMode(TILE_SIZE * NUM_OF_BUTTONS, TILE_SIZE + TILE_SIZE * m_board.getRows()), APP_NAME);
	else
		m_window.create(sf::VideoMode(TILE_SIZE * m_board.getCols(), TILE_SIZE + TILE_SIZE * m_board.getRows()), APP_NAME);
}

void Manager::draw()
{
	m_window.clear();
	m_toolbar.draw(m_window);
	m_board.draw(m_window);
	m_window.display();
}

void Manager::HandleEvents()
{
	Event event;
	if (m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				// Save the position of the mouse click:
				const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				if (event.mouseButton.y >= 0 && event.mouseButton.y < TILE_SIZE)	// Toolbar area
				{
					Object_t button;	// variable to save the button that was pressed
					m_toolbar.setSelection(mousePos, button);

					if (button == O_CLEAN)
					{
						m_window.close();
						m_board.clearBoard();
						createNewFile();
						m_board.createNewBoard();
						m_board.setTilesTexture(m_textures[O_TILE]);
						createWindow();
					}
					else if (button == O_SAVE)
					{
						m_board.saveBoard(m_file);
					}
				}
				else	// Board area
				{
					m_board.setObject(mousePos, m_toolbar.getSelectedBtn(), m_textures);
				}
			}
			break;
		case Event::MouseMoved:
			// Save the position of the mouse:
			const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			if (event.mouseMove.y >= 0 && event.mouseMove.y < TILE_SIZE)	// Toolbar area
			{
				m_board.unhighlightTile();
				m_toolbar.highlightButton(mousePos);
			}
			else															// Board area
			{
				m_toolbar.unhighlightButton();
				m_board.highlightTile(mousePos);
			}
			break;
		}
	}
}
