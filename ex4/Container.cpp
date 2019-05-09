#include "Container.h"

const float PADDING = 8.0f;

Container::Container() : m_isObjectAdded(false)
{
}

Container::~Container()
{
}

void Container::draw(RenderWindow & window)
{
	Tile::draw(window);

	if (m_isObjectAdded)
	{
		window.draw(m_objectSprite);
	}
}

void Container::setPos(const Vector2f & pos)
{
	Tile::setPos(pos);
	m_objectSprite.setPosition(pos);	// Make the object we're holding the same position as the tile itself
}

void Container::setObject(const Object_t & obj, const Texture & texture)
{
	if (obj == O_DELETE)
	{
		deleteObject();
	}
	else
	{
		if (m_object != obj)	// if the new object isn't the same as the old object
		{
			// Reset the sprite to it's default values:
			m_objectSprite.setOrigin({ 0,0 });
			m_objectSprite.setScale({ 1,1 });
			
			// Assign the new texture:
			m_objectSprite.setTexture(texture);
			// Set the TextureRect based on the new assigned texture:
			m_objectSprite.setTextureRect(sf::IntRect(0, 0, m_objectSprite.getTexture()->getSize().x, m_objectSprite.getTexture()->getSize().y));
			// Scale the new sprite
			m_objectSprite.setOrigin(m_objectSprite.getGlobalBounds().width / 2, m_objectSprite.getGlobalBounds().height / 2);
			m_objectSprite.setScale((TILE_SIZE - PADDING) / m_objectSprite.getGlobalBounds().width, (TILE_SIZE - PADDING) / m_objectSprite.getGlobalBounds().height);
			m_object = obj;
			m_isObjectAdded = true;
		}
	}
}

void Container::deleteObject()
{
	m_isObjectAdded = false;
	m_object = O_DELETE;
}

Char_t Container::getObject() const
{
	if (m_isObjectAdded)
	{
		switch (m_object)
		{
		case O_ROBOT:
			return C_ROBOT;
		case O_GUARD:
			return C_GUARD;
		case O_WALL:
			return C_WALL;
		case O_ROCK:
			return C_ROCK;
		case O_DOOR:
			return C_DOOR;
		default:
			break;
		}
	}
	return C_EMPTY;
}
