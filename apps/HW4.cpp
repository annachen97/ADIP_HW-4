#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/img_process.hpp"
using namespace cv;

void hw1_a()
{   
    int height=512;
    int width=512;
    int size=height*width;

    char house512_path[]="../data/house512.raw";
    char lena512_path[]="../data/lena512.raw";

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

    showImage(hs_windowname,house_512);
    showImage(lena_windowname,lenamat_512);
    showImage(hs_new_windowname,new_house_512);
    showImage(hs_his_windowname,house_512_his);
    showImage(lena_his_windowname,lenamat_512_his);
    showImage(hs_his_new_windowname,new_house_512_his);
    closeImage(hs_windowname);
}

int main(int argc, char const *argv[])
{
    hw1_a();
    return 0;
}