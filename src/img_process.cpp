#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/img_process.hpp"
using namespace cv;

void check(FILE *checkfile){
if (checkfile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
}

unsigned char *readImage(char fileIn_path[],int imageSize,FILE *file,unsigned char *pixel) //for any size of image
{
    file=fopen(fileIn_path,"rb");
    check(file);
    fread(pixel, sizeof(char), imageSize, file);
    return pixel;
}

void showImage (char window_name[], Mat Mat_name){
    cvNamedWindow(window_name);
	cvMoveWindow(window_name, 0, 0);
	imshow(window_name, Mat_name);
}

void closeImage(char window_name[])
{
    cvWaitKey(0);
    // cvDestroyWindow(window_name);
}


unsigned int *histogram(unsigned int *gryl_statistics,unsigned char *pixel,int size)
{
    int grylevel=0;
    for(int i=0;i<size;i++)
    {
        grylevel=pixel[i];
        gryl_statistics[grylevel]=gryl_statistics[grylevel]+1;
        
        /*method 2*/
        // for(int j=0;j<256;j++)
        // {
        //     if(pixel[i]==j)
        //     {
        //         gryl_statistics[j]=gryl_statistics[j]+1;
        //     }
        // }
    }
    // int sum=0;
    // for(int i=0;i<256;i++)
    // {
    //     sum=sum+gryl_statistics[i];
    //     // printf("gryl=%d\n",gryl_statistics[i]);
    // }
    // printf("sum=%d\n",sum);
    return gryl_statistics;
} 

double cdf(unsigned char *gryl_statistics,int size,int x)
{
    double cdf=0.0;
    for(int i=0;i<=x;i++)
    {
        cdf=cdf+gryl_statistics[i];
    }
    cdf=cdf/size;
    return cdf;
}

Mat drawHistogram(unsigned int *gryl_statistics, Mat histogram,int max)
{
    for(int i=0;i<256;i++)
    {
        // std::cout<<"gryl_statistics[i])/max="<<gryl_statistics[i]/max<<std::endl;
        for(int j=0;j<=(gryl_statistics[i])/max;j++)
        {
            histogram.col(i).row(255-j)=255;
        }
    }
    return histogram;
}

int findMax(unsigned int *gryl_statistics)  //find maximum statistic
{
    int max=0;
    for(int i=0;i<256;i++)
    {
        if(gryl_statistics[i]>max){
            max=gryl_statistics[i];
        }
        
    }
    return max;
}

unsigned char *histogramMatching(unsigned int *gryl_statistics1,unsigned int *gryl_statistics2)
{   
    int amount_sum1=0;
    int amount_sum2=0;
    int j=0;
    bool in=false;
    unsigned char *mapping=new unsigned char[256]();
    for(int i=0;i<256;i++)
    {
        amount_sum1=amount_sum1+gryl_statistics1[i];
        // printf("amount_sum1=%d\n",amount_sum1);
        while(amount_sum2<amount_sum1)
        {
            in=true;
            amount_sum2=amount_sum2+gryl_statistics2[j];
            j++;
        }
        if(in==true|amount_sum2!=0)
        {
            amount_sum2=amount_sum2-gryl_statistics2[j];
            j--;
        }
        // printf("amount_sum2=%d\n",amount_sum2);
        mapping[i]=j;  //原圖灰階＝i的pixel之灰階要改成j
        // printf("i=%d\n",i);
        // printf("mapping[i]=%d\n",mapping[i]);
        in=false;
    }

    return mapping;
}

unsigned char *match(unsigned char *mapping,unsigned char *hs_pixel,unsigned char *hs_new_pixel,int size)
{
    int map;
    for(int i=0;i<size;i++)
    {
        map=hs_pixel[i];
        hs_new_pixel[i]=mapping[map];
    }
    return hs_new_pixel;
}



