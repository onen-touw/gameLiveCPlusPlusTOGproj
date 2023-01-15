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

	///return position {i, j}
	position findCellByCoord(position mousePos) {
		if (mousePos.i > gameSettings::winObjSize.menuHeader)
		{
			for (int i = this->fieldShift.i; i <= this->fieldShift.i + gameSettings::fieldSetting.minCountCellInWin.height; i++)
			{
				for (int j = this->fieldShift.j; j <= this->fieldShift.j + gameSettings::fieldSetting.minCountCellInWin.width; j++)
				{
					if (
						mousePos.i >= fieldV[i][j].pixelPosition.i && mousePos.i <= fieldV[i][j].pixelPosition.i + gameSettings::winObjSize.cellSize
						&& mousePos.j >= fieldV[i][j].pixelPosition.j && mousePos.j <= fieldV[i][j].pixelPosition.j + gameSettings::winObjSize.cellSize
						)
					{
						return fieldV[i][j].position; ///return position {i, j}
					}
				}
			}
		}
		else return { -1, -1 };
	}

	void setHouse(position pos, std::string metric) {
		if (metric == "px")
		{
			/// pos(px, px) -> pos(i,j)
			std::cout << pos.i << "-" << pos.j << " px\n";

			pos = this->findCellByCoord(pos);
		}

		std::cout << pos.i << "-" << pos.j << " hTeoretic\n";
		fieldV[pos.i][pos.j].hasSmth = true;

		fieldV[pos.i][pos.j].exploration = gameSettings::fieldSetting.explorationEnum::houseArea;
		fieldV[pos.i+1][pos.j].exploration = gameSettings::fieldSetting.explorationEnum::houseArea;
		fieldV[pos.i][pos.j+1].exploration = gameSettings::fieldSetting.explorationEnum::houseArea;
		fieldV[pos.i+1][pos.j+1].exploration = gameSettings::fieldSetting.explorationEnum::houseArea;

		fieldV[pos.i][pos.j].objectType = gameSettings::fieldSetting.objectEnum::house;
		fieldV[pos.i+1][pos.j].objectType = gameSettings::fieldSetting.objectEnum::partOfHouse;
		fieldV[pos.i][pos.j+1].objectType = gameSettings::fieldSetting.objectEnum::partOfHouse;
		fieldV[pos.i+1][pos.j+1].objectType = gameSettings::fieldSetting.objectEnum::partOfHouse;

		this->setAreas(pos);
	}

	///r - remove from this point
	///t - add to new position
	void setPersonCoors(int i, int j, std::string type) {
		if (type == "r")
		{
			fieldV[i][j].hasHuman = false;
		}
		else if (type == "t")
		{
			fieldV[i][j].hasHuman = true;
		} 
	}

	void setAreas(position pos) {
		position searchStartPos = { 0,0 };
		position searchEndtPos = { 0,0 };
		position houseAreaStartPos = { 0,0 };
		position houseAreaEndPos = { 0,0 };
		
		if (pos.i - 20 >=0)
		{
			searchStartPos.i = pos.i - 20;
		}
		else
		{
			searchStartPos.i = 0;
		}
		if (pos.i - 9 > 0)
		{
			houseAreaStartPos.i = pos.i - 9;
		}
		else
		{
			houseAreaStartPos.i = 0;
		}
		if (pos.j - 20 >= 0)
		{
			searchStartPos.j = pos.j - 20;
			
		}
		else
		{
			searchStartPos.j = 0;
		}
		if (pos.j - 9 > 0)
		{
			houseAreaStartPos.j = pos.j - 9;
		}
		else
		{
			houseAreaStartPos.j = 0;
		}
		if (pos.i + 21 < fieldV.size())
		{
			searchEndtPos.i = pos.i + 21;
		}
		else
		{
			searchEndtPos.i = fieldV[0].size()-1;
		}
		if (pos.i + 10 <= fieldV.size())
		{
			houseAreaEndPos.i = pos.i + 10;
		}
		else
		{
			houseAreaEndPos.i = fieldV[0].size() - 1;
		}
		if (pos.j + 21 < fieldV.size())
		{
			searchEndtPos.j = pos.j + 21;
		}
		else
		{
			searchEndtPos.j = fieldV[0].size()-1;
		}
		if (pos.j + 10 <= fieldV[0].size())
		{
			houseAreaEndPos.j = pos.j + 10;
		}
		else
		{
			houseAreaEndPos.j = fieldV[0].size() - 1;
		}

		for (int i = searchStartPos.i; i <= searchEndtPos.i; i++)
		{
			for (int j = searchStartPos.j; j <= searchEndtPos.j; j++)
			{
				if (i >= houseAreaStartPos.i && j >= houseAreaStartPos.j &&
					i<= houseAreaEndPos.i && j <=houseAreaEndPos.j)
				{
					this->fieldV[i][j].exploration = gameSettings::fieldSetting.explorationEnum::houseArea ;
				}
				else
				{
					if (fieldV[i][j].exploration != gameSettings::fieldSetting.explorationEnum::houseArea)
					{
						this->fieldV[i][j].exploration = gameSettings::fieldSetting.explorationEnum::visibleArea;
					}
				}
			}
			std::cout << "\n";
		}

	}

	

	void blitChoseZone(int img, position pos) {
		SDL_Rect mr = { fieldV[pos.i][pos.j].pixelPosition.i, fieldV[pos.i][pos.j].pixelPosition.j,
					 gameSettings::winObjSize.cellSize * 2, gameSettings::winObjSize.cellSize * 2
		};
		SDL_BlitScaled(gameSettings::imageVector[img], NULL, gameSettings::surface, &mr);
	}

	void blitBigObjects(int img, position pos, int size) {
		SDL_Rect mr = { fieldV[pos.i][pos.j].pixelPosition.i, fieldV[pos.i][pos.j].pixelPosition.j,
					 gameSettings::winObjSize.cellSize * size, gameSettings::winObjSize.cellSize * size
		};
		SDL_BlitScaled(gameSettings::imageVector[img], NULL, gameSettings::surface, &mr);
	}

	bool chosePositionForHouse(position mousePos) {
		position temp = this->findCellByCoord(mousePos);
		if (!fieldV[temp.i][temp.j].hasSmth)
		{
			if (!fieldV[temp.i + 1][temp.j].hasSmth && !fieldV[temp.i][temp.j+1].hasSmth && !fieldV[temp.i+1][temp.j+1].hasSmth)
			{
				this->blitChoseZone(imagesNames::emptyCellHouseArea, temp);
				return true;
			}
			else
			{
				this->blitChoseZone(imagesNames::emptyCellVisibleArea, temp);
				return false;
			}
		}
		else
		{
			this->blitChoseZone(imagesNames::emptyCellVisibleArea, temp);
			return false;
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
			std::cout << fieldShift.i + gameSettings::fieldSetting.minCountCellInWin.height 
				<< "x" << fieldShift.j + gameSettings::fieldSetting.minCountCellInWin.width << "<<endPoint\n\n";

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
		short int x = 0, y = gameSettings::winObjSize.menuHeader;

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
							break;
						case gameSettings::fieldSetting.objectEnum::rock:
							///blit rock
							this->blit(imagesNames::rockCell, i, j);
							break;
						case gameSettings::fieldSetting.objectEnum::tree:
							///blit tree
							this->blit(imagesNames::treeCell, i, j);

							break;
						default:
							break;
						}
					}
					else
					{
						///blit emptyCell
						this->blit(imagesNames::emptyCell, i, j);
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
									//this->blit(imagesNames::treeCellVisibleArea, i, j);

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
								this->blit(imagesNames::bushWithBerryCellVisibleArea, i, j);

								break;
							case gameSettings::fieldSetting.objectEnum::rock:
								///blit rock
								this->blit(imagesNames::rockCellVisibleArea, i, j);

								break;
							case gameSettings::fieldSetting.objectEnum::tree:
								///blit tree
								this->blit(imagesNames::treeCellVisibleArea, i, j);

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
							this->blit(imagesNames::personCellVisibleArea, i, j);
						}
						else
						{
							this->blit(imagesNames::emptyCellVisibleArea, i, j);
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
							if (fieldV[i][j].objectType != gameSettings::fieldSetting.objectEnum::partOfHouse)
							{
								switch (fieldV[i][j].objectType)
								{
								case gameSettings::fieldSetting.objectEnum::bushWithBerry:
									///blit bush
									this->blit(imagesNames::bushWithBerryCellHouseArea, i, j);
									break;
								case gameSettings::fieldSetting.objectEnum::bushWithoutBerry:
									///blit bush without berry
									break;
								case gameSettings::fieldSetting.objectEnum::rock:
									///blit rock
									this->blit(imagesNames::rockCellHouseArea, i, j);
									break;
								case gameSettings::fieldSetting.objectEnum::tree:
									///blit tree
									this->blit(imagesNames::treeCellHouseArea, i, j);
									break;
								case gameSettings::fieldSetting.objectEnum::farm:
									///blit farm
									this->blitBigObjects(imagesNames::farmImg, { (short)i, (short)j }, 3);
									break;
								case gameSettings::fieldSetting.objectEnum::house:
									///blit house
									this->blitBigObjects(imagesNames::houseImg, { (short)i, (short)j }, 2);
									std::cout << i << "-" << j << " <House\n";
									break;
								default:
									break;
								}
							}
							//else std::cout << i << " " << j << "\n";
						}
					}
					else
					{
						if (fieldV[i][j].hasHuman)
						{
							///blit cell with human
							this->blit(imagesNames::personCellHouseArea, i, j);
						}
						else
						{
							if (fieldV[i][j].objectType != gameSettings::fieldSetting.objectEnum::partOfHouse)
							{
								///blit empty cell}
								this->blit(imagesNames::emptyCellHouseArea, i, j);
							}
						}
					}
					break;
				default:
					break;
				}
				x += gameSettings::winObjSize.cellSize;
			}
			y += gameSettings::winObjSize.cellSize;
			x = 0;
		}
	}

};

