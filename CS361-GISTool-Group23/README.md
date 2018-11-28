# CS361-GISTool-Group23

## imagecompar feature 

This program compares 2 images and outputs the difference as a grayscale image.
It uses OpenCV library (flip has it installed)  

#### How to compile and run on flip

- Place the 2 images to compare in the same directory as imagecompar.cpp

- **To compile:** g++ `` `pkg-config --cflags opencv` `` imagecompar.cpp `` `pkg-config --libs opencv` `` -o imagecompar 
 
- **To run:** imagecompar <image 1> <image 2> <damage type>

- **Output:** diffimage.png is the difference image in grayscale

## file feature

This program takes the input files, and checks to make sure they exist. 
If the input is given no file extension, it will add .png to it then attempt to check its existence.

#### How to compile and run on flip

- Place the files you want to test in the same directory as file.*, support.* and the makefile

- **To compile:** type "make" at the command line, in the same directory as noted above.  

- **To run:** file_test <image 1> <image 2> <damage type(road or flood)>
- **Output:** Shows success or shows where it failed.

## discolordetect feature 

This program detects discoloration when comparing 2 images (an old and a new one). It takes discoloration threshold parameter specifying the % discoloration above which to detect discoloration. It outputs an image diffimage.png with discoloration marked in red. The program uses OpenCV library (flip has it installed) 

#### Images 
Should be of the same area. Example images included: **satellite1.png**, **satellite2.png** 

#### How to compile and run on flip

- Place the 2 images to compare in the same directory as imagecompar.cpp

- **To compile:** g++ `` `pkg-config --cflags opencv` `` discolordetect.cpp `` `pkg-config --libs opencv` `` -o discolordetect  

- **To run:** discolordetect <image 1> <image 2> <damage type> <discoloration threshold %>
Example run: discolordetect satellite1.png satellite2.png road 20%

- **Output:** diffimage.png is the resulting image with discolored areas marked in red