//
// Created by 13342 on 2018/3/11.
//
#include <istream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int core1_a(){
    Mat img = imread("../1.jpg",CV_LOAD_IMAGE_COLOR);
    if (img.empty()){
        cout << "no data for img" << endl;
        return -1;
    }
    namedWindow("1.jpg",CV_WINDOW_AUTOSIZE);
    imshow("1.jpg",img);
}