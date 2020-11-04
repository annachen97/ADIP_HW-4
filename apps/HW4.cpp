#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/img_process.hpp"
#include "../include/VideoReader.hpp"
using namespace cv;

void hw1_a()
{
    int height = 512;
    int width = 512;
    int size = height * width;

    char house512_path[] = "../data/house512.raw";
    char lena512_path[] = "../data/lena512.raw";
    char house_new_path[] = "../data/1.a_house.png";
    char house_his_path[] = "../data/1.a_house_his.png";
    char lena_his_path[] = "../data/1.a_lena_his.png";
    char house_his_new_path[] = "../data/1.a_house_his_new.png";

    FILE *hs_512, *lena_512;

    unsigned char *hs_pixel = new unsigned char[size]();
    unsigned char *lena_pixel = new unsigned char[size]();
    unsigned char *hs_new_pixel = new unsigned char[size]();
    unsigned int *hs_gryl_statistics = new unsigned int[256](); //統計每個pixel的灰階，用unsigned char會溢位
    unsigned int *lena_gryl_statistics = new unsigned int[256]();
    unsigned int *hs_gryl_statistics_new = new unsigned int[256]();
    unsigned char *mapping = new unsigned char[256]();

    Mat house_512, new_house_512, lenamat_512, house_512_his, lenamat_512_his, new_house_512_his;
    char hs_windowname[] = "1.a_hs512";
    char lena_windowname[] = "1.a_lena512";
    char hs_new_windowname[] = "1.a_hs512_new";
    char hs_his_windowname[] = "1.a_hs_his";
    char lena_his_windowname[] = "1.a_lena_his";
    char hs_his_new_windowname[] = "1.a_hs_his_new";

    hs_pixel = readImage(house512_path, size, hs_512, hs_pixel);
    lena_pixel = readImage(lena512_path, size, lena_512, lena_pixel);

    house_512.create(height, width, CV_8UC1);
    new_house_512.create(height, width, CV_8UC1);
    lenamat_512.create(height, width, CV_8UC1);
    house_512_his.create(height / 2, width / 2, CV_8UC1);
    lenamat_512_his.create(height / 2, width / 2, CV_8UC1);
    new_house_512_his.create(height / 2, width / 2, CV_8UC1);

    memcpy(house_512.data, hs_pixel, size);
    memcpy(lenamat_512.data, lena_pixel, size);

    hs_gryl_statistics = histogram(hs_gryl_statistics, hs_pixel, size);
    lena_gryl_statistics = histogram(lena_gryl_statistics, lena_pixel, size);
    // int count=0;
    int max = 0;
    // for(int i=0;i<256;i++)
    // {
    //     count=count+lena_gryl_statistics[i];
    // }
    // std::cout<<count<<std::endl;

    max = findMax(hs_gryl_statistics);
    std::cout << "max=" << max << std::endl;
    max = max / 255 + 1;
    house_512_his = drawHistogram(hs_gryl_statistics, house_512_his, max);

    max = findMax(lena_gryl_statistics);
    std::cout << "max=" << max << std::endl;
    max = max / 255 + 1;
    lenamat_512_his = drawHistogram(lena_gryl_statistics, lenamat_512_his, max);

    mapping = histogramMatching(hs_gryl_statistics, lena_gryl_statistics);

    hs_new_pixel = match(mapping, hs_pixel, hs_new_pixel, size);
    memcpy(new_house_512.data, hs_new_pixel, size);

    hs_gryl_statistics_new = histogram(hs_gryl_statistics_new, hs_new_pixel, size);
    max = findMax(hs_gryl_statistics_new);
    std::cout << "max=" << max << std::endl;
    max = max / 255 + 1;
    new_house_512_his = drawHistogram(hs_gryl_statistics_new, new_house_512_his, max);

    imwrite(house_new_path, new_house_512);
    imwrite(house_his_path, house_512_his);
    imwrite(lena_his_path, lenamat_512_his);
    // imwrite(house_his_new_path,new_house_512_his);
    // showImage(hs_windowname,house_512);
    // showImage(lena_windowname,lenamat_512);
    // showImage(hs_new_windowname,new_house_512);
    // showImage(hs_his_windowname,house_512_his);
    // showImage(lena_his_windowname,lenamat_512_his);
    // showImage(hs_his_new_windowname,new_house_512_his);
    // closeImage(hs_windowname);
}

