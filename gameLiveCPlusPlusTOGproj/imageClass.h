#pragma once
#include"settings.h"
class imageClass
{
protected:

	std::vector<SDL_Surface*> imageVector;


private:
	void createImageVector(int size) {
		imageVector.resize(size);
	}

	void load(std::string path, unsigned enumName) {

		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return;
		}
		//flower = SDL_ConvertSurface(flower, gameSettings::surface->format, NULL);
		/*if (flower == nullptr) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			return;
		}*/
		imageVector[enumName] = flower;
		return;
	}

public:

	imageClass(){}

	~imageClass()
	{
		imageVector.clear();
	}

	SDL_Surface* getImage(unsigned enumName) {
		return imageVector[enumName];
	}

	void loadImages(std::vector<imagePath>vPaths) {

		this->createImageVector(vPaths.size());
		
		for (int i = 0; i < this->imageVector.size(); i++)
		{
			std::cout << vPaths[i].path << "<< loading #" << i << "\n";
			this->load(vPaths[i].path, vPaths[i].position);
		}
	}

	SDL_Surface* loadOneImg(std::string path) {
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return nullptr;
		}
		return flower;
	}


	void logOut() {
		for (int i = 0; i < imageVector.size(); i++)
		{
			if (imageVector[i] != nullptr)
			{
				std::cout << "picture uploaded:: #" << i << "\n";
			}
		}
	}

};

