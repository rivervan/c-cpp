#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//#include <opencv2/core.hpp>



#include <iostream>
#include <string>

using namespace std;
using namespace cv;


class MyTestCV2{

 public:
	string type2str(int type);


};


string MyTestCV2::type2str (int type){
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}





int main(void) {
	
	// 1. Read image in GrayScale mode
	Mat image = imread("../images/number_zero.jpg",IMREAD_GRAYSCALE);  //IMREAD_GRAYSCALE | IMREAD_COLOR | IMREAD_UNCHANGED      
	cout << image << std::endl; // 0 means black pixel and as the value increases, it moves towards white. A value of 255 is a white pixel.

	MyTestCV2 myTestCV2; 
	cout<<"Type of image: "<<  myTestCV2.type2str(image.type())<< endl;
	cout<<"Size of image: "<<  image.size().height << " x " << image.size().width << endl;
     //image.size() is derived template cv::Size_< _Tp >

    //2. Accessing pixels
	cout<<"Pos(4,2): "<<(int)image.at<uchar>(2,4)<<endl;//CV: (y,x) = (row, col)

	//3. Modifying pixels
	image.at<uchar>(0,0) = 200;
	cout << image << std::endl;


	//4. ROI of pixels
	Mat test_roi = image(Range(1,12), Range(2,11));	
	cout<<"selecttion ROI: \n"<<test_roi<< endl;
	//Range: [start,end).


    //5. Write the image to disk  & Display a image throught one matriz		
	imwrite("../images/roi.jpg", test_roi);
	Mat myRoi = imread("../images/roi.jpg",IMREAD_GRAYSCALE);
	
	namedWindow("Zero whole", WINDOW_NORMAL );
    imshow("Zero whole", image);

	namedWindow("ROI", WINDOW_NORMAL );
    imshow("ROI", myRoi);
	
	waitKey(0);
	destroyAllWindows();


	//6. Color images: In OpenCV, the order of channels R, G and B is reverse.
    Mat boy = imread("../images/boy.jpg");
	cout<< "Image size: " << boy.size() << endl;
	cout<< "Image channels: " << boy. channels() << endl;
	namedWindow("Boy", WINDOW_NORMAL );
    imshow("Boy", boy);	
	waitKey(0);
	destroyAllWindows();
	






	return 0;
}
