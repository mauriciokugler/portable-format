# C++ Portable Pixmap Format

Yet another C++ implementation for [Portable Pixmap Format](https://en.wikipedia.org/wiki/Netpbm_format) image manipulation. This class provides simple methods for reading and writing ASCII Portable PixMap (P3) images, as well as exporting ASCII Portable GrayMap (P2) images.

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

The `main.cpp` file contains a simple example ...

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

<img src="image.png" alt="drawing" width="400"/>




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
