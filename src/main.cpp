/***********************************************************************
Main.cpp
Copyright (c) 2016-2017 Thomas Wolf and Rasmus R. Paulsen (people.compute.dtu.dk/rapa)

This file is part of the Magic Sand.

The Magic Sand is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Magic Sand is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with the Augmented Reality Sandbox; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
***********************************************************************/


#include "ofMain.h"
#include "ofApp.h"

const std::string MagicSandVersion = "1.5.1.1";

bool setFirstWindowDimensions(ofGLFWWindowSettings& settings) {
	// Check screens size and location
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (monitor) {
		int xM; int yM;
		glfwGetMonitorPos(monitor, &xM, &yM);
		const GLFWvidmode * desktopMode = glfwGetVideoMode(monitor);

		settings.width = desktopMode->width * 0.8;
		settings.height = desktopMode->height * 0.8;
		settings.setPosition(ofVec2f(xM, yM));

		return true;
	}
	else {
		settings.width = 1600; // Default settings if there is only one screen
		settings.height = 800;
		settings.setPosition(ofVec2f(0, 0));
		return false;
	}

}

bool setSecondWindowDimensions(ofGLFWWindowSettings& settings) {
	// Check screens size and location
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	cout << "Number of screens found: " << count << endl;
	if (count>1) {
		int xM; int yM;
		glfwGetMonitorPos(monitors[1], &xM, &yM); // We take the second monitor
		const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[1]);

		settings.width = desktopMode->width;
		settings.height = desktopMode->height;
		settings.setPosition(ofVec2f(xM, yM));

		// In debug mode an external hi-res screen might be attached
		if (settings.width > 2000)
		{
			cout << "External screen with width > 2000 found - going in debug mode" << std::endl;
			settings.width = 800; // Default settings if there is only one screen
			settings.height = 600;
			settings.setPosition(ofVec2f(0, 0));
			return false;
		}

		return true;
	} else {
		settings.width = 800; // Default settings if there is only one screen
		settings.height = 600;
		settings.setPosition(ofVec2f(0, 0));
		return false;
	}

}

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	setFirstWindowDimensions(settings);
	//settings.width = 1200;
 //	settings.height = 600;
	settings.resizable = true;
	settings.decorated = true;
	settings.title = "Magic-Sand " + MagicSandVersion;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	mainWindow->setWindowPosition(ofGetScreenWidth() / 2 - settings.width / 2, ofGetScreenHeight() / 2 - settings.height / 2);

	setSecondWindowDimensions(settings);
	settings.resizable = false;
	settings.decorated = false;
	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(settings);
	secondWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	ofAddListener(secondWindow->events().draw, mainApp.get(), &ofApp::drawProjWindow);
	mainApp->projWindow = secondWindow;
		
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
