#include <iostream>
#include <fstream>
using namespace std;

int main () {
	ofstream myfile;
	myfile.open ("test.bmp");
	
	//Standard
	int headerSize = 0x35;
	
	
	//More specifik settings
	int imageWidth = 4;
	int imageHeight = 12;
	
	int fileSize = headerSize+imageWidth*imageHeight*3;
	
	//The data to the file is stored in this variable
	char bmpfile[fileSize];

	//
	//  Header
	//
	bmpfile[0] = 0x42; //B
	bmpfile[1] = 0x4D; //M
	bmpfile[2] = 0x00; //Size of image
	bmpfile[3] = 0x00;
	bmpfile[4] = 0x00;
	bmpfile[5] = 0x00;

	myfile.write(bmpfile, fileSize);
	// myfile << bmpfile;

	myfile.close();
	return 0;
}