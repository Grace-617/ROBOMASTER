#ifndef ARMOR_DETECTOR_H
#define ARMOR_DETECTOR_H


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



class ArmorDetector
{

public:


    ArmorDetector();


    void detect(Mat& img);



private:


    // HSV颜色分割
    Mat colorThreshold(Mat hsv);



    // 灯条筛选

    vector<RotatedRect> findLights(Mat binary);



    // 灯条匹配装甲板

    void matchArmor(
        vector<RotatedRect>& lights,
        Mat& img
    );


};


#endif
