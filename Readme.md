# IC - Projecto 2

Entropy coding of audio and images.

<br>

## Installation

No installation of any software is needed. All needed libraries are included. 

<br>

## Languages

[<img src="https://raw.githubusercontent.com/isocpp/logos/64ef037049f87ac74875dbe72695e59118b52186/cpp_logo.svg" width="35"/>](cpp.png)
[<img src="https://cdn.worldvectorlogo.com/logos/python-5.svg" width="35"/>](python.png)

All of the Codecs, Bitstream and Golomb classes, as well as their testing programs have been writte using C++.

Python is used on exercise 2 in PartB as a way to create the histogram images, since it's a simpler implementation. 

<br>

## Running

All directories have an example file containing a simple g++ config to run the program.

Example:
```bash
g++ testImageCodec.cpp ../../PartA/1/bitstream.cpp ../../PartA/3/Golomb.cpp ../1/ImageCodec.cpp -lX11 -lpthread -o lossyimage
```
