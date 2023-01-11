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

		for (int i = 0; i < this->fieldV.size(); i++)
		{
			for (int j = 0; j < this->fieldV[0].size(); j++)
			{
				this->fieldV[i][j].position.i = i;
				this->fieldV[i][j].position.j = j;
			}
		}
		std::cout << fieldV.size() << "\n";
		std::cout << fieldV[0].size() << "\n";
		std::cout << gameSettings::fieldSetting.minCountCellInWin.height << "\n";
		std::cout << gameSettings::fieldSetting.minCountCellInWin.width << "\n";

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
			if (fieldShift.j < gameSettings::fieldSetting.size.width - gameSettings::fieldSetting.minCountCellInWin.width)
			{
				fieldShift.j++;
				changeFieldPosition = true;
			}
			break;
		case directions::down:
			if (fieldShift.i < gameSettings::fieldSetting.size.height - gameSettings::fieldSetting.minCountCellInWin.height)
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
			this->blit();
		}
		return;
	}

	void blit() {
		for (int i = this->fieldShift.i ; i <= this->fieldShift.i + gameSettings::fieldSetting.minCountCellInWin.height; i++)
		{
			for (int j = this->fieldShift.j; j <= this->fieldShift.j + gameSettings::fieldSetting.minCountCellInWin.width; j++)
			{
				std::cout << fieldV[i][j].position.i << "x" << fieldV[i][j].position.j << " ";
			}
			std::cout << "\n";
		}
	}

};

