#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */

int main( int argc, char** argv )
{
	/// Read image given by user
	String imageName( "./mrieke.png" ); // by default

	if( argc > 1)
	{
		imageName = argv[1];
	}

	Mat image;
	image = imread( imageName, IMREAD_COLOR );  // Read the file 1

	if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Not found Image" << std::endl ;
        return -1;
    }

	Mat new_image = Mat::zeros( image.size(), image.type() );

	/// Input value
	std::cout << "* Enter the alpha value [1.0-3.0]: "; 
	std::cin>>alpha;
	
	std::cout << "* Enter the beta value [0-100]: "; 
	std::cin>>beta;

	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for( int y = 0; y < image.rows; y++ )
	{ 
		for( int x = 0; x < image.cols; x++ )
		{ 
			for( int c = 0; c < 3; c++ ) //B G R
			{
				new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
			}
		}
	}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("Contrast Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("Contrast Image", new_image);

	/// Wait until user press some key
	waitKey();
	return 0;
}