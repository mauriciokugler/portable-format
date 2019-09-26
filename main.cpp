//Copyright (c) 2019 Mauricio Kugler, Nagoya Institute of Technology

#include "PortableFormat.h"

int main(void)
{
	PortableFormat *PPM1 = new PortableFormat("image.ppm");
	PortableFormat *PPM2 = new PortableFormat(PPM1->width, PPM1->height);

	for(unsigned int i=0;i<PPM1->height;i++) {
		for(unsigned int j=0;j<PPM1->width;j++) {
			for(unsigned int k=0;k<PPM1->depth;k++) {
				PPM2->data[i][j][k] = 255 - PPM1->data[i][j][k];
			}
		}
	}

	PPM1->grayScale("gray.pgm", "Grayscale image!");
	PPM2->saveImage("negative.ppm", "Negative image!");

	delete PPM1;
	delete PPM2;

	return 0;
}