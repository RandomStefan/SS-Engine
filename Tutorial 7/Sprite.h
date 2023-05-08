#pragma once
#include "Input.h"
#include "bitmap.h"
#include <iostream>
#include <vector>

class Sprite
{
private:

	Input* input;
	Bitmap* bitmap; // Bitmap used to create the sprite
	

public:

	//Constructor

	/// <summary>
	/// Constructor. Creates a bitmap from the asset given in the "path" variable and set's it's position according to the "x" and "y" variables.
	/// Sets if the image will use transparency using the "transparency" boolean variable.
	/// </summary>
	/// <param name="m_gameRenderer"> - Renderer responsible for drawing elements</param>
	/// <param name="path"> - Path to file to be used for the bitmap</param>
	/// <param name="x"> - Position on x axis</param>
	/// <param name="y"> - Position on y axis</param>
	/// <param name="transparent"> - Use transparency ?</param>
	Sprite(SDL_Renderer* m_gameRenderer, string path, int x, int y, bool transparent);

	//------------------Variables------------------

	// Auxiliary coords
	int xCoord; 
	int yCoord;

	//------------------Methods------------------

	/// <summary>
	/// Draws the sprite on screen by calling the draw function of the bitmap.
	/// </summary>
	void draw();

	/// <summary>
	/// Destroys the bitmap and the input members when called.
	/// </summary>
	void destroy();

	/// <summary>
	/// Used for debugging. Not used at the moment.
	/// </summary>
	void updateInput();

	/// <summary>
	/// Sets the value of x and y of the sprite.
	/// </summary>
	/// <param name="x"> - Sets the value of x Axis to "x"</param>
	/// <param name="y"> - Sets the value of y Axis to "y"</param>
	void setPosition(int x, int y);

	/// <summary>
	/// Offset the position by an ammount
	/// </summary>
	/// <param name="x"> - x ammount of offset on the x Axis</param>
	/// <param name="y"> - y ammount of offset on the y Axis</param>
	void offsetPosition(int x, int y);

	/// <summary>
	/// Returns a vector with two values positioned on the [0] and [1] positions inside the vector.
	/// [0] - position on the x axis
	/// [1] - position on the y axis
	/// </summary>
	/// <returns> Returns a vector with two values positioned on the [0] and [1] positions inside the vector.</returns>
	vector<int> getPosition();
	
	/// <summary>
	/// Returns the texture image of a sprite.
	/// </summary>
	/// <returns> - Returns a texture type object that stores the image of the sprite</returns>
	SDL_Texture* getSpriteTexture();

	/// <summary>
	/// Checks to see if the pointer is situated over the sprite by calling the method of the bitmap to check for this.
	/// </summary>
	/// <param name="x"> - x coord of the point</param>
	/// <param name="y"> - y coord of th point</param>
	/// <param name="clicked"> - Is the mouse clicked ?</param>
	/// <returns> - Returns true if the pointer is inside and clicked false if otherwise</returns>
	bool isPointerOver(int x, int y, bool clicked);

	/// <summary>
	/// Gets size of the sprite's texture.
	/// </summary>
	/// <returns> Returns an SDL_Point type object that will store the width and the height of the texture: x holds the widht and y holds the height</returns>
	SDL_Point getsize();

	/// <summary>
	/// Returns path to the image used for the sprite.
	/// </summary>
	/// <returns> - Returns string that holds the path to the image used for the sprite</returns>
	string getPathToTexture();
};

