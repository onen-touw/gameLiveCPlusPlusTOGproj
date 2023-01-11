#include"settings.h"

namespace gameSettings {
	humanSettings humanSetting;
	farmSettings farmSetting;
	builderSettings builderSetting;
	winObjSizes winObjSize;
	fieldSettings fieldSetting;

	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
	std::vector<imagePath>imagePathVector = {
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
	};
	std::vector<SDL_Surface*> imageVector;
}