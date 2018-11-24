# CS361-GISTool-Group23

## imagecompar feature 

This program compares 2 images and outputs the difference as a grayscale image.
It uses OpenCV library (flip has it installed)  

#### How to compile and run on flip

- Place the 2 images to compare in the same directory as imagecompar.cpp

- **To compile:** g++ `` `pkg-config --cflags opencv` `` imagecompar.cpp `` `pkg-config --libs opencv` `` -o imagecompar  
- **To run:** imagecompar <image 1> <image 2>
- **Output:** diffimage.jpg is the difference image in grayscale

## file feature

This program takes the input files, and checks to make sure they exist. 
If the input is given no file extension, it will add .png to it then attempt to check its existence.

#### How to compile and run on flip

- Place the files you want to test in the same directory as file.*, support.* and the makefile

- **To compile:** type "make" at the command line, in the same directory as noted above.  

- **To run:** file_test <image 1> <image 2> <damage type(road or flood)>
- **Output:** Shows success or shows where it failed.