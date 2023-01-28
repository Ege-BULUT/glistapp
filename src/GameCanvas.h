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
	void setCamera(int xi, int yi, int x1, int y1, int x2, int y2);
	void setCameraToPrevious();
	void setMapBorders(float bx1, float by1, float bx2, float by2);
	void setMapBordersToPrevious();


private:
	bool DEBUG;

	static const int KEY_W = 2, KEY_A = 4, KEY_S = 8, KEY_D = 16;
	static const int MENU = -1, LOADING = 0, PLAYING = 1, PAUSED = 2, LOADSAVE = 3;
	bool paused = false;
	static const int IN_MAP = 0, IN_BUILDING = 1;
	int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;
	static const int BUTTON_GUI = 0, BUTTON_INGAME = 1;
    static const int Button_Type_Small = 0, Button_Type_Large = 1,
                     Button_Type_With_Electricity = 2, Button_Type_Effect = 3,
                     Button_Type_Billboard = 4, Button_Type_Paper = 5;

    static const int BB_P_Index = 0, BB_P_Title = 1,
    BB_P_ImgIndex = 2,  BB_P_Picked = 3, BB_P_Details = 4, BB_P_Reward = 5;

    std::array<int, 3> Buttons_Papers;
    std::array<int, 3> Buttons_on_Paper;

    std::array<gImage, 3> img_Buttons_Billboard;
	static const int Button_ExitBuilding = 0, Button_Armory = 1, Button_Potionary = 2, Button_Assassin = 3,
                     Button_Training = 4, Button_Debug = 5, Button_Billboard = 6;
	static const int X = 0, Y = 1, VEG_DES_TYPE = 2;
	std::array<std::array<float, 2>, 2> mapBoundaries;
	//races
	//static const int ROCK = 0, PAPER = 1, SCISSORS = 2;
	int ROCK = 0, PAPER = 1, SCISSORS = 2;
	int GRASS = 0, STONE = 1, TREE = 2;

	void createVegetation(int veg_type, int design_type, float x, float y, float sizeMultiplier);
	void drawVegetation();

	std::array<int, 3> env_amounts;
	std::vector<std::vector<std::vector<float>>> forests;
	//forests[1][min][X] - forests[1][min][Y]
	//forests[1][max][X] - forests[1][max][Y]

	std::vector<int> vegetationAmounts;

	std::vector<std::vector<std::vector<float>>> vegetationCoordinates;
	// usage :
	// vegetationCoords[TREE][0][X] || vegetationCoords[TREE][0][Y]
	// vegetationCoords[STONE][i][Y] etc...

	std::vector<std::vector<std::vector<float>>> vegetations;
	//vegetations[TYPE][DESIGN][X = 0||Y = 1||VEG_DES_TYPE = 2||SCALE = 3];

    // GUI - CharacterBar
    static const int ChBar_ChBar = 0, ChBar_Pr_BG = 1, ChBar_Pr_P = 2,
                     ChBar_Pr_B = 3, ChBar_HPBar = 4, ChBar_HPBar_B= 5,
                     ChBar_MPBar= 6, ChBar_MPBar_B = 7,ChBar_EXPBar = 8,
                     ChBar_EXPBar_B = 9, ChBar_Coin = 10, ChBar_Exp = 11;

    std::array<float, 12> characterbar_xs;
    std::array<float, 12> characterbar_ys;
    std::array<gImage, 12> img_characterbar;
    void drawCharacterBar();


	//GUI - MENUS
	gImage background_defocus;
	std::array<gImage, 8> img_menus;
	static const int MENU_VERTICAL = 0, MENU_HORIZONTAL = 1,
                     MENU_BILLBOARD = 7;
    int MENU_PAPER = 8, paperPressed = -1;
	static const int MENU_CENTERED = -1;
    static const int MENU_INDEX      = 0,
                     MENU_X          = 1, MENU_Y         = 2,
                     MENU_VISIBILITY = 3, MENU_TYPE      = 4,
                     MENU_TITLE      = 5, MENU_BTN_TYPE  = 6,
                     MENU_BTN_COUNT  = 7;

	int Menu_Stop = 0, Menu_Test = 1, Menu_Billboard = 2, Menu_Paper = 3;
	//int Menu_QUIZ_0 = 1, Menu_Quiz_1 = 2;
	std::vector<int> Menu_Quiz_Questions;

	void createMenu(
            std::vector<std::string> button_texts,
            std::string menu_title = " ",
            int x = MENU_CENTERED, int y = MENU_CENTERED,
            int menu_type = MENU_VERTICAL, int button_type = Button_Type_Large,
            bool menu_visibility = false);
    void drawMenus();
	void drawMenu(int menuIndex);
    void hideMenu(int menuIndex);
    void showMenu(int menuIndex);
    void toggleVisMenu(int menuIndex);
	std::vector<std::vector<std::string>> menus;
	/* Menu System v0.1
	 * menus[
	 * 	{
	 * 	"0", 			//menu_index 	- 0
	 * 	"x",			//menu_x		- 1
	 * 	"y",			//menu_y		- 2
	 *  "visibility"    //menu_vis      - 3
	 * 	"menuType", 	//menu_type 	- 4
	 * 	"Title",		//menu_title	- 5
	 * 	"btn_type",		//btn_types		- 6
	 * 	"btncount(2)",	//btn_count		- 7
	 * 	"bi0.string btn0",	//btn_0			- 8
	 * 	"bin.string btn1",  //btn_n			- 8+n
	 * 	//yukaridaki format : bi = button_index
	 * 	//button_index.button text'i, '.' ile ayirdik.
	 * 	},
	 * 	{
	 * 	...
	 * 	}
	 * ]
	 */

	//props
	static const int SPAWN_POINT = 0;
	static const int BILLBOARD = 1;
    std::array<float, 3> BB_paperXs; //Billboard paper xs
    std::array<float, 3> BB_paperYs; //Billboard paper ys


	//buildings
	//static const int SHOP_POTION = 0, SHOP_ARMORY = 1;
	int BUILDING_ROCK = 0, BUILDING_PAPER = 1, BUILDING_SCISSORS = 2;
	int BUILDING_TRAINING = 3;

	static const int propAmount = 1, buildingAmount = 10, NPCAmount = 3;
	std::array<int, buildingAmount> interiorAmounts; //her bina i?in o binanýn kaç iç odasý varsa ayrý ayrý tut.
	static const int maxInteriorAmount = 1;
	void createBuilding(int index, int index_outerImg, float x, float y, std::string innerinfos);
	void drawBuildings();
	int buildingPressed;
	std::vector<std::vector<std::string>> buildings;
	std::vector<int> currentInterior;
	/* Building Structure :
	 * [index, index_outerimg, x, y, innerinfo1, innerinfo2, innerinfo...]
	 * (innerinfo0 : index_interiorImg)
	 * (innerinfo1 : index_NPC)
	 * (innerinfo2 : index_NPCx)
	 * (innerinfo3 : index_NPCy)
	 * (innerinfo4 : playerspawnx)
	 * (innerinfo5 : playerspawny)
	 * (innerinfo6 : prop_amount) //prop amount in this interior
	 * (innerinfo7+: [prop_index1, x1, y1], [prop_index2, x2, y2]...
	 */

	// Training Ground :
    static const int TrainingGrounds_BG = 0,
                     TrainingGrounds_Cati25 = 1,
                     TrainingGrounds_Cati100 = 2,
                     TrainingGrounds_Area1 = 3,
                     TrainingGrounds_Area2 = 4,
                     TrainingGrounds_Kukla = 5,
                     TrainingGrounds_NPC = 6;

	std::array<gImage, 7> imgs_Training_Ground;
	std::array<int, 6> tg_coordinates;

	//animation
	static const int characterframeNum = 3;
	int characterframecounter, characterframeno;
	int characterframecounterlimit, characterframenum;

	//buttons
    static const int BTN_X = 0, BTN_Y = 1, BTN_TYPE = 2,
                     BTN_R = 3, BTN_G = 4, BTN_B = 5,
                     BTN_TEXTTYPE = 6, BTN_X2 = 7, BTN_Y2 = 8,
                     BTN_LOC = 9, BTN_VIS = 10;

	static const int btnAmount = 5;
	void createButton(
            std::string btntext, int btnx = 0, int btny = 0, int btntype = 0,
            int btnR = 255, int btnG = 255, int btnB = 255, int texttype = 0,
            int btnLocation = BUTTON_GUI, bool visibility = true);

	void updateButtons();
    void drawButton(int btn_index);

	void drawButtons();
	int buttonPressed;
	gFont buttontext;
	std::vector<std::string> buttonTexts;
	std::vector<std::vector<int>> buttons;
	//[
	// [x, y, btntype, R, G, B, textype, x2, y2, btnLocation, visibility, ]
	////0, 1, 2,       3, 4, 4, 6,       7,  8, 9, 10 ]
	//]

	void listener(); //button & building & npc vs clicklerini dinlemek i?in

	void updateLoad(int index);
	void drawLoad();

	void setInitialVariables();

