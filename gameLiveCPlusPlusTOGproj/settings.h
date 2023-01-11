#pragma once

#include<SDL.h>
#include<SDL_image.h>

#include <iostream>
#include <vector>
#include <string>
 
enum imagesNames
{
	emptyCell =0,
	emptyCellHouseArea,
	emptyCellVisibleArea,

	bushWithBerryCell,
	bushWithBerryCellHouseArea,
	bushWithBerryCellVisibleArea,

	bushWithoutBerryCellHouseArea,

	rockCell,
	rockCellHouseArea,
	rockCellVisibleArea,

	treeCell,
	treeCellHouseArea,
	treeCellVisibleArea,

	personCellHouseArea,
	personCellVisibleArea,

	houseImg,
	farmImg,

	imagesTOTAL
};
struct imagePath
{
	std::string path;
	short int position;
};



enum directions
{
	up,
	right,
	left,
	down
};

enum material
{
	wood = 1,
	stone
};
enum taskType
{
	getWood = 1,
	getStone,
	buildingFarm,
	buildingHouse
};

struct position
{
	short int i = 0;
	short int j = 0;
};

struct task
{
	position position = { 0,0 };
	short int workTime = 0;
};

struct humanSettings
{
	short int hp = 10;
	short int stamina = 90; // TODO: ������� ����� ��� � ���-�� �������
	short int satiety = 6;
};

struct sizes
{
	short int width = 0;
	short int height = 0;
};

struct houseSettings
{
	sizes size = { 2, 2 };
};

struct farmSettings
{
	sizes size = { 3, 3 };
	short int income = 10;
};

struct builderSettings
{
	short int inventorySize = 4;
};

struct winObjSizes
{
	short int menuHeader = 70;			///px
	short int cellSize = 30;			///px
	const short int winTopBorder = 31;	///px
};

struct cell
{
	position pixelPosition = { 0,0 };
	position position = { 0, 0 };		/// position of cell in field vector
	short int objectType = 0;			/// which object is stored in this cell. (defined by enum)
	short int exploration = 0;			/// for coloring home zones, search zones (defined by enum)
	bool hasHuman = false;				/// is the person in the cell? (true = yes )
	bool hasSmth = false;				/// whether the cell has any object. (true = yes )
};

struct fieldSettings
{
	///tempSizes for tests (100x100); normalSizes (500,500);
	sizes size = { 100, 100 };			///cells x cells
	sizes minCountCellInWin = { 0, 0 };	/// minimalCounts cells which we can see in gameWindow
	short int densityOfTree = size.height * size.width / 10;
	short int densityOfRock = size.height * size.width / 10;
	short int densityOfBush = size.height * size.width / 10;

	enum objectEnum
	{
		bushWithBerry,
		bushWithoutBerry,
		rock,
		tree,
		farm,
		house,
		partOfHouse
	};
	enum explorationEnum
	{
		emptyArea,
		visibleArea,
		houseArea
	};
	
};

namespace gameSettings {
	extern humanSettings humanSetting;			///settings for human
	extern farmSettings farmSetting;			///settings for farms - obj
	extern builderSettings builderSetting;		///settings for builder - human
	extern winObjSizes winObjSize;				///settings for static objects such as menuHeader, menuBtns and other
	extern fieldSettings fieldSetting;			///settings for field

	extern SDL_Window* win;						///object win
	extern SDL_Surface* surface;				///object surface
	extern std::vector<imagePath>imagePathVector;
	extern std::vector<SDL_Surface*> imageVector;
}