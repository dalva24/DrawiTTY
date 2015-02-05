#ifndef FRAME_H
#define FRAME_H

#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Frame {
	private:
		int width;
		int height;
		Color **screen;
		Color baseColor;
		
	public:
		Frame(int width, int height, Color bc){
			this->width = width;
			this->height = height;
			this->baseColor = bc;
			
			screen = new Color*[this->height];
			for(int i = 0; i < this->height; ++i) {
				screen[i] = new Color[this->width];
			}
			
			for(int i = 0; i < this->height; i++){
				for(int j = 0; j < this->width; j++){
					screen[i][j].setColor(baseColor);
				}
			}
		}
		
		void flush() {
			int x;
			int y;
			for (y=0; y < height; y++) {
				for (x=0; x<width; x++) {
					setColor(x, y, baseColor);
				}
			}
		}	
		
		void flushWith(Color color) {
			int x;
			int y;
			for (y=0; y < height; y++) {
				for (x=0; x<width; x++) {
					setColor(x, y, color);
				}
			}
		}	
		
		Color getColor(int x, int y){
			return screen[x][y];
		}
		
		void setRColor(int x, int y, unsigned char r){
			screen[x][y].setR(r);
		}
		
		void setGColor(int x, int y, unsigned char g){
			screen[x][y].setG(g);
		}
		
		void setBColor(int x, int y, unsigned char b){
			screen[x][y].setB(b);
		}
		
		void setColor(int x, int y, Color color){
			screen[x][y].setColor(color);
		}
		
};

#endif


