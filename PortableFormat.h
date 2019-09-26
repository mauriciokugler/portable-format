//Copyright (c) 2019 Mauricio Kugler, Nagoya Institute of Technology

#ifndef PORTABLEFORMATH
#define PORTABLEFORMATH

class PortableFormat
{
private:

	void createImage(unsigned int w, unsigned int h);

public:

	static const unsigned int depth = 3;

	PortableFormat(unsigned int w, unsigned int h);
	PortableFormat(char *filename);
	~PortableFormat();

	unsigned int width;
	unsigned int height;
	unsigned int scale;

	unsigned char ***data;
	unsigned char **gray;
	
	bool saveImage(char *filename, char *comment);

	unsigned char** grayScale();
	bool grayScale(char *filename, char *comment);
};

#endif