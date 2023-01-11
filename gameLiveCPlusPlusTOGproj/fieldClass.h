#pragma once

#include"settings.h"

class fieldClass
{
private:

	std::vector<std::vector<cell>>fieldV;
	position fieldShift ={0, 0};

public:

	void createFieldV() {
		
		fieldV.resize(gameSettings::fieldSetting.size.height);
		for (int i = 0; i < this->fieldV.size(); i++)
		{
			this->fieldV[i].resize(gameSettings::fieldSetting.size.width);
		}

		for (short int i = 0; i < this->fieldV.size(); i++)
		{
			for (short int j = 0; j < this->fieldV[0].size(); j++)
			{
				this->fieldV[i][j].position= {i,j};
			}
		}
		std::cout << fieldV.size() << "\n";
		std::cout << fieldV[0].size() << "\n";
		std::cout << gameSettings::fieldSetting.minCountCellInWin.height << "\n";
		std::cout << gameSettings::fieldSetting.minCountCellInWin.width << "\n";

	}

	void generationObjects() {
		srand(time(0));
		for (int i = 0; i < gameSettings::fieldSetting.densityOfTree; i++)
		{
			short int x = rand() % fieldV.size();
			short int y = rand() % fieldV[0].size();
			if (fieldV[x][y].hasSmth)
			{
				i--;
			}
			else
			{
				fieldV[x][y].objectType = gameSettings::fieldSetting.objectEnum::tree;
				fieldV[x][y].hasSmth = true;
			}
		}
		for (int i = 0; i < gameSettings::fieldSetting.densityOfRock; i++)
		{
			short int x = rand() % fieldV.size();
			short int y = rand() % fieldV[0].size();
			if (fieldV[x][y].hasSmth)
			{
				i--;
			}
			else
			{
				fieldV[x][y].objectType = gameSettings::fieldSetting.objectEnum::rock;
				fieldV[x][y].hasSmth = true;
			}
		}

		for (int i = 0; i < gameSettings::fieldSetting.densityOfBush; i++)
		{
			short int x = rand() % fieldV.size();
			short int y = rand() % fieldV[0].size();
			if (fieldV[x][y].hasSmth)
			{
				i--;
			}
			else
			{
				fieldV[x][y].objectType = gameSettings::fieldSetting.objectEnum::bushWithBerry;
				fieldV[x][y].hasSmth = true;
			}
		}
		
	}

	void transmitField(int direction) {
		bool changeFieldPosition = false;
		switch (direction)
		{
		case directions::up:
			if (fieldShift.i > 0)
			{
				fieldShift.i--;
				changeFieldPosition = true;
			}
			break;
		case directions::right:
			if (fieldShift.j < gameSettings::fieldSetting.size.width - gameSettings::fieldSetting.minCountCellInWin.width-1)
			{
				fieldShift.j++;
				changeFieldPosition = true;
			}
			break;
		case directions::down:
			if (fieldShift.i < gameSettings::fieldSetting.size.height - gameSettings::fieldSetting.minCountCellInWin.height-1)
			{
				fieldShift.i++;
				changeFieldPosition = true;
			}
			break;
		case directions::left:
			if (fieldShift.j > 0)
			{
				fieldShift.j--;
				changeFieldPosition = true;
				
			}
			break;
		
		default:
			break;
		}

		if (changeFieldPosition)
		{
			system("cls");
			//this->blit();

			std::cout << fieldShift.i << "x" << fieldShift.j << "<<startPoint\n";
			std::cout << fieldShift.i + gameSettings::fieldSetting.minCountCellInWin.height << "x" << fieldShift.j + gameSettings::fieldSetting.minCountCellInWin.width << "<<endPoint\n\n";

			this->blitField();
			SDL_UpdateWindowSurface(gameSettings::win);
		}
		else
		{
			std::cout << "transmit:: lock\n";
		}
		
		return;
	}
	void blit(int imageName, int i, int j ) {
		SDL_Rect mr = {fieldV[i][j].pixelPosition.i, fieldV[i][j].pixelPosition.j, gameSettings::winObjSize.cellSize, gameSettings::winObjSize.cellSize };
		SDL_BlitScaled(gameSettings::imageVector[imageName], NULL, gameSettings::surface, &mr);
	}

