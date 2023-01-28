#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-for-range-copy"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma ide diagnostic ignored "bugprone-integer-division"
#pragma ide diagnostic ignored "bugprone-unused-raii"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
/*
 * Creators : Ege BULUT & Erdoðan
 *
 *
 *
 *
 */


#include "GameCanvas.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}
#pragma clang diagnostic pop

GameCanvas::~GameCanvas() = default;

void GameCanvas::setup() {
	DEBUG = false;
	gLogi("GameCanvas Setup");
	img_blueprint.loadImage("GUI/blueprint.png");
}

void GameCanvas::update() {
	framecounter++;
    if(!paused) {
        if (mouseHold) {
            mouseHoldedFor_frames++;
            if (framecounter % 60 == 0) {
                mouseHoldedFor_seconds++;
            }
        }

        if (game_status == LOADING) {
            gLogi("\n#\nloadindex: " + gToStr(loadindex) + "\n#");
            updateLoad(loadindex);
            loadindex++;
        } else if (game_status == PLAYING) {
            listener();
            updateCharacter();
            updateButtons();
            updateMap();
        }
    }
}

void GameCanvas::draw() {
	if (game_status == LOADING) {
		drawLoad();
		if(DEBUG) { //debug
			fonts[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
			fonts[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);
		}
	} else if (game_status == PLAYING) {
		drawGame();
		drawGUI();

		if(DEBUG) {	//debug
			fonts[font_INGAME].drawText("game_map == " + gToStr(game_map), 20, 100);
			fonts[font_LOAD2].drawText("Mouse Hold For " + gToStr(mouseHoldedFor_seconds) + " seconds",10,10);
			fonts[font_LOAD2].drawText("Mouse Hold For " + gToStr(mouseHoldedFor_frames) + " frames",10,30);
			fonts[font_INGAME].drawText("x:"+gToStr(mousex)+",y:"+gToStr(mousey), mousex, mousey+5);
		}
	}
}

void GameCanvas::initilaize() {
	img_blueprint.loadImage("GUI/blueprint.png");
	game_status = LOADING;
	game_map = IN_MAP;
	loadindex = 0;
	framecounter = 0;
	seccounter = 0;
	buttonPressed = -1;
    paperPressed = -1;
	buildingPressed = -1;
	mouseHold = false;
	mouseHoldedFor_frames = 0;
	mouseHoldedFor_seconds = 0;
	mousex = getWidth() / 2;
	mousey = getHeight() / 2;

	env_amounts[GRASS] = 5;
	env_amounts[STONE] = 3;
	env_amounts[TREE] = 3;

	gLogi("#DEBUG_test(19)");
	gLogi("#DEBUG_test(20)");/*
	fonts.push_back(font_load_1);
	fonts.push_back(font_load_2);
	fonts.push_back(font_button_1);
	fonts.push_back(font_ingame_1);*/
	gLogi("#DEBUG_test(21)");/*
	fonts[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	fonts[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);
	fonts[font_BUTTON].loadFont("FreeSans.ttf", fontsizes[font_BUTTON]);
	fonts[font_INGAME].loadFont("FreeSans.ttf", fontsizes[font_INGAME]);
*/
	loadingtext.emplace_back("LOADING");
	loadingtext.emplace_back("");

	characterscalelevel = 2;
	globalscalelevel = 2;

	scalelevels.emplace_back(0.5); // 0
	scalelevels.emplace_back(0.8); // 1
	scalelevels.emplace_back(1.0); // 2
	scalelevels.emplace_back(1.2); // 3
	scalelevels.emplace_back(1.5); // 4
	scalelevels.emplace_back(1.8); // 5
	scalelevels.emplace_back(2.5); // 6
	scalelevels.emplace_back(3.0); // 7

	fontsizes.emplace_back(24); //font_LOAD1
	fontsizes.emplace_back(14); //font_LOAD2
	fontsizes.emplace_back(18); //font_BUTTON
	fontsizes.emplace_back(12); //font_INGAME

	font_load_1.loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	font_load_2.loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);
	font_button_1.loadFont("FreeSans.ttf", fontsizes[font_BUTTON]);
	font_ingame_1.loadFont("FreeSans.ttf", fontsizes[font_INGAME]);

	gLogi("case 12 - 1");
	fonts[font_LOAD1] = (font_load_1);
	gLogi("case 12 - 2");
	fonts[font_LOAD2] = (font_load_2);
	gLogi("case 12 - 3");
	fonts[font_BUTTON] = (font_button_1);
	gLogi("case 12 - 4");
	fonts[font_INGAME] = (font_ingame_1);
	gLogi("case 12 - 5");

	gLogi("#DEBUG_test(27)");
	interiorAmounts[BUILDING_PAPER] = 1;
	gLogi("#DEBUG_test(28)");
	interiorAmounts[BUILDING_ROCK] = 1;
	gLogi("#DEBUG_test(29)");
	interiorAmounts[BUILDING_SCISSORS] = 1;
	interiorAmounts[3] = 1;
	interiorAmounts[4] = 1;
	interiorAmounts[5] = 1;
	interiorAmounts[6] = 1;
	interiorAmounts[7] = 1;
	interiorAmounts[8] = 1;
	interiorAmounts[9] = 0;

	gLogi("#DEBUG_test(30)");
	totalCharacterAmount = 1;
	gLogi("#DEBUG_test(31)");
	playerIndex = 0;
	gLogi("#DEBUG_test(32)");

	std::vector<int> tmpvals;

	for(int i = 0; i < totalCharacterAmount; i++) {
		std::vector<gImage> tmpimgs;
		characters.push_back(tmpvals);
		gLogi("characters.push_back - ok");
		characterEquipped.push_back(tmpvals);
		gLogi("characterEquipped.push_back - ok");

	}
	/*
	gLogi("194");
	for(int i = 0; i < buildingAmount; i++) {
		std::vector<int> tmpvals;
		shopInventories.push_back(tmpvals);
		for(int vi = 0; vi < 11; vi++) {
			shopInventories[i].push_back(0);
		}
	}
	gLogi("203");
	gImage tmpi;
	std::vector<gImage> tmp_imgvec;
	std::vector<std::vector<gImage>> tmp_imgvecvec;
	tmpi.loadImage("game/charactertest/base.png");
	for(int i = 0; i < 4; i++) { //RACE AMOUNT (ROCK-PAPER-SCISSORS)
		img_equipables.push_back(tmp_imgvecvec);
		for(int j = 0; j < 5; j++) { //TYPE AMOUNT (ARMOR-HELMET-WEAPON-EFFECT)
			img_equipables[i].push_back(tmp_imgvec);
			//for(int k = 0; k < 5; k++) { //TYPE AMOUNT (ARMOR-HELMET-WEAPON-EFFECT)
			//	img_equipables[i][j].push_back(tmpi);
			//}
		}
	}
*/
	characters[playerIndex].push_back(cx);		//x
	gLogi("#DEBUG_test(33)");
	characters[playerIndex].push_back(cy);		//y
	characters[playerIndex].push_back(crot);	//rotation
	characters[playerIndex].push_back(characterframeno);
	characters[playerIndex].emplace_back(0);	//race
	characters[playerIndex].emplace_back(1); 		//level
	gLogi("#DEBUG_test(34)");

	characters[playerIndex].emplace_back(1);		//STR
	characters[playerIndex].emplace_back(1);		//VIT
	characters[playerIndex].emplace_back(1);		//DEF/DEX
	characters[playerIndex].emplace_back(1);		//AGI/STA
	characters[playerIndex].emplace_back(1);		//MAG
	gLogi("#DEBUG_test(35)");

	characterEquipped[playerIndex].emplace_back(0); // BASE
	characterEquipped[playerIndex].emplace_back(0); //ARMOR
	characterEquipped[playerIndex].emplace_back(0); //HELMET
	characterEquipped[playerIndex].emplace_back(0); //WEAPON
	characterEquipped[playerIndex].emplace_back(-1);//EFFECT
	gLogi("#DEBUG_test(36)");
	gLogi("characterEquipped[playerIndex][ARMOR] : " + gToStr(characterEquipped[playerIndex][ARMOR]) ); //ARMOR
	/*
	characterInventory.push_back(playerIndex);
	characterInventory.push_back(1);		//Item Amount
	characterInventory.push_back(123);		//Coins
	characterInventory.push_back(1);		//ItemIndex
	characterInventory.push_back(5);		//Item Amount
	gLogi("#DEBUG_test(37)");

	shopInventories[SHOP_POTION].push_back(0);
	shopInventories[SHOP_POTION].push_back(2);
	shopInventories[SHOP_POTION].push_back(1500);
	shopInventories[SHOP_POTION].push_back(1);
	shopInventories[SHOP_POTION].push_back(99);
	shopInventories[SHOP_POTION].push_back(2);
	shopInventories[SHOP_POTION].push_back(99);
	gLogi("#DEBUG_test(38)");

	initilaized = true;
	gLogi("ee amk");
	*/

	//Vegetation Part
	std::vector<std::vector<float>> dummy;
	vegetations.push_back(dummy);
	vegetations.push_back(dummy);
	vegetations.push_back(dummy);

	//vegetationCoordinates[TREE] = scatterRandPointsOnGeometry(mapBoundaries, tree_amount);
	int grass_amount = 40;
	int tree_amount = 20;
	int stone_amount = 30;
	vegetationAmounts.push_back(grass_amount);
	vegetationAmounts.push_back(tree_amount);
	vegetationAmounts.push_back(stone_amount);
}

void GameCanvas::updateLoad(int index) {
	loadingtext[1] = "Loaded : ";
		switch (index) {
            case 0:
                img_menu.loadImage("menu/menu_0.png");
                loadingtext[1] += "menu/menu_0.png";
                break;
            case 1:
                for (int i = 0; i < 8; i++) {
                    img_menus[i].loadImage("menu/menu_" + gToStr(i) + ".png");
                    loadingtext[1] += "menu/menu_" + gToStr(i) + ".png";
                }
                background_defocus.loadImage("menu/defocus.png");
                break;
            case 2: // BUTTONLAR YÜKLENDÝ
                loadingtext[1] += "menu/btn.png";
                for (int i = 0; i < btnAmount; i++) {
                    img_button[i].loadImage("menu/btn_" + gToStr(i) + ".png");
                }
                break;
            case 3:
                img_background.loadImage("game/map.png");
                loadingtext[1] += "game/map.png";
                break;
            case 4:
                loadingtext[1] += "Props";
                for (int i = 0; i < propAmount; i++) {
                    img_props[i].loadImage("game/props/prop_" + gToStr(i) + ".png");
                }
                break;
            case 5:
                loadingtext[1] += "Buildings";
                for (int i = 0; i < buildingAmount; i++) {
                    img_buildings[i].loadImage("game/props/building_" + gToStr(i) + "_.png");
                    for (int j = 0; j < interiorAmounts[i]; j++) {
                        gLogi("interiorAmounts[" + gToStr(i) + "] : " + gToStr(interiorAmounts[i]));
                        img_interior[i][j].loadImage("game/props/building_" + gToStr(i) + "_" + gToStr(j) + ".png");
                        gLogi("img_interior[i" + gToStr(i) + "][j" + gToStr(j) + "].loadImage('game/props/building_" +
                              gToStr(i) + "_" + gToStr(j) + ".png");
                    }
                }
                break;
            case 6:
                loadingtext[1] += "NPCs";
                for (int i = 0; i < NPCAmount; i++) {
                    img_NPCs[i].loadImage("game/props/NPC_" + gToStr(i) + ".png");
                }
                break;
            case 7:
                for (int i = 0; i < 3; i++) {
                    img_characterBases[i].loadImage("game/charactertest/NPC_" + gToStr(i) + ".png");
                    loadingtext[1] += "game/charactertest/NPC_" + gToStr(i) + ".png";
                    gLogi("game/charactertest/NPC_" + gToStr(i) + ".png");
                }
                break;
            case 8:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < env_amounts[i]; j++) {
                        std::string prefix;
                        if (i == GRASS) {
                            prefix = "grass";
                        }
                        if (i == STONE) {
                            prefix = "rock";
                        }
                        if (i == TREE) {
                            prefix = "tree";
                        }
                        gLogi("img_ENVs[i][j].loadImage('game/props/env_'" + prefix + "'_'" + gToStr(j));

                        img_ENVs[i][j].loadImage("game/props/env_" + prefix + "_" + gToStr(j) + ".png");

                        gLogi("img_ENVs[i][j].getFilename() : " + gToStr(img_ENVs[i][j].getFilename()));
                    }
                }
                loadingtext[1] = "ENV props";
                gLogi("ENV props");
                break;
            case 9:

                imgs_Training_Ground[TrainingGrounds_BG].loadImage("game/props/TrainingGround_bg.png");
                imgs_Training_Ground[TrainingGrounds_Cati25].loadImage("game/props/TrainingGround_cati_25.png");
                imgs_Training_Ground[TrainingGrounds_Cati100].loadImage("game/props/TrainingGround_cati_100.png");
                imgs_Training_Ground[TrainingGrounds_Area1].loadImage("game/props/TrainingGround_area_1.png");
                imgs_Training_Ground[TrainingGrounds_Area2].loadImage("game/props/TrainingGround_area_2.png");
                imgs_Training_Ground[TrainingGrounds_Kukla].loadImage("game/props/TrainingGround_kukla_0.png");
                imgs_Training_Ground[TrainingGrounds_NPC].loadImage("game/props/TrainingGround_kukla_1.png");

                loadingtext[1] += "Training Grounds";

                /*
                tmpimg.loadImage("game/charactertest/base.png");
                for(int i = 0; i < 3; i++) { //RACE AMOUNT (ROCK-PAPER-SCISSORS)
                    for(int j = 0; j < 5; j++) { //TYPE AMOUNT (ARMOR-HELMET-WEAPON-EFFECT)
                        for(int k = 0; k < 2; k++) {
                            img_equipables[i][j].push_back(tmpimg);
                            gLogi("game/charactertest/base.png [" + gToStr(i) + "][" + gToStr(j) + "][" + gToStr(k) + "]");
                        }
                    }
                }
                gLogi("case 8 ended");
                */
                break;
            case 10:
                gLogi("case 10 start");
                loadingtext[1] = "Characterbar";
                img_characterbar[ChBar_ChBar].loadImage("GUI/Character_bar.png");
                img_characterbar[ChBar_Pr_BG].loadImage("GUI/CharacterProfileBG.png");
                img_characterbar[ChBar_Pr_P].loadImage("GUI/NPC_1_Portrait.png");
                img_characterbar[ChBar_Pr_B].loadImage("GUI/minimap_border.png");
                img_characterbar[ChBar_HPBar].loadImage("GUI/hpbar.png");
                img_characterbar[ChBar_HPBar_B].loadImage("GUI/hpbar_border.png");
                img_characterbar[ChBar_MPBar].loadImage("GUI/mpbar.png");
                img_characterbar[ChBar_MPBar_B].loadImage("GUI/mpbar_border.png");
                img_characterbar[ChBar_EXPBar].loadImage("GUI/expbar.png");
                img_characterbar[ChBar_EXPBar_B].loadImage("GUI/expbar_border.png");
                img_characterbar[ChBar_Coin].loadImage("GUI/Coin.png");
                img_characterbar[ChBar_Exp].loadImage("GUI/Exp.png");
                break;
            case 11:
                gLogi("case 11 start");
                loadingtext[1] = "Billboard";
                gLogi("Loading Billboard sources...");

                img_Buttons_Billboard[0].loadImage("game/props/billboard_paper_0.png");
                img_Buttons_Billboard[1].loadImage("game/props/billboard_paper_1.png");
                img_Buttons_Billboard[2].loadImage("game/props/billboard_paper_2.png");

                break;
            case 20:
                gLogi("case 20 start");
                loadingtext[1] = "initial variables";
                gLogi("SETTING INITIAL VARS");
                setInitialVariables();
                gLogi("Fonts loaded again");
                gLogi("INITIAL VARS HAS BEEN SETTED");
                gLogi("gamestatus : " + gToStr(game_status));
                gLogi("gamemap : " + gToStr(game_map));
                break;
            case 100:
                gLogi("case 100");
                game_status = PLAYING;
                game_map = IN_MAP;
                paused = false;
                gLogi("Game Loaded");
                break;
            default:
                gLogi("index: " + gToStr(index));
                loadingtext[1] += "...";
                break;
        }
}

