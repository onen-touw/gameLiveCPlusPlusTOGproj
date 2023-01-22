#pragma once

#include"baseGameClass.h"
#include "fieldClass.h"
#include"houseAreaClass.h"
#include"headerClass.h"

class settlmentActionsClass
{
private:
	baseGameClass baseGame;
	imageClass images;
	fieldClass field;
	headerClass header;

	std::vector<houseAreaClass> houseAreas;

	bool game = true;
	bool firstHouse = false;
	bool goodForHouse = false;
	bool pause = false;

	int cursor_X = 0, cursor_Y = 0;
	short int gSecond = 0;
	short int gLoop = 0;
	short int wood = 0;
	short int stone = 0;
	short int food = gameSettings::settlmentSetting.settlmentStartFood;
	short int peopleCount = 0;

	short timeRation = 0;
	short itInOneLoop= 0;
public:

	settlmentActionsClass()
	{
		field.createFieldV();
		field.generationObjects();

		this->timeRation = gameSettings::settlmentSetting.startTimeRation;
		this->itInOneLoop = gameSettings::settlmentSetting.secondsInOneLoop;
		std::cout << "ready\n";
	}
	~settlmentActionsClass()
	{
		gameSettings::gameImagesPathVector.clear();
		gameSettings::headerImagesPathVector.clear();
	}

	void restart()
	{
		this->houseAreas.clear();
		//fieldClass newField;
		//this->field = newField;
		this->field.clearField();
		
		game = true;
		firstHouse = false;
		goodForHouse = false;
		pause = false;

		cursor_X = 0, cursor_Y = 0;
		gSecond = 0;
		gLoop = 0;
		wood = 0;
		stone = 0;
		food = gameSettings::settlmentSetting.settlmentStartFood;
		peopleCount = 0;

		field.createFieldV();
		field.generationObjects();

		field.blitField();
		header.blitHeader();

		field.blitField();

		SDL_UpdateWindowSurface(gameSettings::win);
	}

