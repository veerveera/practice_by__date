#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

int main() {

	cv::Mat image = cv::imread("C:/Users/veras/Desktop/emae.jpg");
	if (image.empty()) {
		std::cout << "Error image" << std::endl;
		return -1;
	}
	
// first 
    cv::namedWindow("RGB", WINDOW_NORMAL);
    imshow("RGB", image);

    cv::Mat HSVImage;
    cvtColor(image, HSVImage, COLOR_BGR2HSV);
    cv::namedWindow("HSV", WINDOW_NORMAL);
    cv::imshow("HSV", HSVImage);

    cv::Mat LABImage;
    cvtColor(image, LABImage, COLOR_BGR2Lab);
    cv::namedWindow("LAB", WINDOW_NORMAL);
    imshow("LAB", LABImage);

    cv::Mat YUVImage;
    cvtColor(image, YUVImage, COLOR_BGR2YUV);
    cv::namedWindow("YUV", WINDOW_NORMAL);
    cv::imshow("YUV", YUVImage);

    cv::Mat XYZImage;
    cvtColor(image, XYZImage, COLOR_BGR2XYZ);
    cv::namedWindow("XYZ", WINDOW_NORMAL);
    cv::imshow("XYZ", XYZImage);

    cv::Mat GRAYImage;
    cvtColor(image, GRAYImage, COLOR_BGR2GRAY);
    cv::namedWindow("GRAY", WINDOW_NORMAL);
    cv::imshow("GRAY", GRAYImage);

//second


	cv::waitKey(0);
	return 0;
}