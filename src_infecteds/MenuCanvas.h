/*
 * MenuCanvas.h
 *
 *  Created on: 25 Aðu 2022
 *      Author: Ege BULUT
 */

#ifndef SRC_MENUCANVAS_H_
#define SRC_MENUCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gBaseApp.h"

class MenuCanvas: public gBaseCanvas {

public:
	MenuCanvas(gApp* root);
	virtual ~MenuCanvas();

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

	void showNotify();
	void hideNotify();

	void setPrevCanvas(int prevCanvasNo);

	int characterGender;

private :
	gApp* root;

	gImage background;
	gImage mainmenu;
	gImage verify;
	gImage mute; //ban

	int prevcanvasno;

	int mainmenux, mainmenuy;
	int verifyx[2], verifyy;
	int mutex, mutey[2];
	int buttonH, buttonW;
	int soundBtnX, soundBtnY;
	int musicBtnX, musicBtnY;
	int aboutBtnX, aboutBtnY;
	int musicmutex, musicmutey;
	int soundmutex, soundmutey;
};

#endif /* SRC_MENUCANVAS_H_ */
