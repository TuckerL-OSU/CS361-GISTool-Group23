# CS361-GISTool-Group23

## Integration Tests for discoloration detection 

This program tests the functionality of units integrated into discolordetect program.  

## Compilation on the flip server
Place 4 test images in the same directory as discolordetect.cpp

#### Conditions
Image 1 and Image 2 should be the same image (no discoloration).  
Image 1 and Image 3 should be the same dimensions, but second image should have discolorations present. 
Image 1 and Image 4 should have different dimensions.  

#### Test data provided
satellite1.png (to be used as Image 1)
satellite2.png (to be used as Image 2)
satellite3.png (to be used as Image 3)
satellite4.png (to be used as Image 4)

#### Compilation
```
 g++ `pkg-config --cflags opencv` discolorIntegrTests.cpp `pkg-config --libs opencv` -o integrationTests 
```

#### Running the tests
```
integrationTests <image1> <image2> <image3> <image4>
```

