#pragma once
// Enum for each object by his char representation.
enum Char_t 
{
	C_EMPTY = ' ', C_ROBOT = '/', C_WALL = '#', C_GUARD = '!', C_DOOR = 'D', C_ROCK = '@'
};

// Enum for each object in the project. 
enum Object_t
{
	O_DELETE, O_ROBOT, O_GUARD, O_WALL, O_ROCK, O_DOOR, O_CLEAN, O_SAVE, O_TILE
};

const unsigned TILE_SIZE = 35;	// The tile's size (in pixels).