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

	if (argc > 1) {
		imageName = argv[1];
	}

	//image value
	Mat image = imread(imageName.c_str(), IMREAD_COLOR);

	Mat y_image = Mat::zeros(image.size(),CV_8UC1);
	Mat cb_image = Mat::zeros(image.size(),CV_8UC1);
	Mat cr_image = Mat::zeros(image.size(),CV_8UC1);

	//If image is empty
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	float y_bgr[3] = {24.966, 128.554, 65.481};
	float cb_bgr[3] = {112, -74.203, -37.797};
	float cr_bgr[3] = {-18.214, -93.786, 112};

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float y_image_temp = 0.0;
			float cb_image_temp = 0.0;
			float cr_image_temp = 0.0;

			for(int c = 0; c < 3; c++)
			{
					y_image_temp += (image.at<Vec3b>(row,col)[c]/255.0) * y_bgr[c];
					cb_image_temp += (image.at<Vec3b>(row,col)[c]/255.0) * cb_bgr[c];
					cr_image_temp += (image.at<Vec3b>(row,col)[c]/255.0) * cr_bgr[c];
			}

			y_image.at<uchar>(row,col) = saturate_cast<uchar>(y_image_temp + 16);
			cb_image.at<uchar>(row,col) = saturate_cast<uchar>(cb_image_temp + 128);
			cr_image.at<uchar>(row,col) = saturate_cast<uchar>(cr_image_temp + 128);
		}
	}

	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("y_image", WINDOW_AUTOSIZE);
	imshow("y_image", y_image);

	namedWindow("cb_image", WINDOW_AUTOSIZE);
	imshow("cb_image", cb_image);

	namedWindow("cr_image", WINDOW_AUTOSIZE);
	imshow("cr_image", cr_image);

	waitKey(0);
	return 0;
}