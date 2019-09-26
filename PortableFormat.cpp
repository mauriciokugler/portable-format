//Copyright (c) 2019 Mauricio Kugler, Nagoya Institute of Technology

#include "PortableFormat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PortableFormat::PortableFormat(unsigned int w, unsigned int h)
{
	data = NULL;
	gray = NULL;
	scale = 255;

	createImage(w, h);
}

PortableFormat::PortableFormat(char *filename)
{
	data = NULL;
	gray = NULL;
	scale = 255;

	FILE *img = fopen(filename, "rt");

	const unsigned int n = 256;
	char buffer[n];
	char pixel[n];

	//image format
	fgets(buffer, n, img);
	if(strcmp(buffer, "P3\n")!=0) {
		fclose(img); return;
	}

	//image comments
	do {
		fgets(buffer, n, img);
	} while(buffer[0]=='#');

	//image dimensions
	sscanf(buffer, "%d %d\n", &width, &height);

	//image maximal value
	fgets(buffer, n, img);							
	scale = atoi(buffer);

	createImage(width, height);

	//image data
	fgets(buffer, n, img);							
	unsigned int p = 0;

	unsigned int i = 0;
	while(i<height) {
		unsigned int j = 0;
		while(j<width) {
			unsigned int k = 0;
			while(k<depth) {
				unsigned int c = 0;
				while(buffer[p]!=' ' && buffer[p]!='\n') {
					pixel[c] = buffer[p];
					c++; p++;
				}
				pixel[c] = '\0';
				data[i][j][k] = atoi(pixel);
				k++;

				while(buffer[p]==' ') p++;

				if(buffer[p]=='\n') {
					fgets(buffer, n, img);
					p = 0;
				}
			}
			j++;
		}
		i++;
	}

	fclose(img);
}

PortableFormat::~PortableFormat()
{
	if(data!=NULL) {
		for(unsigned int i=0;i<height;i++) {
			for(unsigned int j=0;j<width;j++) {
				delete[] data[i][j];
			}
			delete[] data[i];
		}
		delete[] data;
	}

	if(gray!=NULL) {
		for(unsigned int i=0;i<height;i++) {
			delete[] gray[i];
		}
		delete[] gray;
	}
}

void PortableFormat::createImage(unsigned int w, unsigned int h)
{
	if(data!=NULL) {
		for(unsigned int i=0;i<height;i++) {
			for(unsigned int j=0;j<width;j++) {
				delete[] data[i][j];
			}
			delete[] data[i];
		}
		delete[] data;
	}

	width = w;
	height = h;

	data = new unsigned char**[height];
	for(unsigned int i=0;i<height;i++) {
		data[i] = new unsigned char*[width];
		for(unsigned int j=0;j<width;j++) {
			data[i][j] = new unsigned char[depth];
		}
	}
}

bool PortableFormat::saveImage(char *filename, char *comment)
{
	FILE *img = fopen(filename, "wt");
	if(img==NULL) return(false);

	fprintf(img, "P3\n# %s\n%d %d\n%d\n", comment, width, height, scale);

	const unsigned int n = 70;
	unsigned int c = 0;
	
	for(unsigned int i=0;i<height;i++) {
		for(unsigned int j=0;j<width;j++) {
			for(unsigned int k=0;k<depth;k++) {
				c += fprintf(img, "%d", data[i][j][k]);
				if(c < n) fprintf(img, " ");
				else { fprintf(img, "\n"); c = 0; }
			}
		}
	}

	fclose(img);

	return(true);
}

unsigned char** PortableFormat::grayScale()
{
	if(gray!=NULL) {
		for(unsigned int i=0;i<height;i++) {
			delete[] gray[i];
		}
		delete[] gray;
	}

	gray = new unsigned char*[height];
	for(unsigned int i=0;i<height;i++) {
		gray[i] = new unsigned char[width];
	}

	//Component coefficients
	const float R = 0.298936021293776f;
	const float G = 0.587043074451121f;
	const float B = 0.114020904255103f;

	for(unsigned int i=0;i<height;i++) {
		for(unsigned int j=0;j<width;j++) {
			unsigned char r = data[i][j][0];
			unsigned char g = data[i][j][1];
			unsigned char b = data[i][j][2];

			gray[i][j] = (unsigned char)(R*r + G*g + B*b);
		}
	}

	return(gray);
}

bool PortableFormat::grayScale(char *filename, char *comment)
{
	if(gray==NULL) grayScale();

	FILE *img = fopen(filename, "wt");
	if(img==NULL) return(false);

	fprintf(img, "P2\n# %s\n%d %d\n%d\n", comment, width, height, scale);

	const unsigned int n = 70;
	unsigned int c = 0;

	for(unsigned int i=0;i<height;i++) {
		for(unsigned int j=0;j<width;j++) {
			c += fprintf(img, "%d", gray[i][j]);
			if(c < n) fprintf(img, " ");
			else { fprintf(img, "\n"); c = 0; }
		}
	}

	fclose(img);

	return(true);
}