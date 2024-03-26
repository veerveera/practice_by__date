#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;

int main() {

    cv::VideoCapture cap("C:/Users/veras/Desktop/vid.mp4");

    if (!cap.isOpened())
    {
        cout << "Error opening" << endl;
        return -1;
    }

    while (true) {
        cv::Mat frame, gauss, edges, gray;
        cap >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, gauss, cv::Size(3, 3), 0);
        cv::Canny(gauss, edges, 40, 250);

        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            double epsilon = 0.01 * arcLength(contours[i], true);
            std::vector<cv::Point> approx;
            approxPolyDP(contours[i], approx, epsilon, true);

            cv::Scalar color = cv::Scalar(0, 255, 0);

            drawContours(frame, contours, (int)i, color, 1, cv::LINE_8, hierarchy, 0);

            cv::Moments M = moments(approx);
            cv::Point center(M.m10 / M.m00, M.m01 / M.m00);

            if (approx.size() == 4) {
                putText(frame, "Rectangle", center, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
            }

        }
        imshow("result", frame);
        char c = (char)cv::waitKey(30);
        if (c == 27) break;

    };

        //for (size_t i = 0; i < contours.size(); i++)
        //{
        //    double area = contourArea(contours[i]);
        //    if (area > 10)
        //    {
        //        cv::Rect rect = boundingRect(contours[i]);
        //        rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        //    }
        //}

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
