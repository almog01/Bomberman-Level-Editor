#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Board.h"
#include "Toolbar.h"

using std::fstream;
using sf::Texture;
using sf::RenderWindow;

class Manager
{
public:
	Manager();	// c-tor
	~Manager();	// d-tor
	
	// Runs the application.
	void run();

private:
	// Loads the needed textures for the application (from Icons folder inside the project).
	void loadTextures();

	// Opens a file for read and write. Returns false if the file doesn't exist.
	bool openFile();

	// Creates a new file for write.
	void createNewFile();

	// Creates the window, with size based on the board size.
	void createWindow();

	// Draws the toolbar and the board on the window, and than displays it.
	void draw();

	// Handles the events: window's closed, left mouse button pressed and mouse moved.
	void HandleEvents();

	RenderWindow m_window;		// Window instance.
	fstream m_file;				// File instance for read and write.
	vector<Texture> m_textures;	// Vector to save the loaded textures.
	Toolbar m_toolbar;			// Toolbar instance.
	Board m_board;				// Board instance.
};

