# CS361-GISTool-Group23

## Unit Tests for the image comparison program 

This program tests the functionality of the imagecompar program.  

## Compilation on the flip server
First, place the 4 images to compare in the same directory as imagecompar.cpp

#### Conditions
Image 1 and Image 2 should be the same image.  
Image 1 and Image 3 should be the same dimensions, but contain different images.  
Image 1 and Image 4 should be different dimensions.  
Damage type can be either road or flood. If a non-existant type is entered,
the program will notify the user.
Indicate a tolerance percentage (i.e. 20%)

#### Compilation
```
 g++ `pkg-config --cflags opencv` discolorTests.cpp `pkg-config --libs opencv` -o test  
```

#### Running the test suite 
```
chmod +x testsuite
testsuite <image1> <image2> <image3> <image4> <damage_type> <threshold %>
```

#### Optional: Manual testing
If you wish to run manual tests, you can run the program via:
```
./test <image1> <image2> <damage_type> <threshold %>
```
