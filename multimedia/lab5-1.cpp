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

	//이미지 불러오기
	string imageName1("./chromakey.jpg");
	string imageName2("./hill.jpg");

	if (argc > 1) {
		imageName1 = argv[1];
	}

	//이미지 값
	Mat image1 = imread(imageName1.c_str(), IMREAD_COLOR);
	Mat image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	Mat ycbcr_image = Mat::zeros(image1.size(),image1.type());

	//If image is empty
	if (image1.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//If image2 is empty
	if (image2.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//ycbcr
	cvtColor(image1,ycbcr_image,CV_BGR2YCrCb);

	//이미지 크기 별 값
	int image1row = image1.rows;
	int image1col = image1.cols;

	int image2row = image2.rows;
	int image2col = image2.cols;

	//cb_key , cr_key 구하기
	vector<int> fre_cr(256);
	vector<int> fre_cb(256);

	for (int row = 0; row < image1row; row++)
	{
		for (int col = 0; col < image1col; col++)
		{

			int cr = saturate_cast<uchar>(ycbcr_image.at<Vec3b>(row,col)[1]);
			int cb = saturate_cast<uchar>(ycbcr_image.at<Vec3b>(row,col)[2]);

			fre_cr[cr]++;
			fre_cb[cb]++;
		}
	}

	//Cb cr key 구하기
	int cr_key = -1;
	int cb_key = -1;

	for(int i = 0; i < 256; i++)
	{

		if(fre_cr[i] > cr_key)
		{
			cr_key = i;
		}

		if(fre_cb[i] > cb_key)
		{
			cb_key = i;
		}
	}

	printf("%d %d", cr_key, cb_key);

	Mat chroma_image = Mat::zeros(image1.size(),image1.type());

	//스레쉬 홀드
	int inner = 25;
	int outer = 46;

	for (int row = 0; row < image1row; row++)
	{
		for (int col = 0; col < image1col; col++)
		{
			int x2 = saturate_cast<uchar>(ycbcr_image.at<Vec3b>(row,col)[1]);
			int y2 = saturate_cast<uchar>(ycbcr_image.at<Vec3b>(row,col)[2]);

			//거리 구하고
			int dis = sqrt(pow(cr_key - x2, 2) + pow(cb_key - y2,2));

			float a = 0.0;

			//거리 조건
			if(dis < inner)
			{
				a = 0;
			}

			else if(dis > outer)
			{
				a = 1;
			}

			else
			{
				a = (dis - inner)/(outer - inner);
			}

			//크로마키 공식
			chroma_image.at<Vec3b>(row,col) = (image1.at<Vec3b>(row,col) * (1-a)) + (image2.at<Vec3b>(row,col) * a);
		}
	}

	//window name and open window
	namedWindow("front image", WINDOW_AUTOSIZE);
	imshow("front image", image1);

	//window name and open window
	namedWindow("background image", WINDOW_AUTOSIZE);
	imshow("background image", image2);

	namedWindow("chroma_image", WINDOW_AUTOSIZE);
	imshow("chroma_image", chroma_image);
	imwrite("chroma_image.bmp",chroma_image);

	waitKey(0);
	

	return 0;
}