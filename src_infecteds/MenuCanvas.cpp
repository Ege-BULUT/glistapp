/*
 * MenuCanvas.cpp
 *
 *  Created on: 25 Aðu 2022
 *      Author: Ege BULUT
 */

#include "MenuCanvas.h"
#include "GameCanvas.h"
#include "gBaseApp.h"
#include "gApp.h"
#include "AboutCanvas.h"

MenuCanvas::MenuCanvas(gApp* root) : gBaseCanvas(root) {
	// TODO Auto-generated constructor stub
	this->root = root;
}

MenuCanvas::~MenuCanvas() {
	// TODO Auto-generated destructor stub
}

void MenuCanvas::setup() {

	background.loadImage("menu/arkaplan.jpg");
	mainmenu.loadImage("menu/anamenu.png");
	verify.loadImage("menu/tikler.png");
	mute.loadImage("menu/ban.png");

	characterGender = 0;
	mainmenux = getWidth() / 2 - mainmenu.getWidth() / 2;
	mainmenuy = getHeight() / 2 - mainmenu.getHeight() / 2;

	buttonH   = 20, buttonW   = 90;
	musicBtnX = 100, musicBtnY = 142;
	soundBtnX = 100, soundBtnY = 168;
	aboutBtnX = 100, aboutBtnY = 194;

	musicmutex = mainmenux + musicBtnX + ((buttonW - mute.getWidth()) / 2);
	musicmutey = mainmenuy + musicBtnY + ((buttonH - mute.getHeight()) / 2);

	soundmutex = mainmenux + soundBtnX + ((buttonW - mute.getWidth()) / 2);
	soundmutey = mainmenuy + soundBtnY + ((buttonH - mute.getHeight()) / 2);

	if(prevcanvasno == gApp::GAME_CANVAS) {
		root->menumusic.play();
		root->menumusic.setVolume(root->volume);
		root->menumusic.setLoopType(gBaseSound::LOOPTYPE_NORMAL);
		root->menumusic.setPaused(!root->musicon);
	}

	verifyx[0] = mainmenux + 382 - verify.getWidth() / 2 - 20;
	verifyx[1] = mainmenux + 390 + 20;
	verifyy = mainmenuy + 402 - verify.getHeight() - 10;
}

void MenuCanvas::update() {
	//gLogi("MenuCanvas update");

}

void MenuCanvas::draw() {
	background.draw(0, 0, getWidth(), getHeight());
	mainmenu.draw(mainmenux, mainmenuy);

	// Draw Male / Female checkboxes
	verify.drawSub(verifyx[0], verifyy, verify.getWidth() / 2, verify.getHeight(), verify.getWidth() / 2 * (1 - characterGender), 0, verify.getWidth() / 2, verify.getHeight());
	verify.drawSub(verifyx[1], verifyy, verify.getWidth() / 2, verify.getHeight(), verify.getWidth() / 2 * characterGender, 0, verify.getWidth() / 2, verify.getHeight());

	if (!root->musicon) {
		//gLogi("calisiyorum!\n" + gToStr(musicmutex) + ", " + gToStr(musicmutey));
		mute.draw(musicmutex, musicmutey);
	}

	if (!root->soundon) {
		//gLogi("calisiyorum!\n" + gToStr(soundmutex) + ", " + gToStr(soundmutey));
		mute.draw(soundmutex, soundmutey);
	}
}

void MenuCanvas::keyPressed(int key) {
}

void MenuCanvas::keyReleased(int key) {
}

void MenuCanvas::mouseMoved(int x, int y) {
}

void MenuCanvas::mouseDragged(int x, int y, int button) {
}

void MenuCanvas::mousePressed(int x, int y, int button) {

}

void MenuCanvas::mouseReleased(int x, int y, int button) {
	// Check Play Button is clicked?
	if ( (x >= (mainmenux + 75) && x <= (mainmenux + 215))
	  && (y >= mainmenuy + 295  && y <= mainmenuy + 355) ) {

		GameCanvas *cnv = new GameCanvas(root);
		cnv->setGender(characterGender);
		root->setCurrentCanvas(cnv);
		root->menumusic.stop();
	}

	if ( x >= verifyx[0] && x <= verifyx[0] + verify.getWidth() / 2 // Check Male Character check box is clicked?
		&& y >= verifyy && y <= verifyy + verify.getHeight()  ) {
		characterGender = 0;
	}

	if ( x >= verifyx[1] && x <= verifyx[1] + verify.getWidth() / 2 // Check Female Character check box is clicked?
		&& y >= verifyy && y <= verifyy + verify.getHeight()  ) {
		characterGender = 1;
	}

	//soundbtn
	if ( (x >= (mainmenux + soundBtnX) && x <= (mainmenux + soundBtnX + buttonW))	// Check Play Button is clicked?
	  && (y >= mainmenuy + soundBtnY  && y <= mainmenuy + soundBtnY + buttonH) ) {
		root->soundon = !root->soundon;
		gLogi("sound : " + gToStr(root->soundon));
		std::string updatestatement = "UPDATE Settings SET soundon = " + gToStr(root->soundon);
		root->settingsdb.execute(updatestatement);
	}

	//musicbtn
	if ( (x >= (mainmenux + musicBtnX) && x <= (mainmenux + musicBtnX + buttonW))	// Check Play Button is clicked?
	  && (y >= mainmenuy + musicBtnY  && y <= mainmenuy + musicBtnY + buttonH) ) {
		root->musicon = !root->musicon;
		root->menumusic.setPaused(!root->musicon);
		gLogi("music : " + gToStr(root->musicon));
		std::string updatestatement = "UPDATE Settings SET musicon = " + gToStr(root->musicon);
		root->settingsdb.execute(updatestatement);
	}

	//aboutbtn
	if ( (x >= (mainmenux + aboutBtnX) && x <= (mainmenux + aboutBtnX + buttonW))	// Check Play Button is clicked?
	  && (y >= mainmenuy + aboutBtnY  && y <= mainmenuy + aboutBtnY + buttonH) ) {
		AboutCanvas *cnv = new AboutCanvas(root);
		root->setCurrentCanvas(cnv);
	}


}

void MenuCanvas::mouseEntered() {
}

void MenuCanvas::mouseExited() {
}

void MenuCanvas::showNotify() {
}

void MenuCanvas::hideNotify() {
}

void MenuCanvas::setPrevCanvas(int prevCanvasNo) {
	prevcanvasno = prevCanvasNo;
}

