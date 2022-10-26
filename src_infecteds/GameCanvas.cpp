/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 *
 *
 *
 *
 *  TODO: �dev: Enemy isColliding d�zeltilecek (yak�n vuru�ta uzaktan vurabiliyor), Enemy'ler ekran�n d���nda ate� ediyor onun d�zeltilmesi gerek.
 *
 *
 */

#include "gBaseApp.h"
#include "gApp.h"
#include "GameCanvas.h"
#include "MenuCanvas.h"
#include "AboutCanvas.h"

GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {

	gamestatus = LOADING;
	loadcounter = 0;

	loadInitialAsset();

}

void GameCanvas::update() {
//	gLogi("GameCanvas") << "update";

	if(gamestatus == LOADING) {
		loadAssets();
		return;
	}
	else {
	if(status == DEFAULT) {
			updateCharacter();
			updateCamera();
			updateEnemies();
			updateBullets();
		}
	}
}

void GameCanvas::draw() {

	if(gamestatus == LOADING) {
		drawLoadingProgress();
		return;
	}
//	gLogi("GameCanvas") << "draw";
	setColor(255,255,255);
	if(status != DEFAULT) {
		setColor(60,60,60);
	}
	drawBackground();
	drawEnemies();
	drawCharacter();
	drawBullets();
	setColor(255,255,255);
	drawGUI();
}

void GameCanvas::setGender(int CharacterGender) {
	characterGender = CharacterGender;
}

void GameCanvas::setLevelNo(int LevelNo) {
	levelno = LevelNo;
}

void GameCanvas::updateCharacter() {
	// Bu kontrolleri burada yapmak yerine switchcase'de yapsaydık yalnızca 1 defa çalışırdı
	crot = gRadToDeg(std::atan2(mousey - (cy + (character[0].getHeight() / 2)), mousex - (cx + (character[0].getWidth() / 2)))) + 90.0f;


	if ((keystate & KEY_W) != 0) {
		//gLogi("W BASILIYOR");
		//cdx = std::sin(gDegToRad(crot)) * cspeed; // cdx - cdy
		//cdy = -std::cos(gDegToRad(crot)) * cspeed;
		cdy = -1 * cspeed;
	}
	else if ((keystate & KEY_S) != 0) {
		//gLogi("S BASILIYOR");
		//cdx = -std::sin(gDegToRad(crot)) * cspeed;
		//cdy = std::cos(gDegToRad(crot)) * cspeed;
		cdy = 1 * cspeed;
	}

	// Çaprazlara hareket edebilmek için A ve D'yi W ve S'ten ayırdık.
	if ((keystate & KEY_A) != 0) {
		//gLogi("A BASILIYOR");
		//cdx += -std::cos(gDegToRad(crot)) * cspeed;
		//cdy += -std::sin(gDegToRad(crot)) * cspeed;
		cdx = -1 * cspeed;
	}
	else if ((keystate & KEY_D) != 0) {
		//gLogi("D BASILIYOR");
		//cdx += std::cos(gDegToRad(crot)) * cspeed;
		//cdy += std::sin(gDegToRad(crot)) * cspeed;
		cdx = 1 * cspeed;

	}

	//Character movement
	if ( cdx != 0.0f || cdy != 0.0f ) {
		characterframecounter++;
		characterframecounterlimit = 12 / cspeed;
		if ( characterframecounter >= characterframecounterlimit ) {
			characterframeno++;
			if(!root->soundcharacterwalk.isPlaying() && root->soundon) {
				root->soundcharacterwalk.play();
			}
			if (characterframeno >= characterframenum){
				characterframeno = 0;
			}
			characterframecounter = 0;
		}
	}
	//root->soundcharacterwalk.stop();
	if(isFiring) {

		float mdx = std::sin(gDegToRad(crot + muzzle_dangle)) * muzzle_distance - (bulletimage.getWidth() / 2);
		float mdy = -std::cos(gDegToRad(crot + muzzle_dangle)) * muzzle_distance - (bulletimage.getHeight() / 2);
		float cbx = cx + (character[0].getWidth() / 2) + mdx + camx;
		float cby = cy + (character[0].getHeight() / 2) + mdy + camy;
		float dx = std::sin(gDegToRad(crot)) * (bulletspeed);
		float dy = -std::cos(gDegToRad(crot)) * (bulletspeed);
		float brot = crot;
		int sender = BULLET_SENDER_CHARACTER;
		generateBullet(cbx, cby, dx, dy, brot, sender);
	}

	cx += cdx;
	cy += cdy;


}

