#ifndef LINE_H
#define LINE_H

#include "coordinate.h"

class Line {
	private:
		Coordinate initialCoordinate;
		Coordinate destinationCoordinate;

	public:
		Line(){

		}

		Line(int x0, int y0, int x1, int y1) : initialCoordinate(x0, y0), destinationCoordinate(x1, y1){

		}

		Coordinate getInitialCoordinate(){
			return initialCoordinate;
		}

		Coordinate getDestinationCoordinate(){
			return destinationCoordinate;
		}

		void setInitialCoordinate(int x, int y){
			initialCoordinate.setCoordinate(x, y);
		}

		void setDestinationCoordinate(int x, int y){
			destinationCoordinate.setCoordinate(x, y);
		}

		void setLine(int x0, int y0, int x1, int y1){
			initialCoordinate.setCoordinate(x0, y0);
			destinationCoordinate.setCoordinate(x1, y1);
		}


};

#endif