#include "bitmap.h"

using namespace std;

Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int xpos, int ypos, bool useTransparency)
{
	
	// Storing the renderer for future configuring and drawing
	m_pRenderer = renderer;

	// Create the bitmap surface and texture
	BitmapData* Data = ResourceManager::instance()->Load(fileName.c_str(),useTransparency,m_pRenderer);
	m_pbitmapSurface = Data->surf;
	m_pbitmapTexture = Data->tex;

	// Coords
	m_x = xpos;
	m_y = ypos;
	// Filename of bitmap
	file = fileName;

}

Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);

	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);

}

void Bitmap::draw()
{
	// Render the bitmap at the x/y coords
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x,m_y,m_pbitmapSurface->w,m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);

	}
}

bool Bitmap::isPointInRect(int x, int y, bool clicked)
{
	SDL_Rect rect;
	rect.x = m_x;
	rect.y = m_y;
	rect.h = m_pbitmapSurface->h;
	rect.w = m_pbitmapSurface->w;

	SDL_Point mousePoint;
	mousePoint.x = x;
	mousePoint.y = y;

	return (SDL_PointInRect(&mousePoint, &rect) && clicked);
}

void Bitmap::setX(int x)
{
	m_x = x;
}

void Bitmap::setY(int y)
{
	m_y = y;
}

SDL_Texture* Bitmap::getTexture()
{
	return  m_pbitmapTexture;
}



int Bitmap::getX()
{
	return m_x;
}

int Bitmap::getY()
{
	return m_y;
}

string Bitmap::getFile()
{
	return file;
}