void GameCanvas::updateCamera() {
	if (cx < camx1 || cx + character[0].getWidth() > camx2) {
		cx -= cdx;
		camx += cdx;
		if (camx < 0) {
			camx = 0;
			camx1 = 0;
		}else {
			camx1 = getWidth() >> 2;
		}
		if (camx + getWidth() >= background.getWidth()) {
			camx = background.getWidth() - getWidth();
			camx2 = getWidth();
		} else {
			camx2 = (getWidth() * 3) >> 2;
		}
	}

	if (cy < camy1 || cy + character[0].getHeight() > camy2) {
		cy -= cdy;
		camy += cdy;
		if (camy < 0) {
			camy = 0;
			camy1 = 0;
		}else {
			camy1 = getHeight() >> 2;
		}
		if (camy + getHeight() >= background.getHeight()) {
			camy = background.getHeight() - getHeight();
			camy2 = getHeight();
		} else {
			camy2 = (getHeight() * 3) >> 2;
		}
	}

	//delta degerlerini sifirliyoruz
	cdx = 0;
	cdy = 0;
}

void GameCanvas::updateEnemies() {
	for(int i = 0; i < enemynum; i++) {
		if(enemy[i].getX() + enemyimage[0][0].getWidth() >= camx &&
		enemy[i].getX() < camx + getWidth() &&
		enemy[i].getY() + enemyimage[0][0].getHeight() >= camy &&
		enemy[i].getY() < camy + getHeight()) {

		//İnce ayar yapılacak, hitboxlar daha iyileştirilebilir.
		bool isColliding = checkCollision(enemy[i].getX() + 50, enemy[i].getY() + 25, enemy[i].getX() + 50 + 160, enemy[i].getY() + 25 + 145,
				cx + camx + 0, cy + camy + 48, cx + camx + character[0].getWidth(), cy + camy + character[0].getHeight());

		if(!(enemy[i].getAnimationNo() == ENEMY_ANIMATION_DEATH)){

			if(isColliding) {
				enemy[i].setAnimationNo(ENEMY_ANIMATION_ATTACK);
				enemy[i].setFrameNum(enemyframenum[ENEMY_ANIMATION_ATTACK]);
				if(enemy[i].getFrameNo() == 2 || enemy[i].getFrameNo() == 6) {
					if(shield <= 0) {
						shield = 0;
						health -= 2;
						if(!root->soundcharacterah.isPlaying() && root->soundon) {
							root->soundcharacterah.play();
							root->soundcharacterah.setVolume(1.0f);
						}
						score -= 2;
						scorex = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(gToStr(score))) / 2;
					}
					else shield -= 2;
					if(!root->soundcharacterah.isPlaying() && root->soundon) {
						root->soundcharacterah.play();
						root->soundcharacterah.setVolume(0.5f);
					}
				}
				if(health <= 0){
					health = 0;
					scorex = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(gToStr(score))) / 2;
					//gLogi("OYUNU KAYBETTINIZ!");
					status = LOSE;
					}
				}

			else {
				enemy[i].setAnimationNo(ENEMY_ANIMATION_WALK);
				enemy[i].setFrameNum(enemyframenum[ENEMY_ANIMATION_WALK]);

				if(enemy[i].getFrameNo() >= enemyframenum[ENEMY_ANIMATION_WALK]) {
					enemy[i].setFrameNo(0);
				}

				enemy[i].setRotation(gRadToDeg(std::atan2((cy + camy + (character[0].getHeight() / 2)) - (enemy[i].getY() + (enemyimage[0][0].getHeight() / 2)),
									(cx + camx + (character[0].getWidth() / 2)) - (enemy[i].getX() + (enemyimage[0][0].getWidth() / 2)))) - 90.0f + 360.0f);
					float enemydx = -std::sin(gDegToRad(enemy[i].getRotation())) * 1.2f;
					float enemydy = std::cos(gDegToRad(enemy[i].getRotation())) * 1.2f;
					enemy[i].setX(enemy[i].getX() + enemydx);
					enemy[i].setY(enemy[i].getY() + enemydy);

					if(!root->soundmonsterwalk.isPlaying() && root->soundon) {
						root->soundmonsterwalk.play();
					}
				}
			}
		}

			enemy[i].nextFrame();

			if(enemy[i].getAnimationNo() == ENEMY_ANIMATION_WALK && (enemy[i].getFrameNo() == 2 || enemy[i].getFrameNo() == 6)) {
					int handno = enemy[i].getFrameNo() / 6; //  2 ile 6'yı böldüğümüzde 0'a yuvalanıyor, 6 ile 6 bölündüğünde 1 oluyor.
					float enemymuzzledistanceX = std::sin(gDegToRad(enemy[i].getRotation() + enemyhandangle[handno])) * enemyhanddistance[handno] - (bulletimage.getWidth() / 2);
					float enemymuzzledistanceY = -std::cos(gDegToRad(enemy[i].getRotation() + enemyhandangle[handno])) * enemyhanddistance[handno] - (bulletimage.getWidth() / 2);
					float bx = enemy[i].getX() + enemyimage[0][0].getWidth() / 2 + enemymuzzledistanceX;
					float by = enemy[i].getY() + enemyimage[0][0].getHeight() / 2 + enemymuzzledistanceY;
					float bdx = -std::sin(gDegToRad(enemy[i].getRotation())) * (bulletspeed);
					float bdy = std::cos(gDegToRad(enemy[i].getRotation())) * (bulletspeed);
					float brot = enemy[i].getRotation();
					int sender = BULLET_SENDER_ENEMY;
					generateBullet(bx, by, bdx, bdy, brot, sender);
				}

			}

	}

