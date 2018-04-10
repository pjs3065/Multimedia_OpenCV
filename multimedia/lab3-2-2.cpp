#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include<math.h>
#include<cstdio>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//image name
	string imageName("./marieke.png");

	if (argc > 1) {
		imageName = argv[1];
	}

	double  sigma, sum =0.0 , gau;
	int n;

	//input
	cout << "Input n : ";
	cin >> n;
	cout << "Input Sigma : ";
	cin >> sigma;

	//image value
	Mat image, image2;

	//open image
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	image2 = Mat::zeros(image.size(), image.type());

	//If image is empty
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// Testing Make mask (i = x , j = y) 
	for (int i = -(n/2); i <= (n/2); i++) {
		for (int j = -(n/2); j <= (n/2); j++) {
			gau = exp((-(pow(i, 2) + pow(j, 2))) / (2 * sigma*sigma));
			printf("%lf\t", gau);
		}
		printf("\n");
	}

	//Gaus filter
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {

			sum = 0;

			//mask (above algorithm)
			for (int k = -(n/2); k <= (n/2); k++) {
				for (int l = -(n/2); l <= (n/2); l++) {

					int px = i + k;
					int py = j + l;

					if (!(px < 0 || px >= image.rows || py < 0 || py >= image.cols))
					{
						gau = exp((-(pow(k, 2) + pow(l, 2))) / (2 * sigma*sigma)) / (2 * 3.14 * sigma * sigma);
						sum += image.at<uchar>(px, py); 
					}
				}
			}
			image2.at<uchar>(i, j) = sum  * gau;
		}
	}

	//window name and open window
	namedWindow("original image", WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("gau image", WINDOW_AUTOSIZE);
	imshow("gau image", image2);

	waitKey(0);
	return 0;
}