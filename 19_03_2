#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

int main() {
    cv::Mat image = cv::imread("C:/Users/veras/Desktop/art.jpeg");
    if (image.empty()) {
        cout << "Error image" << endl;
        return -1;
    }

    cv::Mat blurredImage;
    GaussianBlur(image, blurredImage, cv::Size(5, 5), 0);

    cv::Mat grayImage;
    cvtColor(blurredImage, grayImage, cv::COLOR_BGR2GRAY);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;

    cv::Mat canny_output;
    Canny(grayImage, canny_output, 50, 150);
    findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat text = cv::Mat::zeros(canny_output.size(), CV_8UC3);
    cv::Scalar color = cv::Scalar(0, 255, 0);
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(text, contours, static_cast<int>(i), color, 1, cv::LINE_8, hierarchy, 0);
    }

    imshow("Original", image);
    imshow("Text", text);

    cv::waitKey(0);
    return 0;
}
