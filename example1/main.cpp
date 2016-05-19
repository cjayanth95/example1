//
//  main.cpp
//  example1
//
//  Created by labuser on 16/05/16.
//  Copyright © 2016 labuser. All rights reserved.
//

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
std::vector<std::vector<cv::Rect>> detectLetters(cv::Mat img, int x , int y , int s)
{
    std::vector<std::vector<cv::Rect>> finalrect;
    std::vector<cv::Rect> boundRect1;
    std::vector<cv::Rect> boundRect2;
    std::vector<cv::Rect> boundRect3;
    std::vector<cv::Rect> boundRect4;
    cv::Mat img_gray,img_gray1, img_sobel,img_sobel1, img_threshold, element , element2,img_threshold1;
    cvtColor(img, img_gray, CV_BGR2GRAY);//converts given image to greyimage format
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);//detects the edges of the grey image
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);//high contrast version
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(x ,y) );//create a rectangle block with kernel of size mentioned
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element );//Does the trick. Gives a binary image
    std::vector< std::vector< cv::Point> > contours;//create a vector of contours specified by vector of points
    cv::findContours(img_threshold, contours, 0, 1);//fill the contours vector with contours. 0, 1 denote the mode and method
    std::vector<std::vector<cv::Point> > contours_poly(contours.size() );
    for( int i = 0; i < contours.size(); i++ ){
        if (contours[i].size()>s)
        {
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i],3, true );//approximates the contours with preicision = 3
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect1.push_back(appRect);
        }
    }
    int sr = boundRect1.size();
    int A[sr];
    for (int h =0; h<sr; h++) {
        A[h] = 0;
    }
    
    cvtColor(img, img_gray1, CV_BGR2GRAY);//converts given image to greyimage format
    cv::Sobel(img_gray1, img_sobel1, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);//detects the edges of the grey image
    cv::threshold(img_sobel1, img_threshold1, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);//high contrast version
    element2 = getStructuringElement(cv::MORPH_RECT, cv::Size(17 ,3) );//create a rectangle block with kernel of size mentioned
    cv::morphologyEx(img_threshold1, img_threshold1, CV_MOP_CLOSE, element2 );//Does the trick. Gives a binary image
    std::vector< std::vector< cv::Point> > contours2;//create a vector of contours specified by vector of points
    cv::findContours(img_threshold1, contours2, 0, 1);//fill the contours vector with contours. 0, 1 denote the mode and method
    std::vector<std::vector<cv::Point> > contours_poly2(contours2.size() );
    for( int i = 0; i < contours2.size(); i++ ){
        if (contours2[i].size()>100)
        {
            cv::approxPolyDP( cv::Mat(contours2[i]), contours_poly2[i],3, true );//approximates the contours with preicision = 3
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly2[i]) ));
            if (appRect.width>appRect.height)
                boundRect2.push_back(appRect);
        }
    }
    for (int u =0; u<boundRect1.size(); u++) {
        for (int y =0; y<boundRect2.size(); y++) {
            if ((boundRect2[y].br().x   <= boundRect1[u].br().x) && (boundRect2[y].br().y   <= boundRect1[u].br().y) && (boundRect2[y].tl().x   >= boundRect1[u].tl().x) && (boundRect2[y].tl().y   >= boundRect1[u].tl().y)) {
                A[u] = A[u] + boundRect2[y].area();
            }
        }
    }
    for (int v =0; v<boundRect1.size(); v++) {
        if ((double) A[v]/boundRect1[v].area() > 0.1) {
            boundRect3.push_back(boundRect1[v]);
        }
        else{
            boundRect4.push_back(boundRect1[v]);
        }
    }
        finalrect.push_back(boundRect3);
        finalrect.push_back(boundRect4);

    for (int h =0; h<sr; h++) {
        cout<<A[h]<<" "<<boundRect1[h].area()<<endl;
    }
    

    
    return finalrect;
}

void Draw(Mat img2){
    std::vector<std::vector<cv::Rect>> finalrect1 =detectLetters(img2 ,350 ,50 ,500);
     std::vector<cv::Rect> letterBBoxes11;
     std::vector<cv::Rect> letterBBoxes12;
    if (finalrect1[0].size() == 0) {
        cout<<"No text fields to display"<<endl;
    }
    else{
        letterBBoxes11=finalrect1[0];
        for(int i=0; i< letterBBoxes11.size(); i++)
            cv::rectangle(img2,letterBBoxes11[i],cv::Scalar(0,255,0),3,8,0);
    }
    if (finalrect1[1].size() == 0) {
        cout<<"No image fields to display"<<endl;
    }
    else{
        letterBBoxes12=finalrect1[1];
        for(int i=0; i< letterBBoxes12.size(); i++)
            cv::rectangle(img2,letterBBoxes12[i],cv::Scalar(255,0,0),3,8,0);
    }
    cv::imwrite( "imgOut24.jpg", img2);
}