void GameCanvas::setInitialVariables() {
	std::vector<gFont> tmpfonts;
	gLogi("setInitVars");
    globalscale = getWidth() / 1920.0f; // globalscale initilization
	gLogi("#DEBUG_test(39)");
		keystate = 0;
	gLogi("#DEBUG_test(40)");
		cx = getWidth() / 2; // baþlangýç pozisyonu x
		cy = getHeight() / 5; // baþlangýç pozisyonu y
		cdx = 0, cdy = 0;
	gLogi("#DEBUG_test(41)");

	/*
	camx = (img_background.getWidth()*globalscale - getWidth()) / 2;
	camy = 0;
	camx1 = 10; //getWidth() >> 3;
	camy1 = 10; //getHeight() >> 3;
	camx2 = getWidth() - 10; //(getWidth() * 7) >> 3;
	camy2 = getHeight() - 10; //(getHeight() * 7) >> 3;;
	 */

	camx = (img_background.getWidth()*globalscale - getWidth()) / 2;
	camy = 0;
	camx1 = 200; //getWidth() >> 3;
	camy1 = 150; //getHeight() >> 3;
	camx2 = getWidth() - 200 * globalscale; //(getWidth() * 7) >> 3;
	//camx2 = getWidth() - img_characterBases[0].getWidth() - 100; //(getWidth() * 7) >> 3;
	camy2 = getHeight() - 150 * globalscale; //(getHeight() * 7) >> 3;;
	//camy2 = getHeight() - img_characterBases[0].getWidth() - 100; //(getHeight() * 7) >> 3;;

	prev_camx = camx;
	prev_camy = camy;
	prev_camx1 = camx1;
	prev_camy1 = camy1;
	prev_camx2 = camx2;
	prev_camy2 = camy2;

    borderx1 = camx1;
    bordery1 = camy1;
    borderx2 = img_background.getWidth();
    bordery2 = img_background.getHeight();
    prev_borderx1 = borderx1;
    prev_bordery1 = bordery1;
    prev_borderx2 = borderx2;
    prev_bordery2 = bordery2;

	cspeed = 2.0f;
	crot = 0;
	mrot = 0;
	characterframenum = 0;

	gLogi("#DEBUG_test(43)");
	propXs[SPAWN_POINT] = cx + camx + (img_characterBases[0].getWidth()/2)*globalscale - (img_props[SPAWN_POINT].getWidth()/2)*globalscale;
	propYs[SPAWN_POINT] = cy + img_characterBases[0].getHeight()*globalscale - (img_props[SPAWN_POINT].getHeight()/2)*globalscale;

    buildingXs[BUILDING_PAPER] = cx + camx - img_buildings[BUILDING_PAPER].getWidth()*3 * globalscale;
	buildingYs[BUILDING_PAPER] = getHeight() / 20;
	buildingXs[BUILDING_ROCK] = cx + camx + img_buildings[BUILDING_PAPER].getWidth()*3 * globalscale;
	buildingYs[BUILDING_ROCK] = buildingYs[BUILDING_PAPER];
	buildingXs[BUILDING_SCISSORS] = buildingXs[BUILDING_ROCK];
	buildingYs[BUILDING_SCISSORS] = buildingYs[BUILDING_PAPER] + img_buildings[BUILDING_SCISSORS].getHeight()*1.25f;
	buildingXs[BUILDING_TRAINING] = buildingXs[BUILDING_PAPER];
	buildingYs[BUILDING_TRAINING] = buildingYs[BUILDING_SCISSORS];

	tg_coordinates[2] = (getWidth()  - imgs_Training_Ground[TrainingGrounds_Cati25].getWidth() )/2; 	// tg_cati_x
	tg_coordinates[3] = (getHeight() - imgs_Training_Ground[TrainingGrounds_Cati25].getHeight())/2; 	// tg_cati_y

	tg_coordinates[0] = (getWidth()  - (imgs_Training_Ground[TrainingGrounds_Cati25].getWidth() // tg_bg_x
            + (imgs_Training_Ground[TrainingGrounds_Cati25].getWidth()*globalscale
            - imgs_Training_Ground[TrainingGrounds_BG].getWidth()*globalscale)/2) )/2;
	tg_coordinates[1] = (getHeight() - ((imgs_Training_Ground[TrainingGrounds_BG].getHeight()
            + imgs_Training_Ground[TrainingGrounds_Cati25].getHeight())*globalscale)/2)/2 + 30;

	tg_coordinates[4] = (tg_coordinates[0] - 300*globalscale) + imgs_Training_Ground[1].getWidth();
			          //+ (getWidth()  - imgs_Training_Ground[3].getWidth())/2; 	// tg_area_x
	tg_coordinates[5] = (getHeight() - imgs_Training_Ground[3].getHeight())/2; 	// tg_area_y

	gLogi("#DEBUG_test(44)");

	createButton(
                    "Exit",
                    getWidth()/2,
                    getHeight()*9/10, 0, 255, 255, 255, font_BUTTON,
                    BUTTON_GUI,
                    false
                ); // index = Button_ExitBuilding = 0

	createButton(
                    "Enter Armory",
                    buildingXs[BUILDING_ROCK],
                    (buildingYs[BUILDING_ROCK] + (img_buildings[BUILDING_ROCK].getHeight() * globalscale)),
                    1, 255, 255, 255, font_BUTTON,
                    BUTTON_INGAME, false
                ); // index = Button_Armory = 1

	createButton(
                    "Enter Potionary",
                    buildingXs[BUILDING_PAPER],
                    (buildingYs[BUILDING_PAPER] + (img_buildings[BUILDING_PAPER].getHeight() * globalscale)),
                    1, 255, 255, 255, font_BUTTON,
                    BUTTON_INGAME, false
                ); // index = Button_Potionary = 2

	createButton(
                    "Enter Building",
                    buildingXs[BUILDING_SCISSORS],
                    (buildingYs[BUILDING_SCISSORS] + (img_buildings[BUILDING_SCISSORS].getHeight() * globalscale)),
                    1, 255, 255, 255, font_BUTTON,
                    BUTTON_INGAME, false
                ); // index = Button_Assassin = 3

	createButton(
                    "Enter Area",
                    buildingXs[BUILDING_TRAINING],
                    (buildingYs[BUILDING_TRAINING] + (img_buildings[BUILDING_TRAINING].getHeight() * globalscale)),
                    1, 255, 255, 255, font_BUTTON,
                    BUTTON_INGAME, false
                ); // index = Button_Assassin = 3

    createButton(
            "DEBUG",
            getWidth() - (img_button[0].getWidth()*globalscale)*1.2f,
            getHeight() - (img_button[0].getHeight()*globalscale)*1.2f, 0, 255, 55, 55, font_BUTTON,
            BUTTON_GUI, false
    ); // index = 4 // debug button

    createButton(
            "Quest Board",
            propXs[SPAWN_POINT] - (img_props[BILLBOARD].getWidth()*globalscale)*1.2f,
            propYs[SPAWN_POINT] - (img_props[BILLBOARD].getHeight()*globalscale)/1.5f,
            Button_Type_Billboard, 255, 255, 255, font_BUTTON,
            BUTTON_INGAME,
            true
    ); // index = 5 // Billboard



	//createButton("TestBtn1", getWidth()/2, getHeight()/2, 2, 255, 255, 0, font_BUTTON, BUTTON_INGAME);
	//createButton("TestBtn2", getWidth()/2, getHeight()/2, 3, 255, 255, 0, font_BUTTON, BUTTON_GUI);

	for(int i = 0; i < totalCharacterAmount; i++) {
		std::vector<gImage> newImgChar;
		img_characters.push_back(newImgChar);
		int characterIndex = characters[i][0];
		gLogi("characterIndex : " + gToStr(characterIndex));
		int race = characters[i][5];
		// character base
		if(DEBUG) {
			gLogi("img_characters[characterIndex(" +  gToStr(characterIndex)+ ")].push_back(img_characterBases[race(" +  gToStr(race)+ ")])");
			gLogi("img_characterBases[race].getFullPath : " + gToStr(img_characterBases[race].getFullPath()));
			gLogi("img_characterBases[race].getFilename : " + gToStr(img_characterBases[race].getFilename()));
		}
		img_characters[characterIndex].push_back(img_characterBases[race]); //cbase
		// character armor
		/*
		img_characters[characterIndex].push_back(img_equipables[race][ARMOR][characterEquipped[characterIndex][ARMOR]]);
		// character helmet
		img_characters[characterIndex].push_back(img_equipables[race][HELMET][characterEquipped[characterIndex][HELMET]]);
		// character weapon
		img_characters[characterIndex].push_back(img_equipables[race][WEAPON][characterEquipped[characterIndex][WEAPON]]);
		// character effect
		img_characters[characterIndex].push_back(img_equipables[race][EFFECT][characterEquipped[characterIndex][EFFECT]]);
	*/
	}
	if(DEBUG) {
		gLogi("path : " + gToStr(img_characters[playerIndex][0].getFullPath()));
		gLogi("filename : " + gToStr(img_characters[playerIndex][0].getFilename()));
	}
	characterframecounterlimit = 12 / cspeed;
	if(DEBUG) gLogi("#DEBUG_test(58)");


	if(DEBUG) {
		gLogi("buildingXs[BUILDING_ROCK], buildingYs[BUILDING_ROCK] : " + gToStr(buildingXs[BUILDING_ROCK]) + "," + gToStr(buildingYs[BUILDING_ROCK]));
		gLogi("buildingXs[SHOP_POTION], buildingYs[SHOP_POTION] : " + gToStr(buildingXs[BUILDING_PAPER]) + "," + gToStr(buildingYs[BUILDING_PAPER]));
		gLogi("\nimg_buildings[ARMORY].getWidth()/2, img_buildings[ARMORY].getHeight()/2\n" + gToStr(img_buildings[BUILDING_ROCK].getWidth()/2) + "," + gToStr(img_buildings[BUILDING_ROCK].getHeight()/2));
		gLogi("\nimg_buildings[POTION].getWidth()/2, img_buildings[POTION].getHeight()/2\n" + gToStr(img_buildings[BUILDING_PAPER].getWidth()/2) + "," + gToStr(img_buildings[BUILDING_PAPER].getHeight()/2));
	}


    // ##### BÝNA YARATMA #####

	std::string innerinfo;
	//inner info ve createbuilding icin ister .h headeri ister asagidaki yorum satirlarini okuyabilirsin.
	/* Building Structure :
	 * [index, index_outerimg, x, y, innerinfo1, innerinfo2, innerinfo...]
	 * (innerinfo0 : index_interiorImg)
	 * (innerinfo1 : index_NPC)
	 * (innerinfo2 : index_NPCx)
	 * (innerinfo3 : index_NPCy)
	 * (innerinfo4 : playerspawnx)
	 * (innerinfo5 : playerspawny)
	 * (innerinfo6 : prop_amount) //prop amount in this interior
	 * (innerinfo7+: [prop_index1, x1, y1], [prop_index2, x2, y2]...
	 *
	 *örnek:
	 * innerinfo = odaindexi, npcindexi, npcx, npcy, propmiktarý(0)
	 * innerinfo = "0," + gToStr(BUILDING_ROCK) + "," + gToStr(getWidth()/3) + ","+ gToStr(getHeight()/4) +",0";
	 *
	 */

	//createBuilding(int index, int index_outerImg, float _x, float _y, std::string innerinfos) {
	//createBuilding(bina indexi, bina resminin indexi, bina posX, bina posY, binanýn içi)
	//örnek:
	//createBuilding(BUILDING_SCISSORS, BUILDING_SCISSORS, buildingXs[BUILDING_SCISSORS], buildingYs[BUILDING_SCISSORS], innerinfo);


	//BUILDING_ROCK
	innerinfo = 	"0," +
					gToStr(BUILDING_ROCK) + "," +
					gToStr(getWidth()/3) + ","+
					gToStr(getHeight()/4) +"," +
					gToStr((1100 - img_characters[playerIndex][0].getWidth()/2)*globalscale) + "," +
					gToStr((660 - img_characters[playerIndex][0].getHeight()/2)*globalscale) +
					",0";
	createBuilding(	BUILDING_ROCK,
					BUILDING_ROCK,
					buildingXs[BUILDING_ROCK],
					buildingYs[BUILDING_ROCK],
					innerinfo);

	//BUILDING_PAPER
	innerinfo = 	"0," +
					gToStr(BUILDING_PAPER) + "," +
					gToStr(getWidth()/2) +
					",50,"  +
					gToStr((930 - img_characters[playerIndex][0].getWidth()/2)*globalscale) + "," +
					gToStr((600 - img_characters[playerIndex][0].getHeight()/2)*globalscale) +
					",0";
	createBuilding(	BUILDING_PAPER,
					BUILDING_PAPER,
					buildingXs[BUILDING_PAPER],
					buildingYs[BUILDING_PAPER],
					innerinfo);

	//BUILDING_SCISSORS
	innerinfo = 	"0," +
					gToStr(BUILDING_SCISSORS) + "," +
					gToStr(getWidth()/3) +
					",70," +
					gToStr((900 - img_characters[playerIndex][0].getWidth()/2)*globalscale) + "," +
					gToStr((821 - img_characters[playerIndex][0].getHeight()/2)*globalscale) +
					",0";
	createBuilding(	BUILDING_SCISSORS,
					BUILDING_SCISSORS,
					buildingXs[BUILDING_SCISSORS],
					buildingYs[BUILDING_SCISSORS],
					innerinfo);

	//BUILDING_TRAINING
	innerinfo = 	"0,-1,-1,-1,"+ //interior index //NPC Index //NPC x //NPC y
					gToStr((950 - img_characters[playerIndex][0].getWidth()/2)*globalscale) + "," +
					gToStr((500 - img_characters[playerIndex][0].getHeight()/2)*globalscale) + "," +
					"0";
	createBuilding(	BUILDING_TRAINING,
					BUILDING_TRAINING,
					buildingXs[BUILDING_TRAINING],
					buildingYs[BUILDING_TRAINING],
					innerinfo);

	gLogi("All buildings created successfully");
	gLogi("Start vegetation creation");

	mapBoundaries[0][X] = 50*globalscale;
	mapBoundaries[0][Y] = 100*globalscale;
	mapBoundaries[1][X] = img_background.getWidth() - 20*globalscale;
	mapBoundaries[1][Y] = (img_background.getHeight() - 100)*globalscale;

	float minX = mapBoundaries[0][X];
	float minY = mapBoundaries[0][Y];
	float maxX = mapBoundaries[1][X];
	float maxY = mapBoundaries[1][Y];

	/*Forest 1*/
	std::vector<std::vector<float>> forest1;

	std::vector<float> Frmin;
	std::vector<float> Frmax;

	Frmin.emplace_back(img_background.getWidth()*4/5);
	Frmin.emplace_back(img_background.getHeight()*1/4);
	Frmax.push_back(maxX);
	Frmax.push_back(maxY);

	forest1.push_back(Frmin);
	forest1.push_back(Frmax);
	/*Forest 1 End*/

	/*Forest 2*/
	std::vector<std::vector<float>> forest2;

	Frmin.clear();
	Frmax.clear();

	Frmin.push_back(minX);
	Frmin.push_back(minY);
	Frmax.emplace_back(img_background.getWidth()/5);
	Frmax.push_back(maxY);

	forest2.push_back(Frmin);
	forest2.push_back(Frmax);
	/*Forest 2 End*/

	forests.push_back(forest1);
	forests.push_back(forest2);

	gLogi("vegetation phase 1: (Stones and grasses)(all map)");
	//gLogi(" min : (" + gToStr(minX) + ", " + gToStr(minY) + ")");
	//gLogi(" max : (" + gToStr(maxX) + ", " + gToStr(maxY) + ")");
	for(int v_type = 0; v_type < 2; v_type++) {
		for(int v = 0; v < vegetationAmounts[v_type]; v++) {
			int x = minX + gRandom(maxX - minX);
			int y = minY + gRandom(maxY - minY);
			//gLogi("randomized x and y : " + gToStr(x) + ", " + gToStr(y));
			int design_type = v_type == GRASS ? gRandom(5.0f) : gRandom(3.0f);
			float sizeMultipler = 0.5f + gRandom(1.0f);
			//gLogi( "Size Multp : " + gToStr(sizeMultipler));
			createVegetation(v_type, design_type, x, y, sizeMultipler);
		}
	}
	gLogi("vegetation phase 1: Success!");

	gLogi("vegetation phase 2: (Trees)(Forests)");
	//gLogi(" min : (" + gToStr(minX) + ", " + gToStr(minY) + ")");
	//gLogi(" max : (" + gToStr(maxX) + ", " + gToStr(maxY) + ")");
	int v_type = TREE;
	for(auto & forest : forests) {
		for(int v = 0; v < vegetationAmounts[v_type]; v++) {
			int x = forest[0][X] + gRandom(forest[1][X] - forest[0][X]);
			int y = forest[0][Y] + gRandom(forest[1][Y] - forest[0][Y]);
			//gLogi("randomized x and y : " + gToStr(x) + ", " + gToStr(y));
			int design_type = gRandom(3.0f);
			float sizeMultipler = 0.5f + gRandom(1.0f);
			//gLogi( "Size Multp : " + gToStr(sizeMultipler));
			createVegetation(v_type, design_type, x, y, sizeMultipler);
		}
	}
	gLogi("vegetation phase 1: Success!");

	gLogi("All vegetation created successfully");


    //menu yaratma:

    std::vector<std::string> pauseMenu_buttons;
    pauseMenu_buttons.emplace_back("Continue");
    pauseMenu_buttons.emplace_back("Main Menu");
    pauseMenu_buttons.emplace_back("Exit");

    createMenu(
            pauseMenu_buttons,
            "- Pause Menu -"
    ); // index = 0 (Menu_Stop)

    std::vector<std::string> testHorizontalMenuButtons;
    testHorizontalMenuButtons.emplace_back("test Button1");
    testHorizontalMenuButtons.emplace_back("test Button2");

    createMenu(
            testHorizontalMenuButtons,
            "- Horizontal Menu -",
            MENU_CENTERED,
            MENU_CENTERED,
            MENU_HORIZONTAL,
            Button_Type_Large,
            false
    ); // index = 1 (Menu_Test)

    std::vector<std::string> billboardMenuButtons;
    // First Quest
    BB_paperXs[0] = 205 * globalscale;
    BB_paperYs[0] = 245 * globalscale;
    std::string detail = "Blacksmith need help with carrying new materials into his workshop."
                         "\nFor more detail, please go and visit him.";
    int reward = 10;
    std::string picked = "1";
    billboardMenuButtons.emplace_back("0-[Quest 0]-0-"+picked+"-"+detail+"-"+gToStr(reward));
    /* Quest Type Billboard ilanlarý :
     * - * Syntax : {i,-,Title,-,img_i,-,detail,-,reward,-,isPicked}
     * 0 *     Paper i : 0
     * 1 *       TITLE : [Quest 0],
     * 2 * image_index : 0,
     * 3 *      DETAIL : *detail
     * 4 *      REWARD : *reward
     * 5 * (üstteki ilk billboardMenuButtons elemanýnýn örneði)
    */

    // Second Quest
    BB_paperXs[1] = 630 * globalscale;
    BB_paperYs[1] = 405 * globalscale;
    detail = "The owner of Paperstation Magic Shop is now hiring for workers to renovate his shop.\n"
             "Please don't be shy when stopping by!";
    reward = 25;

    billboardMenuButtons.emplace_back("1-[Quest 1]-1-"+picked+"-"+detail+"-"+gToStr(reward));

    // First News
    BB_paperXs[2] = 1325 * globalscale;
    BB_paperYs[2] = 295 * globalscale;
    detail = "Assassins Sect is now recruiting new adventurers that passionate about assassination.\n"
             "If you are interested, please stop by to Sect Building.";
    billboardMenuButtons.emplace_back("2-[News 0]-2-"+picked+"-"+detail);
    /* Haber tipi billboard ilanlarý:
     * Syntax : {i,-,Title,-,img_i,-,detail,-,isPicked}
     *       TITLE : [News 0],
     * image_index : 2,
     *      DETAIL : *detail
     * (üstteki üçüncü billboardMenuButtons elemanýnýn örneði)
    */
    createMenu(
            billboardMenuButtons,
            "- Town Billboard - ",
            MENU_CENTERED,
            MENU_CENTERED,
            MENU_BILLBOARD, // hatamý buldum, menu_billboard'ýn arrayde karþýlýðý yok, yükle. todo
            Button_Type_Paper,
            false
            ); // index = 2 (Menu_Billboard)

            gLogi("menus[Menu_Billboard][MENU_BTN_COUNT] : " + menus[Menu_Billboard][MENU_BTN_COUNT] );

    std::vector<std::string> questPaperChoices;
    questPaperChoices.emplace_back("Put it back");
    questPaperChoices.emplace_back("Accept");

    createMenu(
            questPaperChoices,
            "MENU_PAPER",
            MENU_CENTERED,
            MENU_CENTERED,
            MENU_PAPER,
            Button_Type_Large,
            false
            ); // index = 3 (Menu_Paper)


    // Coordinates for ChBar_ChBar
    characterbar_xs[ChBar_ChBar] = 15*globalscale;
    characterbar_ys[ChBar_ChBar] = 35*globalscale;

    // Coordinates for ChBar_Pr_BG
    characterbar_xs[ChBar_Pr_BG] = characterbar_xs[ChBar_ChBar] + 40*globalscale;
    characterbar_ys[ChBar_Pr_BG] = characterbar_ys[ChBar_ChBar] + 20*globalscale;

    // Coordinates for ChBar_Pr_P
    characterbar_xs[ChBar_Pr_P] = characterbar_xs[ChBar_Pr_BG];
    characterbar_ys[ChBar_Pr_P] = characterbar_ys[ChBar_Pr_BG];

    // Coordinates for ChBar_Pr_B
    characterbar_xs[ChBar_Pr_B] = characterbar_xs[ChBar_ChBar] + 30*globalscale;
    characterbar_ys[ChBar_Pr_B] = characterbar_ys[ChBar_ChBar] + 10*globalscale;

    // Coordinates for ChBar_HPBar
    characterbar_xs[ChBar_HPBar] = characterbar_xs[ChBar_ChBar] + 205*globalscale;
    characterbar_ys[ChBar_HPBar] = characterbar_ys[ChBar_ChBar] + 35*globalscale;

    // Coordinates for ChBar_HPBar_B
    characterbar_xs[ChBar_HPBar_B] = characterbar_xs[ChBar_ChBar] + 185*globalscale;
    characterbar_ys[ChBar_HPBar_B] = characterbar_ys[ChBar_ChBar] + 20*globalscale;

    // Coordinates for ChBar_MPBar
    characterbar_xs[ChBar_MPBar] = characterbar_xs[ChBar_ChBar] + 220*globalscale;
    characterbar_ys[ChBar_MPBar] = characterbar_ys[ChBar_ChBar] + 65*globalscale;

    // Coordinates for ChBar_MPBar_B
    characterbar_xs[ChBar_MPBar_B] = characterbar_xs[ChBar_ChBar] + 205*globalscale;
    characterbar_ys[ChBar_MPBar_B] = characterbar_ys[ChBar_ChBar] + 50*globalscale;

    // Coordinates for ChBar_EXPBar
    characterbar_xs[ChBar_EXPBar] = characterbar_xs[ChBar_ChBar] + 270*globalscale;
    characterbar_ys[ChBar_EXPBar] = characterbar_ys[ChBar_ChBar] + 100*globalscale;

    // Coordinates for ChBar_EXPBar_B
    characterbar_xs[ChBar_EXPBar_B] = characterbar_xs[ChBar_ChBar] + 240*globalscale;
    characterbar_ys[ChBar_EXPBar_B] = characterbar_ys[ChBar_ChBar] + 85*globalscale;

    // Coordinates for ChBar_Coin
    characterbar_xs[ChBar_Coin] = characterbar_xs[ChBar_ChBar] + 340*globalscale;
    characterbar_ys[ChBar_Coin] = characterbar_ys[ChBar_ChBar] + 140*globalscale;

    for(int b = 0; b < buttons.size(); b++) {
        gLogi("Button_" + gToStr(b) + " - TYPE : " + gToStr(buttons[b][BTN_TYPE]));
        gLogi("\tButton X,X2 : " + gToStr(buttons[b][BTN_X]) + ", " + gToStr(buttons[b][BTN_X2]));
        gLogi("\tButton Y,Y2 : " + gToStr(buttons[b][BTN_Y]) + ", " + gToStr(buttons[b][BTN_Y2]));
    }
}

