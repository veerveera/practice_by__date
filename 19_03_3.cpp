#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(){
    Mat image = cv::imread("C:/Users/veras/Desktop/figure.png");
    if (!image.data)
    {
        cout << "Error image" << endl;
        return -1;
    }

    imshow("Original", image);

    Mat emae;
    GaussianBlur(image, emae, Size(3, 3), 0);
    Mat edges;
    Canny(emae, edges, 50, 200);
    
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    vector<Point2f> mc(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    }
    vector<vector<Point>> contourPoly(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
    {
        int c_area = contourArea(contours[i]);
        float peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);
        drawContours(image, contours, (int)i, Scalar(0, 255, 0), 1, LINE_8, hierarchy, 0);

        int obj_corners = (int)contourPoly[i].size();
        string obj_name;

        if (obj_corners == 3)
            obj_name = "Triangle";
        else if (obj_corners == 4){
            obj_name = "Rectangle";
        }
        else if (obj_corners > 6)
            obj_name = "Circle";

        putText(image, obj_name,mc[i],FONT_HERSHEY_PLAIN,1, Scalar(255, 255, 255), 2);
    }
    imshow("Canny", edges);
    imshow("Text on image", image);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
