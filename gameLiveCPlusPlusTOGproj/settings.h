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
	bushWithPerson,

	bushWithoutBerryPerson,
	bushWithoutBerryCellHouseArea,

	rockCell,
	rockCellHouseArea,
	rockCellVisibleArea,
	rockWithPersonHouse,
	rockWithPersonArea,

	treeCell,
	treeCellHouseArea,
	treeCellVisibleArea,
	treeWithPersonHouse,
	treeWithPersonArea,

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
	buildingHouse,
	getSomething,
	getFood
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
	short int type = 0;
};

struct humanSettings
{
	short int hp = 10;
	short int stamina = 90; 
	short int satiety = 6;
	short int deilyRation = 2;
};

struct sizes
{
	short int width = 0;
	short int height = 0;
};

struct houseSettings
{
	sizes size = { 2, 2 };
	short int workTime = 30;
};

struct farmSettings
{
	sizes size = { 3, 3 };
	short int income = 10;
	short int workTime = 30;
};

struct objectSettings
{
	short int treeResources = 4;
	short int rockResources = 4;
	short int bushResources = 4;
};

struct builderSettings
{
	short int inventorySize = 4;
};

struct settlmentSettings
{
	short int secondsInOneLoop = 5;
	short int loopsInOneDay = 90;
	short int foodForBirth = 40;
	short int stoneForBildingHouse = 30;
	short int woodForBildingHouse = 30;
	short int woodForBildingFarm = 15;
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
	short int densityOfBush = size.height * size.width / 70;

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

struct houseAreasPoints
{
	position searchStartPos = { 0,0 };
	position searchEndtPos = { 0,0 };
	position houseAreaStartPos = { 0,0 };
	position houseAreaEndPos = { 0,0 };
};

struct headerSettings
{
	

	enum headerImgs
	{
		bg,
		numbers,
		stone,
		wood, 
		food, 
		people,


		btnQiut,
		btnRestart,
		btnFAQ,
		btnSpeedUp,
		btnSpeedDown,


		menuImgsTOTAL
	};

	enum counters
	{
		/*wood,
		stone,
		food,
		people,*/
		///days
	};
};


namespace gameSettings {
	extern humanSettings humanSetting;			///settings for human
	extern farmSettings farmSetting;			///settings for farms - obj
	extern houseSettings houseSetting;
	extern builderSettings builderSetting;		///settings for builder - human
	extern winObjSizes winObjSize;				///settings for static objects such as menuHeader, menuBtns and other
	extern fieldSettings fieldSetting;			///settings for field
	extern objectSettings objectSetting;
	extern settlmentSettings settlmentSetting;
	extern headerSettings headerSetting;

	extern SDL_Window* win;						///object win
	extern SDL_Surface* surface;				///object surface
	extern std::vector<imagePath>gameImagesPathVector;
	extern std::vector<imagePath>headerImagesPathVector;

	//extern std::vector<SDL_Surface*> imageVector;
}