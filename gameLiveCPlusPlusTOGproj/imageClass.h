#pragma once
#include"settings.h"
class imageClass
{
private:
	std::vector<SDL_Surface*>images;

	void createImageVector() {
		this->images.resize(gameSettings::imageVector.size());
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
		images[enumName] = flower;
		return;
	}

public:

	imageClass(){}

	~imageClass()
	{
		this->images.clear();
	}

	SDL_Surface* getImage(unsigned enumName) {
		return this->images[enumName];
	}
	void loadImages() {
		this->createImageVector();
		
		for (int i = 0; i < this->images.size(); i++)
		{
			std::cout << gameSettings::imageVector[i].path << "<< loading\n";
			this->load(gameSettings::imageVector[i].path, gameSettings::imageVector[i].position);
		}
	}

	void logOut() {
		for (int i = 0; i < this->images.size(); i++)
		{
			if (this->images[i] != nullptr)
			{
				std::cout << "picture uploaded:: #" << i << "\n";
			}
		}
	}

	

};

