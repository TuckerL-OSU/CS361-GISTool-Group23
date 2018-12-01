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

using namespace cv;
using namespace std;

int validInput(int argc);
int validImages( Mat image1, Mat image2);
Mat compareImages(Mat image1, Mat image2);
Mat setGreyscale(Mat diffimage);
int damageType(char* damageParam);
int checkTolParam(char* tolerance);

// This function is used to compare a pair of vectors (intensity)
int compIntensity(Vec3b x, Vec3b y) {
	if (x == y) 
	{
		return 1;
	} 
	else 
	{
		return 0;
	}
}

// This function is used to see if the tests pass by
// comparing an expected value (x) to the actual value (y).
int assertTrue(int x, int y) {
	if (x == y) 
	{
		cout << "TEST SUCCESSFUL" << endl;
		return 1;
	} 
	else 
	{
		cout << "TEST FAILED" << endl;
		cout << "Expected: " << x << " | Actual: " << y << endl;
		return 0;
	}
}

int main(int argc, char** argv)
{
	// Test for correct # of arguments
	if (argc != 6) 
	{
		assertTrue(0, validInput(argc));
		return -1;
	}

	// read in the 2 images	
	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

	// check input data
	int x = validImages(image1, image2);
	if (!x)
	{
		assertTrue(0, x);
		return -1;
	}
	
	// check damage type
	int damage = damageType(argv[3]);
	if (damage == 1 || damage == 2) 
	{
		cout << "TEST: damageType function correctly assigns the damage type" << endl;
	}
	else 
	{
		cout << "TEST: Damage type not recognized" << endl;
	}
	

	// output damage type info	
	switch(damage) 
	{
		case 1:
			cout << "Analysis for road damage" << endl;
			assertTrue(1, damage);
                        cout << endl;
			break;
		case 2:
			cout << "Analysis for flood damage" << endl;
			assertTrue(2, damage);
                        cout << endl;
			break;
		case 0:
			cout << "Damage type parameter was not recognized" << endl;
			assertTrue(1, damage);
                        cout << endl;
	}	

	int tolerance = checkTolParam(argv[4]);
	if (damage == 1 || damage == 2) 
	{
		cout << "TEST: Correctly assigns the tolerance type" << endl;
	}
	else 
	{
		cout << "TEST: Tolerance type recognized" << endl;
	}
	

	// output tolerance type info	
	switch(tolerance) 
	{
		case 1:
			cout << "Analysis for length changes" << endl;
			assertTrue(1, tolerance);
                        cout << endl;
			break;
		case 2:
			cout << "Analysis for width changes" << endl;
			assertTrue(2, tolerance);
                        cout << endl;
			break;
		case 0:
			cout << "Tolerance type parameter was not recognized" << endl;
			assertTrue(1, tolerance);
                        cout << endl;
	}

	int percent = atoi(argv[5]);
	if (percent == 0) {
		cout << "TEST: Invalid parameter detected" << endl;
		cout << "Cannot have threshold of 0 or invalid threshold" << endl;
		assertTrue(0, percent);
		cout << endl;
	}

	// get difference between 2 images
	Mat diffimage = compareImages(image1, image2);

	// turn image into greyscale
	Mat diffgrey = setGreyscale(diffimage);

	// write the output image
	imwrite("diffimage.png", diffgrey);	

	return 0;
}

int validInput(int argc)
{
	// check arguments
	if (argc != 6)
	{
		cout << "TEST: Invalid Number of Arguments" << endl;
		cout << "Usage: imagecompar <first image> <second image> <damage type>" << endl;
		return 0;
	}
	return 1;
}

int validImages(Mat image1, Mat image2)
{
	// check images
	if (!image1.data)
	{
		cout << "TEST: First image does not exist" << endl;
		cout << "NOTE: If both files don't exist, program exits at first image" << endl;
		cout << "Could not open or find first image" << endl;
		return 0;
	}
	if (!image2.data)
	{
		cout << "TEST: Second image does not exist" << endl;
		cout << "Could not open or find second image" << endl;
		return 0;
	}

	if (image1.rows != image2.rows || image1.cols != image2.cols)
	{
		cout << "TEST: Dimensions are different" << endl;
		cout << "Image dimensions differ" << endl;
		return 0;
	}

	return 1;
}

int damageType(char* damageParam)
{
	if (strcmp(damageParam, "road") == 0)
	{
		return 1;
	}
	else if (strcmp(damageParam, "flood") == 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

// Checks which tolerance parameter is indicated
int checkTolParam(char* type)
{
	if (strcmp(type, "length") == 0)
	{
		return 1;
	}
	else if (strcmp(type, "width") == 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

Mat compareImages(Mat image1, Mat image2)
{

	// create a blank difference image 
	Mat diffimage(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));
	
	// Total pixels
	int pixels = image1.rows * image1.cols;
	int counter = 0;
	
	cout << "TEST: Intensities are the same for both images" << endl;
	cout << "NOTE: Test will fail if images are different" << endl;

	// loop through the pixels of images
	for (int i = 0; i < image1.rows; i++)
	{
		for (int j = 0; j < image1.cols; j++)
		{
			// get current pixel's intensity in image 1 						
			Vec3b intensity1 = image1.at<Vec3b>(Point(j, i));

			// get current pixel's intensity in image 2
			Vec3b intensity2 = image2.at<Vec3b>(Point(j, i));
			
			// Increment the counter if the intensities are the same
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
	// If intensity is not same, check if difference in pixels
	// between the two images is correct
	if (!isSame) 
	{
		cout << endl;  
		// Find the difference in pixels between the two images.
		int diff = pixels - counter;
	
		// Create a blank white image object
		Mat blank(diffimage.rows, diffimage.cols, CV_8UC3, Scalar(255, 255, 255));	  
		counter = 0;
		cout << "TEST: Diffimage file has correct amount of different pixels" << endl;
	
		// Compare the blank image to the diffimage
		for (int i = 0; i < diffimage.rows; i++) 
		{
			for (int j = 0; j < diffimage.cols; j++) 
			{
	
				// Initialize the intensities for comparison
				Vec3b intensity1 = blank.at<Vec3b>(Point(j, i));
				Vec3b intensity2 = diffimage.at<Vec3b>(Point(j, i));
        
				// If the intensity is different, increment the counter
				if (!compIntensity(intensity1, intensity2)) 
				{
					counter += 1;
				}
			}
		}
   
    // Check to see if test passes or fails
    assertTrue(diff, counter);
  }
	
	return diffimage;

}

Mat setGreyscale(Mat diffimage)
{
	// set difference image grayscale
	Mat diffgrey;
	cvtColor(diffimage, diffgrey, CV_BGR2GRAY);

	return diffgrey;
}
