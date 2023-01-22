#pragma once

#include"settings.h"		

class fontClass
{
private:
	TTF_Font* font = nullptr;
public:

	fontClass() {

		this->font = TTF_OpenFont("./font/courier.ttf", 20);
		if (this->font == nullptr)
		{
			std::cout << "ttf load font error\n";
		}
		std::cout << "ttf load font\n";
	}

	TTF_Font* getFont() { return this->font; }

	~fontClass()
	{
		TTF_CloseFont(font);
	}
};

