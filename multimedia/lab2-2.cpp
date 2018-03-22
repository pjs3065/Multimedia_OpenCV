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
	//이미지 이름
	String imageName("./mrieke.png");
	String imageName2("./kakao_talk.png");

	//이미지 변수
	Mat image;
	Mat image2;
	Mat blinding_image;

	//입력
	std::cout<<" Enter alpha : ";
	std::cin>>alpha;

	//이미지 입력값
	image = imread(imageName.c_str(), IMREAD_COLOR);
	image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	//계산
	beta = 1.0 - alpha;
	
	//이미지 크기 조절 (image크기를 blinding_image로)
	cv::resize(image,blinding_image, cv::Size(image2.cols, image2.rows), 0, 0, CV_INTER_NN);

	//조절한 이미지 크기 만큼 pixel 합치기
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
	
	//창 띄우기
	namedWindow("Blinding Image", 1);
	imshow("Blinding Image",blinding_image);

	waitKey(0);
	return 0;
}