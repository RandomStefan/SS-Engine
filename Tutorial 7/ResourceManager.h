#pragma once
#include <map>
#include <SDL.h>
#include <string>

using namespace std;


struct BitmapData
{
	SDL_Texture* tex;
	SDL_Surface* surf;
};


class ResourceManager
{
public:
	static ResourceManager* instance()
	{
		static  ResourceManager* instance;

		if (!instance)
			instance = new ResourceManager();

		return instance;
	}
	map<string, BitmapData*> ResourceManager_TextureMap;
	ResourceManager();
	~ResourceManager();

	BitmapData* Load(const std::string fileName, bool useTransparancy, SDL_Renderer* PRenderer); // Loads a bitmap
	void Unload(const std::string fileName); // Unloads a bitmap

};

