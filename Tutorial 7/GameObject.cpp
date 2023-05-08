#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* m_game, Type objType, string objName)
{
	game = m_game;
	type = objType;
	name = objName;
	layer = -1;
}

void GameObject::destroy()
{
	if (type == SPRITE)
		m_Sprite->destroy();
	if (type == TEXT)
	{
		TTF_CloseFont(defaultFont);
	}
}

void GameObject::render()
{

	switch (type) 
	{
	case SPRITE: m_Sprite->draw(); break;
	case TRIGGER: cout << "Trigger created at (x,y): "<<objCoords.x<<" "<< objCoords.y << endl; break;
	case TEXT: break;
	default: cout << "Unrecognized game object type !" << endl; break;

	}

}

void GameObject::updateInput()
{
	m_Sprite->updateInput();
}

int GameObject::checkName(vector<GameObject*> objects)
{
	int number = 0;
	for (GameObject* object : objects)
		if (this->name == object->name)
			number++;
	return number;
}

string GameObject::getPathToTexture()
{
	return m_Sprite->getPathToTexture();
}

void GameObject::initSprite(string path, int x, int y, bool transparent, int layer)
{
	if (type == SPRITE)
	{
		this->layer = layer;
		this->m_Sprite = new Sprite(this->game, path, x, y, transparent);
		this->objCoords.x = x;
		this->objCoords.y = y;
	}
		
	else
		cout << "Object is not a sprite/n";
	
}

void GameObject::initTrigger(int x, int y)
{
	if (type == TRIGGER)
	{
		this->objCoords.x = x;
		this->objCoords.y = y;
	}
}

void GameObject::initText(const char* path)
{
	TTF_Init();
	fontPath = path;
}

void GameObject::UpdateText(string msg, int x, int y, int fontSize, SDL_Color colour)
{
	{
		TTF_Font* font;
		font = TTF_OpenFont(fontPath, fontSize);
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;

		int texW = 0;
		int texH = 0;


		surface = TTF_RenderText_Solid(font, msg.c_str(), colour);

		if (!surface)
		{
			//surface not loaded? output the error
			printf("SURFACE for font not loaded !\n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(game, surface);
			if (!texture)
			{
				printf("SURFACE for font not loaded ! \n");
				printf("%s\n", SDL_GetError());
			}
			else
			{
				SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
				SDL_Rect textRect = { x, y, texW, texH };

				SDL_RenderCopy(game, texture, NULL, &textRect);
			}
		}

		if (texture)
			SDL_DestroyTexture(texture);
		if (surface)
			SDL_FreeSurface(surface);
	}
}

void GameObject::handleInput(Input* m_input)
{
	if (type == SPRITE)
	{
		this->input = m_input;
		if (input->KeyIsPressed(KEY_W))
			this->offsetPosition(0, -10);
		if (input->KeyIsPressed(KEY_S))
			this->offsetPosition(0, 10);
		if (input->KeyIsPressed(KEY_A))
			this->offsetPosition(-10, 0);
		if (input->KeyIsPressed(KEY_D))
			this->offsetPosition(10, 0);
	}
	else
		cout << "Only sprites can handle input.\n";
}

void GameObject::offsetPosition(int x, int y)
{
	this->objCoords.x = m_Sprite->xCoord;
	this->objCoords.y = m_Sprite->yCoord;
	m_Sprite->offsetPosition(x, y);
	
	
}

void GameObject::autoMoveYAxis(bool dir)
{
		bool changeDir = 0;

		if (type == SPRITE)
		{
			if (dir == 0)
			{
				this->objCoords.y = this->objCoords.y + 10;
				this->setCoords(this->objCoords.x, this->objCoords.y);
			}
			else
			{
				this->objCoords.y = this->objCoords.y - 10;
				this->setCoords(this->objCoords.x, this->objCoords.y);
			}

		}
		else
			cout << "Behaviour only allowed by SPRITE type game objects\n";

}

void GameObject::setCoords(int x, int y)
{
	this->objCoords.x = m_Sprite->xCoord;
	this->objCoords.y = m_Sprite->yCoord;
	m_Sprite->setPosition(x, y);
}

bool GameObject::checkCollision(GameObject* object)
{
	SDL_Point thisObj; // variable that holds the width and height of the current object's sprite texture
	SDL_Point otherObj; // variable that holds the width and height of the compared object's sprite texture

	// if the object type is trigger then the width and height of the object are set to 0 as they dont have a sprite

	if ((this->type == SPRITE) && (object->type == SPRITE))
	{
		thisObj = this->m_Sprite->getsize();
		otherObj = object->m_Sprite->getsize(); 
	}
	else if ((this->type == TRIGGER) && (object->type == SPRITE))
	{
		thisObj.x = 0;
		thisObj.y = 0;
		otherObj = object->m_Sprite->getsize();
	}
	else if ((this->type == SPRITE) && (object->type == TRIGGER))
	{
		thisObj = this->m_Sprite->getsize();
		otherObj.x = 0;
		otherObj.y = 0;
	}
	else if ((this->type == TRIGGER) && (object->type == TRIGGER))
	{
		thisObj.x = 0;
		thisObj.y = 0;

		otherObj.x = 0;
		otherObj.y = 0;
	}
	else
	{
		cout << "Collision can only happen between sprites and triggers\n";
		return false;
	}


	if (this->layer <= object->layer)
	{
		if (((this->objCoords.x + thisObj.x >= object->objCoords.x) && (this->objCoords.x + thisObj.x <= object->objCoords.x + otherObj.x)) ||
			((this->objCoords.x <= object->objCoords.x + otherObj.x) && (this->objCoords.x >= object->objCoords.x + otherObj.x)))
		{
			if (((this->objCoords.y + thisObj.y >= object->objCoords.y) && (this->objCoords.y + thisObj.y <= object->objCoords.y + otherObj.y)) ||
				((this->objCoords.y <= object->objCoords.y + otherObj.y) && (this->objCoords.y >= object->objCoords.y)))

			{
				cout << "\n" << this->name;
				printf(" Colliding with ");
				cout << object->name << "\n";
				return true;
			}
		}

	}

	return false;
}
	
void GameObject::addObject(std::vector<GameObject*>& Objects)
{
	Objects.push_back(this);
}

void GameObject::removeObject(std::vector<GameObject*>& Objects)
{
	for (int i = 0; i < Objects.size(); i++)
		if (Objects[i]->name == this->name)
			Objects.erase(Objects.begin()+i);

}

