/*
 * gApp.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef EXAMPLES_TESTEXAMPLE_GAPP_H_
#define EXAMPLES_TESTEXAMPLE_GAPP_H_

#include "gBaseApp.h"
#include "gFmodSound.h"
#include "gDatabase.h"

class gApp : public gBaseApp {
public:
	static const int GAPP = 0, MENU_CANVAS = 1, GAME_CANVAS = 2, ABOUT_CANVAS = 3;

	gApp();
	~gApp();

	void setup();
	void update();

	bool soundon, musicon;
	float volume;

	gDatabase settingsdb;

	gFmodSound menumusic;
	gFmodSound gamemusic;
	gFmodSound soundnext;
	gFmodSound soundclick;
	gFmodSound soundgunshot;
	gFmodSound soundcharacterwalk;
	gFmodSound soundcharacterah;
	gFmodSound soundmonstergunshot;
	gFmodSound soundmonsterdeath;
	gFmodSound soundmonsterwalk;

	std::vector<int> settings;

};

#endif /* EXAMPLES_TESTEXAMPLE_GAPP_H_ */
