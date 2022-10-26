/*
 * AboutCanvas.cpp
 *
 *  Created on: 8 Eyl 2022
 *      Author: Ege BULUT
 */

#include "AboutCanvas.h"
#include "gBaseApp.h"
#include "gApp.h"
#include "MenuCanvas.h"

AboutCanvas::AboutCanvas(gApp* root) : gBaseCanvas(root) {
	// TODO Auto-generated constructor stub
	this->root = root;
}

AboutCanvas::~AboutCanvas() {
	// TODO Auto-generated destructor stub
}

void AboutCanvas::setup() {

	background.loadImage("menu/arkaplan.jpg");
	aboutinfo[0] = "GELÝÞTÝRENLER";
	//aboutinfo[0] = "";
	aboutinfo[1] = "Yavuz BÝLGÝNOÐLU";
	aboutinfo[2] = "Alperen ÇOLAK";
	aboutinfo[3] = "Barýþ BAKIRDÖVEN";
	aboutinfo[4] = "Batuhan GÖKER";
	aboutinfo[5] = "Büþra SIKAR";
	aboutinfo[6] = "Ceyda ÇINARDAL";
	aboutinfo[7] = "Ege BULUT";
	aboutinfo[8] = "Erdinç ARABACIOÐLU";
	aboutinfo[9] = "Esma ADAK";
	aboutinfo[10] = "Niyazi Mert USLU ";
	aboutinfo[11] = "Umut ÜZER";
	aboutinfo[12] = "Umutcan TÜRKMEN";
	aboutinfo[13] = "";
	aboutinfo[14] = "Bu oyun Gamelab Ýstanbul Ýleri Düzey Oyun";
	aboutinfo[15] = "Programlama Eðitimi'nde geliþtirilmiþtir.";
	aboutinfo[16] = "(c) 2022 Gamelab Ýstanbul";

	fontsize = 24;
	linepadding = 1.5f;
	lineymult = fontsize * linepadding;
	texttotalh = lineymult * linenum;
	firstliney = getHeight() + fontsize;
	gLogi(gToStr(texttotalh));
	font.loadFont("FreeSans.ttf", fontsize);

	for(int i = 0; i < linenum; i++){
		linex[i] = (getWidth() - font.getStringWidth(aboutinfo[i])) / 2;

	}
}

void AboutCanvas::update() {
	firstliney -= 1;
	if(firstliney < -texttotalh) {
		firstliney = getHeight() + fontsize;
	}

}

void AboutCanvas::draw() {
	setColor(128, 128, 128);
	background.draw(0, 0, getWidth(), getHeight());
	setColor(255, 255, 255);
	for(int i = 0; i < linenum; i++) {
		if(i == 0) {
			setColor(20, 255, 255);
		}
		liney = firstliney + (lineymult * i);

		setColor(0, 0, 0, 50);
		font.drawText(aboutinfo[i], linex[i] + 4, liney + 4);
		setColor(20, 255, 255);

		font.drawText(aboutinfo[i], linex[i], liney);
	}
}

void AboutCanvas::keyPressed(int key) {
}

void AboutCanvas::keyReleased(int key) {
}

void AboutCanvas::mouseMoved(int x, int y) {
}

void AboutCanvas::mouseDragged(int x, int y, int button) {
}

void AboutCanvas::mousePressed(int x, int y, int button) {

	MenuCanvas *cnv = new MenuCanvas(root);
	cnv->setPrevCanvas(root->ABOUT_CANVAS);
	root->setCurrentCanvas(cnv);

}

void AboutCanvas::mouseReleased(int x, int y, int button) {
}

void AboutCanvas::mouseEntered() {
}

void AboutCanvas::mouseExited() {
}

void AboutCanvas::showNotify() {
}

void AboutCanvas::hideNotify() {
}
