#include "armor_detector.h"



ArmorDetector::ArmorDetector()
{

}



// HSV颜色筛选

Mat ArmorDetector::colorThreshold(Mat hsv)
{

    Mat red1,red2,red;


    Mat blue;



    // 红色范围

    inRange(
        hsv,
        Scalar(0,100,100),
        Scalar(10,255,255),
        red1
    );


    inRange(
        hsv,
        Scalar(160,100,100),
        Scalar(180,255,255),
        red2
    );


    red = red1 | red2;



    // 蓝色范围

    inRange(
        hsv,
        Scalar(90,80,80),
        Scalar(130,255,255),
        blue
    );



    // 红蓝合并

    Mat result;


    result = red | blue;



    return result;

}





vector<RotatedRect> ArmorDetector::findLights(Mat binary)
{


    vector<vector<Point>> contours;


    findContours(
        binary,
        contours,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE
    );



    vector<RotatedRect> lights;



    for(auto contour:contours)
    {


        if(contour.size()<5)
            continue;



        RotatedRect rect=minAreaRect(contour);



        float width=rect.size.width;

        float height=rect.size.height;



        if(width>height)
        {
            swap(width,height);
        }



        float ratio=height/width;



        // 灯条特征

        if(
            ratio>2.0 &&
            ratio<20 &&
            height>8
        )
        {

            lights.push_back(rect);

        }


    }


    return lights;

}






void ArmorDetector::matchArmor(
    vector<RotatedRect>& lights,
    Mat& img
)
{


    for(size_t i=0;i<lights.size();i++)
    {


        for(size_t j=i+1;j<lights.size();j++)
        {


            RotatedRect left=lights[i];

            RotatedRect right=lights[j];



            Point2f p1=left.center;

            Point2f p2=right.center;



            float distance=
            abs(p1.x-p2.x);



            float heightDiff=
            abs(
                left.size.height-
                right.size.height
            );



            // 两灯条匹配条件

            if(
                distance>20 &&
                distance<300 &&
                heightDiff<30
            )
            {



                Point2f center(
                    (p1.x+p2.x)/2,
                    (p1.y+p2.y)/2
                );



                float w=distance;

                float h=
                max(
                    left.size.height,
                    right.size.height
                );



                Rect armor(
                    center.x-w/2,
                    center.y-h/2,
                    w,
                    h
                );



                rectangle(
                    img,
                    armor,
                    Scalar(0,255,0),
                    2
                );



                putText(
                    img,
                    "Armor",
                    center,
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Scalar(0,255,0),
                    2
                );

            }


        }

    }


}





void ArmorDetector::detect(Mat& img)
{


    Mat hsv;


    cvtColor(
        img,
        hsv,
        COLOR_BGR2HSV
    );



    //颜色提取

    Mat mask=
    colorThreshold(hsv);



    //去噪

    Mat kernel=
    getStructuringElement(
        MORPH_RECT,
        Size(3,3)
    );



    morphologyEx(
        mask,
        mask,
        MORPH_CLOSE,
        kernel
    );



    vector<RotatedRect> lights =
    findLights(mask);



    matchArmor(
        lights,
        img
    );



    imshow(
        "binary",
        mask
    );

}
