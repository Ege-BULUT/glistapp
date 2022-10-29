/*
 * Copyright (C) 2014 Nitra Games Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "gAppManager.h"
#include "gBaseWindow.h"
#include "gApp.h"


int main(int argc, char **argv) {
	gStartEngine(new gApp(), "(R)ock(P)aper(S)cissors RPG", gBaseWindow::WINDOWMODE_APP, 1600, 900);
	//gStartEngine(new gApp(), "Rock Paper Scissors RPG", gBaseWindow::WINDOWMODE_APP, 1920, 1080);
	//gStartEngine(app, appName, windowMode, xSize, ySize)
	return 0;
}
