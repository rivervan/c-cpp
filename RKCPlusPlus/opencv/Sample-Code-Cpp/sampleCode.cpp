//#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>


using namespace cv;
using namespace std;

int main(void) {
	
	// Read image in GrayScale mode
	Mat image = imread("../boy.jpg",IMREAD_GRAYSCALE);
    cout << image << std::endl;
    cout<<"Size of image: "<<  image.size().height << " x " << image.size().width << endl;

	// Save grayscale image
	imwrite("../boyGray.jpg",image);

	return 0;
}