void GameCanvas::updateBullets() {

	int bulletnum = bullets.size();
	for(int i = bulletnum - 1; i >= 0; i--) {
		bullets[i][0] += bullets[i][2]; //bullet in x i += bullet in dx i
		bullets[i][1] += bullets[i][3];
		bullets[i][5]++;

		if(bullets[i][5] >= 90) {
			bullets.erase(bullets.begin() + i);
			continue;
		}

		if(bullets[i][6] == BULLET_SENDER_CHARACTER) {

			for(int j = 0; j < enemynum; j++) {

				if(enemy[j].getAnimationNo() == ENEMY_ANIMATION_DEATH) continue;

				bool isColliding = checkCollision(enemy[j].getX() + 50, enemy[j].getY() + 25, enemy[j].getX() + 50 + 160, enemy[j].getY() + 25 + 145,
						bullets[i][0], bullets[i][1], bullets[i][0] + bulletimage.getWidth(), bullets[i][1] + bulletimage.getHeight());

				if(isColliding) {
					//Mermi düşmana çarptı.
					enemy[j].setAnimationNo(ENEMY_ANIMATION_DEATH);
					enemy[j].setFrameNum(enemyframenum[ENEMY_ANIMATION_DEATH]);
					enemy[j].setFrameNo(0);
					enemy[j].setLooping(false);

					if(!root->soundmonsterdeath.isPlaying() && root->soundon) {
						root->soundmonsterdeath.play();
					}

					aliveenemynum--;

					score += 50;
					scorex = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(gToStr(score))) / 2;

					if(aliveenemynum <= 0) {
						aliveenemynum = 0;
						//gLogi("OYUNU KAZANDINIZ!");
						status = WIN;
					}
					bullets.erase(bullets.begin() + i);
					break;
				}

			}
		}

		else if(bullets[i][6] == BULLET_SENDER_ENEMY) {

			bool isColliding = checkCollision(cx + camx, cy + camy, cx + character[0].getWidth() + camx, cy + character[0].getHeight() + camy,
					bullets[i][0], bullets[i][1], bullets[i][0] + bulletimage.getWidth(), bullets[i][1] + bulletimage.getHeight());
			if(isColliding) {

					if(shield <= 0) {
						shield = 0;
						health -= 2;
						if(!root->soundcharacterah.isPlaying() && root->soundon) {
							root->soundcharacterah.play();
							root->soundcharacterah.setVolume(1.0f);
						}
						score -= 2;
						if(score <= 0) {
							score = 0;
						}
						scorex = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(gToStr(score))) / 2;
					}
					else {
						shield -= 2;
						if(!root->soundcharacterah.isPlaying() && root->soundon) {
							root->soundcharacterah.play();
							root->soundcharacterah.setVolume(0.5f);
						}
					}
					//gLogi("can") << health;

					if(health <= 0) {
						health = 0;
						//gLogi("OYUNU KAYBETTINIZ!") << health;
						status = LOSE;
					}

					bullets.erase(bullets.begin() + i);
					break;
				}
			}



	}
}