void GameCanvas::setCamera(int xi, int yi, int x1, int y1, int x2, int y2) {
	prev_camx = camx;
	prev_camy = camy;
	prev_camx1 = camx1;
	prev_camy1 = camy1;
	prev_camx2 = camx2;
	prev_camy2 = camy2;

	camx = xi;
	camy = yi;
	camx1 = x1;
	camy1 = y1;
	camx2 = x2;
	camy2 = y2;
	
	//(img_background.getWidth()*globalscale - getWidth()) / 2;
	gLogi("Camera setted : {" + gToStr(xi) + ", "
							  + gToStr(yi) + ", "
							  + gToStr(x1) + ", "
							  + gToStr(y1) + ", "
							  + gToStr(x2) + ", "
							  + gToStr(y2) + "}");
}

void GameCanvas::setCameraToPrevious() {
	camx = prev_camx;
	camy = prev_camy;
	camx1 = prev_camx1;
	camy1 = prev_camy1;
	camx2 = prev_camx2;
	camy2 = prev_camy2;
}

void GameCanvas::setMapBorders(float bx1, float by1, float bx2, float by2) {
	prev_borderx1 = borderx1;
	prev_bordery1 = bordery1;
	prev_borderx2 = borderx2;
	prev_bordery2 = bordery2;

	borderx1 = bx1;
	bordery1 = by1;
	borderx2 = bx2;
	bordery2 = by2;

	gLogi("Map Borders setted : {" + gToStr(bx1) + ", "
							  + gToStr(by1) + ", "
							  + gToStr(bx2) + ", "
							  + gToStr(by2) + "}");

}

