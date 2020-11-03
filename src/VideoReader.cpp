#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//使用方法
/*
Put street.avi in your project.
Set the link with opencv.
*/

int videoReader(int framenum,char saveimg_path[],bool total) {

    int count=1;
    int max=0;
    int framecount=0;
    unsigned int pixel[540*960]={0};
    unsigned char *pixel_new=new unsigned char[540*960]();
    VideoCapture cap("../data/street.avi");
 
    if (!cap.isOpened()) {
        cout << "Error opening video" << endl;
        return -1;
    }
    Mat bkgnd(540,960,CV_8UC1);
    bkgnd.zeros(540,960,CV_8UC1);
    framecount=cap.get(cv::CAP_PROP_FRAME_COUNT);
    if(total==true)
    {
        framenum=framecount;
    }
    while (1) {
        Mat frame;

        //下方程式碼會依序獲得每一帧
        //請根據上課所學修改此段
        cap >> frame;
        
        //若影片結束跳出迴圈
        if (frame.empty()||count>framenum)
            break;    
        cvtColor(frame,frame,COLOR_BGR2GRAY);

        for(int i=0;i<frame.rows;i++)
        {
            for (int j = 0; j < frame.cols; j++)
            {
               pixel[i*960+j]=pixel[i*960+j]+frame.at<uchar>(i,j);
            //    printf("pixel=%d\n",pixel[i]);
            }
        }

        count=count+1;

        // char c = (char)waitKey(25);
        // if (c == 27)
        //     break;
    }
    for(int i=0;i<540*960;i++)
    {
        
        pixel[i]=pixel[i]/framenum;
        pixel_new[i]=pixel[i];
        //    printf("pixel=%d\n",pixel[i]);
        
    }
    memcpy(bkgnd.data,pixel_new,540*960);
    imshow("bkgnd", bkgnd);
    imwrite(saveimg_path,bkgnd);
    waitKey(0);
    cap.release();
    destroyAllWindows();

    return 0;
}