void GameCanvas::drawBackground() {
	background.drawSub(0, 0, getWidth(), getHeight(), camx, camy, getWidth(), getHeight());

}

void GameCanvas::drawCharacter() {

	character[characterframeno].draw(cx, cy, character[0].getWidth(), character[0].getHeight(), crot); //void draw(int x, int y, int w, int h, float rotate);
}

void GameCanvas::drawEnemies() {
	for(int i = 0; i < enemynum; i++) {
		enemyimage[enemy[i].getAnimationNo()][enemy[i].getFrameNo()].draw(enemy[i].getX() - camx, enemy[i].getY() - camy, enemyimage[0][0].getWidth(), enemyimage[0][0].getHeight(), enemy[i].getRotation());
	}

}

void GameCanvas::drawLevelMap() {
	levelmap.draw(levelmapx, levelmapy);
	for(int i = 0; i < enemynum; i++) {
		if(enemy[i].getAnimationNo() != ENEMY_ANIMATION_DEATH)
			levelmapsign[1].draw(levelmapx + 2 + (enemy[i].getX() / 32), levelmapy + 2 + (enemy[i].getY() / 32));
	}
	levelmapsign[0].draw(levelmapx + 2 + ((cx + camx) / 32), levelmapy + 2 + ((cy + camy) / 32));
}

void GameCanvas::drawBullets() {

	for(int i = 0; i < bullets.size(); i++) {

			bulletimage.draw(bullets[i][0] - camx, bullets[i][1] - camy, bulletimage.getWidth(), bulletimage.getHeight(), bullets[i][4]);

	}
}

void GameCanvas::drawGUI() {

	//5,8
	if(status == PAUSE) {
		dialoguepause.draw(dialogx, dialogy);
		btncontinue.draw(leftbtnx, btny);
		btnmainmenu.draw(rightbtnx, btny);
		scorefont.drawText(gToStr(score), scorex, scoretexty - scorefontsize * 1.5f);
		scorefont.drawText(scoretext, scoretextx, scoretexty);

	}

	else if(status == LOSE) {
		dialoguelose.draw(dialogx, dialogy);
		btnreplay.draw(leftbtnx, btny);
		btnmainmenu.draw(rightbtnx, btny);

		setColor(255,0,0);
		scorefont.drawText(gToStr(score), scorex, scoretexty - scorefontsize * 1.5f);
		setColor(255,255,255);
		scorefont.drawText(scoretext, scoretextx, scoretexty);

	}

	else if(status == WIN) {
		dialoguewin.draw(dialogx, dialogy);

		if(levelno == 2){
			btnexit.draw(leftbtnx, btny); 	//exit btn
		} else {
			btnnextlevel.draw(leftbtnx, btny); 	//next level btn
		}
		btnmainmenu.draw(rightbtnx, btny);
		setColor(0,255,0);
		scorefont.drawText(gToStr(score), scorex, scoretexty - scorefontsize * 1.5f);
		setColor(255,255,255);
		scorefont.drawText(scoretext, scoretextx, scoretexty);

	}

	else if (status == DEFAULT) {
		drawLevelMap();
		charactericon.draw(ciconx, cicony);
		healthicon.draw(hiconx, hicony);
		shieldicon.draw(siconx, sicony);
		progressbarbackground.draw(hpbarx + 5, hpbary + 8);
		hpprogressbar.draw(hpbarx + 5, hpbary + 8, hpprogressbar.getWidth() * health / 100, hpprogressbar.getHeight());
		progressbarframe.draw(hpbarx, hpbary);

		progressbarbackground.draw(shbarx + 5, shbary + 8);
		shieldbar.draw(shbarx + 5, shbary + 8, shieldbar.getWidth() * shield / 100, shieldbar.getHeight());
		progressbarframe.draw(shbarx, shbary);
	}

}

