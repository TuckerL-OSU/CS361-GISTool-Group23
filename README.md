# CS361-GISTool-Group23

## imagecompar feature 

This program compares 2 images and outputs the difference as a grayscale image.
It uses OpenCV library (flip has it installed)  

#### How to compile and run on flip

- Place the 2 images to compare in the same directory as imagecompar.cpp

- **To compile:** g++ `pkg-config --cflags opencv` imagecompar2.cpp `pkg-config --libs opencv` -o imagecompar  
- **To run:** imagecompar <image 1> <image 2>
- **Output:** diffimage.jpg is the difference image in grayscale