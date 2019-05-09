#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Globals.h"

using sf::Texture;
using std::vector;

class Toolbar
{
public:
	Toolbar(unsigned numOfButtons);	// c-tor
	~Toolbar();						// d-tor

	// Sets the texture of the buttons.
	void setBtnTextures(const vector<Texture> &textures); // textures - Vector of loaded textures.

	// Draws the toolbar on a window.
	void draw(sf::RenderWindow & window);	// window - The window to draw on.

	// Highlights the button in the given position.
	void highlightButton(const Vector2f & pos);	// pos - The position of the button to highlight.

	// Unhighlights the last button that was highlighted.
	void unhighlightButton();

	// Sets a selected button in the given position.
	void setSelection(const Vector2f & pos		// pos - The position of the button.
						, Object_t & button);	// button - Variable to return the selected button.

	// Returns the button that is currently selected.
	Object_t getSelectedBtn() const;

private:
	// Sets the toolbar (vector of buttons) with size and position.
	void initializeToolbar();

	vector<Button> m_buttons;	// Vector to hold buttons.
	unsigned m_numOfButtons;	// Number of buttons existing.
	Object_t m_currSelection;	// The currently selected button.
	Object_t m_prevSelection;	// The previous selected button.
	bool m_isHighlighted;		// True if any button is highlighted.
	unsigned m_highlightedBtn;	// The highlighted button number.
};

