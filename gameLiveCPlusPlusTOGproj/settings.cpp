#include"settings.h"

namespace gameSettings {
	humanSettings humanSetting;
	farmSettings farmSetting;
	builderSettings builderSetting;
	winObjSizes winObjSize;
	fieldSettings fieldSetting;

	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
	std::vector<imagePath>imageVector = {
		{"./images/fieldImages/emptyCell.png", imagesNames::emptyCell},
		{"./images/fieldImages/houseAreaCell.png", imagesNames::houseAreaCell},
	};
}