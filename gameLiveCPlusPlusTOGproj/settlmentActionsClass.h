#pragma once

#include"baseGameClass.h"
#include "fieldClass.h"
#include"imageClass.h"
#include"houseAreaClass.h"

class settlmentActionsClass
{
private:
	baseGameClass baseGame;
	imageClass images;
	fieldClass field;
	std::vector<houseAreaClass> houseAreas;


	bool game = true;
	bool firstHouse = false;
	bool goodForHouse = false;
	bool night = false;

	int cursor_X = 0, cursor_Y = 0;
	short int gSecond = 0;
	short int gLoop = 0;
	short int wood = 0;
	short int stone = 0;
	short int food = 0;
	short int peopleCount = 0;

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

	void oneDayActions()
	{
		// ���� � ����������� �������� ��������� � ������� ����������� ���
		for (int i = 0; i < this->houseAreas.size(); i++) 
		{
			this->wood += this->houseAreas[i].getWood();
			this->houseAreas[i].claimWood();
			this->stone += this->houseAreas[i].getStone();
			this->houseAreas[i].claimStone();
			short int freeFood = this->houseAreas[i].getFreeFood();
			if ( freeFood >= 0)
			{
				this->food += freeFood;
				this->houseAreas[i].claimFood(freeFood);
			}
			else
			{
				if (this->food > abs(freeFood))
				{
					this->houseAreas[i].sendFood(abs(freeFood));
					this->food -= abs(freeFood);
				}
				else
				{
					this->houseAreas[i].sendFood(this->food);
					this->food = 0;
				}
			}
		}
		// ���������� ����� ��� �������� ��������� �� ���� ����
		for (int i = 0; i < this->houseAreas.size(); i++)
		{
			std::vector<humanClass*> humans = this->houseAreas[i].getHumans();
			std::vector<builderClass> builders;
			farmerClass farmer = *((farmerClass*)humans[0]);
			humans.erase(humans.begin());
			for (int j = 0; j < humans.size(); j++)
			{
				builders.push_back(*((builderClass*)humans[i]));
			}
			for (int j = 1; j < this->houseAreas[i].getHumans().size(); j++)
			{
				if (this->food >= ((this->peopleCount + 1) * gameSettings::humanSetting.deilyRation) * 3 + gameSettings::settlmentSetting.foodForBirth)
				{
					if (this->stone >= gameSettings::settlmentSetting.stoneForBildingHouse)
					{
						if (this->wood >= gameSettings::settlmentSetting.woodForBildingHouse)
						{
							//������� ������
							/*this->houseAreas[i].createBuilderQueue(taskType::buildingHouse, j);
							this->food -= gameSettings::settlmentSetting.foodForBirth;
							this->wood -= gameSettings::settlmentSetting.woodForBildingHouse;
							this->stone -= gameSettings::settlmentSetting.stoneForBildingHouse;*/
							//�������� ������
							std::cout << "we can build house" << std::endl;
							this->houseAreas[i].createBuilderQueue(taskType::getSomething, j);
						}
						else
						{
							this->houseAreas[i].createBuilderQueue(taskType::getWood, j);
						}
					}
					else
					{
						this->houseAreas[i].createBuilderQueue(taskType::getStone, j);
					}
				}
				else if (this->houseAreas[i].getFarmsCount() < 4)
				{
					if (this->wood >= gameSettings::settlmentSetting.woodForBildingFarm)
					{
						//������� ������
						/*this->houseAreas[i].createBuilderQueue(taskType::buildingFarm, j);
						this->wood -= gameSettings::settlmentSetting.woodForBildingFarm;*/
						//�������� ������
						std::cout << "we can build farm" << std::endl;
						this->houseAreas[i].createBuilderQueue(taskType::getSomething, j);
					}
					else
					{
						this->houseAreas[i].createBuilderQueue(taskType::getWood, j);
					}
				}
				else
				{
					this->houseAreas[i].createBuilderQueue(taskType::getSomething, j);
				}
			}
		}
	}

	void oneTikActions()
	{
		for (int i = 0; i < this->houseAreas.size(); i++)
		{
			for (int j = 0; j < this->houseAreas[i].getHumans().size(); j++)
			{
				this->houseAreas[i].getHumans()[j]->humanTransmit();
				position pos = this->houseAreas[i].getHumans()[j]->getPosition();
			}
		}
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
					if (event.type == SDL_QUIT)//������������ �������� ���� ����� ������ "�����"
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
					else
					{
						if (++gSecond == gameSettings::settlmentSetting.secondsInOneLoop)
						{
							if (++gLoop == gameSettings::settlmentSetting.loopsInOneDay)
							{
								//���������� � ������ ���

								gLoop = 0;
							}
							else
							{
								//������� ���� ������� ����

							}
							gSecond = 0;
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

