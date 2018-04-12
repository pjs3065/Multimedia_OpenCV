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
	string imageName("./lena_noise.png");

	if (argc > 1) {
		imageName = argv[1];
	}

	double sum1 = 0.0;
	int n = 3;

	vector<int> gx(9);

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
			//초기화
			for(int k = 0; k < 9; k++)
			{
				gx[k] = 0;
			}

			//이미지 값에서 뽑아 내기
			for (int x = -(n/2); x <= (n/2); x++)
			{
				for (int y = -(n/2); y <= (n/2); y++)
				{
					if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
					{
						gx[(x+1) * 3 + (y + 1)] = image.at<uchar>(row+x,col+y);
					}
				}
			}

			sort(gx.begin(),gx.end());

			int median = (gx[3] + gx[4]) / 2;
			result_image.at<uchar>(row, col) = median;
		}
	}
	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("median image", WINDOW_AUTOSIZE);
	imshow("median image", result_image);

	waitKey(0);
	return 0;
}