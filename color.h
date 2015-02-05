#ifndef COLOR_H
#define COLOR_H

class Color {
	private:
		unsigned char r;
		unsigned char g;
		unsigned char b;

	public:
		Color(unsigned char r, unsigned char g, unsigned char b){
			this->r = r;
			this->g = g;
			this->b = b;
		}

		Color(){
			r = 0;
			g = 0;
			b = 0;
		}

		unsigned char getRValue(){
			return r;
		}

		unsigned char getGValue(){
			return g;
		}

		unsigned char getBValue(){
			return b;
		}

		void setRValue(unsigned char r){
			this->r = r;
		}

		void setGValue(unsigned char g){
			this->g = g;
		}

		void setBValue(unsigned char b){
			this->b = b;
		}

		void setColor(Color color){
			this->r = color.getRValue();
			this->g = color.getGValue();
			this->b = color.getBValue();
		}

		void multiply(Color bottomColorValue, Color topColorValue){
			this->r = topColorValue.r * bottomColorValue.r / 255;
			this->g = topColorValue.g * bottomColorValue.g / 255;
			this->b = topColorValue.b * bottomColorValue.b / 255;
		}

		void darken(Color bottomColorValue, Color topColorValue){
			if(topColorValue.r > bottomColorValue.r)
				this->r = bottomColorValue.r;
			else
				this->r = topColorValue.r;

			if(topColorValue.g > bottomColorValue.g)
				this->g = bottomColorValue.g;
			else
				this->g = topColorValue.g;

			if(topColorValue.b > bottomColorValue.b)
				this->b = bottomColorValue.b;
			else
				this->b = topColorValue.b;
		}

};

#endif
