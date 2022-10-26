/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"
#include "MainMenu.h"


GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
	DEBUG = true;
	img_blueprint.loadImage("GUI/blueprint.png");

	gLogi("GameCanvas Setup");

	playerIndex = 0; //sunucudan al bunu
	totalCharacterAmount = 1; //sunucudan al bunu
	img_characters = new gImage[totalCharacterAmount];

}

void GameCanvas::update() {

	framecounter++;
	if(mouseHold) {
		mouseHoldedFor_frames++;
	}
	if(framecounter % 60 == 0) {
		seccounter++;
		if(mouseHold) {
			mouseHoldedFor_seconds++;
		}
	}
	if (status == LOADING) {
		updateLoad(loadindex);
		loadindex++;
	} else if (status == PLAYING) {

	}
}

void GameCanvas::draw() {

	 if (status == LOADING) {
		drawLoad();
		//debug
		if(DEBUG) {
			font[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
			font[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);
		}
	} else if (status == PLAYING) {
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
	gLogi("GameCanvas initilaize");
	gFont empty1, empty2;
	img_blueprint.loadImage("GUI/blueprint.png");
	status = LOADING;
	loadindex = 0;
	framecounter = 0;
	seccounter = 0;

	mouseHold = false;
	mouseHoldedFor_frames = 0;
	mouseHoldedFor_seconds = 0;

	mousex = getWidth() / 2;
	mousey = getHeight() / 2;

	fontsizes.push_back(24);
	fontsizes.push_back(14);

	font.push_back(empty1);
	font.push_back(empty2);
	font[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	font[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);

	loadingtext.push_back("LOADING");
	loadingtext.push_back("");

	interiorAmounts[SHOP_POTION] = 1;
	interiorAmounts[SHOP_ARMORY] = 1;
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

			loadingtext[1] = "Setting up all initial variables...";
			break;
		case 8:

			loadingtext[1] = "Setting up all initial variables...";
			break;
		case 9:
			loadingtext[1] = "Setting up all initial variables...";
			setInitialVariables();
			break;
		case 100:
			status = PLAYING;
			break;
		}
}

void GameCanvas::setInitialVariables() {
	globalscale = getWidth() / 1920.0f;

	keystate = 0;


	cx = getWidth() / 2; // baþlangýç pozisyonu x
	cy = 100; // baþlangýç pozisyonu y
	cdx = 0, cdy = 0;

	camx = img_background.getWidth() / 2;
	camy = 0;
	camx1 = 0, camy1 = 0;
	camx2 = 0, camy2 = 0;
	crot = 0;
	mrot = 0;

	characterframenum = 0;

	propXs[SPAWN_POINT] = (getWidth() - img_props[SPAWN_POINT].getWidth()) / 2;
	propYs[SPAWN_POINT] = 100 - (img_props[SPAWN_POINT].getHeight() / 2);

	buildingXs[SHOP_POTION] = getWidth()/4 - img_buildings[SHOP_POTION].getWidth();
	buildingYs[SHOP_POTION] = 250;

	buildingXs[SHOP_ARMORY] = getWidth()*3/4;
	buildingYs[SHOP_ARMORY] = 250;

	for(int i = 0; i < totalCharacterAmount; i++) {
		int characterIndex = characters[i][0];
		int race = characters[i][5];

		// character base
		img_characters[characterIndex][CBASE] = img_characterBases[race];
		// character armor
		img_characters[characterIndex][ARMOR] = img_equipables[race][ARMOR][characterEquipped[characterIndex][ARMOR]];
		// character helmet
		img_characters[characterIndex][HELMET] = img_equipables[race][HELMET][characterEquipped[characterIndex][HELMET]];
		// character weapon
		img_characters[characterIndex][WEAPON] = img_equipables[race][WEAPON][characterEquipped[characterIndex][WEAPON]];
		// character effect
		img_characters[characterIndex][EFFECT] = img_equipables[race][WEAPON][characterEquipped[characterIndex][WEAPON]];
	}

	characterframecounterlimit = 12 / cspeed;
}

/*[update] methods -> */
void GameCanvas::updateCharacter() {
	// Bu kontrolleri burada yapmak yerine switchcase'de yapsaydÄ±k yalnÄ±zca 1 defa Ã§alÄ±ÅŸÄ±rdÄ±



	if ((keystate & KEY_W) != 0) {
		//gLogi("W BASILIYOR");
		//cdx = std::sin(gDegToRad(mrot)) * cspeed; // cdx - cdy
		//cdy = -std::cos(gDegToRad(mrot)) * cspeed;
		cdy = -1 * cspeed;
	}
	else if ((keystate & KEY_S) != 0) {
		//gLogi("S BASILIYOR");
		//cdx = -std::sin(gDegToRad(mrot)) * cspeed;
		//cdy = std::cos(gDegToRad(mrot)) * cspeed;
		cdy = 1 * cspeed;
	}

	// Ã‡aprazlara hareket edebilmek iÃ§in A ve D'yi W ve S'ten ayÄ±rdÄ±k.
	if ((keystate & KEY_A) != 0) {
		//gLogi("A BASILIYOR");
		//cdx += -std::cos(gDegToRad(mrot)) * cspeed;
		//cdy += -std::sin(gDegToRad(mrot)) * cspeed;
		cdx = -1 * cspeed;
	}
	else if ((keystate & KEY_D) != 0) {
		//gLogi("D BASILIYOR");
		//cdx += std::cos(gDegToRad(mrot)) * cspeed;
		//cdy += std::sin(gDegToRad(mrot)) * cspeed;
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

}

void GameCanvas::updateCamera() {
	if (cx < camx1 || cx + img_characterBases[0].getWidth() > camx2) {
		cx -= cdx;
		camx += cdx;
		if (camx < 0) {
			camx = 0;
			camx1 = 0;
		}else {
			camx1 = getWidth() >> 2;
		}
		if (camx + getWidth() >= img_background.getWidth()) {
			camx = img_background.getWidth() - getWidth();
			camx2 = getWidth();
		} else {
			camx2 = (getWidth() * 3) >> 2;
		}
	}

	if (cy < camy1 || cy + img_characterBases[0].getHeight() > camy2) {
		cy -= cdy;
		camy += cdy;
		if (camy < 0) {
			camy = 0;
			camy1 = 0;
		}else {
			camy1 = getHeight() >> 2;
		}
		if (camy + getHeight() >= img_background.getHeight()) {
			camy = img_background.getHeight() - getHeight();
			camy2 = getHeight();
		} else {
			camy2 = (getHeight() * 3) >> 2;
		}
	}

	//delta degerlerini sifirliyoruz
	cdx = 0;
	cdy = 0;
}

/* [draw] Methods -> */
void GameCanvas::drawLoad() {

	img_blueprint.draw(0, 0, globalscale);

	if(framecounter % 15 == 0) {
		gLogi("a");
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

	font[font_LOAD1].drawText(loadingtext[0], 554, getHeight()*4/5);
	font[font_LOAD2].drawText(loadingtext[1], 500, getHeight()*4/5 + fontsizes[0]);
}

void GameCanvas::drawGame() {

	drawMapBG();
	drawMid();
	drawCharacter();
	drawMapFG();

}

void GameCanvas::drawMapBG() {

	img_background.draw(-20,-20, globalscale);
	//img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);
}

void GameCanvas::drawMid() {
	//healer

	img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);

	img_buildings[SHOP_POTION].draw(buildingXs[SHOP_POTION], buildingYs[SHOP_POTION], globalscale);

	img_buildings[SHOP_ARMORY].draw(buildingXs[SHOP_ARMORY], buildingYs[SHOP_ARMORY], globalscale);

}

void GameCanvas::drawCharacter() {

}

void GameCanvas::drawMapFG() {

}

void GameCanvas::drawGUI() {

}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
	int pressed = 0;
	switch (key){
		case 87:
			pressed = KEY_W;
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
			if(status == PAUSED) {
				status = PLAYING;
			}
			else if (status == PLAYING) {
				status = PAUSED;
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

void GameCanvas::listenButtons() {
	if(buttonPressed != -1) {
		buttonPressed = -1; // reset action
	}
}