void GameCanvas::keyPressed(int key) {
	//gLogi("Key Code : ") << "keyPressed:" << key;
	int pressed = 0;
	switch (key){
		case 87:
			pressed = KEY_W;
			break;
		case 65:
			pressed = KEY_A;
			break;
		case 83:
			pressed = KEY_S;
			break;
		case 68:
			pressed = KEY_D;
			break;
		case 256:
			if(status == PAUSE) {
				status = DEFAULT;
			}
			else if (status == DEFAULT) {
				status = PAUSE;
			}
			break;
		case 340:
				cspeed += 4.0f; // Shift tusuna basildiginda karakter hizini artiriyoruz.
			break;
		default:
			break;
	}
	keystate |= pressed; // bitwise için '+='

}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;

	int released = 0;
		switch (key){
			case 87:
				released = KEY_W;
				break;
			case 65:
				released = KEY_A;
				break;
			case 83:
				released = KEY_S;
				break;
			case 68:
				released = KEY_D;
				break;
			case 340:
				cspeed = 2.0f;
				break;
			default:
				break;
		}

		keystate &= ~released; // bitwise'da '-='

}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
	mousex = x; //A ve D'ye basildiginda mouse hareket ettirmeye gerek duymadan etrafýndan donmek icin...
	mousey = y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
	mousex = x;
	mousey = y;
}

void GameCanvas::mousePressed(int x, int y, int button) {

	if(button == 0) {
		isFiring = true;
		mousex = x;
		mousey = y;
	}
}

void GameCanvas::mouseReleased(int x, int y, int button) {
 //gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	if(button == 0) {
		isFiring = false;
	}

	//btncontinue
	if((status == PAUSE) && (button == 0) && ((x >= leftbtnx && x <= leftbtnx + btncontinue.getWidth())
					 && (y >= btny && y <= btny + btncontinue.getHeight()))) {
		status = DEFAULT;
	}

	//btnreplay
	if((status == LOSE) && (button == 0) && ((x >= leftbtnx && x <= leftbtnx + btnreplay.getWidth())
					 && (y >= btny && y <= btny + btnreplay.getHeight()))) {

		//create new game
		GameCanvas *cnv = new GameCanvas(root);
		//root->setPrevCanvas(root->GAME_CANVAS);
		cnv->setGender(characterGender);
		root->setCurrentCanvas(cnv);
	}

	if((status == WIN) && (button == 0) && ((x >= leftbtnx && x <= leftbtnx + btnnextlevel.getWidth())
					 && (y >= btny && y <= btny + btnnextlevel.getHeight()))) {
		if(levelno == 2){

			//exit btn
			AboutCanvas *cnv = new AboutCanvas(root);
			root->setCurrentCanvas(cnv);

		} else {
			int nextlevelno = levelno + 1;
			if (nextlevelno > 2) {
				nextlevelno = 0;
			}

			GameCanvas *cnv = new GameCanvas(root);
			//root->setPrevCanvas(root->GAME_CANVAS);
			cnv->setLevelNo(nextlevelno);
			cnv->setGender(characterGender);
			root->setCurrentCanvas(cnv);
		}
	}

	if((status != DEFAULT) && (button == 0) && ((x >= rightbtnx && x <= rightbtnx + btncontinue.getWidth())
					 && (y >= btny && y <= btny + btncontinue.getHeight()))) {
		endGame();
	}
}

void GameCanvas::endGame() {

	MenuCanvas *cnv = new MenuCanvas(root);
	cnv->setPrevCanvas(gApp::GAME_CANVAS);
	root->setCurrentCanvas(cnv);
	root->gamemusic.stop();
	root->gamemusic.close();

}

void GameCanvas::mouseEntered() {
	//gLogi("mouseEntered");
	//status = DEFAULT;
}