int main(int argc,char** argv)
{
    
    cv::Mat img2=cv::imread("2.jpg");
    cv::Mat img3=cv::imread("3.jpg");
    cv::Mat img4=cv::imread("4.jpg");
//    cv::Mat img5=cv::imread("5.jpg");
//    cv::Mat img6=cv::imread("6.jpg");
    cv::Mat img7=cv::imread("7.jpg");
    cv::Mat img8=cv::imread("8.jpg");
    cv::Mat img9=cv::imread("9.jpg");
    cv::Mat img10=cv::imread("10.jpg");
    cv::Mat img11=cv::imread("11.jpg");
    cv::Mat img12=cv::imread("12.jpg");
    cv::Mat img13=cv::imread("13.jpg");
    cv::Mat img14=cv::imread("14.jpg");
    cv::Mat img15=cv::imread("15.jpg");
    cv::Mat img16=cv::imread("16.jpg");
    cv::Mat img17=cv::imread("17.jpg");
    cv::Mat img18=cv::imread("18.jpg");
    cv::Mat img19=cv::imread("19.jpg");
    cv::Mat img20=cv::imread("20.jpg");
    cv::Mat img21=cv::imread("21.jpg");
    cv::Mat img22=cv::imread("22.jpg");
    cv::Mat img23=cv::imread("23.jpg");
    cv::Mat img24=cv::imread("24.jpg");
    Draw(img24);
    return 0;
}


















//resize(img_sobel, img_sobel, Size(img_sobel.cols/2, img_sobel.rows/2));
//    namedWindow( "Contours", WINDOW_AUTOSIZE );
//    imshow( "Contours", img_sobel );
//    waitKey(10000000);
//    cv::imwrite( "imgOut2.jpg", img2);
//    cv::imwrite( "imgOut3.jpg", img3);
//    cv::imwrite( "imgOut4.jpg", img4);
//    for(int i=0; i< letterBBoxes21.size(); i++)
//        cv::rectangle(img2,letterBBoxes21[i],cv::Scalar(0,255,0),3,8,0);
//    for(int i=0; i< letterBBoxes22.size(); i++)
//        cv::rectangle(img2,letterBBoxes22[i],cv::Scalar(255,0,0),3,8,0);
//    cv::imwrite( "imgOut2.jpg", img2);
//    for(int i=0; i< letterBBoxes31.size(); i++)
//        cv::rectangle(img3,letterBBoxes31[i],cv::Scalar(0,255,0),3,8,0);
//    for(int i=0; i< letterBBoxes32.size(); i++)
//        cv::rectangle(img3,letterBBoxes32[i],cv::Scalar(0,255,0),3,8,0);
//    cv::imwrite( "imgOut3.jpg", img3);
//    for(int i=0; i< letterBBoxes41.size(); i++)
//        cv::rectangle(img4,letterBBoxes41[i],cv::Scalar(0,255,0),3,8,0);
//    for(int i=0; i< letterBBoxes42.size(); i++)
//        cv::rectangle(img4,letterBBoxes42[i],cv::Scalar(255,0,0),3,8,0);
//    cv::imwrite( "imgOut4.jpg", img4);
//    if (detectLetters(img2,350 ,50 ,500)[0].size() == 0) {
//        cout<<"No text fields to display"<<endl;
//    }
//    else{
//        letterBBoxes21=detectLetters(img2,350 ,50 ,500)[0];
//        for(int i=0; i< letterBBoxes21.size(); i++)
//            cv::rectangle(img2,letterBBoxes21[i],cv::Scalar(0,255,0),3,8,0);
//    }
//    if (detectLetters(img2,350 ,50 ,500)[1].size() == 0) {
//        cout<<"No image fields to display"<<endl;
//    }
//    else{
//        letterBBoxes22=detectLetters(img2,350 ,50 ,500)[1];
//        for(int i=0; i< letterBBoxes22.size(); i++)
//            cv::rectangle(img2,letterBBoxes22[i],cv::Scalar(255,0,0),3,8,0);
//    }
//    if (detectLetters(img3,350 ,50 ,500)[0].size() == 0) {
//        cout<<"No text fields to display"<<endl;
//    }
//    else{
//        letterBBoxes31=detectLetters(img3,350 ,50 ,500)[0];
//        for(int i=0; i< letterBBoxes31.size(); i++)
//            cv::rectangle(img3,letterBBoxes31[i],cv::Scalar(0,255,0),3,8,0);
//    }
//    if (detectLetters(img3,350 ,50 ,500)[1].size() == 0) {
//        cout<<"No image fields to display"<<endl;
//    }
//    else{
//        letterBBoxes32=detectLetters(img3,350 ,50 ,500)[1];
//        for(int i=0; i< letterBBoxes32.size(); i++)
//            cv::rectangle(img3,letterBBoxes32[i],cv::Scalar(255,0,0),3,8,0);
//    }
//    if (detectLetters(img4,350 ,50 ,500)[0].size() == 0) {
//        cout<<"No text fields to display"<<endl;
//    }
//    else{
//        letterBBoxes41=detectLetters(img4,350 ,50 ,500)[0];
//        for(int i=0; i< letterBBoxes41.size(); i++)
//            cv::rectangle(img4,letterBBoxes41[i],cv::Scalar(0,255,0),3,8,0);
//    }
//    if (detectLetters(img4,350 ,50 ,500)[1].size() == 0) {
//        cout<<"No image fields to display"<<endl;
//    }
//    else{
//        letterBBoxes42=detectLetters(img4,350 ,50 ,500)[1];
//        for(int i=0; i< letterBBoxes42.size(); i++)
//            cv::rectangle(img4,letterBBoxes42[i],cv::Scalar(255,0,0),3,8,0);
//    }
//
//    std::vector<cv::Rect> letterBBoxes21=detectLetters(img2)[1];
//    //std::vector<cv::Rect> letterBBoxes22=detectLetters(img2)[2];
//    std::vector<cv::Rect> letterBBoxes31=detectLetters(img3)[1];
//    std::vector<cv::Rect> letterBBoxes32=detectLetters(img3)[2];
//    std::vector<cv::Rect> letterBBoxes41=detectLetters(img4)[1];
//    std::vector<cv::Rect> letterBBoxes42=detectLetters(img4)[2];


