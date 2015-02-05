#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "input.h"
#include "frames.h"
#include "coordinate.h"
#include "color.h"
#include "framebuffer.h"

class Controller {
	private:
		int screenXstart;
		int screenWidth;
		int screenHeight;
		Input mouse;
		Frame compositionFrame;
		Framebuffer fb;

	public:
		Controller(int screenWidth, int screenHeight, int screenXstart, int mouseStartingAxis, int mouseStartingOrdinate, int mouseSensitivity) : mouse(mouseStartingAxis, mouseStartingOrdinate, mouseSensitivity), compositionFrame(screenWidth, screenHeight){
			this->screenWidth = screenWidth;
			this->screenHeight = screenHeight;
			this->screenXstart = screenXstart;
		}
		
	private:

		void insertPixel(Coordinate location, Color color) {
			// do bounding check:
			if (!(location.getX() >= screenWidth || location.getX() < 0 || location.getY() >= screenHeight || location.getY() < 0)) {
				compositionFrame.setRColor(location.getX(), location.getY(), color.getRValue());
				compositionFrame.setGColor(location.getX(), location.getY(), color.getGValue());
				compositionFrame.setBColor(location.getX(), location.getY(), color.getBValue());
			}
		}

		void insertSprite(Coordinate location, unsigned short type) {
			switch (type) {
				case 1 : { // the mouse sprite
					insertPixel(location, Color(255,255,255));
					int i;
					for (i=5; i<10; i++) {
						insertPixel(coordinate(location.getX()-i, location.getY()), Color(0,0,0));
						insertPixel(Coordinate(location.getX()+i, location.getY()), Color(0,0,0));
						insertPixel(Coordinate(location.getX(), location.getY()-i), Color(0,0,0));
						insertPixel(Coordinate(location.getX(), location.getY()+i), Color(0,0,0));
						
						insertPixel(Coordinate(location.getX()-i, location.getY()+1), Color(255,255,255));
						insertPixel(Coordinate(location.getX()-i, location.getY()-1), Color(255,255,255));
						insertPixel(Coordinate(location.getX()+i, location.getY()+1), Color(255,255,255));
						insertPixel(Coordinate(location.getX()+i, location.getY()-1), Color(255,255,255));
						insertPixel(Coordinate(location.getX()+1, location.getY()-i), Color(255,255,255));
						insertPixel(Coordinate(location.getX()-1, location.getY()-i), Color(255,255,255));
						insertPixel(Coordinate(location.getX()+1, location.getY()+i), Color(255,255,255));
						insertPixel(Coordinate(location.getX()-1, location.getY()+i), Color(255,255,255));
					}
				} break;

				case 2 : { // something?
					
				} break;
			}	
		}

		void showFrame () {
			int x;
			int y;
			for (y=0; y<screenHeight y++) {
				for (x=screenXstart; x<screenWidth; x++) {
					int location = x * (fb->bpp/8) + y * fb->lineLen;
					*(fb->ptr + location    ) = compositionFrame.getColor(x, y).getRValue(); // blue
					*(fb->ptr + location + 1) = compositionFrame.getColor(x, y).getGValue(); // green
					*(fb->ptr + location + 2) = compositionFrame.getColor(x, y).getBValue(); // red
					*(fb->ptr + location + 3) = 255; // transparency
				}
			}
		}
		
		void run(){
			struct fb_var_screeninfo vInfo; // variable screen info
			struct fb_fix_screeninfo sInfo; // static screen info
			int fbFile;	 // frame buffer file descriptor
			fbFile = open("/dev/fb0",O_RDWR);
			if (!fbFile) {
				printf("Error: cannot open framebuffer device.\n");
				exit(1);
			}
			if (ioctl (fbFile, FBIOGET_FSCREENINFO, &sInfo)) {
				printf("Error reading fixed information.\n");
				exit(2);
			}
			if (ioctl (fbFile, FBIOGET_VSCREENINFO, &vInfo)) {
				printf("Error reading variable information.\n");
				exit(3);
			}
			
			//create the FrameBuffer struct with its important infos.
			fb.smemLen = sInfo.smem_len;
			fb.lineLen = sInfo.line_length;
			fb.bpp = vInfo.bits_per_pixel;
			
			//and map the framebuffer to the FB struct.
			fb.ptr = (char*)mmap(0, sInfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbFile, 0);
			if ((long int)fb.ptr == -1) {
				printf ("Error: failed to map framebuffer device to memory.\n");
				exit(4);
			}
			
			//prepare mouse controller
			FILE *fmouse;
			char mouseRaw[3];
			fmouse = fopen("/dev/input/mice","r");
			Coordinate mouse; // mouse internal counter
			mouse.x = 0;
			mouse.y = 0;
			
			
			
			//prepare environment controller
			unsigned char loop = 1; // frame loop controller
			Frame cFrame; // composition frame (Video RAM)
			
			flushFrame(&canvas, rgb(255,255,255)); // prepare canvas
			
			int i; //for drawing.
			
			/* Main Loop ------------------------------------------------------- */
			while (loop) {
				
				//clean
				flushFrame(&cFrame, rgb(0,0,0));
				
				//fill mouse LAST
				insertSprite(&cFrame, getCursorCoord(&mouse), 1);
				
				//show frame
				showFrame(&cFrame,&fb);
				
				//read next mouse
				fread(mouseRaw,sizeof(char),3,fmouse);
				mouse.x += mouseRaw[1];
				mouse.y -= mouseRaw[2];
				
			}

			/* Cleanup --------------------------------------------------------- */
			munmap(fb.ptr, sInfo.smem_len);
			close(fbFile);
			fclose(fmouse);
			//resetTermios();
		}



};

#endif
