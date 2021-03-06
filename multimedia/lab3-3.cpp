#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include<math.h>
#include<cstdio>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//image name
	string imageName("./marieke.png");

	if (argc > 1) {
		imageName = argv[1];
	}

	double sum1 = 0.0, sum2 = 0.0;
	int n = 3;

	int gx[3][3] = {{1,0,-1},
					{2,0,-2},
					{1,0,-1}};

	int gy[3][3] = {{1, 2, 1},
					{0, 0, 0},
					{-1,-2,-1}};

	cout << n << "*" << n << ":";

	//image value
	Mat image, result_image;

	//open image
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	//If image is empty
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	result_image = image.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			sum1 = 0;
			sum2 = 0;
			//마스크 만큼 확인하기
			for (int x = -(n/2); x <= (n/2); x++)
			{
				for (int y = -(n/2); y <= (n/2); y++)
				{
					if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
					{
						sum1 += image.at<uchar>(row + x , col + y) * gx[x+1][y+1];
						sum2 += image.at<uchar>(row + x, col + y) * gy[x+1][y+1];
					}
				}
			}
			result_image.at<uchar>(row, col) = sqrt(sum1 * sum1 + sum2 * sum2);
		}
	}

	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("derivative image", WINDOW_AUTOSIZE);
	imshow("derivative image", result_image);

	waitKey(0);
	return 0;
}