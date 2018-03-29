#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	//�̹��� �̸�
	String imageName("./kakao_talk.png");

	//�̹��� ����
	Mat image;
	Mat image2;

	//�̹��� �Է°�
	image = imread(imageName.c_str(), IMREAD_COLOR);

	// gray scale�� ��ȯ
	cvtColor(image, image, CV_BGR2GRAY);

	// Equalize ������׷�
	equalizeHist(image, image2);
	
	//â ����
	namedWindow("original image", 1);
	namedWindow("Equalize histogram", 1);
	imshow("original image",image);
	imshow("Equalize histogram",image2);

	waitKey(0);
	return 0;
}