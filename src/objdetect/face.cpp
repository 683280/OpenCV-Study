//
// Created by 13342 on 2018/3/11.
//

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** �������� */
void detectAndDisplay( Mat frame );

/** ȫ�ֱ��� */
string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);

/** @������ */
int face()
{
//    CvCapture* capture;
    Mat frame;
    IplImage* img;
    //-- 1. ���ؼ����������ļ�
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

    //-- 2. ����������ͷ��Ƶ��

//    capture = cvCreateCameraCapture(0);
    VideoCapture capture(0);
    if (!capture.isOpened()){
        printf("open capture error");
        return -1;
    }
    if(true)
    {
        while( true )
        {
            capture >> frame;
//            img = cvQueryFrame(capture);
//            frame = cvarrToMat(img, true);

            //-- 3. �Ե�ǰ֡ʹ�÷��������м��
            if( !frame.empty() ) {
//                imshow( window_name, frame );
                detectAndDisplay( frame );
            }
            else
            { printf(" --(!) No captured frame -- Break!"); break; }

            int c = waitKey(30);
            if( (char)c == 'c' ) { break; }
        }
    }
    return 0;
}

/** @���� detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- ��ߴ�������
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- ��ÿ�������ϼ��˫��
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( int j = 0; j < eyes.size(); j++ )
        {
            Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
            int radius = cvRound( (eyes[j].width + eyes[i].height)*0.25 );
            circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- ��ʾ���ͼ��
    imshow( window_name, frame );
}