	void oneDayActions()
	{
		// ñáîð è îáúåäèíåíèå ðåñóðñîâ ñîáðàííûõ â òå÷åíèè ïðåäûäóùåãî äíÿ
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
					std::vector<humanClass*> humansInThisArea = houseAreas[i].getHumans();
					if (this->food == 0)
					{
						peopleCount -= humansInThisArea.size();
						humansInThisArea.clear();
					}
					else if (this->food == 1)
					{
						while (humansInThisArea.size() > 1)
						{
							humansInThisArea.pop_back();
							peopleCount--;
						}
						humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina / 2);
					}
					else if (this->food == 2)
					{
						while (humansInThisArea.size() > 1)
						{
							humansInThisArea.pop_back();
							peopleCount--;
						}
						humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
					}
					else if (this->food == 3)
					{
						while (humansInThisArea.size() > 2)
						{
							humansInThisArea.pop_back();
							peopleCount--;
						}
						humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
						humansInThisArea[1]->setStamina(gameSettings::humanSetting.stamina / 2);
					}
					else if (this->food == 4)
					{
						if (humansInThisArea.size() == 2)
						{
							humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
							humansInThisArea[1]->setStamina(gameSettings::humanSetting.stamina);
						}
						else
						{
							humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
							humansInThisArea[1]->setStamina(gameSettings::humanSetting.stamina / 2);
							humansInThisArea[2]->setStamina(gameSettings::humanSetting.stamina / 2);
						}
					}
					else if (this->food == 5)
					{
						humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
						humansInThisArea[1]->setStamina(gameSettings::humanSetting.stamina);
						humansInThisArea[2]->setStamina(gameSettings::humanSetting.stamina / 2);
					}
					else
					{
						humansInThisArea[0]->setStamina(gameSettings::humanSetting.stamina);
						humansInThisArea[1]->setStamina(gameSettings::humanSetting.stamina);
						humansInThisArea[2]->setStamina(gameSettings::humanSetting.stamina);
					}
					this->houseAreas[i].sendFood(this->food);
					this->houseAreas[i].setHumans(humansInThisArea);
					this->food = 0;
				}
			}
		}
		//header.counter(wood, food, stone, peopleCount);
		// ïîñòàíîâêà çàäà÷ äëÿ ðàçâèòèÿ ïîñåëåíèÿ íà ýòîò äåíü

		for (int i = 0; i < this->houseAreas.size(); i++)
		{
			for (int j = 0; j < this->houseAreas[i].getBushesInArea().size(); j++)
			{
				this->field.updateBushes(this->houseAreas[i].getBushesInArea()[j].getPosition());
			}
			if (houseAreas[i].getHumans().size() < 3 && this->food >= ((this->peopleCount + 1) * gameSettings::humanSetting.deilyRation) * 3 + gameSettings::settlmentSetting.foodForBirth)
			{
				houseAreas[i].spawnBuilder();
				food -= gameSettings::settlmentSetting.foodForBirth;
				peopleCount++;
			}
			for (int j = 0; j < this->houseAreas[i].getHumans().size(); j++)
			{
				if (j == 0)
				{
					this->houseAreas[i].setFarmerQueue();
				}
				else
				{
					if (this->food >= ((this->peopleCount + 1) * gameSettings::humanSetting.deilyRation) * 3 + gameSettings::settlmentSetting.foodForBirth)
					{
						if (this->stone >= gameSettings::settlmentSetting.stoneForBildingHouse)
						{
							if (this->wood >= gameSettings::settlmentSetting.woodForBildingHouse)
							{
								//ãëàâíàÿ âåðñèÿ
								if (this->houseAreas[i].createBuilderQueue(taskType::buildingHouse, j))
								{
									this->food -= gameSettings::settlmentSetting.foodForBirth;
									this->wood -= gameSettings::settlmentSetting.woodForBildingHouse;
									this->stone -= gameSettings::settlmentSetting.stoneForBildingHouse;
								}
								//òåñòîâàÿ âåðñèÿ
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
							//ãëàâíàÿ âåðñèÿ
							/*this->houseAreas[i].createBuilderQueue(taskType::buildingFarm, j);
							this->wood -= gameSettings::settlmentSetting.woodForBildingFarm;*/
							///òåñòîâàÿ âåðñèÿ
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
		std::cout << "food: " << food << std::endl;
		std::cout << "wood: " << wood << std::endl;
		std::cout << "stone: " << stone << std::endl;
		this->header.counter(wood, food, stone, peopleCount);
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
						if (posBefor.j - 20 >= 3)
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
						if (posBefor.i - 20 >= 3)
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
						if (posBefor.j + 20 < 98)
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
						if (posBefor.i + 20 < 98)
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
						peopleCount++;
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

			///bliting
			header.blitHeader();

			field.blitField();

			SDL_UpdateWindowSurface(gameSettings::win);

			while (this->game)
			{
				while (SDL_PollEvent(&event) || this->game)
				{
					if (event.type == SDL_QUIT)
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
					else if (event.type == SDL_MOUSEMOTION)
					{
						cursor_X = event.motion.x; cursor_Y = event.motion.y;
					}

					if (!firstHouse)
					{
						this->field.blitField();
						if (cursor_Y > gameSettings::winObjSize.menuHeader)
						{
							this->goodForHouse = field.chosePositionForHouse({ (short int)cursor_X, (short int)cursor_Y });
							SDL_UpdateWindowSurface(gameSettings::win);
						}

						if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP && this->goodForHouse)
						{
							///если курсор за игровой зоной но goodForHouse = true 
							///проверка на положение курсора в игровой зоне
							if (cursor_Y > gameSettings::winObjSize.menuHeader)
							{
								field.setHouse({ (short)cursor_X,(short)cursor_Y }, "px");
								position pos = field.findCellByCoord({ (short)cursor_X,(short)cursor_Y });
								houseAreaClass houseArea = houseAreaClass(pos, field.getFieldV(), field.getAreasPointsPosition(pos), false, false, false, false);
								peopleCount++;
								header.counter(wood, food, stone, peopleCount);
								this->houseAreas.push_back(houseArea);
								field.blitField();
								SDL_UpdateWindowSurface(gameSettings::win);

								firstHouse = true;

								std::cout << "ok\n";
							}
						}
					}
					else
					{
						if (!this->pause)
						{
							if (++gSecond == this-> itInOneLoop )
							{
								if (++gLoop == gameSettings::settlmentSetting.loopsInOneDay)
								{
									//îáíîâëåíèÿ â íà÷àëå äíÿ
									oneDayActions();

									//std::cout << gLoop << std::endl;
									gLoop = 0;
								}
								else
								{
									//èãðîâîé öèêë êàæäîãî òèêà
									oneTikActions();
									//std::cout << gSecond << std::endl;
									field.blitField();
									SDL_UpdateWindowSurface(gameSettings::win);

									this->itInOneLoop =int( gameSettings::settlmentSetting.secondsInOneLoop / this->timeRation);
								}
								gSecond = 0;
							}
						}
					}
					if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
					{
						if (this->cursor_Y < gameSettings::winObjSize.menuHeader)
						{
							SDL_GetMouseState(&this->cursor_X, &this->cursor_Y );
							if (this->cursor_X >= this->header.getBtnSpriteListX())
							{
								switch (this->header.btnParse(this->cursor_X))
								{
								case gameSettings::headerSetting.btns::playPause:
									if (this->firstHouse)
									{
										!this->pause ? this->pause = true : this->pause = false;
										this->header.toggleForPlayBtn(this->pause);
									}
									break;
								case gameSettings::headerSetting.btns::devide2:
									if (this->timeRation != 1) { this->timeRation /= 2; }
									std::cout << "time::\t" <<gameSettings::settlmentSetting.secondsInOneLoop / this->timeRation << "\n";
									this->header.blitXClock(this->timeRation);
									break;
								case gameSettings::headerSetting.btns::multipl2:
									if (this->timeRation != 8) { this->timeRation *= 2; }
									std::cout << "time::\t" << gameSettings::settlmentSetting.secondsInOneLoop / this->timeRation << "\n";
									this->header.blitXClock(this->timeRation);
									break;
								case gameSettings::headerSetting.btns::restart:
									std::cout << "menu::\trestart\n";
									restart();
									

									break;
								case gameSettings::headerSetting.btns::faq:
									std::cout << "menu::\tfaq\n";
									break;
								case gameSettings::headerSetting.btns::quit:
									std::cout << "menu::\tquit\n";
									return 0;
									break;

								default:
									break;
								}
							}
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

