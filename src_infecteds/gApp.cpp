/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gApp.h"
#include "GameCanvas.h"
#include "MenuCanvas.h"

gApp::gApp() {

}

gApp::~gApp() {
}

void gApp::setup() {

	settingsdb.openDatabase("settings.db");
	std::string searchstatement = "SELECT * FROM Settings";
	std::string selectdata = " ";

	settingsdb.execute(searchstatement);

	while (settingsdb.hasSelectData()) {
		selectdata = settingsdb.getSelectData();
	}

	musicon = gToInt(selectdata.substr(2, 1));
	soundon = gToInt(selectdata.substr(4, 1));

	volume = 0.1f;

	menumusic.loadSound("birthofahero.mp3");
	gamemusic.loadSound("savage-law.mp3");

	soundnext.loadSound("sound_next5.wav");
	soundclick.loadSound("sound_click2.wav");

	soundcharacterwalk.loadSound("player_run.mp3");
	soundgunshot.loadSound("gun_shot_2.wav");
	soundcharacterah.loadSound("ah.wav");
	//soundmonstergunshot.loadSound("gun_shot_2.wav");
	soundmonsterdeath.loadSound("monster_death.wav");
	soundmonsterwalk.loadSound("monster_footsteps.wav");

	menumusic.play();
	menumusic.setLoopType(gBaseSound::LOOPTYPE_NORMAL);
	menumusic.setPaused(!musicon);

	MenuCanvas *cnv = new MenuCanvas(this);
	cnv->setPrevCanvas(GAPP);
	appmanager->setCurrentCanvas(cnv);

}

void gApp::update() {
}

