/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"
#include "MainMenu.h"
#include "gUtils.h"

GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
	DEBUG = true;
	gLogi("GameCanvas Setup");
	img_blueprint.loadImage("GUI/blueprint.png");

}

void GameCanvas::update() {
	framecounter++;
	if(mouseHold) {
		mouseHoldedFor_frames++;
		if(framecounter % 60 == 0) {
			mouseHoldedFor_seconds++;
		}
	}

	if (game_status == LOADING) {
		updateLoad(loadindex);
		loadindex++;
	} else if (game_status == PLAYING) {
		listener();
		updateCharacter();
		updateMap();
	}
}

void GameCanvas::draw() {
	if (game_status == LOADING) {
		drawLoad();
		//debug
		if(DEBUG) {
			font[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
			font[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);
		}
	} else if (game_status == PLAYING) {
		//debug
		if(DEBUG) {
			font[font_LOAD2].drawText("Mouse Hold For " + gToStr(mouseHoldedFor_seconds) + " seconds",10,10);
			font[font_LOAD2].drawText("Mouse Hold For " + gToStr(mouseHoldedFor_frames) + " frames",10,30);
		}

		drawGame();
		drawGUI();
	}

}

void GameCanvas::initilaize() {
	gFont empty1, empty2, empty3, empty4;
		img_blueprint.loadImage("GUI/blueprint.png");
		game_status = LOADING;
		loadindex = 0;
		framecounter = 0;
		seccounter = 0;
		buttonPressed = -1;
		buildingPressed = -1;
		mouseHold = false;
		mouseHoldedFor_frames = 0;
		mouseHoldedFor_seconds = 0;

		mousex = getWidth() / 2;
		mousey = getHeight() / 2;
		fontsizes.push_back(24); //font_LOAD1
		fontsizes.push_back(14); //font_LOAD2
		fontsizes.push_back(18); //font_BUTTON
		fontsizes.push_back(12); //font_INGAME

	gLogi("#DEBUG_test(19)");
		font.push_back(empty1);
	gLogi("#DEBUG_test(20)");
		font.push_back(empty2);
		font.push_back(empty3);
		font.push_back(empty4);
	gLogi("#DEBUG_test(21)");
		font[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
		font[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);
		font[font_BUTTON].loadFont("FreeSans.ttf", fontsizes[font_BUTTON]);
		font[font_INGAME].loadFont("FreeSans.ttf", fontsizes[font_INGAME]);

		loadingtext.push_back("LOADING");
		loadingtext.push_back("");

	gLogi("#DEBUG_test(27)");
		interiorAmounts[SHOP_POTION] = 1;
	gLogi("#DEBUG_test(28)");
		interiorAmounts[SHOP_ARMORY] = 1;
	gLogi("#DEBUG_test(29)");

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
	characters[playerIndex].push_back(0);	//race
	characters[playerIndex].push_back(1); 		//level
	gLogi("#DEBUG_test(34)");

	characters[playerIndex].push_back(1);		//STR
	characters[playerIndex].push_back(1);		//VIT
	characters[playerIndex].push_back(1);		//DEF/DEX
	characters[playerIndex].push_back(1);		//AGI/STA
	characters[playerIndex].push_back(1);		//MAG
	gLogi("#DEBUG_test(35)");

	characterEquipped[playerIndex].push_back(0); // BASE
	characterEquipped[playerIndex].push_back(0); //ARMOR
	characterEquipped[playerIndex].push_back(0); //HELMET
	characterEquipped[playerIndex].push_back(0); //WEAPON
	characterEquipped[playerIndex].push_back(-1);//EFFECT
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
}


void GameCanvas::updateLoad(int index) {
	loadingtext[1] = "Loaded : ";
		switch (index) {
		case 0:
			img_menu.loadImage("menu/mainmenubg.png");
			loadingtext[1] += "menu/mainmenubg.png";
			break;
		case 1:
			img_dialogbox.loadImage("GUI/dialogbox2.png");
			loadingtext[1] += "GUI/dialogbox.png";
			break;
		case 2: // BUTTONLAR YÜKLENDÝ
			loadingtext[1] += "menu/btn.png";
			for(int i = 0; i < btnAmount; i++) {
				img_button[i].loadImage("menu/btn_" + gToStr(i) + ".png");
			}
			break;
		case 3:
			img_background.loadImage("game/map.png");
			loadingtext[1] += "game/map.png";
			break;
		case 4:
			loadingtext[1] += "Props";
			for(int i = 0; i < propAmount; i++) {
				img_props[i].loadImage("game/props/prop_" + gToStr(i) + ".png");
			}
			break;
		case 5:
			loadingtext[1] += "Buildings";
			for(int i = 0; i < buildingAmount; i++) {
				img_buildings[i].loadImage("game/props/building_" + gToStr(i) + ".png");
				for(int j = 0; j < interiorAmounts[i]; j++) {
					gLogi("interiorAmounts[" + gToStr(i) + "] : " + gToStr(interiorAmounts[i]));
					img_interior[i][j].loadImage("game/props/building_" + gToStr(i) + "" + gToStr(j) +".png");
					gLogi("img_interior[i"+gToStr(i)+"][j"+gToStr(j)+"].loadImage('game/props/building_"+ gToStr(i) + "" + gToStr(j) +".png");
				}
			}
		break;
		case 6:
			loadingtext[1] += "NPCs";
			for(int i = 0; i < NPCAmount; i++) {
				img_NPCs[i].loadImage("game/props/NPC_" + gToStr(i) + ".png");
			}
		break;
		case 7:
			for(int i = 0; i < 3; i++) {
				img_characterBases[i].loadImage("game/charactertest/NPC_" + gToStr(i) + ".png");
				loadingtext[1] = "game/charactertest/NPC_" + gToStr(i) + ".png";
				gLogi("game/charactertest/NPC_" + gToStr(i) + ".png");
			}
			break;
			/*
		case 8:
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
			break;
	*/
		case 9:
			gLogi("case 9 start");



			loadingtext[1] = "Fonts";
			gLogi("SETTING INITIAL VARS");
			setInitialVariables();
			gLogi("INITIAL VARS HAS BEEN SETTED");
			break;
		case 100:
			game_status = PLAYING;
			game_map = IN_MAP;
			gLogi("Game Loaded");
			break;
		}
}

void GameCanvas::setInitialVariables() {
	gLogi("setInitVars");

	globalscale = getWidth() / 1920.0f;
	gLogi("#DEBUG_test(39)");
		keystate = 0;
	gLogi("#DEBUG_test(40)");
		cx = getWidth() / 2; // baþlangýç pozisyonu x
		cy = getHeight() / 5;; // baþlangýç pozisyonu y
		cdx = 0, cdy = 0;
	gLogi("#DEBUG_test(41)");

		camx = (img_background.getWidth()*globalscale - getWidth()) / 2;
		camy = 0;
		camx1 = getWidth() >> 3;
		camy1 = getHeight() >> 3;
		camx2 = (getWidth() * 7) >> 3;
		camy2 = (getHeight() * 7) >> 3;;
		cspeed = 2.0f;
		crot = 0;
		mrot = 0;
		characterframenum = 0;

	gLogi("#DEBUG_test(43)");
		propXs[SPAWN_POINT] = cx + camx + (img_characterBases[0].getWidth()/2)*globalscale - (img_props[SPAWN_POINT].getWidth()/2)*globalscale;
	gLogi("#DEBUG_test(44)");
		propYs[SPAWN_POINT] = cy + img_characterBases[0].getHeight()*globalscale - (img_props[SPAWN_POINT].getHeight()/2)*globalscale;
	gLogi("#DEBUG_test(45)");
		buildingXs[SHOP_POTION] = cx + camx - img_buildings[SHOP_POTION].getWidth()*3 * globalscale;
	gLogi("#DEBUG_test(46)");
		buildingYs[SHOP_POTION] = getHeight() / 20;
	gLogi("#DEBUG_test(47)");
		buildingXs[SHOP_ARMORY] = cx + camx + img_buildings[SHOP_POTION].getWidth()*3 * globalscale;
	gLogi("#DEBUG_test(48)");
		buildingYs[SHOP_ARMORY] = getHeight() / 20;

	for(int i = 0; i < totalCharacterAmount; i++) {
		std::vector<gImage> newImgChar;
		img_characters.push_back(newImgChar);
		int characterIndex = characters[i][0];
		gLogi("characterIndex : " + gToStr(characterIndex));
		int race = characters[i][5];
		// character base
		gLogi("img_characters[characterIndex(" +  gToStr(characterIndex)+ ")].push_back(img_characterBases[race(" +  gToStr(race)+ ")])");
		gLogi("img_characterBases[race].getFullPath : " + gToStr(img_characterBases[race].getFullPath()));
		gLogi("img_characterBases[race].getFilename : " + gToStr(img_characterBases[race].getFilename()));
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
	gLogi("path : " + gToStr(img_characters[playerIndex][0].getFullPath()));
	gLogi("filename : " + gToStr(img_characters[playerIndex][0].getFilename()));

	characterframecounterlimit = 12 / cspeed;
	gLogi("#DEBUG_test(58)");

	//createBuilding(int index, int index_outerImg, float _x, float _y, std::string innerinfos) {
	/* Building Structure :
	 * [index, index_outerimg, x, y, innerinfo1, innerinfo2, innerinfo...]
	 * (innerinfo0 : index_interiorImg)
	 * (innerinfo1 : index_NPC)
	 * (innerinfo2 : index_NPCx)
	 * (innerinfo3 : index_NPCy)
	 * (innerinfo4 : prop_amount) //prop amount in this interior
	 * (innerinfo5+: [prop_index1, x1, y1], [prop_index2, x2, y2]...
	 */
	gLogi("buildingXs[SHOP_ARMORY], buildingYs[SHOP_ARMORY] : " + gToStr(buildingXs[SHOP_ARMORY]) + "," + gToStr(buildingYs[SHOP_ARMORY]));
	gLogi("buildingXs[SHOP_POTION], buildingYs[SHOP_POTION] : " + gToStr(buildingXs[SHOP_POTION]) + "," + gToStr(buildingYs[SHOP_POTION]));
	gLogi("\nimg_buildings[ARMORY].getWidth()/2, img_buildings[ARMORY].getHeight()/2\n" + gToStr(img_buildings[SHOP_ARMORY].getWidth()/2) + "," + gToStr(img_buildings[SHOP_ARMORY].getHeight()/2));
	gLogi("\nimg_buildings[POTION].getWidth()/2, img_buildings[POTION].getHeight()/2\n" + gToStr(img_buildings[SHOP_POTION].getWidth()/2) + "," + gToStr(img_buildings[SHOP_POTION].getHeight()/2));

	std::string innerinfo;
	innerinfo = "0," + gToStr(SHOP_ARMORY) + "," + gToStr(getWidth()/3) + ","+ gToStr(getHeight()/4) +",0";
	createBuilding(SHOP_ARMORY, SHOP_ARMORY, buildingXs[SHOP_ARMORY], buildingYs[SHOP_ARMORY], innerinfo);
	innerinfo = "0," + gToStr(SHOP_POTION) + "," + gToStr(getWidth()/2) + ",50,0";
	createBuilding(SHOP_POTION, SHOP_POTION, buildingXs[SHOP_POTION], buildingYs[SHOP_POTION], innerinfo);

	/*
	 * std::string innerinfo;
	int x, y;
	innerinfo = "0," + gToStr(SHOP_ARMORY) + "," + gToStr(getWidth()/3 - img_NPCs[SHOP_POTION].getWidth()*globalscale/2) + ","+ gToStr(getHeight()/4) +",0";
	x = (getWidth() - img_interior[SHOP_ARMORY][0].getWidth())/2;
	y = (getHeight() - img_interior[SHOP_ARMORY][0].getHeight())/2;
	createBuilding(SHOP_ARMORY, SHOP_ARMORY, (getWidth() - img_interior[SHOP_ARMORY][0].getWidth())/2, buildingYs[SHOP_ARMORY], innerinfo);
	innerinfo = "0," + gToStr(SHOP_POTION) + "," + gToStr((getWidth() - img_NPCs[SHOP_POTION].getWidth()*globalscale)/2) + ",50,0";
	x = (getWidth() - img_interior[SHOP_POTION][0].getWidth())/2;
	y = (getHeight() - img_interior[SHOP_POTION][0].getHeight())/2;
	createBuilding(SHOP_POTION, SHOP_POTION, x, y, innerinfo);
	 *
	 */

}

/*[update] methods -> */
void GameCanvas::updateCharacter() {
	if ((keystate & KEY_W) != 0) {
		//gLogi("W BASILIYOR");
		//cdx = std::sin(gDegToRad(mrot)) * cspeed; // cdx - cdy
		//cdy = -std::cos(gDegToRad(mrot)) * cspeed;
		cdy = -1 * cspeed;
		gLogi("cdx : " + gToStr(cdx));
		gLogi("cdy : " + gToStr(cdy));

	}
	else if ((keystate & KEY_S) != 0) {
		//gLogi("S BASILIYOR");
		//cdx = -std::sin(gDegToRad(mrot)) * cspeed;
		//cdy = std::cos(gDegToRad(mrot)) * cspeed;
		cdy = 1 * cspeed;
		gLogi("cdx : " + gToStr(cdx));
		gLogi("cdy : " + gToStr(cdy));

	}

	// Ã‡aprazlara hareket edebilmek iÃ§in A ve D'yi W ve S'ten ayÄ±rdÄ±k.
	if ((keystate & KEY_A) != 0) {
		//gLogi("A BASILIYOR");
		//cdx += -std::cos(gDegToRad(mrot)) * cspeed;
		//cdy += -std::sin(gDegToRad(mrot)) * cspeed;
		cdx = -1 * cspeed;
		gLogi("cdx : " + gToStr(cdx));
		gLogi("cdy : " + gToStr(cdy));

	}
	else if ((keystate & KEY_D) != 0) {
		//gLogi("D BASILIYOR");
		//cdx += std::cos(gDegToRad(mrot)) * cspeed;
		//cdy += std::sin(gDegToRad(mrot)) * cspeed;
		cdx = 1 * cspeed;
		gLogi("cdx : " + gToStr(cdx));
		gLogi("cdy : " + gToStr(cdy));

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
	if (cx - (img_characterBases[0].getWidth()/2)*globalscale < camx1 || cx + (img_characterBases[0].getWidth()/2)*globalscale > camx2) {
		cx -= cdx;
		camx += cdx;
		if (camx < 0) {
			camx = 0;
			camx1 = 0;
		}else {
			camx1 = getWidth() >> 3;
		}
		if (camx + getWidth() >= img_background.getWidth()) {
			camx = img_background.getWidth() - getWidth();
			camx2 = getWidth() - (img_characterBases[0].getWidth()/2)*globalscale ;
		} else {
			camx2 = (getWidth() * 7) >> 3;
		}
	}

	if (cy - (img_characterBases[0].getHeight()/2)*globalscale  < camy1 || cy + (img_characterBases[0].getHeight()/2)*globalscale > camy2) {
		cy -= cdy;
		camy += cdy;
		if (camy < 0) {
			camy = 0;
			camy1 = 0;
		}else {
			camy1 = getHeight() >> 3;
		}
		if (camy + getHeight() >= img_background.getHeight()*globalscale) {
			camy = img_background.getHeight()*globalscale - getHeight();
			camy2 = getHeight() - (img_characterBases[0].getHeight()/2)*globalscale;
		} else {
			camy2 = (getHeight() * 7) >> 3;
		}
	}

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
	font[font_LOAD1].drawText(loadingtext[0],  getWidth()/2 - 100, getHeight()*4/5);
	font[font_LOAD2].drawText(loadingtext[1],  getWidth()/2 - 200, getHeight()*4/5 + fontsizes[0]);
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
		img_background.drawSub(0, 0, getWidth(), getHeight(), camx, camy, getWidth(), getHeight());
	}
	if(game_map == IN_BUILDING){ // draw building background
		gLogi("img_interior[buildingPressed(" + gToStr(buildingPressed) + ")][currentInterior[0](" + gToStr(currentInterior[0]) + ")]");
		gLogi("img_interior[" + gToStr(buildingPressed) + "][" + gToStr(currentInterior[0]) + "]].getfilename : " + gToStr(img_interior[buildingPressed][currentInterior[0]] .getFilename()));
		img_interior[buildingPressed][currentInterior[0]].draw(
				(getWidth() - img_interior[buildingPressed][currentInterior[0]].getWidth() * globalscale) / 2,
				(getHeight() - img_interior[buildingPressed][currentInterior[0]].getHeight()* globalscale) / 2 ,
				globalscale);
	}
	//img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);
}

void GameCanvas::drawMid() {
	//healer
	if(game_map == IN_MAP) { // draw props and buildings
		img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT] - camx, propYs[SPAWN_POINT] - camy, globalscale);
		drawBuildings();
		for(int buildingIndex = 0; buildingIndex < buildingAmount; buildingIndex++) {
			//img_buildings[buildingIndex].draw(buildingXs[buildingIndex] - camx, buildingYs[buildingIndex] - camy, globalscale);
			int initx = (img_buildings[buildingIndex].getWidth()/2)* globalscale;
			if(buildingIndex == SHOP_ARMORY) {
				font[font_INGAME].drawText("ARMORY SHOP", buildingXs[buildingIndex] - camx - (font[font_INGAME].getStringWidth("ARMORY SHOP")/2)*globalscale + initx, buildingYs[buildingIndex] + img_buildings[buildingIndex].getHeight()*globalscale - camy, 255, 220, 220);
			} else if (buildingIndex == SHOP_POTION) {
				font[font_INGAME].drawText("POTION SHOP", buildingXs[buildingIndex] - camx - (font[font_INGAME].getStringWidth("POTION SHOP")/2)*globalscale + initx, buildingYs[buildingIndex] + img_buildings[buildingIndex].getHeight()*globalscale - camy, 255, 220, 220);
			}
		}
	}
	if(game_map == IN_BUILDING) { // draw NPC
		gLogi("img_NPCs[currentInterior[1](" + gToStr(currentInterior[1]) + ")]");
		gLogi("img_NPCs[" + gToStr(currentInterior[1]) + "].getfilename : " + gToStr(img_NPCs[currentInterior[1]].getFilename()));

		img_NPCs[currentInterior[1]].draw(currentInterior[2], currentInterior[3], globalscale);
	}
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
	//gLogi("drawcharacter(0)");
	int initx = (img_characterBases[0].getWidth()/2)* globalscale ;
	//gLogi("drawcharacter(1)");
	str = "Player(ID:" + gToStr(playerIndex) + ")";
	//gLogi("drawcharacter(2)");
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*4.5);
	//gLogi("drawcharacter(3)");
	str = "RaceIndex:"+gToStr(characters[playerIndex][5]);
	//gLogi("drawcharacter(4)");
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*3);
	//gLogi("drawcharacter(5)");
	str = "cx+camx:"+gToStr(cx+camx)+"|cy+camy:"+gToStr(cy+camy);
	//gLogi("drawcharacter(6)");
	font[font_INGAME].drawText(str, cx - (font[font_INGAME].getStringWidth(str)/2) + initx, cy - fontsizes[font_INGAME]*1.5,20,255,20);

	//gLogi("drawcharacter(7)");
	//gLogi("playerIndex : " + gToStr(playerIndex));
	//gLogi("path : " + gToStr(img_characters[playerIndex][0].getFullPath()));
	//gLogi("filename : " + gToStr(img_characters[playerIndex][0].getFilename()));
	//gLogi("drawcharacter(8)");
	img_characters[playerIndex][0].draw(cx, cy, globalscale); //void draw(int x, int y, int w, int h, float rotate);
	//gLogi("drawcharacter(9)");
}

