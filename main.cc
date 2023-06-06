#define cimg_display 0
#include "CImg.h"
#include <iostream>
#include <cstdlib>
using namespace cimg_library;
using namespace std;

//This will dump the contents of an image file to the screen
//an img is a 3d array, each pixel is 3 unsigned chars,  
void print_image (unsigned char *in, int width, int height) {
	for (int i = 0; i < width*height*3; i++)
		cout << (unsigned int)in[i] << endl;
}

//connect asm to c code
#ifdef student_darken
extern "C" {
	void sdarken(unsigned char *in,unsigned char *out, int width, int height);
}
#else 
extern "C" {
	void darken(unsigned char *in,unsigned char *out, int width, int height) {
		int stride = width*height;
		for (int i = 0; i < width*height; i++) {
			//The first 2D array of width*height pixels is red
			out[i] = in[i] / 2; //Divide red by 2
			//The second 2D array of width*height pixels is green
			out[i+stride] = in[i+stride] / 2; //Divide green by 2
			//The third 2D array of width*height pixels is blue
			out[i+stride+stride] = in[i+stride+stride] / 4; //Divide blue by 2
		}
	}
}
#endif

void usage() {
	cout << "Error: this program needs to be called with a command line parameter indicating what file to open.\n";
	cout << "For example, a.out kyoto.jpg\n";
	exit(1);
}

int main(int argc, char **argv) {
	if (argc != 2) usage(); //Check command line parameters

	//PHASE 1 - Load the image
	clock_t start_time = clock();
	CImg<unsigned char> image(argv[1]);
	CImg<unsigned char> darkimage(image.width(),image.height(),1,3,0);
	clock_t end_time = clock();
	cerr << "Image load time: " << double(end_time - start_time)/CLOCKS_PER_SEC << " secs\n";

	//PHASE 2 - Do the image processing operation
	start_time = clock();
#ifdef student_darken
	sdarken(image,darkimage,image.width(),image.height());
	end_time = clock();
	cerr << "Student Darken time: " << double(end_time - start_time)/CLOCKS_PER_SEC << " secs\n";
#else
	darken(image,darkimage,image.width(),image.height());
	end_time = clock();
	cerr << "Reference Darken time: " << double(end_time - start_time)/CLOCKS_PER_SEC << " secs\n";
#endif

	//PHASE 3 - Write the image
	start_time = clock();
	darkimage.save_jpeg("output.jpg",50);
	//darkimage.save_png("output.png");
	end_time = clock();
	cerr << "Image write time: " << double(end_time - start_time)/CLOCKS_PER_SEC << " secs\n";
}
