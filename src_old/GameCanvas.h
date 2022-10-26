 /*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GAMECANVAS_H_
#define GAMECANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"

class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gApp* root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();

private:

	static const int MENU = -1, LOADING = 0, PLAYING = 1, PAUSED = 2, LOADSAVE = 3;
	static const int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;
	static const int SPAWN_POINT = 0;
	static const int btnAmount = 4, propAmount = 1;
	int buttonPressed;
	void createButton(std::string btntext, int btnx = 0, int btny = 0, int btntype = 0, int btnR = 255, int btnG = 255, int btnB = 255, int texttype = 0);
	void drawButton(std::string btntext, int btnx = 0, int btny = 0, int btntype = 0, int btnR = 255, int btnG = 255, int btnB = 255, int texttype = 0); //0 -> default(15) | 1 -> savefont(12)
	void drawButtons();
	void listenButtons();
	gFont buttontext;

	//[
	// [x, y, btntype, R, G, B, textype, x2, y2]
	////0, 1, 2,       3, 4, 4, 6,       7,  8 ]
	//]
	std::vector<std::vector<int>> buttons;
	std::vector<std::string> buttonTexts;

	void initilaize();
	void updateLoad(int index);
	void drawLoad();

	void setInitialVariables();

	void drawGame();
	void drawMapBG();
	void drawMid();
	void drawCharacter();
	void drawMapFG();
	void drawGUI();

	gApp* root;

	gImage img_background;
	gImage img_menu;
	gImage img_dialogbox;
	gImage img_button[btnAmount];
	gImage img_props[propAmount];

	int propXs[propAmount];
	int propYs[propAmount];

	std::vector<gFont> font;
	std::vector<int> fontsizes;
	std::vector<std::string> loadingtext;

	int status;
	int loadindex;

	float globalscale;

	int framecounter;
	int seccounter;

	////////////////////////////////////

	int camx, camy, zoom;
	int cx, cy, crot, cdx, cdy;
};

#endif /* GAMECANVAS_H_ */
