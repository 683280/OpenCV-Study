//
// Created by 13342 on 2018/3/11.
//
#include <istream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table);
int scan_img_a(){
    int timer = 1000;
    Mat img = imread("../1.jpg",CV_LOAD_IMAGE_COLOR);
    int divideWith = 50;
    uchar table[256];

    for (int i = 0; i < 256; ++i) {
        table[i] = divideWith * (i / divideWith);
    }
    double t = (double)getTickCount();
//    for (int j = 0; j < timer; ++j) {
        ScanImageAndReduceC(img,table);
//    }
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "the time is " << t << endl;
    return 0;
}
Mat& LUT(Mat&I , const uchar*const table){
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];
}
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));

    int channels = I.channels();

    int nRows = I.rows * channels;
    int nCols = I.cols;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            int offset = p[j];
            p[j] = table[offset];
        }
    }
    return I;
}