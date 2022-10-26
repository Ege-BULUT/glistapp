#include "gApp.h"
#include "MainMenu.h"
#include "GameCanvas.h"
#include "gBaseApp.h"

MainMenu::MainMenu(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

MainMenu::~MainMenu() {
}

void MainMenu::setup() {
	gLogi(" globalscalemm (getWidth() / 1920) = " + gToStr( (getWidth() / 1920.0f) ));
	globalscale = 0.66f;
	//globalscale = getWidth() / 1920.0f;
	status = LOADING;
	loadindex = 0;
	seccounter = 0;
	framecounter = 0;
	initilaize();
}

void MainMenu::update() {
	framecounter++;
	if(framecounter % 60 == 0) {
		seccounter++;
	}
	listenButtons();
	if (status == LOADING) {
		updateLoad(loadindex);
		loadindex++;
	} else if (status == MENU) {
		savesMenu();
	}
}

void MainMenu::draw() {
	if (status == LOADING) {
		drawLoad();
		//DEBUG
		font[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
		font[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);
	} else if (status == MENU) {
		drawMenu();
	}
}

void MainMenu::initilaize() {

	gLogi("initialize TEST");
	img_blueprint.loadImage("GUI/blueprint.png");

	buttonPressed = -1;

	gFont empty1;

	fontsizes.push_back(32 * globalscale);
	fontsizes.push_back(18 * globalscale);
	fontsizes.push_back(24 * globalscale);

	font.push_back(empty1);
	font.push_back(empty1);
	font.push_back(empty1);
	font[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	font[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);
	font[font_BUTTON].loadFont("FreeSans.ttf", fontsizes[font_BUTTON]);

	loadingtext.push_back("LOADING");
	loadingtext.push_back("");
}

void MainMenu::updateLoad(int index) {
	loadingtext[1] = "Loaded : ";
	switch (index) {

	case 0:
		img_menu.loadImage("menu/mainmenubg.png");
		loadingtext[1] += "menu/mainmenubg.png";
		break;
	case 1:
		img_dialogbox.loadImage("GUI/dialogbox2.png");
		loadingtext[1] += "GUI/dialogbox.png";
		break;
	case 2:
		loadingtext[1] += "menu/btn.png";
		for(int i = 0; i < buttonImageAmount; i++) {
			img_button[i].loadImage("menu/btn_" + gToStr(i) + ".png");
		}
		break;
	case 3:
		img_background.loadImage("game/map.png");
		loadingtext[1] += "game/map.png";
		break;
	case 4:

		loadingtext[1] += "";
		break;
	case 5:

		loadingtext[1] += "";
		break;
	case 6:

		loadingtext[1] += "";
		break;
	case 7:

		loadingtext[1] = "Setting up all initial variables...";
		break;
	case 8:

		loadingtext[1] = "Setting up all initial variables...";
		break;
	case 9:
		loadingtext[1] = "Setting up all initial variables...";
		setInitialVariables();
		break;
	case 100:
		status = MENU;
		break;

	}
}

void MainMenu::setInitialVariables() {
	gLogi(" set initial var TEST");
	// load saves vs dediðimiz zaman menünün kayacaðý 2. kýsým
	// x_mainmenu > getWidth()/20											//margin %5 from begin
	x_mainmenu = (getWidth() - (img_menu.getWidth() * globalscale)) / 2;	// center
	y_mainmenu = ((getHeight() - (img_menu.getHeight() * globalscale)) / 2) - getWidth()/50;	// center

	x_btnmm2 = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[0].getWidth() * globalscale)) / 2;
	x_btnmm = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[1].getWidth() * globalscale)) / 2;
	y_btnmm = y_mainmenu + (338 * globalscale);

	//CREATE BUTTONS
	y_btnmm = y_mainmenu + (338 * globalscale);
	createButton("New Game", x_btnmm, y_btnmm, 1, 255, 255, 255, font_BUTTON);
	y_btnmm += (img_button[1].getHeight() * globalscale) + 11;
	createButton("Load Game", x_btnmm, y_btnmm, 1, 255, 255, 255, font_BUTTON);
	y_btnmm += (img_button[1].getHeight() * globalscale) + 11;
	createButton("Credits", x_btnmm, y_btnmm, 1, 255, 255, 20, font_BUTTON);
	y_btnmm += (img_button[1].getHeight() * globalscale) + 11;
	createButton("Exit", x_btnmm2, y_btnmm, 0, 255, 20, 20, font_BUTTON);

	for(int b = 0; b<buttons.size(); b++) {
		gLogi(gToStr(b) + ". -> [" + gToStr(buttons[b][0]) + ", " + gToStr(buttons[b][1]) + ", " + gToStr(buttons[b][7]) + ", " + gToStr(buttons[b][8]) + "]");
	}

	loadsaveanimation = false;
}

void MainMenu::drawLoad() {
	img_blueprint.draw(0, 0, globalscale);

	if(framecounter % 15 == 0) {
		switch(loadingtext[0].length()) {
		case 7: case 8: case 9:
			loadingtext[0] += ".";
			break;
		case 10:
			loadingtext[0] = "LOADING.";
			break;
		}
	}
	//int x = (getWidth() - font[font_LOAD1].getStringWidth(loadingtext[0]))/2;
//	gLogi(gToStr(x));

	font[font_LOAD1].drawText(loadingtext[0], getWidth()/2 - 100, getHeight()*4/5, 255, 255, 0);
	font[font_LOAD2].drawText(loadingtext[1], getWidth()/2 - 250, getHeight()*4/5 + fontsizes[0]);

}

