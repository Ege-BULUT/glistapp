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

	// // // // // // // //

	void initilaize();

private:

	static const int MENU = -1, LOADING = 0, PLAYING = 1, PAUSED = 2, LOADSAVE = 3;
	static const int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;

	//props
	static const int SPAWN_POINT = 0;

	//buildings
	static const int SHOP_POTION = 0, SHOP_ARMORY = 1;

	//bu sayýlarý database'e ekle oradan çek
	static const int btnAmount = 4, propAmount = 1, buildingAmount = 2, NPCAmount = 2;
	static const int maxInteriorAmount = 1;
	int interiorAmounts[buildingAmount]; //her bina için o binanýn kaç iç odasý varsa ayrý ayrý tut.
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
	gImage img_blueprint;
	gImage img_menu;
	gImage img_dialogbox;

	gImage img_button[btnAmount];
	gImage img_props[propAmount];
	gImage img_buildings[buildingAmount];
	gImage img_interior[buildingAmount][maxInteriorAmount]; //[buildingAmount][max(interiorAmounts)]
	gImage img_NPCs[NPCAmount];

	int propXs[propAmount];
	int propYs[propAmount];
	int buildingXs[buildingAmount];
	int buildingYs[buildingAmount];

	std::vector<gFont> font;
	std::vector<int> fontsizes;
	std::vector<std::string> loadingtext;

	int game_status;
	int loadindex;

	float globalscale;

	int framecounter;
	int seccounter;

	////////////////////////////////////

	int camx, camy, zoom;
	int cx, cy, crot, cdx, cdy;

};

#endif /* GAMECANVAS_H_ */
