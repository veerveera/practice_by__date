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

int main()
{
    auto start = std::chrono::steady_clock::now();

    VideoCapture cap("C:/Users/veras/Desktop/ZUA.mp4");

    if (!cap.isOpened())
    {
        cout << "Error opening" << endl;
        return -1;
    }

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(cv::CAP_PROP_FPS);
    VideoWriter video("C:/Users/veras/Desktop/9.04/output.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), fps, Size(frame_width, frame_height));

    CascadeClassifier face_cascade_eye;
    if (!face_cascade_eye.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_eye.xml")) {
        cout << "File Error" << endl;
        return -1;
    }

    CascadeClassifier face_cascade_smile;
    if (!face_cascade_smile.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_smile.xml")) {
        cout << "File Error" << endl;
        return -1;
    }


    CascadeClassifier face_cascade_face;
    if (!face_cascade_face.load("C:/Users/veras/Desktop/9.04/data/haarcascades/haarcascade_frontalface_default.xml")) {
        cout << "File Error" << endl;
        return -1;
    }

    Mat frame, gray, gauss;

    while (true) {

        cap >> frame;
        if (frame.empty()) break;
        resize(frame, frame, cv::Size(), 0.75, 0.75); // Лучше задавать ресайз через дроби, а не через прямой доступ к пикселям
        Mat original_frame = frame.clone();
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        //GaussianBlur(gray, gauss, Size(3, 3), 0);

        vector<Rect> eyes, faces, smiles;
        face_cascade_eye.detectMultiScale(gray, eyes, 1.1/*Масштабирование*/, 35 /*Количество соседей в поиске*/, 0, cv::Size(10, 10) /*Минимальный размер объекта (окна отрисовки)*/, /*Максимальный размер объекта (окна отрисовки)*/cv::Size(50, 50));
        face_cascade_smile.detectMultiScale(gray, smiles, 1.5, 28, 0, cv::Size(50, 50), cv::Size(130, 130));
        face_cascade_face.detectMultiScale(gray, faces, 1.1, 9);



        for (const auto& eye : eyes)
        {
            rectangle(frame, eye, Scalar(255, 0, 0), 2);
        }

        for (const auto& smile : smiles)
        {
            rectangle(frame, smile, Scalar(0, 255, 0), 2);
        }

        for (const auto& face : faces)
        {
            rectangle(frame, face, Scalar(0, 0, 255), 2);
        }

        resize(frame, frame, Size(frame_width, frame_height));
        imshow("Face", frame);
        video.write(frame);
        
        char c = (char)cv::waitKey(30);
        if (c == 27) break;
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "time: " << elapsed_seconds.count() << endl;

    cap.release();
    video.release();
    destroyAllWindows();
    return 0;
}
