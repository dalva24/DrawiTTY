#ifndef INPUT_H
#define INPUT_H

#include "coordinate.h"
#include <stdio.h>

using namespace std;

class Input {
	private:
		Coordinate cursorCoordinate;
		int mouseSensitivity;
		FILE *fmouse;
		char mouseRaw[3];
		int screenX;
		int screenY;
		
		Coordinate getCursorCoordinate(Coordinate coordinate){
			Coordinate nextCursorCoordinate;

			if (coordinate.getX() < 0) {
				coordinate.setX(0);
				nextCursorCoordinate.setX(0);
			} else if (coordinate.getX() >= screenX*mouseSensitivity) {
				coordinate.setX(screenX*mouseSensitivity-1);
				nextCursorCoordinate.setX(screenX - 1);
			} else {
				nextCursorCoordinate.setX((int) cursorCoordinate.getX() / mouseSensitivity);
			}

			if (coordinate.getY() < 0) {
				coordinate.setY(0);
				nextCursorCoordinate.setY(0);
			} else if (coordinate.getY() >= screenY*mouseSensitivity) {
				coordinate.setY(screenY*mouseSensitivity-1);
				nextCursorCoordinate.setY(screenY-1);
			} else {
				nextCursorCoordinate.setY((int) cursorCoordinate.getY() / mouseSensitivity);
			}

			return nextCursorCoordinate;
		}

	public: 
		Input(){
			mouseSensitivity = 1;
		}

		Input(int x, int y, int mouseSensitivity, int screenX, int screenY) : cursorCoordinate(x, y){
			this->mouseSensitivity = mouseSensitivity;
			this->screenX;
			this->screenY;
			
			//prepare mouse controller
			fmouse = fopen("/dev/input/mice","r");
		}
		
		Coordinate getNextCursorCoordinate(){
			//read next mouse
			fread(mouseRaw,sizeof(char),3,fmouse);
			
			Coordinate mouse;
			mouse.setX(cursorCoordinate.getX() + mouseRaw[1]);
			mouse.setY(cursorCoordinate.getY() - mouseRaw[2]);
			
			return getCursorCoordinate(mouse);
		}


};

#endif
