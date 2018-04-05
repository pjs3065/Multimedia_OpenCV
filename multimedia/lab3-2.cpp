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

	//����ũ ������
	const int mask_size = 3;
	float average_factor = 0.11;
	int n;

	//�̹��� �̸� ��������
	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat image, result_image;

	//�̹��� �б�
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	//�̹��� ��ǲ�� �´��� Ȯ��
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/// n��ǲ �� �ޱ�
	std::cout << "Input your n value : "; 
	std::cin >> n;

	//�������� �̹��� �� ���� �ϱ�
	result_image = image.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float sum = 0;

			//����ũ ��ŭ Ȯ���ϱ�
			for (int x = -(n/2); x <= (n/2); x++)
			{
				for (int y = -(n/2); y <= (n/2); y++)
				{
					if ((col + y >= 0 && col + y < image.cols) && (row + x >= 0 && row + x < image.rows))
					{
						sum += image.at<uchar>(row + x, col + y);
					}
				}
			}
			result_image.at<uchar>(row, col) = sum / (n * n);
		}
	}

	//â �̸�
	namedWindow("original image", 1);
	namedWindow("result_image", 1);

	//â ����
	imshow("original image", image);
	imshow("result_image", result_image);
	
	waitKey(0);
	return 0;
}