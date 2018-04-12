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
	string imageName("./lena_color.png");

	if (argc > 1) {
		imageName = argv[1];
	}
	
	double sum1 = 0.0, sum2 = 0.0;
	int n = 3;

	int gx[3][3] = {{0,-1,0},
					{-1,4,-1},
					{0,-1,0}};


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
	Mat result_image2 = result_image.clone();

		for (int row = 0; row < image.rows; row++)
		{
			for (int col = 0; col < image.cols; col++)
			{
				sum1 = 0;

				//마스크 만큼 확인하기
				for (int x = -(n/2); x <= (n/2); x++)
				{
					for (int y = -(n/2); y <= (n/2); y++)
					{
						if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
						{
							sum1 += image.at<uchar>(row + x , col + y) * gx[x+1][y+1];
						}
					}
				}
				result_image.at<uchar>(row, col) = abs(sum1);
				result_image2.at<uchar>(row, col) = saturate_cast<uchar>(image.at<uchar>(row,col) + sum1);
			}
		}
/*
		Mat result_image2 = result_image.clone();
		for (int row = 0; row < result_image2.rows; row++)
		{
			for (int col = 0; col < result_image2.cols; col++)
			{
				result_image2.at<uchar>(row, col) = saturate_cast<uchar>(result_image2.at<uchar>(row,col) + image.at<uchar>(row,col));
			}
		}
		*/
	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("masking image", WINDOW_AUTOSIZE);
	imshow("masking image", result_image);

	
	namedWindow("laplacian image", WINDOW_AUTOSIZE);
	imshow("laplacian image", result_image2);
	

	waitKey(0);
	return 0;
}