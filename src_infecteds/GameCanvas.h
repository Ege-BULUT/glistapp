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
#include "Enemy.h"
#include "gBaseApp.h"
#include "gFont.h"
#include "gFmodSound.h"

class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gApp* root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered();
	void mouseExited();

	void setGender(int CharacterGender);
	void setLevelNo(int LevelNo);

	void showNotify();
	void hideNotify();

private:
	gApp* root;

	static const int KEY_W = 2, KEY_A = 4, KEY_S = 8, KEY_D = 16;
	static const int BULLET_SENDER_CHARACTER = 0, BULLET_SENDER_ENEMY = 1;
	static const int ENEMY_ANIMATION_WALK = 0, ENEMY_ANIMATION_ATTACK = 1, ENEMY_ANIMATION_DEATH = 2;
	static const int LOADING = 0, PLAYING = 1;
	static const int DEFAULT = 0, WIN = 1, LOSE = -1, PAUSE = 2;
	static const int loadanimframenum = 4;
	static const int characterframenum = 6;
	static const int enemynum = 20;
	static const int enemyanimationnum = 3;
	static const int enemymaxframenum = 16;

	gFont scorefont;

	gImage loadbackground, loadtext, loadprogressbar;
	gImage background;
	gImage character[characterframenum];
	gImage enemyimage[enemyanimationnum][enemymaxframenum];
	gImage levelmap;
	gImage levelmapsign[2];
	gImage bulletimage;
	gImage enemybulletimage;
	gImage charactericon;
	gImage healthicon;
	gImage hpprogressbar, shieldbar;
	gImage progressbarframe, progressbarbackground;
	gImage shieldicon;
	gImage dialoguewin, dialoguelose, dialoguepause;
	gImage btncontinue, btnexit, btnmainmenu, btnnextlevel, btnreplay;

	int dialogx, dialogy;
	int leftbtnx, rightbtnx;
	int btny;

	int levelno;

	float cx, cy;
	float crot;
	int keystate;
	float cdx, cdy;
	float cspeed;
	float bulletspeed;
	float camx, camy;
	float camx1, camy1;
	float camx2, camy2;
	float mousex, mousey;
	float muzzle_dangle;
	float muzzle_distance;
	float enemyhandangle[2], enemyhanddistance[2];
	bool isFiring;
	bool musicOn, soundOn;

	int gamestatus;
	int status;

	int loadcounter;
	int loadtextx, loadtexty, loadprogx, loadprogy;
	int loadingtextw[loadanimframenum];
	int loadanimcounter, loadanimframeno, loadcounterlimit;

	int score;
	int scorex;
	int scoretextx, scoretexty;
	int scorefontsize;

	int characterGender;
	int characterframeno;
	int characterframecounter;
	int characterframecounterlimit;
	int levelmapx, levelmapy;
	int firerate, bulletframecounter;
	int enemyframenum[enemyanimationnum];
	int aliveenemynum;
	int health, shield;
	int ciconx, cicony,
		hiconx, hicony,
		siconx, sicony,
		hpbarx, hpbary,
		shbarx, shbary;
	/*
	cicon = charactericon
	hicon = healthicon
	sicon = shieldicon
	*/

	std::vector<Enemy> enemy;
	std::vector<std::vector<float>> bullets;
	std::string characterPath, charactericonPath;

	std::string scoretext;

	void loadAssets();
	void loadAsset(int assetNo);
	void loadVariables();
	void drawLoadingProgress();
	void loadInitialAsset();

	void generateBullet(float bulletX, float bulletY, float bulletdx, float bulletdy, float bulletRot, int bulletSender);
	void updateCharacter();
	void updateCamera();
	void updateEnemies();
	void updateBullets();
	void drawBackground();
	void drawCharacter();
	void drawEnemies();
	void drawLevelMap();
	void drawBullets();
	void drawGUI();
	void endGame();
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);

};

#endif /* GAMECANVAS_H_ */