void GameCanvas::drawMapFG() {

	if(game_map == IN_BUILDING) {
		if(currentInterior[4] > 0) {
			int index = 5;
			for(int i = 0; i < currentInterior[4]; i++) {
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
	}

}

void GameCanvas::drawGUI() {

}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
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
		case 256:
			if(game_status == PAUSED) {
				game_status = PLAYING;
			}
			else if (game_status == PLAYING) {
				game_status = PAUSED;
			}
			break;
		case 340:
				cspeed += 4.0f; // Shift tusuna basildiginda karakter hizini artiriyoruz.
			break;
		default:
			break;
	}
	keystate |= pressed; // bitwise '+='

}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;
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
		if(x > buttons[b][0] && y > buttons[b][1] && x < buttons[b][7] && y < buttons[b][8]) {
			buttonPressed = b;
			gLogi("buttonPressed = " + gToStr(b));
		}
	}
	gLogi("building.size" + gToStr(buildings.size())); // TODO: burada kaldin binalari dumduz cizdirdigin icin calismiyor, onun yerine olusturdugun createBuilding methodunu kullan!
	for(int b = 0; b < buildings.size(); b++) {
		gLogi("#########\nBuilding : "+gToStr(b)+":\n");
		gLogi("(\nx: " + gToStr(x) + "+ camx" + gToStr(camx) + ")" + gToStr(x + camx) + ") > " + gToStr(gToInt(buildings[b][2])) + " &&\n" +
			   "\ny: " + gToStr(y) + "+ camy" + gToStr(camy) + ")" + gToStr(y + camy) + ") > " + gToStr(gToInt(buildings[b][3])) + " &&"+
			   "\nx: " + gToStr(x + camx) + " < " + gToStr(gToInt(buildings[b][2]) + img_buildings[gToInt(buildings[b][1])].getWidth()*globalscale) + " &&"+
			   "\ny: " + gToStr(y + camy) + " < " + gToStr(gToInt(buildings[b][3]) + img_buildings[gToInt(buildings[b][1])].getHeight()*globalscale));
	}
	for(int b = 0; b < buildings.size(); b++) {
		if(x + camx > gToInt(buildings[b][2])&&
		   y + camy > gToInt(buildings[b][3]) &&
		   x + camx < (gToInt(buildings[b][2]) + img_buildings[gToInt(buildings[b][1])].getWidth()*globalscale) &&
		   y + camy < (gToInt(buildings[b][3])) + img_buildings[gToInt(buildings[b][1])].getHeight()*globalscale){
			buildingPressed = b;
			gLogi("buildingPressed = " + gToStr(b));
		}
	}
}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
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