void GameCanvas::setMapBordersToPrevious() {

	borderx1 = prev_borderx1;
	bordery1 = prev_bordery1;
	borderx2 = prev_borderx2;
	bordery2 = prev_bordery2;

}

/*[update] methods -> */
void GameCanvas::updateCharacter() {
	if ((keystate & KEY_W) != 0) {
		cdy = -1 * cspeed;
	}
	else if ((keystate & KEY_S) != 0) {
		cdy = 1 * cspeed;
	}

	// Ã‡aprazlara hareket edebilmek iÃ§in A ve D'yi W ve S'ten ayÄ±rdÄ±k.
	if ((keystate & KEY_A) != 0) {
		cdx = -1 * cspeed;
	}
	else if ((keystate & KEY_D) != 0) {
		cdx = 1 * cspeed;
	}

	//Character movement
	if ( cdx != 0.0f || cdy != 0.0f ) {
		characterframecounter++;
		characterframecounterlimit = 12 / cspeed;
		if ( characterframecounter >= characterframecounterlimit ) {
			if (characterframeno >= characterframenum){
				characterframeno = 0;
			}
			characterframecounter = 0;
		}
	}

/* Ateþ etme template'i, gelecekteki update'ler için altyapý.
	//root->soundcharacterwalk.stop();
	if(isFiring) {

		float mdx = std::sin(gDegToRad(mrot + muzzle_dangle)) * muzzle_distance - (bulletimage.getWidth() / 2);
		float mdy = -std::cos(gDegToRad(mrot + muzzle_dangle)) * muzzle_distance - (bulletimage.getHeight() / 2);
		float cbx = cx + (character[0].getWidth() / 2) + mdx + camx;
		float cby = cy + (character[0].getHeight() / 2) + mdy + camy;
		float dx = std::sin(gDegToRad(mrot)) * (bulletspeed);
		float dy = -std::cos(gDegToRad(mrot)) * (bulletspeed);
		float brot = mrot;
		int sender = BULLET_SENDER_CHARACTER;
		generateBullet(cbx, cby, dx, dy, brot, sender);
	}
*/

	cx += cdx;
	cy += cdy;
	updateCamera();
}

void GameCanvas::updateCamera() {

	if (cx < camx1 || cx + (img_characterBases[0].getWidth()*globalscale) > camx2) {
		cx -= cdx;
		camx += cdx;
		if (camx < 0) {
			camx = 0;
			camx1 = 0;
		}else {
			camx1 = borderx1;
		}
		if (camx + getWidth() > borderx2) {
			camx = borderx2 - getWidth();
			camx2 = getWidth(); //*globalscale
		} else {
			camx2 = getWidth() - 200 * globalscale; //(getWidth() * 7) >> 3;
			//camx2 = getWidth() - img_characterBases[0].getWidth()*globalscale - 100; //(getWidth() * 7) >> 3;
		}
	}
    //if (cy - (img_characterBases[0].getHeight()/2)*globalscale  < camy1 || cy + (img_characterBases[0].getHeight()/2)*globalscale > camy2) {
    //
	//if (cy - (img_characterBases[0].getHeight()/2)*globalscale < camy1 || cy + (img_characterBases[0].getHeight()/2)*globalscale > camy2) {
	if (cy < camy1 || cy + (img_characterBases[0].getHeight()*globalscale) > camy2) {
		cy -= cdy;
		camy += cdy;
		if (camy < 0) {
			camy = 0;
			camy1 = 0;
		}else {
			camy1 = bordery1; // >> 3;
		}
		if (camy + getHeight() > bordery2) {
			camy = bordery2 - getHeight();
			camy2 = getHeight(); //
		} else {
			//camy2 = getHeight() - img_characterBases[0].getHeight()*globalscale - 80; //(getHeight() * 7) >> 3;
			camy2 = getHeight() - 150 * globalscale; //(getHeight() * 7) >> 3;
		}
	}

//TODO BURADA KALDIN YANLIÞ YAPTIN BUNU DÜZELT. 05.11.2022
/*
	if (cx - img_characterBases[0].getWidth() > camx2) {
		int cfx = cx - camx2;
		cx -= cfx*1.2f;
		camx += cfx*1.2f;
	}

	if (cx < camx1) {
		int cfx = camx1 - cx;
		cx += cfx*1.2f;
		camx -= cfx*1.2f;
	}

	if (cy - img_characterBases[0].getHeight() > camy2) { //globalscale
		int cfy = cy - camy2;
		cy -= cfy*1.2f;
		camy += cfy*1.2f;
	}

	if (cy < camy1) {
		int cfy = camy1 - cy;
		cy += cfy*1.2f;
		camy -= cfy*1.2f;
	}
*/
	//delta degerlerini sifirliyoruz
	cdx = 0;
	cdy = 0;
}

void GameCanvas::updateMap() {

}

/* [draw] Methods -> */
void GameCanvas::drawLoad() {

	img_blueprint.draw(0, 0, globalscale);
	if(framecounter % 15 == 0) {
		switch(loadingtext[0].length()) {
		case 7: case 8: case 9:
			loadingtext[0] += ".";
			break;
		case 10:
			loadingtext[0] = "LOADING.";
			break;
		}
	}
	//int x = (getWidth() - font[font_LOAD1].getStringWidth(loadingtext[0]))/2;
	//	gLogi(gToStr(x));
	if(DEBUG) {
		fonts[font_LOAD1].drawText(loadingtext[0],  getWidth()/2 - 100, getHeight()*4/5);
		fonts[font_LOAD2].drawText(loadingtext[1],  getWidth()/2 - 200, getHeight()*4/5 + fontsizes[0]);
	}
}

void GameCanvas::drawGame() {
	//gLogi("568");
	drawMapBG();
	//gLogi("576");
	drawMid();
	//gLogi("572");
	drawCharacter();
	//gLogi("574");
	drawMapFG();
	//gLogi("576");
}

void GameCanvas::drawMapBG() {
	if(game_map == IN_MAP) { // draw main map background
		//img_background.draw(-20,-20, globalscale);
		//gLogi("drawMapBg::game_map == IN_MAP");
		//gLogi("drawing game_map : IN_MAP");
		img_background.drawSub(0, 0, getWidth(), getHeight(), camx, camy, getWidth(), getHeight());
	}
	if(game_map == IN_BUILDING){ // draw building background

		if(buildingPressed == BUILDING_TRAINING) {
			img_background.drawSub(-50, -50, getWidth()+50, getHeight()+50, camx, camy, getWidth(), getHeight());
            imgs_Training_Ground[3].draw(tg_coordinates[4] - camx, tg_coordinates[5] - camy);
            imgs_Training_Ground[0].draw(tg_coordinates[0] - camx, tg_coordinates[1] - camy);
		}
		else {
			//gLogi("img_interior[buildingPressed(" + gToStr(buildingPressed) + ")][currentInterior[0](" + gToStr(currentInterior[0]) + ")]");
			//gLogi("img_interior[" + gToStr(buildingPressed) + "][" + gToStr(currentInterior[0]) + "]].getfilename : " + gToStr(img_interior[buildingPressed][currentInterior[0]] .getFilename()));
			//gLogi("drawMapBg::game_map == IN_BUILDING");

			gLogi("drawing : img_interior[buildingPressed(" + gToStr(buildingPressed) + ")][currentInterior[0](" + gToStr(currentInterior[0]) + ")]\n " + gToStr(img_interior[buildingPressed][currentInterior[0]].getFilename()));


			img_interior[buildingPressed][currentInterior[0]].draw(
					(getWidth() - img_interior[buildingPressed][currentInterior[0]].getWidth() * globalscale) / 2,
					(getHeight() - img_interior[buildingPressed][currentInterior[0]].getHeight()* globalscale) / 2 ,
					globalscale);
			gLogi("drawed interior");
		}
	}
	//img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);
}

void GameCanvas::createVegetation(int veg_type, int design_type, float x, float y, float sizeMultiplier) {
	gLogi("createVegetation() is working");
	std::vector<float> tmpVeg;
	tmpVeg.push_back(x);
	tmpVeg.push_back(y);
	tmpVeg.push_back(design_type);
	tmpVeg.push_back(sizeMultiplier);

	gLogi("tmpVeg created successfully!");
	vegetations[veg_type].push_back(tmpVeg);
	gLogi("createVegetation() is worked successfully!");
}