void GameCanvas::mouseExited() {
	//gLogi("mouseExited");
	if(status == DEFAULT) {
		status = PAUSE;
	}
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

void GameCanvas::generateBullet(float bulletX, float bulletY, float bulletdx, float bulletdy, float bulletRot, int bulletSender) {


	bulletframecounter++;
	if(bulletframecounter == 60 / firerate) {
		std::vector<float> bullet;
		bullet.push_back(bulletX); //x degeri
		bullet.push_back(bulletY); //y degeri
		bullet.push_back(bulletdx); //dx degeri
		bullet.push_back(bulletdy); //dy degeri
		bullet.push_back(bulletRot); //rotation degeri
		bullet.push_back(0.0f); //kapsama alani
		bullet.push_back(bulletSender);
		bullets.push_back(bullet);
		bulletframecounter = 0;

		if(root->soundon && bulletSender == BULLET_SENDER_CHARACTER) {
			root->soundgunshot.play();
			root->soundgunshot.setVolume(1.0f);
			root->soundgunshot.setLoopType(gBaseSound::LOOPTYPE_NONE);
		}
	}
}

void GameCanvas::drawLoadingProgress() {

	setColor(128,128,128);
	loadbackground.draw(0, 0, getWidth(), getHeight());
	setColor(255,255,255);


	//loading
	loadtext.drawSub(loadtextx, loadtexty, loadingtextw[loadanimframeno], loadtext.getHeight(), 0, 0, loadingtextw[loadanimframeno], loadtext.getHeight());

	/*
	//.
	if (loadanimframeno <= 3) {
		loadtext.drawSub(loadtextx, loadtexty, loadingtextw[0], loadtext.getHeight(), loadingtextw[0], 0, loadingtextw[1], loadtext.getHeight());
	}
	// .
	if (loadanimframeno <= 6 && loadanimframeno > 3 ) {
		loadtext.drawSub(loadtextx, loadtexty, loadingtextw[0], loadtext.getHeight(), loadingtextw[1], 0, loadingtextw[2], loadtext.getHeight());
	}
	// .
	if (loadanimframeno <= 9 && loadanimframeno > 6) {
		loadtext.drawSub(loadtextx, loadtexty, loadingtextw[0], loadtext.getHeight(), loadingtextw[2], 0, loadingtextw[3], loadtext.getHeight());
	}
*/
	loadprogressbar.drawSub(loadprogx, loadprogy, loadprogressbar.getWidth(), loadprogressbar.getHeight() / 4, 0, 0, loadprogressbar.getWidth(), loadprogressbar.getHeight() / 4);
	loadprogressbar.drawSub(loadprogx, loadprogy, loadprogressbar.getWidth() * loadcounter/100, loadprogressbar.getHeight() / 4, 0, loadprogressbar.getHeight() / 2, loadprogressbar.getWidth() * loadcounter/100, loadprogressbar.getHeight() / 4);
}

void GameCanvas::loadInitialAsset() {

	loadbackground.loadImage("menu/arkaplan.jpg");
	loadtext.loadImage("gui/gui_loadingtext2.png");
	loadprogressbar.loadImage("gui/gui_progressbar.png");

	loadprogx = (getWidth() -loadprogressbar.getWidth()) / 2;
	loadprogy = getHeight() * 3/4;

	loadtextx = (getWidth() -loadtext.getWidth()) / 2;
	loadtexty = loadprogy - loadtext.getHeight() * 1.5f ;

	loadingtextw[0] = 143;
	loadingtextw[1] = 150;
	loadingtextw[2] = 157;
	loadingtextw[3] = loadtext.getWidth();

	loadanimcounter = 0;
	loadanimframeno = 0;
	loadcounterlimit = 8; //60/7,5
}

bool GameCanvas::checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2) {
	if(xLeft1 < xRight2 && xRight1 > xLeft2 && yBottom1 > yUp2 && yUp1 < yBottom2) {
		return true;
	}
	return false;
}

void GameCanvas::loadAssets() {
	loadAsset(loadcounter);
	loadcounter++;

	loadanimcounter++;
	if(loadanimcounter >= loadcounterlimit) {
		loadanimframeno++;
		if(loadanimframeno >= loadanimframenum) {
			loadanimframeno = 0;
		}
		loadanimcounter = 0;
	}
}

