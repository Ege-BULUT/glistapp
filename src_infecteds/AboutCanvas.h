/*
 * AboutCanvas.h
 *
 *  Created on: 8 Eyl 2022
 *      Author: Ege BULUT
 */

#ifndef SRC_ABOUTCANVAS_H_
#define SRC_ABOUTCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gBaseApp.h"
#include "gImage.h"
#include "gFont.h"

class AboutCanvas: public gBaseCanvas {
public:
	AboutCanvas(gApp* root);
	virtual ~AboutCanvas();

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

private:
	gApp* root;

	static const int linenum = 17;

	float linepadding;
	gImage background;
	gImage exitbtn;
	std::string aboutinfo[linenum];
	int fontsize;
	int firstliney;
	int linex[linenum];
	int liney;
	int texttotalh;
	float lineymult;
	gFont font;





};

#endif /* SRC_ABOUTCANVAS_H_ */