void GameCanvas::drawVegetation() {
	int c = 255/1.1f;
	// c = 	color value, minimum 255/1.1f oranýnda genel temadan daha koyu olmasýný saðlýyor

	//renderer->setColor(c,c,c,255);

	for (int v_type = 0; v_type < vegetations.size(); v_type++) {

		for (int v = 0; v < vegetations[v_type].size(); v++) {

			//gLogi("drawing veg [" + gToStr(v_type) + "][" + gToStr(v) + "]");
			//gToInt(gToStr(vegetations[v_type][v][VEG_DES_TYPE]))
			float dx = (img_ENVs[v_type][vegetations[v_type][v][2]].getWidth()*vegetations[v_type][v][3] * globalscale)/2;
			float dy = (img_ENVs[v_type][vegetations[v_type][v][2]].getHeight()*vegetations[v_type][v][3] * globalscale)/2;

			img_ENVs[v_type][vegetations[v_type][v][2]].drawDetailed(
				vegetations[v_type][v][X] - camx - dx,
				vegetations[v_type][v][Y] - camy - dy,
				vegetations[v_type][v][3] * globalscale,
				c,c,c
			);
			if(DEBUG) {
				fonts[font_INGAME].drawText(
					"Type: " + gToStr(v_type) + "|" + gToStr(vegetations[v_type][v][VEG_DES_TYPE]),
					vegetations[v_type][v][X] - dx - camx,
					(vegetations[v_type][v][Y] + img_ENVs[v_type][vegetations[v_type][v][VEG_DES_TYPE]].getHeight()* vegetations[v_type][v][3]*globalscale) +5 - camy - dy,
					128, 255, 128
				);
			}
		}
	}
	//renderer->setColor(255,255,255,255);


/*
	img_ENVs[GRASS][0].draw(900 - camx, 1050 - camy);
	img_ENVs[TREE][0].draw(1100 - camx, 1050 - camy);
	img_ENVs[STONE][0].draw(1300 - camx, 1050 - camy);

	fonts[font_LOAD1].drawText(
						"TEST AREA : ",
						900 - camx,
						1000 - camy,
						128, 220, 255
					);
*/
/*
	img_ENVs[GRASS][2].draw(10 - camx, 10 - camy, globalscale);
	img_ENVs[GRASS][1].draw(15 - camx, 15 - camy, globalscale);
	img_ENVs[GRASS][3].draw(20 - camx, 20- camy, globalscale);

	img_ENVs[TREE][2].draw(1000 - camx, 1050 - camy, globalscale);
	img_ENVs[TREE][0].draw(900 - camx, 1050 - camy, globalscale);
	img_ENVs[TREE][1].draw(800 - camx, 1050 - camy, globalscale);

	img_ENVs[STONE][2].draw(2000 - camx, 1050 - camy, globalscale);
	img_ENVs[STONE][0].draw(3000 - camx, 1050 - camy, globalscale);
	img_ENVs[STONE][1].draw(2500 - camx, 1050 - camy, globalscale);

	//gLogi("img_ENVs[0][0].getFileName " + gToStr(img_ENVs[GRASS][0].getFilename()));
*/
}
/*
std::vector<std::vector<float>> GameCanvas::scatterRandPointsOnGeometry(std::vector<float[2]> boundaries, int pointAmount) {
	std::vector<std::vector<float>> points;
	float minX = boundaries[0][0];
	float maxX = boundaries[1][0];
	float minY = boundaries[0][1];
	float maxY = boundaries[1][1];

	for (int i = 0; i < pointAmount; i++) {
		std::vector<float> tmpCoord;
		tmpCoord.push_back(minX + gRandom(maxX - minX));
		tmpCoord.push_back(minY + gRandom(maxY - minY));
		points.push_back(tmpCoord);
	}

	return points;
}
*/

void GameCanvas::drawMid() {
	//healer
	if(game_map == IN_MAP) { // draw props and buildings
        drawVegetation();
        drawProps();
        drawBuildings();

		for(int buildingIndex = 0; buildingIndex < buildingAmount; buildingIndex++) {
			//img_buildings[buildingIndex].draw(buildingXs[buildingIndex] - camx, buildingYs[buildingIndex] - camy, globalscale);
			int initx = (img_buildings[buildingIndex].getWidth()/2)*globalscale;
			int _x = buildingXs[buildingIndex] - camx + initx;
			int _y = buildingYs[buildingIndex] - 10*globalscale - camy;

			if(buildingIndex == BUILDING_ROCK) {
				fonts[font_INGAME].drawText("ARMORY SHOP", _x - fonts[font_INGAME].getStringWidth("ARMORY SHOP")/2 , _y, 255, 220, 220);
			} else if (buildingIndex == BUILDING_PAPER) {
				fonts[font_INGAME].drawText("POTION SHOP", _x - fonts[font_INGAME].getStringWidth("POTION SHOP")/2, _y, 255, 220, 220);
			} else if (buildingIndex == BUILDING_SCISSORS) {
				fonts[font_INGAME].drawText("ASSASSINATION BUILDING", _x - fonts[font_INGAME].getStringWidth("ASSASSINATION BUILDING")/2, _y, 255, 220, 220);
			} else if (buildingIndex == BUILDING_TRAINING) {
				fonts[font_INGAME].drawText("TRAINING GROUNDS", _x - fonts[font_INGAME].getStringWidth("TRAINING GROUNDS")/2, _y, 255, 220, 220);
			}

        }

	}

	if(game_map == IN_BUILDING){ // draw NPC
		if(buildingPressed == BUILDING_TRAINING) {
            int x = tg_coordinates[4]
                    + (100*globalscale)
                    - camx;
            int y = tg_coordinates[5]
                    + (imgs_Training_Ground[5].getHeight()*globalscale*1.2f)
                    - camy;
            imgs_Training_Ground[5].draw(x, y);
            x = tg_coordinates[4]
              + (imgs_Training_Ground[3].getWidth()
              - (imgs_Training_Ground[6].getWidth() + 100))
              * globalscale
              - camx;
            y = tg_coordinates[5] + imgs_Training_Ground[3].getHeight()*globalscale
              - (imgs_Training_Ground[6].getHeight()*globalscale*1.2f)
              - camy;
            imgs_Training_Ground[6].draw(x, y);

		}
		else {
			if (currentInterior[1] != -1) { //check npc index
				gLogi("NPC : BUILDING PRESSED : " + gToStr(buildingPressed));

				gLogi("img_NPCs[currentInterior[1](" + gToStr(currentInterior[1]) + ")]");
				gLogi("img_NPCs[" + gToStr(currentInterior[1]) + "].getfilename : " + gToStr(img_NPCs[currentInterior[1]].getFilename()));

				img_NPCs[currentInterior[1]].draw(currentInterior[2], currentInterior[3], globalscale);
			}
		}
	}


	//INGAME butonlarý burada çizdiriyoruz, GUI butonlarý ise drawGUI/drawButtons'ta çizdiriyoruz
	for(int i = 0; i < buttons.size(); i++) {
		if(buttons[i][10] == 1) { //visibility check
			if (buttons[i][9] == BUTTON_INGAME) {
				drawButton(i);
			}
		}
	}
}

void GameCanvas::drawProps() {
    img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT] - camx, propYs[SPAWN_POINT] - camy, globalscale);
}

