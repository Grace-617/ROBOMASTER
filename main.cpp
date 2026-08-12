#include <opencv2/opencv.hpp>
#include "armor_detector.h"

using namespace cv;
using namespace std;


int main()
{

    // 读取测试图片
    Mat img = imread("../test.jpg");


    if(img.empty())
    {
        cout << "图片读取失败!" << endl;
        return -1;
    }


    ArmorDetector detector;


    // 检测装甲板
    detector.detect(img);



    // 显示结果

    imshow("Armor Detection Result", img);


    waitKey(0);


    return 0;

}
