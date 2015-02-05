#ifndef LINE_H
#define LINE_H

#include "coordinate.h"

class Line {
	private:
		Coordinate C1;
		Coordinate C2;

	public:
		Line(){

		}

		Line(int x0, int y0, int x1, int y1) : C1(x0, y0), C2(x1, y1){

		}

		Coordinate getInitial(){
			return C1;
		}

		Coordinate getFinal(){
			return C2;
		}

		void setInitial(int x, int y){
			C1.setCoordinate(x, y);
		}

		void setFinal(int x, int y){
			C2.setCoordinate(x, y);
		}

		void setLine(int x0, int y0, int x1, int y1){
			C1.setCoordinate(x0, y0);
			C2.setCoordinate(x1, y1);
		}


};

#endif
