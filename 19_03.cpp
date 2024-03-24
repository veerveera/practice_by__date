#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

int main() {
	cv::Mat image = cv::imread("C:/Users/veras/Desktop/booksiki.jpg");
	if (image.empty()) {
		std::cout << "Error image" << std::endl;
		return -1;
	}
    imshow("Original image", image);

    cv::Mat new_image;
    cv::Mat edges;
    cv::Mat res;
    
    GaussianBlur(image, new_image, cv::Size(0, 0), 2);
    cv::cvtColor(new_image, new_image, cv::COLOR_BGR2GRAY);
    imshow("Convert", new_image);
    
    Canny(new_image, edges, 0, 100);
    imshow("Edges", edges);
    // выделение контуров
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::drawContours(image, contours, (int)i, cv::Scalar(0, 255, 0), 1, cv::LINE_8, hierarchy, 0);
    }
    imshow("Contours 1", image);
    cv::waitKey(0);
    return 0;
}
