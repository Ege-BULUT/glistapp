 /*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef SRC_MAINMENU_H_
#define SRC_MAINMENU_H_

#include "gBaseCanvas.h"
#include "GameCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"
#include "gBaseApp.h"


class MainMenu : public gBaseCanvas {
public:
	MainMenu(gApp* root);
	virtual ~MainMenu();

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

	// // // // // // // // // // // // // // // // //

	static const int MENU = -1, LOADING = 0, PLAYING = 1, PAUSED = 2, LOADSAVE = 3;
	static const int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;
	static const int buttonImageAmount = 4;

	int framecounter, seccounter;

	void createButton(std::string btntext, int btnx = 0, int btny = 0, int btntype = 0, int btnR = 255, int btnG = 255, int btnB = 255, int texttype = 0);
	void drawButton(std::string btntext, int btnx = 0, int btny = 0, int btntype = 0, int btnR = 255, int btnG = 255, int btnB = 255, int texttype = 0); //0 -> default(15) | 1 -> savefont(12)
	void drawButtons();
	void listenButtons();
	gFont buttontext;

	std::vector<gFont> font;
	std::vector<int> fontsizes;
	gImage img_button[buttonImageAmount];

	gImage img_background;
	gImage img_statue;
	gImage img_blueprint;
	gImage img_menu;
	gImage img_dialogbox;

	//[
	// [x, y, btntype, R, G, B, textype, x2, y2]
	////0, 1, 2,       3, 4, 4, 6,       7,  8 ]
	//]
	std::vector<std::vector<int>> buttons;
	std::vector<std::string> buttonTexts;

private:

	void initilaize();
	void updateLoad(int index);
	void drawLoad();
	void setInitialVariables();
	void drawMenu();

	void savesMenu();
	gApp* root;

	// TODO: BURADA KALDIN, .cpp dosyasýnda bunlarý yükle
	std::vector<std::string> loadingtext;

	int status;
	int loadindex;

	float globalscale;

	int buttonPressed;

	int x_mainmenu, y_mainmenu, x_btnmm, x_btnmm2, y_btnmm; //mainmenu
	int statue1x, statue2x, statuey;
	bool loadsaveanimation;

};

#endif /* GAMECANVAS_H_ */