	void blitField() {
		short int x = 0, y = 0;

		for (int i = this->fieldShift.i ; i <= this->fieldShift.i + gameSettings::fieldSetting.minCountCellInWin.height; i++)
		{
			for (int j = this->fieldShift.j; j <= this->fieldShift.j + gameSettings::fieldSetting.minCountCellInWin.width; j++)
			{
				fieldV[i][j].pixelPosition = {x, y};

				switch (fieldV[i][j].exploration)
				{
				case gameSettings::fieldSetting.explorationEnum::emptyArea:
					if (fieldV[i][j].hasSmth)
					{
						switch (fieldV[i][j].objectType)
						{
						case gameSettings::fieldSetting.objectEnum::bushWithBerry:
							///blit bush
							this->blit(imagesNames::bushWithBerryCell, i, j);
							//std::cout << "b ";
							break;
						case gameSettings::fieldSetting.objectEnum::rock:
							///blit rock
							this->blit(imagesNames::rockCell, i, j);
							//std::cout << "r ";
							break;
						case gameSettings::fieldSetting.objectEnum::tree:
							///blit tree
							this->blit(imagesNames::treeCell, i, j);

							//std::cout << "t ";
							break;
						default:
							break;
						}
					}
					else
					{
						///blit emptyCell
						this->blit(imagesNames::emptyCell, i, j);

						//std::cout << "0 ";
					}
					break;

				case gameSettings::fieldSetting.explorationEnum::visibleArea:
					if (fieldV[i][j].hasSmth)
					{
						if (fieldV[i][j].hasHuman)
						{
								switch (fieldV[i][j].objectType)
								{
								case gameSettings::fieldSetting.objectEnum::rock:
									///blit rock with persone
									break;
								case gameSettings::fieldSetting.objectEnum::tree:
									///blit tree with persone
									break;
								default:
									break;
								}
						}
						else
						{
							switch (fieldV[i][j].objectType)
							{
							case gameSettings::fieldSetting.objectEnum::bushWithBerry:
								///blit bush
								break;
							case gameSettings::fieldSetting.objectEnum::rock:
								///blit rock
								break;
							case gameSettings::fieldSetting.objectEnum::tree:
								///blit tree
								break;
							case gameSettings::fieldSetting.objectEnum::farm:
								///blit farm
								break;
							case gameSettings::fieldSetting.objectEnum::house:
								///blit house
								break;
							default:
								break;
							}
						}
					}
					else
					{
						if (fieldV[i][j].hasHuman)
						{
							
							///blit cell with human
						}
						else
						{
							///blit empty cell
						}
					}
					break;

				case gameSettings::fieldSetting.explorationEnum::houseArea:
					if (fieldV[i][j].hasSmth)
					{
						if (fieldV[i][j].hasHuman)
						{
							if (fieldV[i][j].objectType != gameSettings::fieldSetting.objectEnum::house &&
								fieldV[i][j].objectType != gameSettings::fieldSetting.objectEnum::partOfHouse)
							{
								switch (fieldV[i][j].objectType)
								{
								case gameSettings::fieldSetting.objectEnum::bushWithBerry:
									///blit bush with persone
									break;;
								case gameSettings::fieldSetting.objectEnum::rock:
									///blit rock with persone
									break;
								case gameSettings::fieldSetting.objectEnum::tree:
									///blit tree with persone
									break;
								default:
									break;
								}
							}
						}
						else
						{
							switch (fieldV[i][j].objectType)
							{
							case gameSettings::fieldSetting.objectEnum::bushWithBerry:
								///blit bush
								break;
								case gameSettings::fieldSetting.objectEnum::bushWithoutBerry:
								///blit bush without berry
								break;
							case gameSettings::fieldSetting.objectEnum::rock:
								///blit rock
								break;
							case gameSettings::fieldSetting.objectEnum::tree:
								///blit tree
								break;
							case gameSettings::fieldSetting.objectEnum::farm:
								///blit farm
								break;
							case gameSettings::fieldSetting.objectEnum::house:
								///blit house
								break;
							default:
								break;
							}
						}
					}
					else
					{
						if (fieldV[i][j].hasHuman)
						{
							///blit cell with human
						}
						else
						{
							///blit empty cell
						}
					}
					break;
				default:
					break;
				}
				x += gameSettings::winObjSize.cellSize;

			}
			//std::cout << "\n";
			y += gameSettings::winObjSize.cellSize;
			x = 0;
		}
	}

};