//	std::vector<std::vector<float>> scatterRandPointsOnGeometry(std::vector<float[2]> boundaries, int pointAmount);
	void scatterRandPointsOnGeometry(std::vector<float[2]> boundaries);

	void drawGame();
	void updateMap();
	void drawMapBG();
	void drawMid();
	void drawProps();
    void drawCharacter();
	void drawMapFG();
	void drawGUI();
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);

	void updateCharacter();
	void updateCamera();

	gApp* root;

	/* gImages */
	gImage img_background;
	gImage img_blueprint;
	gImage img_menu;
	gImage img_dialogbox;

	gImage img_button[btnAmount];
	gImage img_props[propAmount];
	gImage img_buildings[buildingAmount];
	gImage img_interior[buildingAmount][maxInteriorAmount]; //[buildingAmount][max(interiorAmounts)]
	std::array<std::array<gImage, 5>, 3> img_ENVs;
	//gImage img_ENVs[3][5]; //istersen bu 3 ve 4 degerleri icin bi int olusturup onu da verebilirsin
						// 3 dedik -> grass-stone-tree | 4 de maks prop sayisi kategorilerdeki
	std::array<gImage, NPCAmount> img_NPCs;
	std::array<gImage, 3> img_characterBases;
	std::vector<std::vector<gImage>> img_characters;
	// img_Characters[characterIndex(ci)][ITEM_INDEX]
	// 2nd Array: [img_base..., img_armor, img_helmet, img_weapon, img_effect]
	//           [ci][0]      [ci][1]    [ci][2]     [ci][3]     [ci][4]
	//total character amount on the current map;

	//static const int CBASE = 0, ARMOR = 1, HELMET = 2, WEAPON = 3, EFFECT = 4;
	int CBASE = 0, ARMOR = 1, HELMET = 2, WEAPON = 3, EFFECT = 4;
	gImage tmpimg;
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
	/*[CharacterIndex, TotalItemAmount, Total Coin, [Items]]
	 *[Items] : {Item_index, Amount}
	*/
	std::vector<std::vector<int>> characterEquipped;
	// 1st Array: characterIndex;
	// 2nd Array: [i_base..., i_armor, i_helmet, i_weapon, i_effect] (i:index)
	// 		      [0]        [1]      [2]       [3]       [4]

	std::vector<std::vector<int>> shopInventories;
	//[ShopIndex, TotalItemAmount, Total Coin, [Items]]

	int globalscalelevel;
	int characterscalelevel;
	std::vector<float> scalelevels;
	//[0.5, 1.0, 1.2, 1.5, 1.8, 2.5, 3.0


	std::array<int, propAmount> propXs;
	std::array<int, propAmount> propYs;
	std::array<int, buildingAmount> buildingXs;
	std::array<int, buildingAmount> buildingYs;
/*
	int propXs[propAmount];
	int propYs[propAmount];
	int buildingXs[buildingAmount];
	int buildingYs[buildingAmount];
*/

	gFont font_load_1, font_load_2, font_button_1, font_ingame_1;
	static const int totalfontsize = 4;
	std::array<gFont, totalfontsize> fonts;
	//gFont fonts[totalfontsize];
	std::vector<int> fontsizes;
	std::vector<std::string> loadingtext;

	int game_status;
	int game_map;
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

	float camera_x, camera_y;
	float mz_x1, mz_y1, mz_x2, mz_y2; //mz : movement zone
	float border_x1, border_y1, border_x2, border_y2;


	float camx, camy, zoom;
	float camx1, camy1;
	float camx2, camy2;
	float prev_camx, prev_camy,
		  prev_camx1, prev_camy1,
		  prev_camx2, prev_camy2;

	float borderx1, bordery1,
		  borderx2, bordery2;
	float prev_borderx1, prev_bordery1,
		  prev_borderx2, prev_bordery2;

	float mousex, mousey;
	float clickx, clicky;
	bool  mouseHold;
	float mouseHoldedFor_frames, mouseHoldedFor_seconds;
};

#endif /* GAMECANVAS_H_ */