void GameCanvas::drawCharacter() {
/*
	font[font_INGAME].drawText("Player(ID:0)", cx + (font[font_INGAME].getStringWidth("Player(ID:0)")/2), cy - fontsizes[font_INGAME]*3.6f - (img_characters[playerIndex][0].getHeight()/2));
	font[font_INGAME].drawText("cx:"+gToStr(cx)+"|cy:"+gToStr(cy), cx + (font[font_INGAME].getStringWidth("cx:"+gToStr(cx)+"|cy:"+gToStr(cy))/2), cy - fontsizes[font_INGAME]*2.4f - (img_characters[playerIndex][0].getHeight()/2),20,255,20);
	font[font_INGAME].drawText("RaceIndex:"+gToStr(characters[playerIndex][5]), cx + (font[font_INGAME].getStringWidth("RaceIndex:2")/2), cy - fontsizes[font_INGAME]*1.2f - (img_characters[playerIndex][0].getHeight()/2));
*/
	/*
	std::string str;
	int initx = (img_characters[playerIndex][0].getWidth()/2)* globalscale ;
	str = "Player(ID:" + gToStr(playerIndex) + ")";
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*4.5);
	str = "RaceIndex:"+gToStr(characters[playerIndex][5]);
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*3);
	str = "cx+camx:"+gToStr(cx+camx)+"|cy+camy:"+gToStr(cy+camy);
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*1.5,20,255,20);

	img_characters[playerIndex][0].draw(cx, cy, globalscale); //void draw(int x, int y, int w, int h, float rotate);
*/

	std::string str;
	int initx = (img_characterBases[0].getWidth()/2)* globalscale * scalelevels[characterscalelevel];
	if(DEBUG) {
		str = "Player(ID:" + gToStr(playerIndex) + ")";
		fonts[font_INGAME].drawText(str, cx - (fonts[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*4.5);
		str = "RaceIndex:"+gToStr(characters[playerIndex][5]);
		fonts[font_INGAME].drawText(str, cx - (fonts[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*3);
		str = "cx+camx:"+gToStr(cx+camx)+"|cy+camy:"+gToStr(cy+camy);
		fonts[font_INGAME].drawText(str, cx - (fonts[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*1.5,20,255,20);
	}
	//gLogi("drawcharacter(7)");
	//gLogi("playerIndex : " + gToStr(playerIndex));
	//gLogi("path : " + gToStr(img_characters[playerIndex][0].getFullPath()));
	//gLogi("filename : " + gToStr(img_characters[playerIndex][0].getFilename()));
	//gLogi("drawcharacter(8)");
	img_characters[playerIndex][0].draw(cx, cy, globalscale * scalelevels[characterscalelevel]); //void draw(int x, int y, int w, int h, float rotate);
	//gLogi("drawcharacter succes");
}

void GameCanvas::drawMapFG() {

	if(game_map == IN_BUILDING){
		if(buildingPressed == Button_Training-1) {

			if(checkCollision(cx + camx + (img_characters[playerIndex][0].getWidth()/2),
                              cy + camy + (img_characters[playerIndex][0].getHeight()/2 * globalscale),
						      cx + camx + (img_characters[playerIndex][0].getWidth()/2),
                              cy + camy + (img_characters[playerIndex][0].getHeight()/2 * globalscale),
							  tg_coordinates[2] + 335*globalscale,
                              tg_coordinates[3] + 335*globalscale,
                              tg_coordinates[2] + 630*globalscale,
                              tg_coordinates[3] + 660*globalscale)
                              ) {
				gLogi("middle");
				imgs_Training_Ground[2].draw(tg_coordinates[2] - camx, tg_coordinates[3] - camy);
			}
			else if (cx+camx + (img_characters[playerIndex][0].getWidth()/2) < tg_coordinates[2] + 900*globalscale
                 && cy + camy + (img_characters[playerIndex][0].getHeight()/2 * globalscale) < tg_coordinates[3] + 860*globalscale ){
				gLogi("border");
				imgs_Training_Ground[1].draw(tg_coordinates[2] - camx, tg_coordinates[3] - camy);
			}
			else {
				gLogi("Outside");
				imgs_Training_Ground[2].draw(tg_coordinates[2] - camx, tg_coordinates[3] - camy);
			}
		}

		else {
			gLogi("before drawing props");
			gLogi("currentIntreior[6] : " + gToStr(currentInterior[6]));
			if(currentInterior[6] > 0) {
				int index = 7;
				for(int i = 0; i < currentInterior[6]; i++) {
					img_props[currentInterior[i + index]].draw(currentInterior[i + index + 1], currentInterior[i + index + 2]);
					index += 2;
				}
				/*
				 * bu for dongusunu bu sekilde kurduk cunku :
				 * currentInterior (.h'deki 70. satýrda ornekteki adiyla 'innerinfo')
				 * bize proplari vermeye  5. index'te basliyor,  6. index X,  7. index Y
				 * sonraki prop icin ise  8. index prop_imgInd,  9. index X, 10. index Y
				 * sonraki prop icin ise 11. index prop_imgInd, 12. index X, 13. index Y
				 * dolayisiyla for dongusu currentInterior[4](prop_amount)'a gore 1er
				 * ilerlerken, x ve y'nin yarattigi 2 indexlik farki bu 'index' degiskeni
				 * kapatmis oluyor index += 2; satiri ile.
				 */
			}
			gLogi("after drawing props");
		}
	}

}

void GameCanvas::drawGUI() {
    drawCharacterBar();
    drawMenus();
    drawButtons();
}

void GameCanvas::keyPressed(int key) {
	//gLogi("GameCanvas") << "keyPressed:" << key;
	int pressed = 0;
	switch (key){
		case 87:
			pressed = KEY_W;
			gLogi("W");
			break;
		case 65:
			pressed = KEY_A;
			break;
		case 83:
			pressed = KEY_S;
			break;
		case 68:
			pressed = KEY_D;
			break;
		//case 256:
		//	paused != paused;//
			/*if(game_status == PAUSED) {
				game_status = PLAYING;
			}
			else if (game_status == PLAYING) {
				game_status = PAUSED;
			}*/
			//break;
		case 340:
				cspeed += 4.0f; // Shift tusuna basildiginda karakter hizini artiriyoruz.
			break;
		default:
			break;
	}
	keystate |= pressed; // bitwise '+='

}

void GameCanvas::keyReleased(int key) {
	gLogi("GameCanvas") << "keyReleased:" << key;
	int released = 0;
	switch (key){
		case 87:
			released = KEY_W;
			break;
		case 65:
			released = KEY_A;
			break;
		case 83:
			released = KEY_S;
			break;
		case 68:
			released = KEY_D;
			break;
		case 256:
			paused = !paused;
            toggleVisMenu(0);
            /*üstteki ile alttaki birebir ayný çalýþýyor
            menus[0][MENU_VISIBILITY] = paused? "1" : "0";
            for(int b = 0; b < gToInt(menus[0][MENU_BTN_COUNT]); b++) {
                int button_index = gToInt(gSplitString(menus[0][MENU_BTN_COUNT+1+b], ".")[0]);
                buttons[button_index][BTN_VIS] = paused;
            }
             */
			break;
		case 340:
			cspeed = 2.0f;
			break;
		default:
			break;
	}
	keystate &= ~released; // bitwise'da '-='
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
	mousex = x; //A ve D'ye basildiginda mouse hareket ettirmeye gerek duymadan etrafÃ½ndan donmek icin...
	mousey = y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
	mousex = x;
	mousey = y;
	clickx = mousex;
	clicky = mousey;
}

void GameCanvas::mousePressed(int x, int y, int button) {
	mouseHold = true;
	mousex = x;
	mousey = y;
	clickx = mousex;
	clicky = mousey;
	crot = (mousex < cx) ? -1 : 1;
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	mouseHold = false;
	mousex = x;
	mousey = y;
	crot = (mousex < cx) ? -1 : 1;

	mouseHoldedFor_frames = 0;
	mouseHoldedFor_seconds = 0;

	for(int b = 0; b < buttons.size(); b++) {
		if(buttons[b][10] == 1) {
			gLogi("Visible button" + gToStr(b));
			if(buttons[b][9] == BUTTON_INGAME) {
				if(x > buttons[b][0] - camx && y > buttons[b][1] - camy && x < buttons[b][7] - camx && y < buttons[b][8] - camy) {
					buttonPressed = b;
					gLogi("buttonPressed = " + gToStr(b));
				}
			}
			if(buttons[b][9] == BUTTON_GUI) {
				if(x > buttons[b][0] && y > buttons[b][1] && x < buttons[b][7] && y < buttons[b][8]) {
					buttonPressed = b;
					gLogi("buttonPressed = " + gToStr(b));
				}
			}
		}
	}

    gLogi("Buttons_on_paper size : " + gToStr(Buttons_on_Paper.size()));
    gLogi("Buttons_on_paper 0 : " + gToStr(Buttons_on_Paper[0]));
    gLogi("Buttons_on_paper 1 : " + gToStr(Buttons_on_Paper[1]));
	//gLogi("building.size " + gToStr(buildings.size()));
	// TODO: burada kaldin binalari dumduz cizdirdigin icin calismiyor, onun yerine olusturdugun createBuilding methodunu kullan!
	// TODO update: halledildi.
	/*//binalara týklayýp girme (bunun yerine her bina için buton koyduk)
	for(int b = 0; b < buildings.size(); b++) {
		if(x + camx > gToInt(buildings[b][2])&&
		   y + camy > gToInt(buildings[b][3]) &&
		   x + camx < (gToInt(buildings[b][2]) + img_buildings[gToInt(buildings[b][1])].getWidth()*globalscale) &&
		   y + camy < (gToInt(buildings[b][3])) + img_buildings[gToInt(buildings[b][1])].getHeight()*globalscale){
			buildingPressed = b;
			gLogi("buildingPressed = " + gToStr(b));
		}
	}
	*/
}

void GameCanvas::mouseScrolled(int x, int y) {
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

bool GameCanvas::checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2) {
	if(xLeft1 < xRight2 && xRight1 > xLeft2 && yBottom1 > yUp2 && yUp1 < yBottom2) {
		return true;
	}
	return false;
}

void::GameCanvas::drawCharacterBar() {
    for(int cb = 0; cb < img_characterbar.size()-1; cb++) { //son eleman olan Exp'i çizdirmek istemiyoruz.
        img_characterbar[cb].draw(characterbar_xs[cb], characterbar_ys[cb], globalscale);
    }
/* Üstteki for loop ayný iþi görüyor.
    img_characterbar[ChBar_ChBar].draw(characterbar_xs[ChBar_ChBar],
                                       characterbar_ys[ChBar_ChBar],
                                     globalscale);
    img_characterbar[ChBar_Pr_BG].draw(characterbar_xs[ChBar_Pr_BG],
                                       characterbar_ys[ChBar_Pr_BG],
                                     globalscale);
    img_characterbar[ChBar_Pr_P].draw(characterbar_xs[ChBar_Pr_P],
                                      characterbar_ys[ChBar_Pr_P],
                                     globalscale);
    img_characterbar[ChBar_Pr_B].draw(characterbar_xs[ChBar_Pr_B],
                                      characterbar_ys[ChBar_Pr_B],
                                     globalscale);
    img_characterbar[ChBar_HPBar].draw(characterbar_xs[ChBar_HPBar],
                                       characterbar_ys[ChBar_HPBar],
                                     globalscale);
    img_characterbar[ChBar_HPBar_B].draw(characterbar_xs[ChBar_HPBar_B],
                                         characterbar_ys[ChBar_HPBar_B],
                                     globalscale);
    img_characterbar[ChBar_MPBar].draw(characterbar_xs[ChBar_MPBar],
                                       characterbar_ys[ChBar_MPBar],
                                     globalscale);
    img_characterbar[ChBar_MPBar_B].draw(characterbar_xs[ChBar_MPBar_B],
                                         characterbar_ys[ChBar_MPBar_B],
                                     globalscale);
    img_characterbar[ChBar_EXPBar].draw(characterbar_xs[ChBar_EXPBar],
                                        characterbar_ys[ChBar_EXPBar],
                                     globalscale);
    img_characterbar[ChBar_EXPBar_B].draw(characterbar_xs[ChBar_EXPBar_B],
                                          characterbar_ys[ChBar_EXPBar_B],
                                     globalscale);
    img_characterbar[ChBar_Coin].draw(characterbar_xs[ChBar_Coin],
                                      characterbar_ys[ChBar_Coin],
                                     globalscale);
    */
}

void GameCanvas::createButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype, int btnLocation, bool visibility) {
	buttonTexts.push_back(btntext);
	std::vector<int> tmpbtn;
	tmpbtn.push_back(btnx);				// btn[0] -> x
	tmpbtn.push_back(btny);				// btn[1] -> y
	tmpbtn.push_back(btntype);			// btn[2] -> btntype (btnimg[btntype])
	tmpbtn.push_back(btnR);				// btn[3] -> R (Text.setColor(R,g,b))
	tmpbtn.push_back(btnG);				// btn[4] -> G (Text.setColor(r,G,b))
	tmpbtn.push_back(btnB);				// btn[5] -> B (Text.setColor(r,g,B))
	tmpbtn.push_back(texttype);			// btn[6] -> text font (fonts[texttype])
	tmpbtn.push_back(btnx + img_button[btntype].getWidth());	// btn[7] -> btnX2
	tmpbtn.push_back(btny + img_button[btntype].getHeight());	// btn[8] -> btnY2
	tmpbtn.push_back(btnLocation);		// btn[9] -> btnCanvas
	if(visibility) {
		tmpbtn.emplace_back(1);
	} else {
		tmpbtn.emplace_back(0);
	}

	buttons.push_back(tmpbtn);
}

void GameCanvas::updateButtons() {

	for(int b = 0; b < buttons.size(); b++) {
		if(buttons[b][BTN_LOC] == BUTTON_INGAME) {
            if (game_map == IN_MAP) {
                if ( cx > buttons[b][BTN_X] - camx - 100 * globalscale
                     && cy > buttons[b][BTN_Y] - camy - 100 * globalscale
                     && cx < buttons[b][BTN_X2] - camx + 50 * globalscale
                     && cy < buttons[b][BTN_Y2] - camy * globalscale) { //zortladý çöz bunu
                        gLogi("Character is near to the " + gToStr(b) + ". button");
                        if (buttons[b][BTN_VIS] == 0) {
                            buttons[b][BTN_VIS] = 1;
                        }
                } else if (buttons[b][BTN_TYPE] != Button_Type_Billboard && buttons[b][BTN_VIS] == 1) {
                    buttons[b][BTN_VIS] = 0;
                }
                if( buttons[b][BTN_TYPE] == Button_Type_Billboard ) {
                    buttons[b][BTN_VIS] = 1;
                }
            } else if (buttons[b][BTN_VIS] == 1) {
                buttons[b][BTN_VIS] = 0;
            }
        }
	}
}

void GameCanvas::drawButton(int btn_index) {
    std::string btntext =  buttonTexts[btn_index];
    int btnx    = buttons[btn_index][BTN_X];
    int btny    = buttons[btn_index][BTN_Y];
    int btntype = buttons[btn_index][BTN_TYPE];
    int btnR    = buttons[btn_index][BTN_R];
    int btnG    = buttons[btn_index][BTN_G];
    int btnB    = buttons[btn_index][BTN_B];
    int texttype = buttons[btn_index][BTN_TEXTTYPE];
    if(buttons[btn_index][BTN_LOC] == BUTTON_INGAME) {
        btnx = btnx - camx;
        btny = btny - camy;
    }

    if(btntype != Button_Type_Paper) {
        //gLogi("MENUCANVAS::DRAWBUTTON -> START");
        img_button[btntype].draw(btnx, btny, globalscale);
        //gLogi("draw emptybtns : [PASSED]");
        fonts[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale) -
                                                   fonts[texttype].getStringWidth(btntext)) / 2),
                                 btny + (img_button[btntype].getHeight() * globalscale) / 2 + 3, btnR / 3, btnG / 3,
                                 btnB / 3);
        //gLogi("draw savetextshadow : [PASSED]");
        fonts[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale) -
                                                   fonts[texttype].getStringWidth(btntext)) / 2) - 1,
                                 btny + (img_button[btntype].getHeight() * globalscale) / 2 + 1, btnR, btnG, btnB);
        //gLogi("draw savetext : [PASSED]");
    }

    else if (btntype == Button_Type_Paper) {
        //gLogi("btntype == Button_Type_Billboard");
        // todo burada kaldýn en son hata bu
        //gLogi("btn_index : " + gToStr(btn_index));
        //gLogi("btntext : " + btntext);
        std::vector<std::string> rawData = gSplitString(btntext,"-");
        //gLogi("rawdata created!");
        int paperIndex = gToInt(rawData[BB_P_Index]);
        //gLogi("paperIndex created!");
        //gLogi("rawData[2] : " + gToStr(rawData[2]));
        int type = gToInt(rawData[BB_P_ImgIndex]);
        //gLogi("type created!");
        //gLogi(gToStr(paperIndex) + ". Paper(" + rawData[BB_P_Title] + ")'s img -> " + rawData[2]);

        /* Draw Background (Papers) */
        img_Buttons_Billboard[type].draw(BB_paperXs[paperIndex], BB_paperYs[paperIndex], globalscale);

       if (DEBUG) {
           gLogi("Paper Ý : " + gToStr(paperIndex));
           gLogi("PaperX : " + gToStr(BB_paperXs[paperIndex]));
           gLogi("PaperY : " + gToStr(BB_paperYs[paperIndex]));
           gLogi("draw successful!");
       }

       btnx = BB_paperXs[paperIndex];
       btny = BB_paperYs[paperIndex];

        /* Draw Title */
        std::string title = rawData[BB_P_Title];
        int testx = btnx + (((img_Buttons_Billboard[type].getWidth() * globalscale) -
                             fonts[texttype].getStringWidth(title)) / 2);
        int testy = btny + (img_Buttons_Billboard[type].getHeight() * globalscale)/5;
        fonts[texttype].drawText(title, testx,
                                 testy, btnR, btnG, btnB);

        //gLogi("Paper (" + title + ") is drawing at -> " + gToStr(btnx) + ", " + gToStr(btny));
       // gLogi("Title drawing at -> " + gToStr(testx) + ", " + gToStr(testy));
    }

    /*
    if(btntype == Button_Type_Billboard) {
        bill
        //örn : [QUEST 1]-0-details-Reward
        std::vector<std::string> rawData = gSplitString(btntext,"-");
        /* [0] : [QUEST 1]
         * [1] : 0
         * [2] : details
         * [3] : reward
         */
/*
        img_Buttons_Billboard[gToInt(rawData[BB_P_ImgIndex])].draw(BB_paperXs[BB_P_Index],
                                                                           BB_paperYs[BB_P_Index],
                                                                        globalscale);

    }
    */
}

void GameCanvas::drawButtons() {

	for(int i = 0; i < buttons.size(); i++) {
		if(buttons[i][BTN_VIS] == 1) { //visibility check
			if(buttons[i][BTN_LOC] == BUTTON_GUI) {
				drawButton(i);
			}
			/* bu playerin vs üstünü kapatmasýn diye bunu drawGame'de çizdiricez
			else if (buttons[i][9] == BUTTON_INGAME) {
				drawButton(buttonTexts[i], buttons[i][0] - camx, buttons[i][1] - camy, buttons[i][2], buttons[i][3], buttons[i][4], buttons[i][5], buttons[i][6]);
			}
			*/
		}
	}

	if(game_map == IN_BUILDING) {
		//gLogi("drawing exitbuilding on : " + gToStr(buttons[Button_ExitBuilding][0]) + ""  + gToStr(buttons[Button_ExitBuilding][1]));
		//drawButton(Button_ExitBuilding);
	}

}

