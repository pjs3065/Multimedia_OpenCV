#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

//네임스페이스 지정
using namespace cv;
using namespace std;

//히스토그램 만들기 위한 변수
int histSize = 256;

float range[] = {0,256};
const float* histRange = {range};

//그래프 만들기 위한 창
int hist_w= 512; int hist_h= 400;

int main( int argc, char** argv )
{
	//이미지 이름
	String imageName("./marieke.png");

	//그래프 빈 변수
	int bin_w= cvRound((double) hist_w/histSize);

	//이미지 변수
	Mat image;
	Mat image2;

	//히스토그램 변수
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
	Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

	Mat b_hist;
	Mat b_hist2;

	//이미지 입력값
	image = imread(imageName.c_str(), IMREAD_COLOR);

	// gray scale로 변환
	cvtColor(image, image, CV_BGR2GRAY);

	// Equalize 히스토그램
	equalizeHist(image, image2);

	//calcHist
	calcHist(&image, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, true, false);
	calcHist(&image2, 1, 0, Mat(), b_hist2, 1, &histSize, &histRange, true, false);

	//정규화
	normalize(image, image, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(image2, image2, 0, histImage2.rows, NORM_MINMAX, -1, Mat() );

	//히스토그램 만들어 주기
	for(int i= 1; i< histSize; i++)
	{
		line(histImage, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))) , Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage2, Point(bin_w*(i-1), hist_h - cvRound(b_hist2.at<float>(i-1))) , Point(bin_w*(i), hist_h - cvRound(b_hist2.at<float>(i)) ), Scalar(255, 0, 0), 2, 8, 0);
	}

	//창 이름 지정
	namedWindow("Input original image", 1);
	namedWindow("Input calcHist Demo", 1);
	namedWindow("original image", 1);
	namedWindow("calcHist Demo", 1);

	//이미지 창 띄우기
	imshow("Input original image",image);
	imshow("Input calcHist Demo",image2);

	//그래프 창 띄우기
	imshow("original image",histImage);
	imshow("calcHist Demo",histImage2);

	waitKey(0);
	return 0;
}