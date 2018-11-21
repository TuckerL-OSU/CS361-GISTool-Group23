/*
 * Image Comparator
 * CS 361 Group 23
 * Description: This program compares 2 images pixel by pixel.
 * It outputs an image where any differences between the 2 images
 * are shown in grayscale. 
 * Input: 2 images 
 * Output: 1 JPG difference image
 * To run: imagecompar <first image> <second image>
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// check usage
	if (argc != 3)
	{
		cout << "Usage: imagecompar <first image> <second image>" << endl;
		return -1;
	}

	// read in the 2 images	
	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	
	if (!image1.data)
	{
		cout << "Could not open or find first image" << endl;
		return -1;
	}
	if (!image2.data)
	{
		cout << "Could not open or find second image" << endl;
		return -1;
	}

	// create a blank difference image 
	Mat diffimage(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));

	// loop through the pixels of images
	for (int i = 0; i < image1.rows; i++)
	{
		for (int j = 0; j < image1.cols; j++)
		{
			// get current pixel's intensity in image 1 						
			Vec3b intensity1 = image1.at<Vec3b>(Point(j, i));

			// get current pixel's intensity in image 2
			Vec3b intensity2 = image2.at<Vec3b>(Point(j, i));

			// set difference image's pixel to the difference of image1 and image2
			// subtract from 255 to have white background	
			diffimage.at<Vec3b>(Point(j, i))[0] = 255 - abs(intensity1.val[0] - intensity2.val[0]);
			diffimage.at<Vec3b>(Point(j, i))[1] = 255 - abs(intensity1.val[1] - intensity2.val[1]);
			diffimage.at<Vec3b>(Point(j, i))[2] = 255 - abs(intensity1.val[2] - intensity2.val[2]); 
			
			}

		}

	// set difference image grayscale
	Mat diffgrey;
	cvtColor(diffimage, diffgrey, CV_BGR2GRAY);

	// write the output image
	imwrite("diffimage.png", diffgrey);	

	return 0;
}