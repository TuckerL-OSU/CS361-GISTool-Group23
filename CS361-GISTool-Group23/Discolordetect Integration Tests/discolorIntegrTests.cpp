/*
 * Integration Tests for Discoloration Detector
 * CS 361 Group 23
 * Description: This program contains integration tests for integrated units of discolordetect program
 * Input: 4 images - image 1 and image 3 are the same image, image 2 has discoloration,
 * image 4 has different dimensions than image 1
 * Output: Test results are printed to console
 * To run: integrationTests <image1> <image2> <image3> <image4>
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
int discolorIntegrated(Mat image1In, Mat image2In, char* damageParam, float discolorThreshIn, int argCount);
void assertTrue(int x, int y);

int main(int argc, char** argv)
{


	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	Mat image3 = imread(argv[3], CV_LOAD_IMAGE_COLOR);
	Mat image4 = imread(argv[4], CV_LOAD_IMAGE_COLOR);
	char damageParamText[] = "road"; 
	char* damageParam = damageParamText;	
	float discolorThreshold = 50;
	int argumentCount = 5;

	// Testing integrated modules of discoloration detection
	cout << endl;
	cout << "TEST 1 - All input valid, discoloration present, analysis completes" << endl;
	assertTrue(0, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount));
	cout << endl;

	cout << "TEST 2 - All input valid, no discoloration, analysis completes" << endl;
	assertTrue(0, discolorIntegrated(image1, image3, damageParam, discolorThreshold, argumentCount));
	cout << endl;

	cout << "TEST 3 - Argument missing" << endl;	
	assertTrue(-1, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount - 1));
	cout << endl;

	cout << "TEST 4 - Images have different dimensions" << endl;
	assertTrue(-1, discolorIntegrated(image1, image4, damageParam, discolorThreshold, argumentCount));
	cout << endl;

	cout << "TEST 5 - Low discoloration threshold is used" << endl;
	discolorThreshold = 1;
	assertTrue(0, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount));
	discolorThreshold = 50;
	cout << endl;
	
	cout << "TEST 6 - High discoloration threshold is used" << endl;
	discolorThreshold = 98;
	assertTrue(0, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount));
	discolorThreshold = 50;
	cout << endl;

	cout << "TEST 7 - Damage parameter flood is used" << endl;
	char damageParamText2[] = "flood";
	damageParam = damageParamText2;
	assertTrue(0, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount));
	damageParam = damageParamText;
	cout << endl;
	
	cout << "TEST 8 - Wrong damage parameter is used" << endl;
	char damageParamText3[] = "buildings";
	damageParam = damageParamText3;
	assertTrue(-1, discolorIntegrated(image1, image2, damageParam, discolorThreshold, argumentCount));
	damageParam = damageParamText;
	cout << endl;

return 0;
}

void assertTrue(int x, int y)
{
 	if (x == y)
	{
		cout << "TEST SUCCESSFUL" << endl;
	}
	else
	{
		cout << "TEST FAILED" << endl;
	}

}

int discolorIntegrated(Mat image1In, Mat image2In, char* damageParam, float discolorThreshIn, int argCount)
{
	// check arguments
	if (!validInput(argCount))
	{
		return -1;
	}

	// check damage type
	int damage = damageType(damageParam);

	// output damage type info	
	switch(damage) 
	{
		case 1:
			cout << "Analysis for road damage" << endl;
			break;
		case 2:
			cout << "Analysis for flood damage" << endl;
			break;
		case 0:
			cout << "Damage type parameter was not recognized" << endl;
			return -1;
	}	

	// read in the 2 images	
	Mat image1 = image1In;
	Mat image2 = image2In;

	// check input image validity
	if (!validImages(image1, image2))
	{
		return -1;
	}

	// get threshold for discoloration
	float discolorThreshold = discolorThreshIn;

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
		cout << "Could not open or find first image" << endl;
		return 0;
	}
	if (!image2.data)
	{
		cout << "Could not open or find second image" << endl;
		return 0;
	}
	// check that dimensions are same
	if (image1.rows != image2.rows || image1.cols != image2.cols)
	{
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
// print out message for user
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
