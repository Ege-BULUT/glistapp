 /*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gApp.h"
#include "MainMenu.h"

gApp::gApp() {
}

gApp::~gApp() {
}

void gApp::setup() {
	gLogi("Set MainMenu as Canvas");
	MainMenu *cnv = new MainMenu(this);
	appmanager->setCurrentCanvas(cnv);
}

void gApp::update() {

}