void MainMenu::drawMenu() {
// TODO:: BURADA KALDIN, GLOBAL SCALE DEÐERÝ OLUÞTUR, YENÝ DRAW METHODU YAZ BUNUNLA
	setColor(128,128,128);
	//img_blueprint.draw(0, 0, globalscale);
	img_background.draw(-20, -20);
	setColor(255,255,255);
	//img_menu.draw(0, 0);
	img_menu.draw(x_mainmenu, y_mainmenu, globalscale);
	drawButtons();

	if (status == LOADSAVE) {
		savesMenu();
	}
}

void MainMenu::createButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	buttonTexts.push_back(btntext);
	std::vector<int> tmpbtn;
	tmpbtn.push_back(btnx);
	tmpbtn.push_back(btny);
	tmpbtn.push_back(btntype);
	tmpbtn.push_back(btnR);
	tmpbtn.push_back(btnG);
	tmpbtn.push_back(btnB);
	tmpbtn.push_back(texttype);
	tmpbtn.push_back(btnx + img_button[btntype].getWidth());
	tmpbtn.push_back(btny + img_button[btntype].getHeight());
	buttons.push_back(tmpbtn);
}

void MainMenu::drawButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	//gLogi("MENUCANVAS::DRAWBUTTON -> START");
	img_button[btntype].draw(btnx, btny, globalscale);
	//gLogi("draw emptybtns : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale)- font[texttype].getStringWidth(btntext)) / 2) , btny + (img_button[btntype].getHeight() * globalscale)/2 + 3, btnR/3,btnG/3,btnB/3);
	//gLogi("draw savetextshadow : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale) - font[texttype].getStringWidth(btntext)) / 2) - 1, btny + (img_button[btntype].getHeight() * globalscale)/2 + 1, btnR, btnG, btnB);
	//gLogi("draw savetext : [PASSED]");
}

void MainMenu::drawButtons() {
	for(int i = 0; i < buttons.size(); i++) {
		drawButton(buttonTexts[i], buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3], buttons[i][4], buttons[i][5], buttons[i][6]);
	}
}

void MainMenu::listenButtons() {
	if(buttonPressed != -1) {
		if(buttonPressed == 0) {
			gLogi("[Play Game] pressed");
			GameCanvas *cnv = new GameCanvas(root);
			cnv->initilaize();
			gLogi("test | before setting new canvas");
			root->setCurrentCanvas(cnv); //bu canvas degistirme olayini switch'te yapinca hata verdi.
		} else {
			switch (buttonPressed) {
				case 1:
					gLogi("[Load Save] pressed");
					loadsaveanimation = !loadsaveanimation;
					savesMenu();
					break;
				case 2:
					gLogi("[Credits] pressed");
					//TODO : Credits.cpp | Credits.h
					break;
				case 3:
					gLogi("[Exit] pressed");
					exit(1);
					break;
				}
		}
		buttonPressed = -1; // reset action
	}
}

void MainMenu::savesMenu() {

	//MENU ANIMATION
	if(loadsaveanimation == true) { // OPENING ANIMATION OF "LOAD SAVES" MENU
		if( x_mainmenu > getWidth()/20 ) {
			x_mainmenu -= 12; // recalculate menu's x value

			// Recalculate buttons' x values
			x_btnmm2 = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[0].getWidth() * globalscale)) / 2;
			x_btnmm = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[1].getWidth() * globalscale)) / 2;

			for(int i = 0; i < 3; i++) { // update buttons' x values
				buttons[i][0] = x_btnmm;
			}
			buttons[3][0] = x_btnmm2;
		}
	} else { // CLOSING ANIMATION OF "LOAD SAVES" MENU
		if(x_mainmenu < (getWidth() - (img_menu.getWidth() * globalscale)) / 2) {
			x_mainmenu += 12; // recalculate menu's x value

			// Recalculate buttons' x values
			x_btnmm2 = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[0].getWidth() * globalscale)) / 2;
			x_btnmm = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[1].getWidth() * globalscale)) / 2;

			for(int i = 0; i < 3; i++) { // update buttons' x values
				buttons[i][0] = x_btnmm;
			}
			buttons[3][0] = x_btnmm2;
		} else {
		status = MENU;
		}
	}
}

void MainMenu::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;

}

void MainMenu::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;

}

void MainMenu::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void MainMenu::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void MainMenu::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void MainMenu::mousePressed(int x, int y, int button) {
}

void MainMenu::mouseReleased(int x, int y, int button) {
	//gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;

	for(int b = 0; b < buttons.size(); b++) {
		if(x > buttons[b][0] && y > buttons[b][1] && x < buttons[b][7] && y < buttons[b][8]) {
			buttonPressed = b;
			gLogi("buttonPressed = " + gToStr(b));
		}
	}
}

void MainMenu::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void MainMenu::mouseEntered() {
}

void MainMenu::mouseExited() {
}

void MainMenu::windowResized(int w, int h) {
}

void MainMenu::showNotify() {

}

void MainMenu::hideNotify() {

}

