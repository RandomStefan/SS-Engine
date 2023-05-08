#pragma once

#include<string>
#include "SDL_render.h"
#include "ResourceManager.h"


struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;



class Bitmap
{
private:

	//------------------Variables------------------

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	int m_x, m_y; // auxiliary coords
	string file;

public:

	//------------------Constructor and destructor------------------

	/// <summary>
	/// Constructor. Creates the bitmap's surface and texture.
	/// </summary>
	/// <param name="renderer"> - Renderer that will be responsible for drawing our bitmaps</param>
	/// <param name="fileName"> - Name of file that we will load to use as our bitmap</param>
	/// <param name="xpos"> - x Position in the scene</param>
	/// <param name="ypos"> - y Position in the scene</param>
	/// <param name="useTransparency"> - Boolean that checks if the bitmap is using transparency. Default - false</param>
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);

	/// <summary>
	/// Frees the memory allocated to the bitmap texture and surface.
	/// </summary>
	~Bitmap();

	//------------------Methods------------------

	/// <summary>
	/// Gets texture file of the object that called the function.
	/// </summary>
	/// <returns> - Returns an SDL_Texture type pointer of the object's texture</returns>
	SDL_Texture* getTexture();

	/// <summary>
	/// Returns the image's path used for the bitmap.
	/// </summary>
	/// <returns></returns>
	string getFile();

	/// <summary>
	/// Set's the x axis value of the bitmap.
	/// </summary>
	/// <param name="x"> - x axis value</param>
	void setX(int x);

	/// <summary>
	/// Set's the y axis value of the bitmap.
	/// </summary>
	/// <param name="y"> - y axis value</param>
	void setY(int y);

	/// <summary>
	/// Returns the x axis position of the bitmap.
	/// </summary>
	/// <returns> - Returns the x axis of the bitmap</returns>
	int getX();

	/// <summary>
	/// Returns the y axis position of the bitmap.
	/// </summary>
	/// <returns> - Returns the y axis of the bitmap</returns>
	int getY();

	/// <summary>
	/// Renders the bitmap at x,y coords of the bitmap object.
	/// </summary>
	void draw();

	/// <summary>
	/// Checks to see if the pointer is situated inside the bitmap's texture.
	/// </summary>
	/// <param name="x"> - x coord of the point</param>
	/// <param name="y"> - y coord of th point</param>
	/// <param name="clicked"> - Is the mouse clicked ?</param>
	/// <returns> - Returns true if the pointer is inside and clicked false if otherwise</returns>
	bool isPointInRect(int x, int y, bool clicked);
};