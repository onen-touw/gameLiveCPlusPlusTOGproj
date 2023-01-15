#pragma once

#include"baseGameClass.h"
#include "fieldClass.h"
#include"imageClass.h"

class settlmentActionsClass
{
private:
	baseGameClass baseGame;
	imageClass images;
	fieldClass field;




	bool game = true;
	bool firstHouse = false;
	bool goodForHouse = false;

	int cursor_X = 0, cursor_Y = 0;

public:

	settlmentActionsClass()
	{
		images.loadImages();
		images.logOut();

		field.createFieldV();
		field.generationObjects();


		std::cout << "ready\n";
		///bliting
		field.blitField();
		SDL_UpdateWindowSurface(gameSettings::win);
	}
	~settlmentActionsClass()
	{

	}


	int start() {

		if (baseGame.initModuls())
		{
			SDL_Event event;


			///test setHouse by Coords + test setPerson BY coords
			/*field.setHouse({ 15,15 }, "");
			field.setPersonCoors(5, 5, "t");
			field.setPersonCoors(7, 7, "t");*/


			while (this->game)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
					{
						this->game = false;
					}

					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
						this->field.transmitField(directions::right);
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
					{
						this->field.transmitField(directions::up);
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
					{
						this->field.transmitField(directions::left);
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
					{
						this->field.transmitField(directions::down);
					}

					if (!firstHouse)
					{
						if (event.type == SDL_MOUSEMOTION)
						{
							this->field.blitField();
							cursor_X = event.motion.x; cursor_Y = event.motion.y;
							if (cursor_Y > gameSettings::winObjSize.menuHeader)
							{
								this->goodForHouse = field.chosePositionForHouse({ (short int)cursor_X, (short int)cursor_Y });
								SDL_UpdateWindowSurface(gameSettings::win);
							}
						}
						if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP && goodForHouse)
						{
							field.setHouse({ (short)cursor_X,(short)cursor_Y }, "px");
							field.blitField();
							SDL_UpdateWindowSurface(gameSettings::win);

							firstHouse = true;

							std::cout << "ok\n";
						}


					}

					SDL_Delay(1000 / 60);
				}
			}
		}

		else
		{
			std::cout << "problemm\n";
		}


		return 0;
	}
};