void GameCanvas::loadAsset(int assetNo) {
	switch(assetNo) {
		case 0:
			background.loadImage("haritalar/arkaplan" + gToStr(levelno + 1) + ".jpg");
			break;

		case 1:
			if (characterGender == 0) {
					characterPath += "erkek/erkek";
					charactericonPath = "erkekikon";
				} else {
					characterPath += "kadin/kadin";
					charactericonPath = "kadinikon";
				}
				for(int i = 0; i < characterframenum; i++) {
					character[i].loadImage("karakterler/" + characterPath + "_tufek_0" + gToStr(i) + ".png");
				}
			break;

		case 2:
			dialoguewin.loadImage("diyaloglar/dialogue_youwin.png");
			break;

		case 3:
			dialoguelose.loadImage("diyaloglar/dialogue_gameover.png");
			break;

		case 4:
			dialoguepause.loadImage("diyaloglar/dialogue_pause.png");
			break;

		case 5:
			btnexit.loadImage("diyaloglar/button_exit.png");
			break;

		case 6:
			btnreplay.loadImage("diyaloglar/button_replay.png");
			break;

		case 7:
			btncontinue.loadImage("diyaloglar/button_continue.png");
			break;

		case 8:
			btnmainmenu.loadImage("diyaloglar/button_mainmenu.png");
			break;

		case 9:
			btnnextlevel.loadImage("diyaloglar/button_nextlevel.png");
			break;

		case 10:
			charactericon.loadImage("gui/" + charactericonPath + ".png");
			break;

		case 11:
			healthicon.loadImage("gui/element_0098_Layer-100.png");
			break;
		case 12:
			shieldicon.loadImage("gui/element_0100_Layer-102.png");
			break;
		case 13:
			hpprogressbar.loadImage("gui/element_0076_Layer-78.png");
			break;
		case 14:
			shieldbar.loadImage("gui/element_0076_Layer-78b.png");
			break;
		case 15:
			progressbarframe.loadImage("gui/element_0092_Layer-94.png");
			break;
		case 16:
			progressbarbackground.loadImage("gui/element_0077_Layer-79.png");
			break;
		case 17:
			enemyframenum[ENEMY_ANIMATION_WALK] = 8;
			enemyframenum[ENEMY_ANIMATION_ATTACK] = 16;
			enemyframenum[ENEMY_ANIMATION_DEATH] = 14;
			for(int i = 0; i < enemyanimationnum; i++)
				for(int j = 0; j < enemyframenum[i]; j++){
					std::string imagepath = "walk/Walk";
					if (i == ENEMY_ANIMATION_ATTACK) imagepath = "attack/attack1";
					else if (i == ENEMY_ANIMATION_DEATH) imagepath = "death/Death";

					std::string imageno = gToStr(j);

					if(imageno.length() == 1) imageno = "0" + imageno;

					enemyimage[i][j].loadImage("dusman/" + imagepath + "_0" + imageno + ".png");
				}
			break;
		case 18:
			levelmap.loadImage("haritalar/radar" + gToStr(levelno+1) + ".png");
			break;
		case 19:
			levelmapsign[0].loadImage("haritalar/radarisaret1.png");//beyaz
			break;
		case 20:
			levelmapsign[1].loadImage("haritalar/radarisaret2.png");//kirmizi
			break;
		case 21:
			bulletimage.loadImage("objeler/mermi.png");
			break;
		case 22:
			enemybulletimage.loadImage("objeler/mermi2.png");
			break;
		case 23:
			scorefontsize = 36;
			scorefont.loadFont("armalite.ttf", scorefontsize);
			break;
		case 24:
			if(root->musicon) {
				root->gamemusic.play();
				root->gamemusic.setLoopType(gBaseSound::LOOPTYPE_NORMAL);
				root->gamemusic.setVolume(root->volume);
			}
			break;
		case 100:
			loadVariables();
			gamestatus = PLAYING;
			break;
		}
}

