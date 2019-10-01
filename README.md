# C++ Portable Pixmap Format

Yet another C++ implementation for [Portable Pixmap Format](https://en.wikipedia.org/wiki/Netpbm_format) image manipulation. This class provides simple methods for reading and writing ASCII Portable PixMap (P3 *.ppm) images, as well as exporting ASCII Portable GrayMap (P2 *.pgm) images.

This implementation is a simple alternative for creating working examples of other image processing algorithms. It should not be used with large images or when efficiency is critical.

## Usage

```C++
PortableFormat(unsigned int w, unsigned int h);
PortableFormat(char *filename);
```

```C++
unsigned int width;
unsigned int height;
unsigned int scale;
```

```C++
unsigned char ***data;
unsigned char **gray;
```


```C++
bool saveImage(char *filename, char *comment);
```


```C++
unsigned char** grayScale();
bool grayScale(char *filename, char *comment);
```

## Example

The `main.cpp` file contains a simple example, in which a PPM image is read, the colors are inverted and the resulting image saved in a new PPM file. The original image is also converted to grayscale and exported to a PGM image.

```C++
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
```

Original image:

<img src="image.png" alt="color image" width=300/>

Negative image: 

<img src="negative.png" alt="negative image" width=300/>

Grayscale image:

<img src="gray.png" alt="grayscale image" width=300/>

## Citing

```TeX
@MISC{Kugler2019,
  author = "Mauricio Kugler",
  title = "C++ Portable Pixmap Format",
  year = "2019",
  url = "https://github.com/mauriciokugler/portable-format",
  note = "Version 1.0.0"
}
```

## License

This project is licensed under the [MIT License](LICENSE).
