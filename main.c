
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "frame.h"

using namespace std;

int main(){
	Frame frame(1366, 768);
	frame.setAllColor(10, 10, Color(211, 200, 200));
	
	cout << (int)frame.getColor(10, 10).getRValue() << endl;
	return 0;
}