void hw1_b()
{
    int height = 512;
    int width = 512;
    int size = height * width;
    int masklength=3;   //masksize=3*3 padlength=1 masklength=3 //must be odd
    char house512_path[] = "../data/house512.raw";
    char hs_le3_path[] = "../data/hw1.b_hs_le3.png";
    char hs_le5_path[] = "../data/hw1.b_hs_le5.png";
    char hs_le9_path[] = "../data/hw1.b_hs_le9.png";
    char hs_windowname[] = "1.b_hs512";
    char hs_pad_windowname[] = "1.b_hs512_pad";
    char hs_le3_windowname[] = "1.b_le3";
    char hs_le5_windowname[] = "1.b_le5";
    char hs_le9_windowname[] = "1.b_le9";
    unsigned char *hs_pixel = new unsigned char[size]();
    unsigned char *hs_pad_pixel = new unsigned char[size]();
    unsigned int *gryl_statistics = new unsigned int[256]();
    Mat house_512, house_512_pad, hs_le3, hs_le5, hs_le9;   //local enhencement
    FILE *hs_512;
    

    house_512.create(height, width, CV_8UC1);
    hs_le3.create(height, width, CV_8UC1);
    hs_le5.create(height, width, CV_8UC1);
    hs_le9.create(height, width, CV_8UC1);

    hs_pixel = readImage(house512_path, size, hs_512, hs_pixel);
    memcpy(house_512.data, hs_pixel, size);

    //mask=9*9 padsize=4
    int padsize = (masklength-1)/2;
    int resize = pow((512 + padsize * 2), 2);
    house_512_pad.create(height + padsize * 2, width + padsize * 2, CV_8UC1);
    int mode = 1;
    house_512_pad = padding(house_512, house_512_pad, padsize, resize, mode);
    // hs_pad_pixel = storeMat2Pixel(house_512_pad, hs_pad_pixel, resize);
    // gryl_statistics = histogram(gryl_statistics, hs_pad_pixel, resize);

    hs_le3=localEnhencement(house_512_pad, height+masklength-1, masklength);

    masklength=5;
    padsize = (masklength-1)/2;
    resize = pow((512 + padsize * 2), 2);
    house_512_pad.create(height + padsize * 2, width + padsize * 2, CV_8UC1);
    house_512_pad = padding(house_512, house_512_pad, padsize, resize, mode);
    hs_le5=localEnhencement(house_512_pad, height+masklength-1, masklength);

    masklength=9;
    padsize = (masklength-1)/2;
    resize = pow((512 + padsize * 2), 2);
    house_512_pad.create(height + padsize * 2, width + padsize * 2, CV_8UC1);
    house_512_pad = padding(house_512, house_512_pad, padsize, resize, mode);
    hs_le9=localEnhencement(house_512_pad, height+masklength-1, masklength);

    imwrite(hs_le3_path,hs_le3);
    imwrite(hs_le5_path,hs_le5);
    imwrite(hs_le9_path,hs_le9);
    showImage(hs_windowname, house_512);
    showImage(hs_pad_windowname, house_512_pad);
    showImage(hs_le3_windowname, hs_le3);
    showImage(hs_le5_windowname, hs_le5);
    showImage(hs_le9_windowname, hs_le9);
    closeImage(hs_windowname);
}

void hw2()
{
    int returnnum = 0;
    int framenum = 10;
    bool total = false;
    char hw2_10frame[] = "../data/hw2_10frame.png";
    returnnum = videoReader(framenum, hw2_10frame, total);
    framenum = 200;
    char hw2_200frame[] = "../data/hw2_200frame.png";
    returnnum = videoReader(framenum, hw2_200frame, total);
    total = true;
    char hw2_allframe[] = "../data/hw2_allframe.png";
    returnnum = videoReader(framenum, hw2_allframe, total);
}

