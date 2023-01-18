#include"settings.h"

namespace gameSettings {
	humanSettings humanSetting;
	farmSettings farmSetting;
	builderSettings builderSetting;
	winObjSizes winObjSize;
	fieldSettings fieldSetting;
	houseSettings houseSetting;
	objectSettings objectSetting;
	settlmentSettings settlmentSetting;
	headerSettings headerSetting;

	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
	std::vector<imagePath>gameImagesPathVector = {
		{"./images/fieldImages/emptyCell.png", imagesNames::emptyCell},
		{"./images/fieldImages/emptyCellHouseArea.png", imagesNames::emptyCellHouseArea },
		{"./images/fieldImages/emptyCellVisibleArea.png", imagesNames::emptyCellVisibleArea },

		{"./images/fieldImages/bushWithBerry.png", imagesNames::bushWithBerryCell },
		{"./images/fieldImages/bushWithBerryHouseArea.png", imagesNames::bushWithBerryCellHouseArea },
		{"./images/fieldImages/bushWithBerryVisibleArea.png", imagesNames::bushWithBerryCellVisibleArea },

		{"./images/fieldImages/bushWithoutBerryHouseArea.png", imagesNames::bushWithoutBerryCellHouseArea },

		{"./images/fieldImages/rockCell.png", imagesNames::rockCell },
		{"./images/fieldImages/rockCellHouseArea.png", imagesNames::rockCellHouseArea },
		{"./images/fieldImages/rockCellVisibleArea.png", imagesNames::rockCellVisibleArea },

		{"./images/fieldImages/treeCell.png", imagesNames::treeCell },
		{"./images/fieldImages/treeCellHouseArea.png", imagesNames::treeCellHouseArea },
		{"./images/fieldImages/treeCellVisibleArea.png", imagesNames::treeCellVisibleArea },

		{"./images/fieldImages/personCellHouseArea.png", imagesNames::personCellHouseArea },
		{"./images/fieldImages/personCellVisibleArea.png", imagesNames::personCellVisibleArea },

		{"./images/fieldImages/farmImg.png", imagesNames::farmImg },
		{"./images/fieldImages/houseHomeAreaImg.png", imagesNames::houseImg},

		{"./images/fieldImages/bushWithPerson.png", imagesNames::bushWithPerson},
		{"./images/fieldImages/bushWithoutBerryPerson.png", imagesNames::bushWithoutBerryPerson},

		{"./images/fieldImages/rockWithPersonHouse.png", imagesNames::rockWithPersonHouse},
		{"./images/fieldImages/rockWithPersonArea.png", imagesNames::rockWithPersonArea},

		{"./images/fieldImages/treeWithPersonHouse.png", imagesNames::treeWithPersonHouse,},
		{"./images/fieldImages/treeWithPersonArea.png", imagesNames::treeWithPersonArea,},
	};

	std::vector<imagePath>headerImagesPathVector = {
		{"./images/headerImgs/bgTemp.png", headerSetting.headerImgs::bg},
		{"./images/headerImgs/numbers.png", headerSetting.headerImgs::numbers},

		{"./images/headerImgs/wood.png", headerSetting.headerImgs::wood},
		{"./images/headerImgs/food.png", headerSetting.headerImgs::food},
		{"./images/headerImgs/stone.png", headerSetting.headerImgs::stone},
		{"./images/headerImgs/people.png", headerSetting.headerImgs::people},

		{"./images/headerImgs/btnsSpriteList.png", headerSetting.headerImgs::btnSpriteList},
	/*	{"./images/headerImgs/people.png", headerSetting.headerImgs::people},
		{"./images/headerImgs/people.png", headerSetting.headerImgs::people},*/
	};

}