#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

int main() {
	cv::Mat image = cv::imread("C:/Users/veras/Desktop/piy.jpeg");
	cv::Mat image1 = cv::imread("C:/Users/veras/Desktop/piy.jpeg");
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

   cv::Mat GRAYImage;
   cvtColor(image, GRAYImage, cv::COLOR_BGR2GRAY);
   cv::imshow("GRAY", GRAYImage);

   cv::Mat gauss;
   cv::GaussianBlur(GRAYImage, gauss, cv::Size(5, 5), 0);

   std::vector<cv::Vec4i> lines;

   cv::Mat edges;
   cv::Canny(GRAYImage, edges, 70, 300);
   cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 1, 20);


   for (size_t i = 0; i < lines.size(); i++) {
	   cv::Vec4i l = lines[i];
	   cv::line(image1, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 255, 0), 3, cv::LINE_AA);
   }

   std::vector<cv::Vec3f> circles;

   cv::HoughCircles(gauss, circles, cv::HOUGH_GRADIENT, 1, GRAYImage.rows / 15, 55, 40, 0, 0);

   for (size_t i = 0; i < circles.size(); i++) {
	   cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	   int radius = cvRound(circles[i][2]);
	   cv::circle(image1, center, radius, cv::Scalar(0, 0, 255), 2, 8, 0);
   }

   cv::imshow("Result", image1);
   cv::waitKey(0);
   return 0;
}
