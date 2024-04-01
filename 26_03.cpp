#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {

	VideoCapture cap("C:/Users/veras/Desktop/vid.mp4");

	if (!cap.isOpened())
	{
		cout << "Error opening" << endl;
		return -1;
	}

	vector <Point> center_yoy;
	vector <Mat> emae; 

	while (true) {
		Mat frame, gauss, edges, gray, dorian, emae_gauss, emae_edges;
		cap >> frame;

		cv::Mat emae_frame = frame.clone();

		if (frame.empty()) break;

		if (emae.size() > 5) {
			emae.erase(emae.begin());
		}

		emae.push_back(frame);

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, gauss, Size(3, 3), 0); 
		Canny(gauss, edges, 100, 200); //

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < emae.size(); i++) {

			cvtColor(emae[i], dorian, COLOR_BGR2GRAY);
			GaussianBlur(dorian, emae_gauss, Size(3, 3), 0);
			Canny(emae_gauss, emae_edges, 80, 200); 

			vector<vector<Point> > emae_contours;
			vector<Vec4i> emae_hierarchy;
			findContours(emae_edges, emae_contours, emae_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

			for (size_t j = 0; j < emae_contours.size(); j++) {
				
				drawContours(emae_frame, emae_contours, (int)j, Scalar(0, 255, 0), 1, LINE_8, hierarchy, 0);

			}

		}

		for (size_t i = 0; i < contours.size(); i++) {
			double epsilon = 0.004 * arcLength(contours[i], true); //
			vector<Point> approx;
			approxPolyDP(contours[i], approx, epsilon, true);

			Scalar color = Scalar(0, 255, 0);

			drawContours(emae_frame, contours, (int)i, color, 1, LINE_8, hierarchy, 0);

			Moments M = moments(approx);
			Point center(M.m10 / M.m00, M.m01 / M.m00);
			

			if (center_yoy.size() > 15) {
				center_yoy.erase(center_yoy.begin());
			}

			for (int j = 0; j < center_yoy.size(); j++) {
				circle(emae_frame, center_yoy[j], 3, color, -1);
			}
			if (approx.size() == 4) {
				center_yoy.push_back(center);
				putText(emae_frame, "Rectangle", center, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
			}

		}
		imshow("result", emae_frame);
		char c = (char)cv::waitKey(30);
		if (c == 27) break;

	};

	//for (size_t i = 0; i < contours.size(); i++)
	//{
	// double area = contourArea(contours[i]);
	// if (area > 10)
	// {
	// cv::Rect rect = boundingRect(contours[i]);
	// rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
	// }
	//}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}
