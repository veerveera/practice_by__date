#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
int main() {

	cv::Mat image = cv::imread("C:/Users/veras/Desktop/emae.jpg");
	if (image.empty()) {
		std::cout << "Error image" << std::endl;
		return -1;
	}
	int width = image.cols;
	int height = image.rows;

	//first
	cv::putText(image, std::to_string(width), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
	cv::putText(image, "x", cv::Point(70, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
	cv::putText(image, std::to_string(height), cv::Point(90, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
	cv::circle(image, cv::Point(300, 100), 50, cv::Scalar(0, 25, 0), 1);
	cv::rectangle(image, cv::Point(100, 150), cv::Point(150, 200), cv::Scalar(255, 0, 0), 1);
	cv::ellipse(image, cv::Point(300, 400), cv::Size(60, 40), 45, 0, 360, cv::Scalar(0, 0, 30), -1);
	cv::line(image, cv::Point(450, 100), cv::Point(100, 450), cv::Scalar(0, 0, 40), 1);
	cv::rectangle(image, cv::Point(320, 340), cv::Point(340, 360), cv::Scalar(255, 0, 0), -1);
	cv::imshow("Image", image);

	//second

	//part
	cv::Rect p1(0, 0, image.cols / 2, image.rows / 2);
	cv::Rect p2(image.cols / 2, 0, image.cols / 2, image.rows / 2);
	cv::Rect p3(0, image.rows / 2, image.cols / 2, image.rows / 2);
	cv::Rect p4(image.cols / 2, image.rows / 2, image.cols / 2, image.rows / 2);

	cv::Mat part1 = image(p1);
	cv::Mat part2 = image(p2);
	cv::Mat part3 = image(p3);
	cv::Mat part4 = image(p4);
	cv::imshow("1", part1);
	cv::imshow("2", part2);
	cv::imshow("3", part3);
	cv::imshow("4", part4);

	//mask
	int radius = std::min(width, height) / 3;
	cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
	std::vector<cv::Point> pts;
	for (int i = 0; i < 6; i++) {
		double angle = 2 * CV_PI / 6 * i;
		int vertexX = width / 2 + radius * cos(angle);
		int vertexY = height / 2 + radius * sin(angle);
		pts.push_back(cv::Point(vertexX, vertexY));
	};
	cv::fillConvexPoly(mask, pts, cv::Scalar(255));
	cv::Mat result;
	image.copyTo(result, mask);
	cv::imshow("Mask Result", result);

	cv::waitKey(0);
	return 0;
}
