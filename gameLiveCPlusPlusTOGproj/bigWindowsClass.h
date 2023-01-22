#pragma once

#include"settings.h" 
///for future developing this progect

class bigWindowsClass
{
protected:
	short pading = 20; // px
	short btnTextPading = 5; //px

	SDL_Rect objRect = { 0,0,0,0 };
	TTF_Font* font = nullptr;
	SDL_Surface* img = nullptr;

public:

	bigWindowsClass() {}

	bigWindowsClass(SDL_Surface* img,  TTF_Font* font, SDL_Rect objRect={0,0,0}) {
		this->img = img;
		this->objRect = objRect;
		this->font = font;
	}

	~bigWindowsClass()
	{
		SDL_FreeSurface(img);
	}

	void blitBg() {
		std::cout << this->objRect.x << " " << this->objRect.w << "\n";
		if (this->img == nullptr)
		{
			std::cout << "bigWindowsClass::error-image is empty\n";
			return;
		}
		SDL_BlitScaled(this->img, NULL, gameSettings::surface, &this->objRect );
	}
	void blitBg(SDL_Surface* img, SDL_Rect objRect) {
		std::cout << this->objRect.x << " " << this->objRect.w << "\n";
		SDL_BlitScaled(img, NULL, gameSettings::surface, &objRect );
	}


	void blitWithTxt(const char* text, SDL_Color color = {0,0,0}) {
		if (this->img == nullptr)
		{
			std::cout << "bigWindowsClass::error-image is empty\n";
			return;
		}
		SDL_BlitScaled(this->img, NULL, gameSettings::surface, &this->objRect);

		SDL_Rect tempRect = { this->objRect.x + this->pading, this->objRect.y + this->pading,
			this->objRect.w - 2 * pading, this->objRect.h - 2 * pading };

		SDL_Surface* tempSurf = TTF_RenderText_Blended_Wrapped(this->font, text, color, tempRect.w);
		SDL_BlitSurface(tempSurf, NULL, gameSettings::surface, &tempRect);
		SDL_UpdateWindowSurface(gameSettings::win);
		SDL_FreeSurface(tempSurf);
	}

	void blitWithTxt(SDL_Surface* img, const char* text, SDL_Rect objRect, SDL_Color color = { 0,0,0 }) {
		SDL_BlitScaled(this->img, NULL, gameSettings::surface, &objRect);

		SDL_Rect tempRect = { objRect.x + this->pading, objRect.y + this->pading,
			objRect.w - 2 * pading, objRect.h - 2 * pading };
		if (this->font == nullptr)
		{
			std::cout << "error\n";
		}
		SDL_Surface* tempSurf = TTF_RenderText_Blended_Wrapped(this->font, text, color, tempRect.w);
		SDL_BlitSurface(tempSurf, NULL, gameSettings::surface, &tempRect);
		SDL_UpdateWindowSurface(gameSettings::win);
		SDL_FreeSurface(tempSurf);
	}

	SDL_Rect getRect() { return this->objRect; }

	void blitWithTextCenter(SDL_Surface* img, const char* text, SDL_Rect objRect, SDL_Color color = { 0,0,0 }){
		SDL_BlitScaled(img, NULL, gameSettings::surface, &objRect);

		SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, text, color);
		/*SDL_Rect tempRect = { objRect.x + objRect.w/2 - (objRect.w - this->btnTextPading*2)/2,
			objRect.y + objRect.h/2 - (objRect.h - this->btnTextPading * 2) / 2,
			objRect.w - 2 * this->btnTextPading, objRect.h - 2 * this->btnTextPading };*/
		SDL_Rect tempRect = { objRect.x + (objRect.w - tempSurf->w) / 2,objRect.y + (objRect.h - tempSurf->h) / 2,0,0 };
		if (this->font == nullptr)
		{
			std::cout << "error\n";
		}
		SDL_BlitSurface(tempSurf, NULL, gameSettings::surface, &tempRect);
		SDL_UpdateWindowSurface(gameSettings::win);
		SDL_FreeSurface(tempSurf);
	}
};

