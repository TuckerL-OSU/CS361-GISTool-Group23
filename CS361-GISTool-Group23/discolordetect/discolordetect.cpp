/*
 * Image Comparator
 * CS 361 Group 23
 * Description: This program compares 2 images pixel by pixel.
 * It outputs an image where any differences between the 2 images
 * are shown in grayscale. 
 * Input: 2 images 
 * Output: 1 PNG difference image
 * To run: imagecompar <first image> <second image>
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

int main(int argc, char** argv)
{
	// check arguments
	if (!validInput(argc))
	{
		return -1;
	}

	// check damage type
	int damage = damageType(argv[3]);

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
	}	

	// read in the 2 images	
	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

	// check input image validity
	if (!validImages(image1, image2))
	{
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
		cout << "Could not open or find first image" << endl;
		return 0;
	}
	if (!image2.data)
	{
		cout << "Could not open or find second image" << endl;
		return 0;
	}
	// check that  dimensions are same
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

			float blue1 = intensity1.val[0];
			float green1 = intensity1.val[1];
			float red1 = intensity1.val[2];
			float blue2 = intensity2.val[0];
			float green2 = intensity2.val[1];
			float red2 = intensity2.val[2];

			float discoloration = sqrt(pow((blue2 - blue1), 2) + pow((green2 - green1), 2) + pow((red2 - red1), 2)); 
			float discolorPercent = (discoloration * 100) / discolorMax;
	
			diffimage.at<Vec3b>(Point(j, i))[0] = blue1;
			diffimage.at<Vec3b>(Point(j, i))[1] = green1;
			diffimage.at<Vec3b>(Point(j, i))[2] = red1;

			if (discolorPercent > discolorThreshold)
			{
				detected = true;
				// mark discolored pixels in red
				diffimage.at<Vec3b>(Point(j, i))[2] = 255;
			} 
		}
	}
outputResult(detected);
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
