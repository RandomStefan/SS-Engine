#include "ResourceManager.h"

using namespace std;


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto value : ResourceManager_TextureMap)
	{
		delete value.second;
		value.second = nullptr;
	}

	delete instance();
	//instance() = nullptr;

}

void ResourceManager::Unload(const std::string fileName)
{

}

BitmapData* ResourceManager::Load(const std::string fileName, bool useTransparancy, SDL_Renderer* PRenderer)
{

	BitmapData* ReturnData =NULL;
	auto searchresult = ResourceManager_TextureMap.find(fileName);



	if (searchresult != ResourceManager_TextureMap.end())
	{
		ReturnData = ResourceManager_TextureMap[fileName];
	}
	else // not found, load, save and return
	{
		SDL_Texture* m_pbitmapTexture = nullptr;
		//if file does not exist in map
		SDL_Surface* pTempSurface = SDL_LoadBMP(fileName.c_str());
		if (!pTempSurface)
		{
			printf("SURFACE for bitmap '%s' not loaded\n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
		else
		{
			if (useTransparancy)
			{
				Uint32 colourKey = SDL_MapRGB(pTempSurface->format, 255, 0, 255);
				SDL_SetColorKey(pTempSurface, SDL_TRUE, colourKey);
			}
			m_pbitmapTexture = SDL_CreateTextureFromSurface(PRenderer, pTempSurface);
			if (!m_pbitmapTexture)
			{
				printf("TEXTURE for bitmap '%s' not loaded!\n", fileName.c_str());
				printf("%s\n", SDL_GetError());
			}

			ReturnData = new BitmapData();
			ReturnData->tex = m_pbitmapTexture;
			ReturnData->surf = pTempSurface;
			ResourceManager_TextureMap[fileName] = ReturnData;
		}
	}
	return ReturnData;

}
