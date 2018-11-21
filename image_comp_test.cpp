/*
 * Unit Tests for Image Comparator Program
 * CS 361 Group 23
 * Description: This program takes the code from the image
 * comparator function and tests the functionality line-by-line.
 */
 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

int compIntensity(Vec3b x, Vec3b y) {
  if (x == y) {
    return 1;
  } else {
    return 0;
  }
}

int assertTrue(int x, int y) {
  if (x == y) {
    cout << "TEST SUCCESSFUL" << endl;
    return 1;
  } else {
    cout << "TEST FAILED" << endl;
    cout << "Expected: " << x << " | Actual: " << y << endl;
    return 0;
  }
}

int imgCompare(int argc, char** argv) {
  // check usage
  if (argc != 3) {
    cout << "Usage: imagecompar <first image> <second image>" << endl;
    return -1;
  }

  // read in the 2 images	
  Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	
  if (!image1.data) {
    cout << "Could not open or find first image" << endl;
    return -1;
  } 
  if (!image2.data) {
    cout << "Could not open or find second image" << endl;
    return -1;
  }

  // create a blank difference image 
  Mat diffimage(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));
        
  // Total pixels
  int pixels = image1.rows * image1.cols;
  int counter = 0;
  cout << "TEST: Intensities are the same for both images" << endl;
  cout << "NOTE: Test will fail if images are different" << endl;
  // loop through the pixels of images
  for (int i = 0; i < image1.rows; i++) {
    for (int j = 0; j < image1.cols; j++) {
      // get current pixel's intensity in image 1 				
      Vec3b intensity1 = image1.at<Vec3b>(Point(j, i));
      // get current pixel's intensity in image 2
      Vec3b intensity2 = image2.at<Vec3b>(Point(j, i));
      counter += compIntensity(intensity1, intensity2);
      // set difference image's pixel to the difference of image1 and image2
      // subtract from 255 to have white background	
      diffimage.at<Vec3b>(Point(j, i))[0] = 255 - abs(intensity1.val[0] - intensity2.val[0]);
      diffimage.at<Vec3b>(Point(j, i))[1] = 255 - abs(intensity1.val[1] - intensity2.val[1]);
      diffimage.at<Vec3b>(Point(j, i))[2] = 255 - abs(intensity1.val[2] - intensity2.val[2]); 
			
    }
  }

  // Check pixels vs intensity (are they the same?)
  int isSame = assertTrue(pixels, counter);

  // set difference image grayscale
  Mat diffgrey;
  cvtColor(diffimage, diffgrey, CV_BGR2GRAY);

  // If intensity is not same, check if difference in pixels
  // between the two images is correct
  if (!isSame) {
    // Create a blank white image object
    Mat blank(diffimage.rows, diffimage.cols, CV_8UC3, Scalar(255, 255, 255));
    counter = 0;
    cout << "TEST: Diffimage file has correct amount of different pixels" << endl;
    for (int i = 0; i < diffimage.rows; i++) {
      for (int j = 0; j < diffimage.cols; j++) {
        Vec3b intensity1 = blank.at<Vec3b>(Point(j, i));
        Vec3b intensity2 = diffimage.at<Vec3b>(Point(j, i));
        
        // If the intensity is different, increment the counter
        if (!compIntensity(intensity1, intensity2)) {
          counter += 1;
        }
      }
    }
    
    // Check to see if test passes or fails
    assertTrue(diff, counter);
  }

  // write the output image
  imwrite("diffimage.png", diffgrey);	

  return 0;
}

int main(int argc, char** argv) {
  imgCompare(argc, argv);
  return 0;
}
