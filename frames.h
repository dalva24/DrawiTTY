#ifndef FRAME_H
#define FRAME_H

#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Frames {
	private:
		int width;
		int height;
		Color **screen;
		
	public:
		Frames(int width, int height){
			this->width = width;
			this->height = height;
			
			screen = new Color*[this->height];
			for(int i = 0; i < this->height; ++i)
			    screen[i] = new Color[this->width];

			for(int i = 0; i < this->height; i++){
				for(int j = 0; j < this->width; j++){
					screen[i][j].setColor(Color(33, 33, 33));
				}
			}
		}
		
		Color getColor(int x, int y){
			return screen[x][y];
		}
		
		void setRColor(int x, int y, unsigned char r){
			screen[x][y].setRValue(r);
		}
		
		void setGColor(int x, int y, unsigned char g){
			screen[x][y].setGValue(g);
		}
		
		void setBColor(int x, int y, unsigned char b){
			screen[x][y].setBValue(b);
		}
		
		void setAllColor(int x, int y, Color color){
			screen[x][y].setColor(color);
		}
		
};

#endif