void hw3_a()
{
    int height = 512;
    int width = 512;
    int size = height * width;
    int mode = 0;
    int padsize=1;
    int masklength=padsize*2+1;
    int masksize=pow(masklength,2);
    int resize = pow((height + padsize * 2), 2);
    char walkbridge_path[] = "../data/walkbridge.raw";
    char wk_pad_windowname[] = "3.a_pad";
    char wk_zf1_windowname[] = "3.a_zf1";
    char wk_rf1_windowname[] = "3.a_rf1";
    char wk_zf2_windowname[] = "3.a_zf2";
    char wk_rf2_windowname[] = "3.a_rf2";
    char hw3_walkbridge[] = "../data/hw3_walkbridge.png";
    char hw3_wkbridge_zf1[] = "../data/hw3.a_wkbridge_zf1.png";
    char hw3_wkbridge_rf1[] = "../data/hw3.a_wkbridge_rf1.png";
    char hw3_wkbridge_zf2[] = "../data/hw3.a_wkbridge_zf2.png";
    char hw3_wkbridge_rf2[] = "../data/hw3.a_wkbridge_rf2.png";
    unsigned char *pixel = new unsigned char[size]();
    double* mask = new double[masksize];
    FILE *walkbridge_file;
    Mat walkbridge, walkbridge_pad,walkbridge_zf1, walkbridge_rf1,walkbridge_zf2, walkbridge_rf2;
    
    walkbridge.create(height, width, CV_8UC1);
    walkbridge_pad.create(height + padsize*2, width + padsize*2, CV_8UC1);
    walkbridge_zf1.create(height, width, CV_8UC1);
    walkbridge_rf1.create(height, width, CV_8UC1);
    walkbridge_zf2.create(height, width, CV_8UC1);
    walkbridge_rf2.create(height, width, CV_8UC1);
    pixel = readImage(walkbridge_path, size, walkbridge_file, pixel);
    memcpy(walkbridge.data, pixel, size);
    imwrite(hw3_walkbridge,walkbridge);
    
    //zf1
    // showImage("raw", walkbridge);
    walkbridge_pad = padding(walkbridge, walkbridge_pad, padsize, resize, mode);
    // showImage("pad1", walkbridge_pad);
    mask[0]=0;mask[1]=-1;mask[2]=0;mask[3]=-1;mask[4]=+4;mask[5]=-1;mask[6]=0;mask[7]=-1;mask[8]=0;
    walkbridge_zf1=conv(walkbridge_pad, walkbridge_zf1, mask, height+padsize*2, masklength);
    
    //rf1
    mode=1;
    walkbridge_pad = padding(walkbridge, walkbridge_pad, padsize, resize, mode);
    // showImage("pad2", walkbridge_pad);
    walkbridge_rf1=conv(walkbridge_pad, walkbridge_rf1, mask, height+padsize*2, masklength);

    mask[0]=-1;mask[1]=-1;mask[2]=-1;mask[3]=-1;mask[4]=+8;mask[5]=-1;mask[6]=-1;mask[7]=-1;mask[8]=-1;
    //zf2
    mode=0;
    walkbridge_pad = padding(walkbridge, walkbridge_pad, padsize, resize, mode);
    // showImage("pad2", walkbridge_pad);
    walkbridge_zf2=conv(walkbridge_pad, walkbridge_zf2, mask, height+padsize*2, masklength);


    //rf2
    mode=1;
    walkbridge_pad = padding(walkbridge, walkbridge_pad, padsize, resize, mode);
    // showImage("pad2", walkbridge_pad);
    walkbridge_rf2=conv(walkbridge_pad, walkbridge_rf2, mask, height+padsize*2, masklength);

    imwrite(hw3_wkbridge_zf1,walkbridge_zf1);
    imwrite(hw3_wkbridge_rf1,walkbridge_rf1);
    imwrite(hw3_wkbridge_zf2,walkbridge_zf2);
    imwrite(hw3_wkbridge_rf2,walkbridge_zf2);
    showImage(wk_zf1_windowname, walkbridge_zf1);
    showImage(wk_rf1_windowname, walkbridge_rf1);
    showImage(wk_zf2_windowname, walkbridge_zf2);
    showImage(wk_rf2_windowname, walkbridge_rf2);
    closeImage(wk_zf1_windowname);
}

