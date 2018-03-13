//
// Created by 13342 on 2018/3/12.
//
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void algorithm(){
    Mat img = imread("../1.jpg",CV_LOAD_IMAGE_COLOR);
    Mat dst;
    Laplacian(img,dst,img.depth());
    imshow("dst",dst);
}