void GameCanvas::listener() {
	if(buttonPressed != -1) {

		if (buttonPressed == Button_ExitBuilding) {
            buttons[5][BTN_VIS] = 0; //DEBUG button
           if(menus[Menu_Test][MENU_VISIBILITY] == "1") {
               hideMenu(Menu_Test);
           }
            if(menus[Menu_Billboard][MENU_VISIBILITY] == "1") {
                gLogi("hide bilboard by pressing exit menu");
                hideMenu(Menu_Billboard);
            }

            if(menus[Menu_Paper][MENU_VISIBILITY] == "1") {
                buttons[Button_ExitBuilding][10] = 0;
            }

			gLogi("Button_ExitBuilding Game_map = " + gToStr(game_map));
			gLogi("Button Pressed : " + gToStr(buttonPressed));
			gLogi("debug 954");

			characterscalelevel = 2;
			gLogi("debug 957");
            if(game_map != IN_MAP) {
                setCamera(
                        gToInt(buildings[buildingPressed][2]) - getWidth() / 2,
                        prev_camy,
                        prev_camx1,
                        prev_camy1,
                        prev_camx2,
                        prev_camy2
                );

                gLogi("SetCamera Successfull - 1741");
                setMapBordersToPrevious();
                gLogi("setMapBordersToPrevious Successfull - 1743");

                camx = gToInt(buildings[buildingPressed][2]) - getWidth() / 2;
                gLogi("camx change successfull?");

                //camx = (img_background.getWidth()*globalscale)/2 - gToInt(buildings[buildingPressed][2])/2;
                //binadan çýkýnca o binayý x ekseninde ortalat 09.01.2023 todo
                //buildingXs[BUILDING_TRAINING] = buildingXs[BUILDING_PAPER];
                //buildingYs[BUILDING_TRAINING] = buildingYs[BUILDING_SCISSORS];


                cx = gToInt(buildings[buildingPressed][2]) +
                     img_buildings[buildingPressed].getWidth() / 2 * globalscale - camx;
                gLogi("debug 960");

                cy = gToInt(buildings[buildingPressed][3]) + img_buildings[buildingPressed].getHeight() * globalscale -
                     camy;
                gLogi("debug 963");
                gLogi("Character exited from the building : " + gToStr(buildingPressed) + "\nto: (" + gToStr(cx) + "," +
                      gToStr(cy) + ")");
                buildingPressed = -1;
                currentInterior.clear();
                //currentInterior.clear();
                gLogi("buttonExitBuilding listener : Complete");
                game_map = IN_MAP;
            }
            buttons[Button_ExitBuilding][10] = 0;
        }

		if (buttonPressed == Button_Armory || buttonPressed == Button_Potionary || buttonPressed == Button_Assassin) {
            buttons[Button_ExitBuilding][BTN_VIS] = 1;

			buildingPressed = buttonPressed - 1;
		    std::vector<std::string> innerInfo = gSplitString(buildings[buttonPressed - 1][4], ",");

		    gLogi("building : " + gToStr(buildingPressed));
		    gLogi("innerInfo1 : " + buildings[buttonPressed - 1][4]);
		    gLogi("innerInfo2 : (parced)");
		    for(std::string s : innerInfo) {
		    	gLogi( s + ",");
		    }

			if(innerInfo[0] != "-1") {
				game_map = IN_BUILDING;
				//gLogi("BuildingPressed Game_map = " + gToStr(game_map));

				//gLogi("Building Pressed : " + gToStr(buildingPressed));
				//gLogi("Building Pressed : " + gToStr(buildings[buildingPressed][0]));
				for(auto & info : innerInfo) {
					//gLogi("CurrentInreior["+gToStr(i)+"] : " + gToStr(gToInt(innerInfo[i])));
					currentInterior.push_back(gToInt(info));
				}

				gLogi("\ncurrentInterior : ");
			    for(int i : currentInterior) {
			    	gLogi( gToStr(i) + ",");
			    }

				gLogi("cx = currentInterior[4](" + gToStr(currentInterior[4]) + ")" );
				gLogi("cy = currentInterior[5](" + gToStr(currentInterior[5]) + ")");
				characterscalelevel = 6;
				cx = currentInterior[4];
				cy = currentInterior[5];
				buttons[Button_ExitBuilding][10] = 1;
				gLogi("#DEBUG CHECK YENI");
			}
			/*
			std::vector<std::string> innerInfo = gSplitString(buildings[buildingPressed][4], ",");
			if(innerInfo[0] != "-1") {
				gLogi("before currentInterior.clear()");
				if(currentInterior.size() > 0) {
					currentInterior.clear();
				}
				game_map = IN_BUILDING;
				gLogi("after currentInterior.clear()");

				gLogi("BuildingPressed Game_map = " + gToStr(game_map));

				//gLogi("Building Pressed : " + gToStr(buildingPressed));
				//gLogi("Building Pressed : " + gToStr(buildings[buildingPressed][0]));
				for(int i = 0; i < innerInfo.size(); i++) {
					//gLogi("CurrentInreior["+gToStr(i)+"] : " + gToStr(gToInt(innerInfo[i])));
					currentInterior.push_back(gToInt(innerInfo[i]));
				}
				gLogi("cx = currentInterior[4](" + gToStr(currentInterior[4]) + ")" );
				gLogi("cy = currentInterior[5](" + gToStr(currentInterior[5]) + ")");
				characterscalelevel = 6;
				cx = currentInterior[4];
				cy = currentInterior[5];
				buttons[Button_ExitBuilding][10] = 1;
				gLogi("#DEBUG CHECK YENI");
			}
			*/
		}

		if (buttonPressed == Button_Training) { //different interior than other buildings (2 pieces)
            buttons[Button_ExitBuilding][BTN_VIS] = 1;
            buttons[5][BTN_VIS] = 1; //DEBUG Btn
            gLogi("########\n#######\n###### BUTTON _ TRAINING has PRESSED ######\n#######\n#######");
            setCamera(0, 0, camx1, camy1, camx2, camy2);
            setMapBorders(0, 0, tg_coordinates[4] + imgs_Training_Ground[3].getWidth() + 200, tg_coordinates[5] + imgs_Training_Ground[3].getHeight() + 200);
            //camx = 0;
            //camy = 0;
			buildingPressed = Button_Training - 1;
			game_map = IN_BUILDING;
			std::vector<std::string> innerInfo = gSplitString(buildings[buildingPressed][4], ",");

			 gLogi("building : " + gToStr(buildingPressed));
			 gLogi("innerInfo1 : " + buildings[buttonPressed - 1][4]);
			 gLogi("innerInfo2 : (parced)");
			 for(std::string s : innerInfo) {
				 gLogi( s + ",");
			 }

			for(auto & info : innerInfo) {
				currentInterior.push_back(gToInt(info));
			}
			gLogi("\ncurrentInterior : ");
			for(int i : currentInterior) {
				gLogi( gToStr(i) + ",");
			}

			characterscalelevel = 6;
			cx = currentInterior[4];
			cy = currentInterior[5];
			buttons[Button_ExitBuilding][10] = 1;

		}

        if (buttonPressed == Button_Debug) { //Debug button
            toggleVisMenu(1);
            buttons[Button_ExitBuilding][BTN_VIS] = (buttons[Button_ExitBuilding][BTN_VIS] == 1) ? 0 : 1;

            /* üstteki kod alttakinin aynýsýný yapýyor.
            menus[1][MENU_VISIBILITY] = menus[1][MENU_VISIBILITY] == "1" ? "0" : "1";
             */
        }

        if(buttonPressed == Button_Billboard) {
            gLogi("Basýldý -> Button_Billboard");
            buttons[Button_ExitBuilding][BTN_VIS] = 1;
            showMenu(Menu_Billboard);
            // billboard menu ekle TODO 12.01.2023
        }

        if(buttonPressed >= Buttons_Papers[0] && buttonPressed <= Buttons_Papers[Buttons_Papers.size() - 1]) {
            paperPressed = buttonPressed;
            menus[Menu_Paper][MENU_TITLE] = buttonTexts[buttonPressed];
            buttons[Button_ExitBuilding][BTN_VIS] = 0;
            showMenu(Menu_Paper);
            for(int btn : Buttons_Papers) {
                buttons[btn][BTN_VIS] = 0;
            }
        }

        if(buttonPressed == Buttons_on_Paper[1]) {
            gLogi("\n#######1\nButtonPressed:" + gToStr(buttonPressed)+"\nBtns_on_Paper[1] : " + gToStr(Buttons_on_Paper[1])+"\n########");
            std::vector<std::string> test = gSplitString(buttonTexts[paperPressed],"-");//
            std::string test2 = "";
            for(int i = 0; i < test.size(); i++) {
                if(i != BB_P_Picked){
                    test2 += test[i];
                    test2 += "-";
                } else {
                    test2 += "0";
                    test2 += "-";
                }
            }
            buttonTexts[paperPressed] = test2;
            buttons[Button_ExitBuilding][BTN_VIS] = 1;
            hideMenu(Menu_Paper);
            gLogi("}#{ Btnpressed : " + gToStr(buttonPressed));
            gLogi("DEBUG 1991");
            for(int Buttons_Paper : Buttons_Papers) {
                test = gSplitString(buttonTexts[Buttons_Paper],"-");
                gLogi("DEBUG 1994");
                buttons[Buttons_Paper][BTN_VIS] = gToInt(test[BB_P_Picked]); //todo burada kaldýn
                gLogi("DEBUG 1996");
            }
        }
        if(buttonPressed == Buttons_on_Paper[0]) {
            gLogi("\n#######0\nButtonPressed:" + gToStr(buttonPressed)+"\nBtns_on_Paper[0] : " + gToStr(Buttons_on_Paper[0])+"\n########");
            buttons[Button_ExitBuilding][BTN_VIS] = 1;
            hideMenu(Menu_Paper);
            std::vector<std::string> test = gSplitString(buttonTexts[paperPressed],"-");//
            for(int Buttons_Paper : Buttons_Papers) {
                test = gSplitString(buttonTexts[Buttons_Paper],"-");
                gLogi("DEBUG 1994");
                buttons[Buttons_Paper][BTN_VIS] = gToInt(test[BB_P_Picked]); //todo burada kaldýn
                gLogi("DEBUG 1996");
            }
        }


        /*
        if(buttonPressed >= Buttons_on_Paper[0] && buttonPressed <=Buttons_on_Paper[Buttons_on_Paper.size()-1]) {
            int exactbtn = Buttons_Papers[0];
            for(int i = 0; i<Buttons_on_Paper.size(); i+2) {
                if(buttonPressed == Buttons_on_Paper[i]) {
                    break;
                } else {
                    exactbtn++;
                }
            }
            if (buttonPressed % 2 != 0) { //First Options : Put it back
                gLogi("Ben Calistim %2");
                gLogi("Exact Button : " + gToStr(exactbtn));
                gLogi("ButtonPressed : " + gToStr(buttonPressed));
                buttons[exactbtn][BTN_VIS] = 0;
            }
            else { // todo burda bug var :
                gLogi("ButtonPressed : " + gToStr(buttonPressed));
                gLogi("!%2 Ben Calistim");
                //gLogi("Buttons_Papers[Exactbtn] : " + gToStr(Buttons_Papers[exactbtn]));
                gLogi("Exact Button : " + gToStr(exactbtn));
                buttons[exactbtn][BTN_VIS] = 0;
                hideMenu(Menu_Paper);
            }
        }
        */

	buttonPressed = -1;
	}


/*
	if(buildingPressed != -1) {

	    std::vector<std::string> innerInfo = gSplitString(buildings[buildingPressed][4], ",");
		if(innerInfo[0] != "-1") {
			game_map = IN_BUILDING;
			gLogi("BuildingPressed Game_map = " + gToStr(game_map));

			//gLogi("Building Pressed : " + gToStr(buildingPressed));
			//gLogi("Building Pressed : " + gToStr(buildings[buildingPressed][0]));
			for(int i = 0; i < innerInfo.size(); i++) {
				//gLogi("CurrentInreior["+gToStr(i)+"] : " + gToStr(gToInt(innerInfo[i])));
				currentInterior.push_back(gToInt(innerInfo[i]));
			}
			gLogi("cx = currentInterior[4](" + gToStr(currentInterior[4]) + ")" );
			gLogi("cy = currentInterior[5](" + gToStr(currentInterior[5]) + ")");
			characterscalelevel = 6;
			cx = currentInterior[4];
			cy = currentInterior[5];
			buttons[Button_ExitBuilding][10] = 1;
			gLogi("#DEBUG CHECK YENI");
		}
	}
*/

}

