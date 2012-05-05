#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;



void printMultipleBits(char file[],int data,int &startPos,int bits)
{
	int devide;
	for(int i=0;i<bits;i++){
		if(i==0){
			devide = 1;
		}
		else{
			devide = 256*i;
		}
		file[startPos + i] = (data/devide) % 256;
	}
	startPos += bits;
}

void printLongInt(char file[],int longint,int &startPos)
{
	printMultipleBits(file,longint,startPos,4);
}

void printWord(char file[],int word,int &startPos)
{
	printMultipleBits(file,word,startPos,2);
}

void printByte(char file[],int byte,int &startPos)
{
	printMultipleBits(file,byte,startPos,1);
}

int main () {
	
	//Count the number of characters and put the characters in a string
	char c;
	string data;
	int count = 0;
    cin >> noskipws;    // Stops all further whitespace skipping
    while (cin >> c) {  // Reads whitespace chars now.
		data += c;
		count++;
    }
	
	
	//Standard
	int headerSize = 0x36;
	
	
	//More specifik settings
	int pixelsNeeded = ceil(count/3.0);
	
	int imageWidth;
	if(pixelsNeeded/4 % 4 == 0){
		imageWidth = pixelsNeeded/4;
	}
	else{
		imageWidth = pixelsNeeded/4+4-(pixelsNeeded/4)%4;
	}
	
	int imageHeight = 4;
	
	int imageDataSize = imageWidth*imageHeight*3;
	
	int fileSize = headerSize+imageDataSize;
	
	// typedef char fileBuffer[fileSize];
	
	//The data to the file is stored in this variable
	char bmpfile[fileSize];
	
	
	int i = 0;
	//
	//  Header
	//
	bmpfile[i++] = 0x42; //B
	bmpfile[i++] = 0x4D; //M
	printLongInt(bmpfile,fileSize,i); //Filesize
	printLongInt(bmpfile,0,i); //Reserved
	printLongInt(bmpfile,0x36,i); //Headersize
	printLongInt(bmpfile,0x28,i); 
	printLongInt(bmpfile,imageWidth,i);
	printLongInt(bmpfile,imageHeight,i);
	printWord(bmpfile,0x01,i);
	printWord(bmpfile,0x18,i);
	printLongInt(bmpfile,0x00,i);
	printLongInt(bmpfile,imageDataSize,i);
	printLongInt(bmpfile,0,i);
	printLongInt(bmpfile,0,i);
	printLongInt(bmpfile,0,i);
	printLongInt(bmpfile,0,i);
	
	//Put the data into the image
	for(int a=0;a<count;a++){
		printByte(bmpfile,data[a],i);
	}
	
	
	//Write to file
	ofstream myfile;
	myfile.open ("test.bmp");
	myfile.write(bmpfile, fileSize);
	// myfile << bmpfile;

	myfile.close();
	return 0;
}


