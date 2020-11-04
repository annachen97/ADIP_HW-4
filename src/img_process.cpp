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


unsigned char* storeMat2Pixel(Mat image,unsigned char* pixel,int size)
{
    int height=pow(size,0.5);
    int width=pow(size,0.5);
    for (int i = 0; i < height; i++)
    {   
        for (int j = 0; i < width; i++)
        {
            pixel[i*width+j]=image.at<uchar>(i,j);
        }
        
        
    }
    return pixel;
}

Mat padding(Mat oldimage,Mat padimage,int padsize,int resize,int mode)
{
    if(mode==0)//zero padding
    {
        padimage.zeros(pow(resize,0.5),pow(resize,0.5),CV_8UC1);
        for(int i=0;i<(pow(resize,0.5)-padsize*2);i++)
        {
            for(int j=0;j<(pow(resize,0.5)-padsize*2);j++)
            {
                padimage.row(i+padsize).col(j+padsize)=oldimage.at<uchar>(i,j);
            }
        }
    }else if (mode==1)
    {
        int boundary=pow(resize,0.5)-padsize;
        padimage.zeros(pow(resize,0.5),pow(resize,0.5),CV_8UC1);
        for(int i=0;i<(pow(resize,0.5));i++)
        {
            for(int j=0;j<(pow(resize,0.5));j++)
            {
                if(i<padsize&&j<padsize) //zone1
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(0,0);
                }else if (i<padsize&&j>=padsize&&j<boundary) //zone2
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(0,j-padsize);
                }else if (i<padsize&&j>=boundary) //zone3
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(0,boundary-padsize-1);
                }else if(i>=padsize&&i<boundary&&j<padsize)    //zone4
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(i-padsize,0);
                }else if(i>=padsize&&i<boundary&&j>=boundary) //zone5
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(i-padsize,boundary-padsize-1);
                }else if (i>=boundary&&j<padsize)   //zone6
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(boundary-padsize-1,0);
                }else if (i>=boundary&&j>=padsize&&j<boundary)   //zone7
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(boundary-padsize-1,j-padsize);
                }else if (i>=boundary&&j>=boundary)   //zone8
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(boundary-padsize-1,boundary-padsize-1);
                }else
                {
                    padimage.at<uchar>(i,j)=oldimage.at<uchar>(i-padsize,j-padsize);
                }
                

            //    padimage.row(i+padsize).col(j+padsize)=oldimage.at<uchar>(i,j);
            }
        } 
    }
    
    return padimage;
}

Mat conv(Mat paded_image, Mat out_image, int* mask, int image_length, int mask_length)
{
    int init_pixel=(mask_length-1)/2;
    int x=0,y=0;
    int result=0;
    int count=0;
    for(int i=init_pixel;i<image_length-init_pixel;i++)
    {
        count=count+1;
        for(int j=init_pixel;j<image_length-init_pixel;j++)
        {
            for(int masky=i-init_pixel;masky<=i+init_pixel;masky++)
            {
                for(int maskx=j-init_pixel;maskx<=j+init_pixel;maskx++)
                {   
                    result=result+paded_image.at<uchar>(masky,maskx)*mask[x*mask_length+y];
                    y=y+1;
                }
                y=0;
                x=x+1;
            }
            if(result<0)
            {
                result=0;
            }else if (result>255)
            {
                result=255;
            }
            
            out_image.at<uchar>(i-init_pixel,j-init_pixel)=result;
            // printf("out_image.at<uchar>(i,j)=%d\n",out_image.at<uchar>(i,j));
            result=0;
            x=0; 
        }
        // printf("count=%d\n",count);
    }
    return out_image;
}

int* highboostMask(int* mask,int A,int masksize)
{
    for(int i=0;i<masksize;i++)
    {
        mask[i]=A*mask[i];
    }

    return mask;
}

Mat localEnhencement(Mat padedimage, int imglength, int masklength) //mask=3*3, masklength=3    
{
    int initial=(masklength-1)/2;
    int masksize=pow(masklength,2);
    int imgsize=pow(imglength,2);
    int gryl=0;
    int x=0,y=0;
    Mat le_mat(imglength-masklength+1,imglength-masklength+1,CV_8UC1);
    unsigned char* pixel=new unsigned char[masksize]();
    for(int i=initial;i<(imglength-initial);i++)
    // for(int i=initial;i<=10;i++) //test
    {
        for (int j=initial; j<(imglength-initial); j++)
        // for (int j=initial; j<=10; j++)
        {
            for(int maskx=(i-initial);maskx<=(i+initial);maskx++)
            {
                
                for(int masky=(j-initial);masky<=(j+initial);masky++)
                {
                    pixel[x*masklength+y]=padedimage.at<uchar>(maskx,masky);
                    y=y+1;
                }
                x=x+1;
                y=0;
                
            }
            
            x=0;
            unsigned int* gryl_statistics=new unsigned int[256]();
            gryl_statistics=histogram(gryl_statistics, pixel, masksize);
            double count=0.0;
            int pixelsgryl=padedimage.at<uchar>(i,j);
            for(int p=0;p<=pixelsgryl;p++)
            {
                count=count+gryl_statistics[p];
            }
             if(count>masksize)
            {
                std::cout<<"error!!"<<std::endl;
            }
            count=count/masksize;
            gryl=255*count;
            if(gryl>255||gryl<0)
            {
                std::cout<<"error!!"<<std::endl;
            }
            le_mat.at<uchar>(i-initial,j-initial)=gryl;

        }
    }
    return le_mat;
}


double* gaussian(int masklength, double sigma)
{
    #define PI 3.1415926
    int masksize=pow(masklength,2);
    int cordinate_initial=(masklength-1)/2;
    double* mask=new double[masksize]();
    int x=0,y=0;
    
    for(int i=0;i<masklength;i++)
    {
        for(int j=0;j<masklength;j++)
        {   
            x=j-cordinate_initial;
            y=i-cordinate_initial;
            mask[i*masklength+j]=(1/(2*PI*sigma))*exp(-1*(x*x+y*y)/(2*sigma*sigma));
        }
    }
    return mask;
}
