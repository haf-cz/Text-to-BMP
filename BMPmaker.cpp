#include <iostream>
#include <fstream>
#include <stdlib.h>
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

bool parameterExist(int nArgs, char* Args[],string arg){
	for(int i=1;i<nArgs;i++){
		if(Args[i]==arg){
			return true;
		}
	}
	return false;
}

string parameterValue(int nArgs, char* Args[],string arg){
	for(int i=1;i<nArgs-1;i++){
		if(Args[i]==arg){
			return Args[i+1];
		}
	}
	return "";
}

int main (int nArgs, char* Args[]) {
	
	//Count the number of characters and put the characters in a string
	char c;
	string data;
	int count = 0;
    cin >> noskipws;  // No whitespace skipping
    while (cin >> c) {
		data += c;
		count++;
    }
	
	//Arguments
	int ArgWidth = atoi(parameterValue(nArgs,Args,"-w").c_str());
	int ArgHeight = atoi(parameterValue(nArgs,Args,"-h").c_str());
	
	
	//Standard
	int headerSize = 0x36;
	
	
	int pixelsNeeded = ceil(count/3.0);
	
	
	
	
	// Width and height
	int imageHeight;
	int imageWidth;
	if(ArgWidth>0 && ArgHeight>0){
		imageHeight = ArgHeight;
		imageWidth = ArgWidth;
	}
	else if(ArgWidth>0){
		int division = pixelsNeeded/ArgWidth;
		if(division % ArgWidth == 0){
			imageHeight = division;
		}
		else{
			imageHeight = division+4-division%4;
		}
		imageWidth = ArgWidth;
	}
	else if(ArgHeight>0){
		int division = pixelsNeeded/ArgHeight;
		if(division % ArgHeight == 0){
			imageWidth = division;
		}
		else{
			imageWidth = division+4-division%4;
		}
		imageHeight = ArgHeight;
	}
	else{
		int standardHeight = 4;
		int division = pixelsNeeded/4;
		if(division % standardHeight == 0){
			imageWidth = division;
		}
		else{
			imageWidth = division+standardHeight-division%standardHeight;
		}
		imageHeight = standardHeight;
	}
	
	cout << imageHeight << imageWidth;
	
	
	
	

	
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


