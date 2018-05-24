#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int get_closerX(int scaled_x, float scale, int max_x);
int get_closerY(int scaled_y, float scale, int max_y);

int main(int argc, char** argv)
{
	string imageName("./Lena_color.png");
	float scale;

	//스케일 받기
	printf("Please type scale factor\n");
	scanf("%f", &scale);

	if (scale <= 0)
		return 0;

	if (argc > 1)
	{
		imageName = argv[1];
	}

	//이미지를 받아오기
	Mat input_image, scaled_image;
	input_image = imread(imageName.c_str(), IMREAD_COLOR);

	if (input_image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//사이즈
	int col_max = input_image.cols;
	int row_max = input_image.rows;

	//스케일된 사이즈
	int scaled_col = (int)(col_max * scale);
	int scaled_row = (int)(row_max * scale);

	//스케일된 이미지 만들기
	scaled_image = Mat::zeros(scaled_row, scaled_col, input_image.type());

	//1step
	for (int row = 0; row < scaled_row; row = row + scale)
	{
		for (int col = 0; col < scaled_col; col = col + scale)
		{
			int cur_row = row/scale;
			int cur_col = col/scale;

			scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(cur_row, cur_col);
		}
	}

	//2step
	for (int row = 0; row < scaled_row; row++)
	{
		for (int col = 0; col < scaled_col; col++)
		{
			int cur_row = row/scale;
			int cur_col = col/scale;

			if(row % (int)scale == 0 && col % (int)scale == 0)
			{
				continue;
			}

			if(col + scale >= scaled_col)
			{

				scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(cur_row, cur_col) * (1- (col % (int)scale * (1/scale)));
			}

			else
			{
				scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(cur_row, cur_col) * (1- (col % (int)scale * (1/scale))) 
					                               + input_image.at<Vec3b>(cur_row, (col + scale)/scale) * (col % (int)scale * (1/scale));
			}
		}
	}

	//3step
	for (int col = 0; col < scaled_col; col++)
	{
		for (int row = 0; row < scaled_row; row++)
		{
			int cur_row = row/scale;
			int cur_col = col/scale;

			if(row % (int)scale == 0 && col % (int)scale == 0)
			{
				continue;
			}

			if(row + scale >= scaled_row)
			{

				scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(cur_row, cur_col) * (1- (row % (int)scale * (1/scale)));
			}

			else
			{
				scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(cur_row, cur_col) * (1- (row % (int)scale * (1/scale))) 
					                               + input_image.at<Vec3b>((row + scale)/scale, cur_col) * (row % (int)scale * (1/scale));
			}
		}
	}

	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", input_image);

	namedWindow("scaled", WINDOW_AUTOSIZE);
	imshow("scaled", scaled_image);
	imwrite("result.bmp", scaled_image);

	waitKey(0);

	return 0;
}