void GameCanvas::loadVariables() {

	characterframeno = 0;
	characterframecounter = 0;

	ciconx = charactericon.getWidth() / 2;
	cicony = charactericon.getHeight() / 2;
	hiconx = ciconx + charactericon.getWidth() + 10;
	hicony = cicony;
	siconx = hiconx + (healthicon.getWidth() - shieldicon.getWidth()) / 2;
	sicony = cicony + healthicon.getHeight() + 5;
	hpbarx = hiconx + healthicon.getWidth() + 5;
	hpbary = hicony + 2;
	shbarx = hpbarx;
	shbary = sicony + 2;

	dialogx = getWidth() / 2 - dialoguewin.getWidth() / 2;
	dialogy = getHeight() / 2 - dialoguewin.getHeight() / 2;

	//dialog kutusu en : 531 | boy : 364
	//btn en : 162px | boy : 48px

	leftbtnx = dialogx + dialoguepause.getWidth() / 2 - btncontinue.getWidth() - 10;
	rightbtnx = dialogx + dialoguepause.getWidth() / 2 + 10;
	btny = dialogy + dialoguepause.getHeight() / 2 + 50;

	cx = (getWidth() - character[0].getWidth()) / 2;
	cy = (getHeight() - character[0].getHeight()) / 2;
	cdx = 0.0f;
	cdy = 0.0f;
	crot = 0.0f;
	cspeed = 2.0f;
	bulletspeed = 8.0f;
	characterframecounterlimit = 12 / cspeed;
	camx = 0.0f;
	camy = 0.0f;
	levelmapx = getWidth() - ciconx - levelmap.getWidth();
	levelmapy = cicony;
	isFiring = false;
	firerate = 20;
	bulletframecounter = 0;

	score = 0;
	scoretext = "SCORE";

	mousex = getWidth() / 2;
	mousey = getHeight() / 2;
	camx1 = getWidth() >> 2;
	camy1 = getHeight() >> 2;
	camx2 = (getWidth() * 3) >> 2;
	camy2 = (getHeight() * 3) >> 2;;

	keystate = 0;
	aliveenemynum = enemynum;
	health = 100;
	shield = 100;

	muzzle_dangle = gRadToDeg(std::atan2(0 - (character[0].getHeight() / 2), 42 - (character[0].getWidth() / 2))) + 90.0f;
	muzzle_distance = std::sqrt(std::pow(0 - (character[0].getHeight() / 2), 2) + std::pow(42 - (character[0].getWidth() / 2), 2)); //hipotenus

	enemyhandangle[0] = gRadToDeg(std::atan2(110 - (enemyimage[0][0].getHeight() / 2), 62 - (enemyimage[0][0].getWidth() / 2))) + 90.0f;
	enemyhanddistance[0] = std::sqrt(std::pow(110 - (enemyimage[0][0].getHeight() / 2), 2) + std::pow(62 - (enemyimage[0][0].getWidth() / 2), 2));

	enemyhandangle[1] = gRadToDeg(std::atan2(104 - (enemyimage[0][0].getHeight() / 2), 100 - (enemyimage[0][0].getWidth() / 2))) + 90.0f;
	enemyhanddistance[1] = std::sqrt(std::pow(104 - (enemyimage[0][0].getHeight() / 2), 2) + std::pow(100 - (enemyimage[0][0].getWidth() / 2), 2));

	for ( int i = 0; i < enemynum; i++) {
		Enemy e;
		enemy.push_back(e);
		int ex, ey;
		do	{
			ex = gRandom(background.getWidth() - enemyimage[0][0].getWidth());
			ey = gRandom(background.getHeight() - enemyimage[0][0].getHeight());
		} while(ex < getWidth() && ey < getHeight());

		enemy[i].setX(ex);
		enemy[i].setY(ey);
		enemy[i].setRotation(gRandom(360));

		enemy[i].setFrameNum(8);
		enemy[i].setFrameNo(gRandom(enemy[i].getFrameNum()));
	}


	scorex = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(gToStr(score))) / 2;
	scoretextx = dialogx + (dialoguewin.getWidth() - scorefont.getStringWidth(scoretext)) / 2;
	scoretexty = (dialogy + dialoguewin.getHeight() / 2) + 24;
}