void GameCanvas::createMenu(std::vector<std::string> button_texts, std::string menu_title,
                            int x, int y, int menu_type, int button_type, bool menu_visibility) {
	std::vector<std::string> tempmenu;
	tempmenu.push_back(gToStr(menus.size()));	// menu_index 	- 0
	if(x == MENU_CENTERED) {
		x = (getWidth() - img_menus[menu_type].getWidth() * globalscale) / 2;
	}
	if(y == MENU_CENTERED) {
        if (menu_type == MENU_VERTICAL || menu_type == MENU_BILLBOARD) {
            y = (getHeight() - img_menus[menu_type].getHeight() * globalscale) / 2;
        }
        else if (menu_type == MENU_HORIZONTAL || menu_type == MENU_PAPER) {
            y = (getHeight() - (img_menus[menu_type].getHeight() * 1.25f) * globalscale);
        }
	}
    std::string visibility = menu_visibility ? "1" : "0";

	tempmenu.push_back(gToStr(x));				// menu_x		- 1
	tempmenu.push_back(gToStr(y));				// menu_y		- 2
    tempmenu.push_back(visibility);                         // menu_vis     - 3
	tempmenu.push_back(gToStr(menu_type));		// menu_type 	- 4
	tempmenu.push_back(menu_title);				            // menu_title	- 5
	tempmenu.push_back(gToStr(button_type));	    // button_types	- 6
	tempmenu.push_back(gToStr(button_texts.size())); //btn_count  - 7

    if(menu_type != MENU_BILLBOARD && menu_type != MENU_PAPER) {
        // For Vertical Menu's Button_Y calculations
        int b_y_0 = 0;
        int b_y_1 = 0;

        // For Horizontal Menu's Button_X calculations
        float menuLength = 0;
        float menuMargin = 0;
        int totalBtnCount = 0;
        float singleButtonLength = 0;
        float gapBetweenButtons = 0;

        int b_x = gToInt(tempmenu[MENU_X])
                  + ((img_menus[gToInt(tempmenu[MENU_TYPE])].getWidth()
                      - img_button[gToInt(tempmenu[MENU_BTN_TYPE])].getWidth()) * globalscale)
                    / 2;
        if (menu_type == MENU_HORIZONTAL) {
            menuLength = img_menus[menu_type].getWidth() * globalscale;
            menuMargin = 140 * globalscale;
            totalBtnCount = button_texts.size();
            singleButtonLength = img_button[button_type].getWidth() * globalscale;
            gapBetweenButtons =
                    ((menuLength - (2 * menuMargin)) - (totalBtnCount * singleButtonLength)) / (totalBtnCount + 1);

            b_x = gToInt(tempmenu[MENU_X]) + menuMargin + gapBetweenButtons;
        }

        /*
        //debug için
        if(menu_title == "- Horizontal Menu -") {
            gLogi(" * * * * * * ");
            gLogi(" * CreateMenu -> MenuX : " + tempmenu[MENU_X] + " | BtnX : " + gToStr(b_x));
            gLogi(" * BtnX = MENU_X + (menu_image.getWidth() * globalscale - img_button.getWidth*globalscale) / 2 ");
            gLogi(" * BtnX(" + gToStr(b_x) + ") = " + tempmenu[MENU_X] +
                  "+ (" + gToStr(img_menus[gToInt(tempmenu[MENU_TYPE])].getWidth()) +
                  " * " + gToStr(globalscale) + ")" +
                  "(" + gToStr(img_menus[gToInt(tempmenu[MENU_TYPE])].getWidth() * globalscale) + ") - " +
                  gToStr(img_button[gToInt(tempmenu[MENU_TYPE])].getWidth()) + " * " + gToStr(globalscale) + ")" +
                  "(" + gToStr(img_button[gToInt(tempmenu[MENU_TYPE])].getWidth() * globalscale) + ") / 2");
        }
        */

        int b_y = gToInt(tempmenu[MENU_Y])
                  + ((img_menus[gToInt(tempmenu[MENU_TYPE])].getHeight()
                      - img_button[gToInt(tempmenu[MENU_BTN_TYPE])].getHeight()) * globalscale)
                    / 2;
        if (menu_type == MENU_VERTICAL) {
            b_y_0 = gToInt(tempmenu[MENU_Y]) + 150 * globalscale;
            b_y_1 = img_button[gToInt(tempmenu[MENU_BTN_TYPE])].getHeight() * 1.25f * globalscale;
        }
        int b_r = 255, b_g = 255, b_b = 255; //rgb


        for (int i = 0; i < button_texts.size(); i++) {
            if (menu_type == MENU_VERTICAL) {
                b_y = b_y_0 + (b_y_1 * (i + 2));
            }
            createButton(button_texts[i], b_x, b_y,
                         button_type,
                         b_r, b_g, b_b, font_BUTTON,
                         BUTTON_GUI, false);
            if (menu_type == MENU_HORIZONTAL) {
                b_x += (singleButtonLength * (i + 1)) + gapBetweenButtons;
            }
            tempmenu.push_back(gToStr(buttons.size() - 1) + "." + button_texts[i]); // btn_i+"."+text 	- {8..8+n}
        }
        menus.push_back(tempmenu);
        gLogi("Menu -" + gToStr(menus.size() - 1) + "- is created successfully!");
    }
    if(menu_type == MENU_BILLBOARD) {
        if(button_type == Button_Type_Paper) {
            int b_r = 30, b_g = 255, b_b = 60;
            for(int i = 0; i < button_texts.size(); i++) {
                b_g = (gSplitString(button_texts[i],"-")[BB_P_Title][1] == 'Q')? 180 : 20;
                b_b = (gSplitString(button_texts[i],"-")[BB_P_Title][1] == 'Q')? 60 : 255;
               /* üstteki iki satýrla ayný iþi görüyor
                if (type == 'Q') { //Quest
                    //todo : TITLE + REWARD -> [TIKLANDIKTAN SONRA] -> detail
                    b_r = 30, b_g = 255, b_b = 60;
                }
                if (type == 'N') { //News
                    //todo : TITLE -> [TIKLANDIKTAN SONRA] -> detail
                    b_r = 30, b_g = 60, b_b = 255;
                }
            */
                createButton(button_texts[i], BB_paperXs[i], BB_paperYs[i],
                             button_type,
                             b_r, b_g, b_b, font_LOAD1,
                             BUTTON_GUI, false);
                tempmenu.push_back(gToStr(buttons.size() - 1) + "." + button_texts[i]); // btn_i+"."+text 	- {8..8+n}
                Buttons_Papers[i] = buttons.size() - 1;
                gLogi("Billboard'a eklenen button indexi : " + gToStr(Buttons_Papers[i]));
                gLogi("Billboard'a eklenen button texti : " + button_texts[i]);

            }
            menus.push_back(tempmenu);
        }
    }

    if(menu_type == MENU_PAPER) {
        int b_r = 30, b_g = 180, b_b = 20;
        int b_x = getWidth()/2 - img_button[Button_Type_Large].getWidth()*globalscale - 50*globalscale;
        int b_y = getHeight() - (img_button[Button_Type_Large].getHeight()*globalscale)*1.5f;
        for(int i = 0; i < button_texts.size(); i++) {
            b_g = (button_texts[i][0] == 'A')? 180 : 20;
            b_r = (button_texts[i][0] == 'A')? 30 : 180;
            /* üstteki iki satýrla ayný iþi görüyor
             if (type == 'Q') { //Quest
                 //todo : TITLE + REWARD -> [TIKLANDIKTAN SONRA] -> detail
                 b_r = 30, b_g = 255, b_b = 60;
             }
             if (type == 'N') { //News
                 //todo : TITLE -> [TIKLANDIKTAN SONRA] -> detail
                 b_r = 30, b_g = 60, b_b = 255;
             }
         */

            createButton(button_texts[i], b_x, b_y,
                         button_type,
                         b_r, b_g, b_b, font_LOAD1,
                         BUTTON_GUI, false);
            b_x =  getWidth()/2 + 50*globalscale;
            tempmenu.push_back(gToStr(buttons.size() - 1) + "." + button_texts[i]); // btn_i+"."+text 	- {8..8+n}
            Buttons_on_Paper[i] = buttons.size() - 1;
            gLogi("Buttons_on_Paper[" + gToStr(i) + "]'ye koydum : " + gToStr(Buttons_on_Paper[i]));
        }
        menus.push_back(tempmenu);
    }
}

void GameCanvas::drawMenus() {
    for(int menu = 0; menu < menus.size(); menu++) {
        if(menus[menu][MENU_VISIBILITY] == "1") {
            if(menu == 0) { //0. menu = Pause Menusu
                background_defocus.draw(0, 0, getWidth(), getHeight());
            }
            drawMenu(menu);
        }
    }
}

void GameCanvas::drawMenu(int menuIndex) {
    std::vector<std::string> menu = menus[menuIndex];
    //for background
    int bg_x = gToInt(menu[MENU_X]); //background_x
    int bg_y = gToInt(menu[MENU_Y]); //background_y


    //for title
    float t_x = bg_x +
                (img_menus[gToInt(menu[MENU_TYPE])].getWidth() * globalscale - fonts[font_LOAD1].getStringWidth(menu[MENU_TITLE])) / 2;
    float t_y = 30; // x,y
    int t_r = 75, t_g = 0, t_b = 50, t_a = 255; //rgba

    //for buttons
    /*old
    int b_x = gToInt(menu[MENU_X]) +
              ((img_menus[gToInt(menu[MENU_TYPE])].getWidth() - img_button[gToInt(menu[MENU_BTN_TYPE])].getWidth()) * globalscale) / 2;
    int b_y_0 = gToInt(menu[MENU_Y]) + 150 * globalscale;
    int b_y_1 = img_button[gToInt(menu[MENU_BTN_TYPE])].getHeight() * 1.25f * globalscale;
    int b_r = 255, b_g = 255, b_b = 255; //rgb
   */

    //background
    img_menus[gToInt(menu[MENU_TYPE])].draw(bg_x, bg_y, globalscale);
    //gLogi("Menü çizdiriliyor : ");
    //gLogi(img_menus[gToInt(menu[MENU_TYPE])].getFilename());
    //gLogi("x : " + gToStr(bg_x) + ", y : " + gToStr(bg_y));

    if(menus[menuIndex][MENU_TYPE] != gToStr(MENU_PAPER) ) {
        //title
        fonts[font_LOAD1].drawText(
                menu[MENU_TITLE],
                t_x,
                t_y,
                t_r, t_g, t_b
        );
    }
    else if(menus[menuIndex][MENU_TYPE] == gToStr(MENU_PAPER)) {
        std::string title = "";
        std::string text = "";
        std::string reward = "";

        gLogi("Pressed on : Paper(" + gToStr(paperPressed) + ")");
        background_defocus.draw(0, 0, getWidth(), getHeight());
        title = gSplitString(buttonTexts[paperPressed],"-")[BB_P_Title];
        gLogi("Title : " + title);
        text = gSplitString(buttonTexts[paperPressed],"-")[BB_P_Details];
        gLogi("text : " + text);
        if(title[1] == 'Q') {
            reward = gSplitString(buttonTexts[paperPressed], "-")[BB_P_Reward];
            gLogi("reward : " + reward);
        }

        float titlex = (getWidth()-fonts[font_LOAD1].getStringWidth(title))/2;
        float titley = 100 * globalscale;

        float textx = getWidth()/4;
        float texty = (getHeight() - fontsizes[font_LOAD1])/2;

        float rewardx = textx;
        float rewardy = texty + fonts[font_LOAD2].getStringHeight(text) + fontsizes[font_LOAD1]*3.0f;

        fonts[font_LOAD1].drawText(title, titlex, titley,
                                   255, 255, 255, 255);

        fonts[font_LOAD2].drawText(text, textx, texty,
                                   255, 255, 255, 255);

        fonts[font_BUTTON].drawText(reward, rewardx, rewardy,
                                    255, 255, 255, 255);

    }

    //buttons

   //for (int i = 0; i < gToInt(menu[MENU_BTN_COUNT]); i++) {
   //    /*
   //     * drawButton( //old.
   //     * 				string btntext,
   //     * 				int btnx, int btny,
   //     * 				int btntype,
   //     * 				int btnR, int btnG, int btnB,
   //     * 				int texttype
   //     * 			)
   //     *
   //     */
   //    //int b_y = b_y_0 + (b_y_1 * (i + 2)); //old
   //    drawButton(gToInt(gSplitString(menu[8 + i], ".")[0])); //
   //    //bunu sonrasýnda bi silmeyi dene bakalým pause menü'deki veya diðer menülerdeki butonlar yine de çizilecek mi acep

   //} //todo

}

void GameCanvas::toggleVisMenu(int menuIndex) {
    switch (gToInt(menus[menuIndex][MENU_VISIBILITY])) {
        case 0:
            showMenu(menuIndex);
            break;
        case 1:
            hideMenu(menuIndex);
            break;
    }
}

void GameCanvas::showMenu(int menuIndex) {
    menus[menuIndex][MENU_VISIBILITY] = "1";
    for(int b = 0; b < gToInt(menus[menuIndex][MENU_BTN_COUNT]); b++) {
        int buttonIndex = gToInt(menus[menuIndex][8 + b]);
        gLogi("showMenu -> buttonindex = " + gToStr(buttonIndex));
        if(menuIndex == Menu_Billboard) {
            std::vector<std::string> test = gSplitString(buttonTexts[buttonIndex],"-");
            buttons[Button_ExitBuilding][BTN_VIS] = 1;
            hideMenu(Menu_Paper);
            buttons[buttonIndex][BTN_VIS] = gToInt(test[BB_P_Picked]); //todo burada kaldýn
        } else {
            buttons[buttonIndex][BTN_VIS] = 1;
        }
    }
}

void GameCanvas::hideMenu(int menuIndex) {
    menus[menuIndex][MENU_VISIBILITY] = "0";
    for(int b = 0; b < gToInt(menus[menuIndex][MENU_BTN_COUNT]); b++) {
        int buttonIndex = gToInt(menus[menuIndex][8 + b]);
        buttons[buttonIndex][BTN_VIS] = 0;
    }
}

void GameCanvas::createBuilding(int index, int index_outerImg, float _x, float _y, std::string innerinfos) {
	std::vector<std::string> tmpBuilding;
	//float x = _x - img_buildings[index_outerImg].getWidth()/2;
	//float y = _y - img_buildings[index_outerImg].getHeight()/2;
	tmpBuilding.push_back(gToStr(index));
	tmpBuilding.push_back(gToStr(index_outerImg));
	tmpBuilding.push_back(gToStr(_x));
	tmpBuilding.push_back(gToStr(_y));
	tmpBuilding.push_back(innerinfos);
	buildings.push_back(tmpBuilding);
}

void GameCanvas::drawBuildings() {

	for(auto & building : buildings) {
		img_buildings[gToInt(building[1])].draw(gToInt(building[2]) - camx, gToInt(building[3]) - camy, globalscale);
	}
}

#pragma clang diagnostic pop