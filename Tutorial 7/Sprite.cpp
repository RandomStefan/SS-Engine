#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* m_gameRenderer, string path, int x, int y, bool transparent)
{
	bitmap = new Bitmap(m_gameRenderer, path, x, y, transparent);
	xCoord = bitmap->getX();
	yCoord = bitmap->getY();
	input = new Input();
}

void Sprite::destroy()
{
	if (bitmap)
	{
		delete bitmap;
		bitmap = nullptr;
	}

	if (input)
	{
		delete input;
		input = nullptr;
	}
		
}

void Sprite::setPosition(int x, int y)
{
	xCoord = x;
	yCoord = y;

	bitmap->setX(xCoord);
	bitmap->setY(yCoord);
}

void Sprite::offsetPosition(int x, int y)
{
	xCoord += x;
	yCoord += y;

	bitmap->setX(xCoord);
	bitmap->setY(yCoord);
}

SDL_Point Sprite::getsize()
{
	SDL_Texture* texture = bitmap->getTexture();
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

vector<int> Sprite::getPosition()
{
	vector<int> returnValues;
	returnValues[0] = xCoord;
	returnValues[1] = yCoord;
	return returnValues;
}

SDL_Texture* Sprite::getSpriteTexture()
{
		return bitmap->getTexture();
}

bool Sprite::isPointerOver(int x, int y, bool clicked)
{
	return bitmap->isPointInRect(x, y, clicked);
}

string Sprite::getPathToTexture()
{
	return bitmap->getFile();
}

void Sprite::updateInput()
{
	if(input->KeyIsPressed(KEY_W))
		cout << "w";
}

void Sprite::draw()
{
	bitmap->draw();
}

