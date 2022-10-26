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
	bool DEBUG;
	static const int KEY_W = 2, KEY_A = 4, KEY_S = 8, KEY_D = 16;

	static const int ROCK = 0, PAPER = 1, SCISSORS = 2;
	static const int MENU = -1, LOADING = 0, PLAYING = 1, PAUSED = 2, LOADSAVE = 3;
	static const int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;

	static const int characterframeNum = 3;
	int characterframecounter, characterframeno;
	int characterframecounterlimit, characterframenum;
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
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);

	void updateCharacter();
	void updateCamera();

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

	gImage img_characterBases[3];
	std::vector<std::vector<gImage>> img_characters;
	// img_Characters[characterIndex(ci)][ITEM_INDEX]
	// 2nd Array: [img_base..., img_armor, img_helmet, img_weapon, img_effect]
	//           [ci][0]      [ci][1]    [ci][2]     [ci][3]     [ci][4]
	//total character amount on the current map;

	static const int CBASE = 0, ARMOR = 1, HELMET = 2, WEAPON = 3, EFFECT = 4;
	std::vector<std::vector<std::vector<gImage>>> img_equipables;
	/*
	 *img_equipables[RACE][TYPE][INDEX]
	 *img_equipables[STONE][ARMOR][3]
	 *img_equipables[PAPER][WEAPON][6]
	 *img_equipables[EFFECT][TYPE][Index]
	 */
	int playerIndex; //Sunucudan al bunu ilerde
	int totalCharacterAmount;
	/* All Characters on the current map */
	std::vector<std::vector<int>> characters;
	//[index, cx, cy, crot, animationFrameNo, race, level, [stats]]
	// 0      1   2   3     4                 5     6      7,8...

	/* Character Inventory */
	std::vector<int> characterInventory;
	//[CharacterIndex, TotalItemAmount, Total Coin, [Items]]

	std::vector<std::vector<int>> characterEquipped;
	// 1st Array: characterIndex;
	// 2nd Array: [i_base..., i_armor, i_helmet, i_weapon, i_effect] (i:index)
	// 		      [0]        [1]      [2]       [3]       [4]


	std::vector<std::vector<int>> shopInventories;
	//[ShopIndex, TotalItemAmount, Total Coin, [Items]]

	int propXs[propAmount];
	int propYs[propAmount];
	int buildingXs[buildingAmount];
	int buildingYs[buildingAmount];

	std::vector<gFont> font;
	std::vector<int> fontsizes;
	std::vector<std::string> loadingtext;

	int status;
	int loadindex;

	float globalscale;

	int framecounter;
	int seccounter;

	////////////////////////////////////

	float cx, cy;
	int crot; //character rotation
	float mrot; //mouse rotation
	int keystate;
	float cdx, cdy;
	float cspeed;
	float camx, camy, zoom;
	float camx1, camy1;
	float camx2, camy2;
	float mousex, mousey;
	float clickx, clicky;
	bool  mouseHold;
	float mouseHoldedFor_frames, mouseHoldedFor_seconds;
};

#endif /* GAMECANVAS_H_ */
