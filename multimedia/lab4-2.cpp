#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include<math.h>
#include<cstdio>
#include<algorithm>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//image name
	string imageName("./Lena_color.png");

	float k = 0.7;

	if (argc > 1) {
		imageName = argv[1];
	}

	//image value
	Mat image = imread(imageName.c_str(), IMREAD_COLOR);

	Mat rgb_image = Mat::zeros(image.size(),image.type());
	Mat ycbcr_image = Mat::zeros(image.size(),image.type());
	Mat cmy_image = Mat::zeros(image.size(),image.type());
	Mat hsv_image = Mat::zeros(image.size(),image.type());

	//If image is empty
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	float y_bgr[3] = {24.966, 128.554, 65.481};
	float cb_bgr[3] = {112, -74.203, -37.797};
	float cr_bgr[3] = {-18.214, -93.786, 112};

	//rgb
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			for(int c = 0; c < 3; c++)
			{
				rgb_image.at<Vec3b>(row,col)[c] = saturate_cast<uchar>(image.at<Vec3b>(row,col)[c] * k);
			}
		}
	}

	//ycbcr
	cvtColor(image,ycbcr_image,CV_BGR2YCrCb);

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			ycbcr_image.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(ycbcr_image.at<Vec3b>(row,col)[0] * k);
		}
	}

	cvtColor(ycbcr_image,ycbcr_image,CV_YCrCb2BGR);

	//CMY
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			for(int c = 0; c < 3; c++)
			{
				cmy_image.at<Vec3b>(row,col)[c] = saturate_cast<uchar>(rgb_image.at<Vec3b>(row,col)[c] + (1 - k));
			}
		}
	}

	//hsv
	cvtColor(image,hsv_image,CV_BGR2HSV);

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
				hsv_image.at<Vec3b>(row,col)[2] = saturate_cast<uchar>(hsv_image.at<Vec3b>(row,col)[2] * k);
		}
	}

	cvtColor(hsv_image,hsv_image,CV_HSV2BGR);

	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("rgb_image", WINDOW_AUTOSIZE);
	imshow("rgb_image", rgb_image);

	namedWindow("ycbcr_image", WINDOW_AUTOSIZE);
	imshow("ycbcr_image", ycbcr_image);

	namedWindow("cmy_image", WINDOW_AUTOSIZE);
	imshow("cmy_image", cmy_image);

	namedWindow("hsv_image", WINDOW_AUTOSIZE);
	imshow("hsv_image", hsv_image);

	waitKey(0);
	return 0;
}