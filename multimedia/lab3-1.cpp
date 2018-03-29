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
	//이미지 이름
	String imageName("./kakao_talk.png");

	//이미지 변수
	Mat image;
	Mat image2;

	//이미지 입력값
	image = imread(imageName.c_str(), IMREAD_COLOR);

	// gray scale로 변환
	cvtColor(image, image, CV_BGR2GRAY);

	// Equalize 히스토그램
	equalizeHist(image, image2);
	
	//창 띄우기
	namedWindow("original image", 1);
	namedWindow("Equalize histogram", 1);
	imshow("original image",image);
	imshow("Equalize histogram",image2);

	waitKey(0);
	return 0;
}