/*
 * Discoloration Detector
 * CS 361 Group 23
 * Description: This program computes combined RGB value "distance"
 * for each pixel of 2 images, uses it as percent of maximum.  If this
 * value is greater than the threshold value entered as command-line
 * parameter, the piexel is marked in red. Results are saved in a
 * new image that shows the 2nd image with discoloration marked on
 * it in red.
 * Input: 2 images of the same area
 * Output: 1 PNG difference image with discoloration marked
 * To run: discolordetect <first image> <second image> <damage type> <discolor threshold>
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

int validInput(int argc);
int validImages( Mat image1, Mat image2);
Mat detectDiscolor(Mat image1, Mat image2, float discolorThreshold);
int damageType(char* damageParam);
void outputResult(bool detected);

// This function is used to compare RGB values
int comp(float x, float y) {
  if (x == y) {
    return 1;
  } else {
    return 0;
  }
}

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
  if (x == y) {
    cout << "TEST SUCCESSFUL" << endl;
    return 1;
  } else {
    cout << "TEST FAILED" << endl;
    cout << "Expected: " << x << " | Actual: " << y << endl;
    return 0;
  }
}

int main(int argc, char** argv)
{
	// Test for correct # of arguments
	if (argc != 5) 
	{
		assertTrue(0, validInput(argc));
		return -1;
	}
	
	// check damage type
	int damage = damageType(argv[3]);
        cout << "TEST: Correctly identifies damage type" << endl;
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

	// get threshold for discoloration
	float discolorThreshold = atof(argv[4]);

	// get difference between 2 images
	Mat diffimage = detectDiscolor(image1, image2, discolorThreshold);

	// write the output image
	imwrite("diffimage.png", diffimage);	

	return 0;
}

int validInput(int argc)
{
	// check arguments
	if (argc != 5)
	{
		cout << "Usage: imagecompar <old image> <new image> <damage type> <discolor threshold>" << endl;
		return 0;
	}
	return 1;
}

int validImages(Mat image1, Mat image2)
{
	// check images
	if (!image1.data)
	{
                cout << "TEST: First image invalid" << endl;
		cout << "Could not open or find first image" << endl;
		return 0;
	}
	if (!image2.data)
	{
                cout << "TEST: Second image invalid" << endl;
		cout << "Could not open or find second image" << endl;
		return 0;
	}
	// check that dimensions are same
	if (image1.rows != image2.rows || image1.cols != image2.cols)
	{
                cout << "TEST: Image dimensions differ" << endl;
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

Mat detectDiscolor(Mat image1, Mat image2, float discolorThreshold)
{

	// create a blank difference image 
	Mat diffimage(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));

	float discolorMax = sqrt(3 * pow(255, 2));
	bool detected = false;
	int counter = 0;
	int redCount = 0;
	int greenCount = 0;
	int blueCount = 0;
	int pixels = image1.rows * image1.cols;
	
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

			// collect rgb values
			float blue1 = intensity1.val[0];
			float green1 = intensity1.val[1];
			float red1 = intensity1.val[2];
			float blue2 = intensity2.val[0];
			float green2 = intensity2.val[1];
			float red2 = intensity2.val[2];
			
			// Compare the RGB values of every pixel
			redCount += comp(red1, red2);
			greenCount += comp(green1, green2);
			blueCount += comp(blue1, blue2);
			counter += compIntensity(intensity1, intensity2);

			
			
			// compute combined pixel intensity, using distance formula for 3 dimensions
			float discoloration = sqrt(pow((blue2 - blue1), 2) + pow((green2 - green1), 2) + pow((red2 - red1), 2)); 
			// compute discoloration amount, as percent maximum
			float discolorPercent = (discoloration * 100) / discolorMax;
	
			// copy pixel of the 2nd image
			diffimage.at<Vec3b>(Point(j, i))[0] = blue1;
			diffimage.at<Vec3b>(Point(j, i))[1] = green1;
			diffimage.at<Vec3b>(Point(j, i))[2] = red1;

			// mark discoloration if greater than threshold
			if (discolorPercent > discolorThreshold)
			{
				detected = true;
				// mark discolored pixels in red
				diffimage.at<Vec3b>(Point(j, i))[2] = 255;
			} 
		}
	}

// Check pixels vs intensity (are they the same?)
cout << endl;
cout << "TEST: Red intensities are the same" << endl;
int isRedSame = assertTrue(pixels, redCount);
cout << "TEST: Green intensities are the same" << endl;
int isGreenSame = assertTrue(pixels, greenCount);
cout << "TEST: Blue intensities are the same" << endl;
int isBlueSame = assertTrue(pixels, blueCount);

// print out meesage for user
outputResult(detected);

// result image
return diffimage; 

}

void outputResult(bool detected)
{

	if (detected)
	{
		cout << "Discoloration detected. See diffimage.png" << endl;
	} 
	else
	{
		cout << "No discoloration was detected" << endl;
	}

}