//Display

//    for(int i=0; i< letterBBoxes12.size(); i++)
//        cv::rectangle(img1,letterBBoxes12[i],cv::Scalar(255,0,0),3,8,0);

//    std::vector<cv::Rect> letterBBoxes22;
//    std::vector<cv::Rect> letterBBoxes32;
//    std::vector<cv::Rect> letterBBoxes42;
//    std::vector<cv::Rect> letterBBoxes21;
//    std::vector<cv::Rect> letterBBoxes31;
//    std::vector<cv::Rect> letterBBoxes41;
//    std::vector<std::vector<cv::Rect>> finalrect1 =detectLetters(img2 ,350 ,50 ,500);
//    if (finalrect1[0].size() == 0) {
//        cout<<"No text fields to display"<<endl;
//    }
//    else{
//        letterBBoxes11=finalrect1[0];
//        for(int i=0; i< letterBBoxes11.size(); i++)
//            cv::rectangle(img2,letterBBoxes11[i],cv::Scalar(0,255,0),3,8,0);
//    }
//    if (finalrect1[1].size() == 0) {
//        cout<<"No image fields to display"<<endl;
//    }
//    else{
//        letterBBoxes12=finalrect1[1];
//        for(int i=0; i< letterBBoxes12.size(); i++)
//            cv::rectangle(img2,letterBBoxes12[i],cv::Scalar(255,0,0),3,8,0);
//    }
//
//    cv::imwrite( "imgOut2.jpg", img2);































//cout<<boundRect1.size()<<endl;
//            namedWindow( "Contours", WINDOW_AUTOSIZE );
//            imshow( "Contours", img(boundRect1[2]) );
//            waitKey(10000000);
//cv::threshold(img_sobel, img_threshold1, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);//high contrast version
//    element2 = getStructuringElement(cv::MORPH_RECT, cv::Size(21,3) );
//    for (int j=0; j<boundRect1.size(); j++) {
//        cvtColor(img(boundRect1[j]), img_gray1, CV_BGR2GRAY);
//        cv::Sobel(img_gray1, img_sobel1, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);//detects the edges of the grey image
//        cv::threshold(img_sobel1, img_threshold1, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);//high contrast version
//        cv::morphologyEx(img_threshold1, img_threshold1, CV_MOP_CLOSE, element2 );
//
//        std::vector< std::vector< cv::Point> > contours2;//create a vector of contours specified by vector of points
//        cv::findContours(img_threshold1, contours2, 0, 1);//fill the contours vector with contours. 0, 1 denote the mode and method
//        int area = 0;
//        std::vector<std::vector<cv::Point> > contours_poly2(contours2.size() );
//        for (int k = 0; k<contours2.size(); k++) {
//            if(contours2[k].size()>300){
//                cv::approxPolyDP( cv::Mat(contours2[k]), contours_poly2[k],3, true );//approximates the contours with preicision = 3
//                cv::Rect appRect( boundingRect( cv::Mat(contours_poly2[k]) ));
//                if (appRect.width>appRect.height){
//                    area = area+appRect.area();
//                }
//            }
//        }
//        //cout<<"area:"<<area<<endl;
//        //cout<<"area2:"<<boundRect1[j].area()<<endl;
//        int area2 =boundRect1[j].area();
//        cout<<"ratio:"<<j<<" "<<(double)area /area2<<endl;
//        if ((double)area /area2  > 0.5) {
//            boundRect2.push_back( boundRect1[j]);
//
//        }
//        else{
//            boundRect3.push_back( boundRect1[j]);
//        }
//
//    }
//    cout<<boundRect2.size()<<endl;
//    cout<<boundRect3.size()<<endl;
//    finalrect.push_back(boundRect2);
//    finalrect.push_back(boundRect3);