void GameCanvas::createButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	buttonTexts.push_back(btntext);
	std::vector<int> tmpbtn;
	tmpbtn.push_back(btnx);
	tmpbtn.push_back(btny);
	tmpbtn.push_back(btntype);
	tmpbtn.push_back(btnR);
	tmpbtn.push_back(btnG);
	tmpbtn.push_back(btnB);
	tmpbtn.push_back(texttype);
	tmpbtn.push_back(btnx + img_button[btntype].getWidth());
	tmpbtn.push_back(btny + img_button[btntype].getHeight());
	buttons.push_back(tmpbtn);
}

void GameCanvas::drawButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	//gLogi("MENUCANVAS::DRAWBUTTON -> START");
	img_button[btntype].draw(btnx, btny, globalscale);
	//gLogi("draw emptybtns : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale)- font[texttype].getStringWidth(btntext)) / 2) , btny + (img_button[btntype].getHeight() * globalscale)/2 + 3, btnR/3,btnG/3,btnB/3);
	//gLogi("draw savetextshadow : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale) - font[texttype].getStringWidth(btntext)) / 2) - 1, btny + (img_button[btntype].getHeight() * globalscale)/2 + 1, btnR, btnG, btnB);
	//gLogi("draw savetext : [PASSED]");
}

void GameCanvas::drawButtons() {
	for(int i = 0; i < buttons.size(); i++) {
		drawButton(buttonTexts[i], buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3], buttons[i][4], buttons[i][5], buttons[i][6]);
	}
}

void GameCanvas::listener() {
	if(buttonPressed != -1) {

		buttonPressed = -1; // reset action
	}

	if(buildingPressed != -1) {
	    std::vector<std::string> innerInfo = gSplitString(buildings[buildingPressed][4], ",");
		if(innerInfo[0] != "-1") {
			game_map = IN_BUILDING;
			gLogi("Building Pressed : " + gToStr(buildingPressed));
			gLogi("Building Pressed : " + gToStr(buildings[buildingPressed][0]));
			for(int i = 0; i < innerInfo.size(); i++) {
				gLogi("CurrentInreior["+gToStr(i)+"] : " + gToStr(gToInt(innerInfo[i])));
				currentInterior.push_back(gToInt(innerInfo[i]));
			}
		}

		//buildingPressed = -1; // reset action
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
	for(int b = 0; b < buildings.size(); b++) {
		img_buildings[gToInt(buildings[b][1])].draw(gToInt(buildings[b][2]) - camx, gToInt(buildings[b][3]) - camy, globalscale);
	}
}
