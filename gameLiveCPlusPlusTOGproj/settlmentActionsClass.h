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
		// сбор и объединение ресурсов собранных в течении предыдущего дня
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
		std::cout << "food: " << food << std::endl;
		std::cout << "wood: " << wood << std::endl;
		std::cout << "stone: " << stone << std::endl;
		// постановка задач для развития поселения на этот день

		for (int i = 0; i < this->houseAreas.size(); i++)
		{
			this->houseAreas[i].setFarmerQueue();
			if (houseAreas[i].getHumans().size() < 3 && this->food >= ((this->peopleCount + 1) * gameSettings::humanSetting.deilyRation) * 3 + gameSettings::settlmentSetting.foodForBirth)
			{
				houseAreas[i].spawnBuilder();
				food -= gameSettings::settlmentSetting.foodForBirth;
			}
			for (int j = 1; j < this->houseAreas[i].getHumans().size(); j++)
			{
				if (this->food >= ((this->peopleCount + 1) * gameSettings::humanSetting.deilyRation) * 3 + gameSettings::settlmentSetting.foodForBirth)
				{
					if (this->stone >= gameSettings::settlmentSetting.stoneForBildingHouse)
					{
						if (this->wood >= gameSettings::settlmentSetting.woodForBildingHouse)
						{
							//главная версия
							if (this->houseAreas[i].createBuilderQueue(taskType::buildingHouse, j))
							{
								this->food -= gameSettings::settlmentSetting.foodForBirth;
								this->wood -= gameSettings::settlmentSetting.woodForBildingHouse;
								this->stone -= gameSettings::settlmentSetting.stoneForBildingHouse;
							}
							//тестовая версия
							/*std::cout << "we can build house" << std::endl;
							this->houseAreas[i].createBuilderQueue(taskType::getSomething, j);*/
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
						//главная версия
						/*this->houseAreas[i].createBuilderQueue(taskType::buildingFarm, j);
						this->wood -= gameSettings::settlmentSetting.woodForBildingFarm;*/
						//тестовая версия
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
				position posBefor = this->houseAreas[i].getHumans()[j]->getPosition();
				this->field.setPersonCoors(posBefor, "r");
				short int taskType = this->houseAreas[i].getHumans()[j]->humanTransmit();
				if (taskType != 0)
				{
					if (taskType == taskType::getWood || taskType == taskType::getStone || taskType == taskType::getFood)
					{
						this->field.removeObject(posBefor);
					}
					else if (taskType == taskType::buildingHouse)
					{
						this->field.setHouse(posBefor, "");
						bool houseAreaHouses[4] = { false, false, false, false };
						if (posBefor.j - 20 >= 0)
						{
							if (field.getFieldV()[posBefor.i][posBefor.j - 20].objectType == gameSettings::fieldSetting.objectEnum::house)
							{
								houseAreaHouses[0] = true;
							}
						}
						else
						{
							houseAreaHouses[0] = true;
						}
						if (posBefor.i - 20 >= 0)
						{
							if (field.getFieldV()[posBefor.i-20][posBefor.j].objectType == gameSettings::fieldSetting.objectEnum::house)
							{
								houseAreaHouses[1] = true;
							}
						}
						else
						{
							houseAreaHouses[1] = true;
						}
						if (posBefor.j + 20 < 100)
						{
							if (field.getFieldV()[posBefor.i][posBefor.j + 20].objectType == gameSettings::fieldSetting.objectEnum::house)
							{
								houseAreaHouses[2] = true;
							}
						}
						else
						{
							houseAreaHouses[2] = true;
						}
						if (posBefor.i + 20 < 100)
						{
							if (field.getFieldV()[posBefor.i+20][posBefor.j].objectType == gameSettings::fieldSetting.objectEnum::house)
							{
								houseAreaHouses[3] = true;
							}
						}
						else
						{
							houseAreaHouses[3] = true;
						}
						houseAreas.push_back(houseAreaClass(posBefor, this->field.getFieldV(), this->field.getAreasPointsPosition(posBefor), houseAreaHouses[0], houseAreaHouses[1], houseAreaHouses[2], houseAreaHouses[3]));
					}
					else if (taskType == taskType::buildingFarm)
					{

					}
					/*field.setPersonCoors(posAfter, "t");*/
				}
				else
				{
					position posAfter = this->houseAreas[i].getHumans()[j]->getPosition();
					field.setPersonCoors(posAfter, "t");
				}
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
				while (SDL_PollEvent(&event) || this->game)
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
							position pos = field.findCellByCoord({ (short)cursor_X,(short)cursor_Y });
							houseAreaClass houseArea = houseAreaClass(pos, field.getFieldV(), field.getAreasPointsPosition(pos), false, false, false, false);
							this->houseAreas.push_back(houseArea);
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
								//обновления в начале дня
								oneDayActions();
								//std::cout << gLoop << std::endl;
								gLoop = 0;
							}
							else
							{
								//игровой цикл каждого тика
								oneTikActions();
								//std::cout << gSecond << std::endl;
								field.blitField();
								SDL_UpdateWindowSurface(gameSettings::win);
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