void hw3_b()
{
    int height = 512;
    int width = 512;
    int size = height * width;
    int mode = 1;
    int padsize=1;
    int masklength=padsize*2+1;
    int masksize=pow(masklength,2);
    int resize = pow((height + padsize * 2), 2);
    int A=1;
    char walkbridge_path[] = "../data/walkbridge.raw";
    char wk_pad_windowname[] = "3.b_pad";
    char wk_r1f1_windowname[] = "3.b_r1f1";
    char wk_r2f1_windowname[] = "3.b_r2f1";
    char wk_r4f1_windowname[] = "3.b_r4f1";
    char wk_r1f2_windowname[] = "3.b_r1f2";
    char wk_r2f2_windowname[] = "3.b_r2f2";
    char wk_r4f2_windowname[] = "3.b_r4f2";
    char hw3_walkbridge[] = "../data/hw3_walkbridge.png";
    char hw3_wkbridge_r1f1[] = "../data/hw3.a_wkbridge_r1f1.png";
    char hw3_wkbridge_r2f1[] = "../data/hw3.a_wkbridge_r2f1.png";
    char hw3_wkbridge_r4f1[] = "../data/hw3.a_wkbridge_r4f1.png";
    char hw3_wkbridge_r1f2[] = "../data/hw3.a_wkbridge_r1f2.png";
    char hw3_wkbridge_r2f2[] = "../data/hw3.a_wkbridge_r2f2.png";
    char hw3_wkbridge_r4f2[] = "../data/hw3.a_wkbridge_r4f2.png";
    unsigned char *pixel = new unsigned char[size]();
    double* mask = new double[masksize];
    double* mask_highboost = new double[masksize];
    FILE *walkbridge_file;
    Mat walkbridge, walkbridge_pad, walkbridge_r1f1, walkbridge_r2f1, walkbridge_r4f1, walkbridge_r1f2, walkbridge_r2f2, walkbridge_r4f2;
    
    walkbridge.create(height, width, CV_8UC1);
    walkbridge_pad.create(height + padsize*2, width + padsize*2, CV_8UC1);
    walkbridge_r1f1.create(height, width, CV_8UC1);
    walkbridge_r2f1.create(height, width, CV_8UC1);
    walkbridge_r4f1.create(height, width, CV_8UC1);
    walkbridge_r1f2.create(height, width, CV_8UC1);
    walkbridge_r2f2.create(height, width, CV_8UC1);
    walkbridge_r4f2.create(height, width, CV_8UC1);
    pixel = readImage(walkbridge_path, size, walkbridge_file, pixel);
    memcpy(walkbridge.data, pixel, size);
    imwrite(hw3_walkbridge,walkbridge);
    
    //r1f1
    walkbridge_pad = padding(walkbridge, walkbridge_pad, padsize, resize, mode);
    mask[0]=0;mask[1]=-1;mask[2]=0;mask[3]=-1;mask[4]=+4;mask[5]=-1;mask[6]=0;mask[7]=-1;mask[8]=0;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r1f1=conv(walkbridge_pad, walkbridge_r1f1, mask_highboost, height+padsize*2, masklength);
    
    //r2f1
    A=2;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r2f1=conv(walkbridge_pad, walkbridge_r2f1, mask_highboost, height+padsize*2, masklength);

    
    
    //r4f1
    A=4;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r4f1=conv(walkbridge_pad, walkbridge_r4f1, mask_highboost, height+padsize*2, masklength);


    //r1f2
    mask[0]=-1;mask[1]=-1;mask[2]=-1;mask[3]=-1;mask[4]=+8;mask[5]=-1;mask[6]=-1;mask[7]=-1;mask[8]=-1;
    A=1;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r1f2=conv(walkbridge_pad, walkbridge_r1f2, mask_highboost, height+padsize*2, masklength);

    //r2f2
    A=2;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r2f2=conv(walkbridge_pad, walkbridge_r2f2, mask_highboost, height+padsize*2, masklength);

    //r4f2
    A=4;
    mask_highboost=highboostMask(mask,A,masksize);
    walkbridge_r4f2=conv(walkbridge_pad, walkbridge_r4f2, mask_highboost, height+padsize*2, masklength);

    

    imwrite(hw3_wkbridge_r1f1,walkbridge_r1f1);
    imwrite(hw3_wkbridge_r2f1,walkbridge_r2f1);
    imwrite(hw3_wkbridge_r4f1,walkbridge_r4f1);
    imwrite(hw3_wkbridge_r1f2,walkbridge_r1f2);
    imwrite(hw3_wkbridge_r2f2,walkbridge_r2f2);
    imwrite(hw3_wkbridge_r4f2,walkbridge_r4f2);
    showImage(wk_r1f1_windowname, walkbridge_r1f1);
    showImage(wk_r2f1_windowname, walkbridge_r2f1);
    showImage(wk_r4f1_windowname, walkbridge_r4f1);
    showImage(wk_r1f2_windowname, walkbridge_r1f2);
    showImage(wk_r2f2_windowname, walkbridge_r2f2);
    showImage(wk_r4f2_windowname, walkbridge_r4f2);
    closeImage(wk_r1f1_windowname);
}

