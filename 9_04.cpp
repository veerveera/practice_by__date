#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <vector>
#include <mpi.h>
#include <stdlib.h> 
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap("C:/Users/veras/Desktop/9.04/ZUA.mp4");

    if (!cap.isOpened())
    {
        cout << "Error opening" << endl;
        return -1;
    }

    //Mat frame = cv::imread("C:/Users/veras/Desktop/image.png", IMREAD_COLOR);
    //resize(frame, frame, cv::Size(700,500));
    //if (!frame.data) {
    //    std::cout << "Could not open" << std::endl;
    //    exit(EXIT_FAILURE);
    //}
    //imshow("Original", frame);

    cv::CascadeClassifier face_cascade_eye;
    //if (!face_cascade_eye.load(samples::findFile("haarcascade_eye.xml")));
    if (!face_cascade_eye.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_eye.xml"));
    cout << "Error" << endl;

    cv::CascadeClassifier face_cascade_smile;
    //if (!face_cascade_smile.load(samples::findFile("haarcascade_smile.xml")));
    if (!face_cascade_smile.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_smile.xml"));
    cout << "Error" << endl;


    cv::CascadeClassifier face_cascade_face;
    //if (!face_cascade_face.load(samples::findFile("haarcascade_frontalface_default.xml")));
    if (!face_cascade_face.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_frontalface_default.xml"));
    cout << "Error" << endl;

    while (true) {

        Mat frame;
        cap >> frame;
        if (frame.empty()) break;
        resize(frame, frame, Size(700, 500));
        Mat countour_frame = frame.clone();
        if (countour_frame.empty()) break;


        Mat gray, gauss;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gauss, Size(3, 3), 0);

        vector<Rect> eyes;
        face_cascade_eye.detectMultiScale(gray, eyes, 1.17, 12);

        for (const auto& eye : eyes)
        {
            rectangle(frame, eye, Scalar(255, 0, 0), 2);
        }

        vector<Rect> smiles;
        face_cascade_smile.detectMultiScale(gray, smiles, 1.1, 40, 0, cv::Size(30, 30));

        for (const auto& smile : smiles)
        {
            rectangle(frame, smile, Scalar(0, 255, 0), 2);
        }

        vector<Rect> faces;
        face_cascade_face.detectMultiScale(gray, faces, 1.1, 5);

        for (const auto& face : faces)
        {
            rectangle(frame, face, Scalar(0, 0, 255), 2);
        }
        imshow("Face", frame);
        char c = (char)cv::waitKey(30);
        if (c == 27) break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
