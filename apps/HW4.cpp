#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/img_process.hpp"
#include "../include/VideoReader.hpp"
using namespace cv;

void hw1_a()
{   
    int height=512;
    int width=512;
    int size=height*width;

    char house512_path[]="../data/house512.raw";
    char lena512_path[]="../data/lena512.raw";
    char house_new_path[]="../data/1.a_house.png";
    char house_his_path[]="../data/1.a_house_his.png";
    char lena_his_path[]="../data/1.a_lena_his.png";
    char house_his_new_path[]="../data/1.a_house_his_new.png";

    FILE *hs_512,*lena_512;

    unsigned char *hs_pixel=new unsigned char[size]();
    unsigned char *lena_pixel=new unsigned char[size]();
    unsigned char *hs_new_pixel=new unsigned char[size]();
    unsigned int *hs_gryl_statistics=new unsigned int[256]();   //統計每個pixel的灰階，用unsigned char會溢位
    unsigned int *lena_gryl_statistics=new unsigned int[256]();
    unsigned int *hs_gryl_statistics_new=new unsigned int[256]();
    unsigned char *mapping=new unsigned char[256]();

    Mat house_512,new_house_512,lenamat_512,house_512_his,lenamat_512_his,new_house_512_his;
    char hs_windowname[]="1.a_hs512";
    char lena_windowname[]="1.a_lena512";
    char hs_new_windowname[]="1.a_hs512_new";
    char hs_his_windowname[]="1.a_hs_his";
    char lena_his_windowname[]="1.a_lena_his";
    char hs_his_new_windowname[]="1.a_hs_his_new";

    hs_pixel=readImage(house512_path,size,hs_512,hs_pixel);
    lena_pixel=readImage(lena512_path,size,lena_512,lena_pixel);

    house_512.create(height,width,CV_8UC1);
    new_house_512.create(height,width,CV_8UC1);
    lenamat_512.create(height,width,CV_8UC1);
    house_512_his.create(height/2,width/2,CV_8UC1);
    lenamat_512_his.create(height/2,width/2,CV_8UC1);
    new_house_512_his.create(height/2,width/2,CV_8UC1);

    memcpy(house_512.data,hs_pixel,size);
    memcpy(lenamat_512.data,lena_pixel,size);

    hs_gryl_statistics=histogram(hs_gryl_statistics,hs_pixel,size);
    lena_gryl_statistics=histogram(lena_gryl_statistics,lena_pixel,size);
    // int count=0;
    int max=0;
    // for(int i=0;i<256;i++)
    // {
    //     count=count+lena_gryl_statistics[i];
    // }
    // std::cout<<count<<std::endl;

    max=findMax(hs_gryl_statistics);
    std::cout<<"max="<<max<<std::endl;
    max=max/255+1;
    house_512_his=drawHistogram(hs_gryl_statistics,house_512_his,max);

    max=findMax(lena_gryl_statistics);
    std::cout<<"max="<<max<<std::endl;
    max=max/255+1;
    lenamat_512_his=drawHistogram(lena_gryl_statistics,lenamat_512_his,max);

    mapping=histogramMatching(hs_gryl_statistics,lena_gryl_statistics);

    hs_new_pixel=match(mapping,hs_pixel,hs_new_pixel,size);
    memcpy(new_house_512.data,hs_new_pixel,size);

    hs_gryl_statistics_new=histogram(hs_gryl_statistics_new,hs_new_pixel,size);
    max=findMax(hs_gryl_statistics_new);
    std::cout<<"max="<<max<<std::endl;
    max=max/255+1;
    new_house_512_his=drawHistogram(hs_gryl_statistics_new,new_house_512_his,max);

    imwrite(house_new_path,new_house_512);
    imwrite(house_his_path,house_512_his);
    imwrite(lena_his_path,lenamat_512_his);
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
    int height=512;
    int width=512;
    int size=height*width;
    char house512_path[]="../data/house512.raw";
    FILE *hs_512;
    unsigned char *hs_pixel=new unsigned char[size]();
    unsigned char *hs_pad_pixel=new unsigned char[size]();
    unsigned int *gryl_statistics=new unsigned int[256]();
    Mat house_512,house_512_pad;
    char hs_windowname[]="1.b_hs512";
    char hs_pad_windowname[]="1.b_hs512_pad";

    house_512.create(height,width,CV_8UC1);
    hs_pixel=readImage(house512_path,size,hs_512,hs_pixel);
    memcpy(house_512.data,hs_pixel,size);
    
    //mask=9*9
    int padsize=4;
    int resize=pow((512+padsize*2),2);
    
    // unsigned char *pd_pixel=new unsigned char[resize]();
    house_512_pad.create(height+padsize*2,width+padsize*2,CV_8UC1);
    int mode=1;
    house_512_pad=padding(house_512,house_512_pad,padsize,resize,mode);
    hs_pad_pixel=storeMat2Pixel(house_512_pad,hs_pad_pixel,resize);
    gryl_statistics=histogram(gryl_statistics,hs_pad_pixel,resize);
    showImage(hs_windowname,house_512);
    showImage(hs_pad_windowname,house_512_pad);
    closeImage(hs_windowname);
}

void hw2()
{
    int returnnum=0;
    int framenum=10;
    bool total=false;
    char hw2_10frame[]="../data/hw2_10frame.png";
    returnnum=videoReader(framenum,hw2_10frame,total);
    framenum=200;
    char hw2_200frame[]="../data/hw2_200frame.png";
    returnnum=videoReader(framenum,hw2_200frame,total);
    total=true;
    char hw2_allframe[]="../data/hw2_allframe.png";
    returnnum=videoReader(framenum,hw2_allframe,total);
}

int main(int argc, char const *argv[])
{
    // hw1_a();
    hw1_b();
    // hw2();
    return 0;
}
