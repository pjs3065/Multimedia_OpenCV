#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string imageName("./mrieke.png");

	//마스크 사이즈
	const int mask_size = 3;
	float average_factor = 0.11;
	int n, gausian_factor, pow_gausian_factor;
	float **mask;

	//이미지 이름 가져오기
	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat image, result_image;

	//이미지 읽기
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	//이미지 인풋이 맞는지 확인
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/// n인풋 값 받기
	std::cout << "Input your n value : "; 
	std::cin >> n;
	std::cout << "Input your gausian_factor value : "; 
	std::cin >> gausian_factor;

	pow_gausian_factor = gausian_factor * gausian_factor;

	// 마스크 공간 동적 할당 만들기
	mask = (float **)malloc(sizeof(float) * n);

	for (int row = 0; row < n; row++)
	{
		mask[row] = (float *)malloc(sizeof(float) * n);
	}

	// 마스크 값 할당하기
	for(int row = 0; row < n; row++)
	{
		for(int col = 0; col <n; col++)
		{
			mask[row][col] = (float)(exp(-1 * (row*row + col*col) / 2 * pow_gausian_factor) / (2 * 3.14 * pow_gausian_factor));
			printf("%f ",mask[row][col]);
		}
		printf("\n");
	}

	//오리지날 이미지 값 복사 하기
	result_image = image.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float sum = 0;

			//마스크 만큼 확인하기
			for (int x = -(n/2); x <= (n/2); x++)
			{
				for (int y = -(n/2); y <= (n/2); y++)
				{
					if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
					{
						sum += float(image.at<uchar>(row + x, col + y) * mask[x][y]);
					}
				}
			}
			result_image.at<uchar>(row, col) = sum / (n*n);
		}
	}

	//창 이름
	namedWindow("original image", 1);
	namedWindow("result_image", 1);

	//창 띄우기
	imshow("original image", image);
	imshow("result_image", result_image);

	waitKey(0);
	return 0;
}