int hw4()
{
    int masklength=5;
    int masksize=masklength*masklength;
    int height=512;
    int width=512;
    int padsize=(masklength-1)/2;
    int resize=pow(height+padsize,2);
    char hw4_turtle[] = "../data/turtle512.raw";
    char hw4_turtle08[] = "../data/hw4.a_turtle08.png";
    char hw4_turtle13[] = "../data/hw4.b_turtle13.png";
    char hw4_turtle2[] = "../data/hw4.b_turtle2.png";
    char turtle08_window[]="hw4.a_turtle_0.8";
    char turtle13_window[]="hw4.a_turtle_1.3";
    char turtle2_window[]="hw4.a_turtle_2";
    double* mask=new double[masksize]();
    double sigma=0.8;
    int mode=1;
    mask=gaussian(masklength, sigma);
    Mat turtle_512(height,width,CV_8UC1);
    Mat turtle_08(height,width,CV_8UC1);
    Mat turtle_13(height,width,CV_8UC1);    //sigma=1.3
    Mat turtle_2(height,width,CV_8UC1); //sigma=2
    Mat padedimage(height+masklength,width+masklength,CV_8UC1);
    FILE *turtle_file;
    unsigned char *turtle_pixel=new unsigned char[height*width]();

    turtle_pixel=readImage(hw4_turtle,height*width,turtle_file,turtle_pixel);
    memcpy(turtle_512.data,turtle_pixel,height*width);
    // for(int i=0;i<masksize;i++)
    // {
    //     printf("%d mask=%f\n",i,mask[i]);
    // }
    padedimage = padding(turtle_512, padedimage, padsize, resize, mode);
    turtle_08=conv(padedimage, turtle_08, mask, height+padsize*2, masklength);

    sigma=1.3;
    mask=gaussian(masklength, sigma);
    turtle_13=conv(padedimage, turtle_13, mask, height+padsize*2, masklength);
    // for(int i=0;i<masksize;i++)
    // {
    //     printf("%d mask=%f\n",i,mask[i]);
    // }

    sigma=2;
    mask=gaussian(masklength, sigma);
    turtle_2=conv(padedimage, turtle_2, mask, height+padsize*2, masklength);
    // for(int i=0;i<masksize;i++)
    // {
    //     printf("%d mask=%f\n",i,mask[i]);
    // }
    
    imwrite(hw4_turtle08,turtle_08);
    imwrite(hw4_turtle13,turtle_13);
    imwrite(hw4_turtle2,turtle_2);
    imshow(turtle08_window,turtle_08);
    imshow(turtle13_window,turtle_13);
    imshow(turtle2_window,turtle_2);
    closeImage(turtle08_window);
}

int main(int argc, char const *argv[])
{
    // hw1_a();
    // hw1_b();
    // hw2();
    // hw3_a();
    // hw3_b();
    hw4();
    return 0;
}
