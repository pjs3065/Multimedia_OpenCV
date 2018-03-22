#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

double alpha;
double beta;

int main( int argc, char** argv )
{
	//�̹��� �̸�
	String imageName("./mrieke.png");
	String imageName2("./kakao_talk.png");

	//�̹��� ����
	Mat image;
	Mat image2;
	Mat blinding_image;

	//�Է�
	std::cout<<" Enter alpha : ";
	std::cin>>alpha;

	//�̹��� �Է°�
	image = imread(imageName.c_str(), IMREAD_COLOR);
	image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	//���
	beta = 1.0 - alpha;
	
	//�̹��� ũ�� ���� (imageũ�⸦ blinding_image��)
	cv::resize(image,blinding_image, cv::Size(image2.cols, image2.rows), 0, 0, CV_INTER_NN);

	//������ �̹��� ũ�� ��ŭ pixel ��ġ��
	for( int y = 0; y < blinding_image.rows; y++ )
	{ 
		for( int x = 0; x < blinding_image.cols; x++ )
		{ 
			for( int c = 0; c < 3; c++ ) //B G R
			{
				blinding_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha * ( blinding_image.at<Vec3b>(y,x)[c] )) + saturate_cast<uchar>( beta *( image2.at<Vec3b>(y,x)[c] ));
			}
		}
	}
	
	//â ����
	namedWindow("Blinding Image", 1);
	imshow("Blinding Image",blinding_image);

	waitKey(0);
	return 0;
}