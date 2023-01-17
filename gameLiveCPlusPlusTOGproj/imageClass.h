#pragma once
#include"settings.h"
class imageClass
{
private:




	void createImageVector() {
		gameSettings::imageVector.resize(gameSettings::imagePathVector.size());
	}

	void load(std::string path, unsigned enumName) {

		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return;
		}
		//flower = SDL_ConvertSurface(flower, gameSettings::surface->format, NULL);
		if (flower == nullptr) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			return;
		}
		gameSettings::imageVector[enumName] = flower;
		return;
	}

public:

	imageClass(){}

	~imageClass()
	{
		gameSettings::imageVector.clear();
	}

	SDL_Surface* getImage(unsigned enumName) {
		return gameSettings::imageVector[enumName];
	}

	void loadImages() {
		this->createImageVector();
		
		for (int i = 0; i < gameSettings::imageVector.size(); i++)
		{
			std::cout << gameSettings::imagePathVector[i].path << "<< loading #" << i << "\n";
			this->load(gameSettings::imagePathVector[i].path, gameSettings::imagePathVector[i].position);
		}
	}

	void logOut() {
		for (int i = 0; i < gameSettings::imageVector.size(); i++)
		{
			if (gameSettings::imageVector[i] != nullptr)
			{
				std::cout << "picture uploaded:: #" << i << "\n";
			}
		}
	}

};

