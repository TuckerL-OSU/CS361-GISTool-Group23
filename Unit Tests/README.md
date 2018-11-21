# CS361-GISTool-Group23

## Unit Test for the image comparison program 

This program tests the functionality of the imagecompar program.  

#### How to compile and run on flip

- Place the 4 images to compare in the same directory as imagecompar.cpp

- **To compile:** g++ `pkg-config --cflags opencv` imageCompTest.cpp `pkg-config --libs opencv` -o test  
- **To run:** testsuite <image1> <image2> <image3> <image4>
- **Conditions:** Image 1 & Image 2 should be the same. Image 1 & Image 3 should be different. Image 1 & Image 4 should have different dimensions.
