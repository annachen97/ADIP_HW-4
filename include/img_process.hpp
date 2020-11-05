#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

unsigned char * readImage(char fileIn_path[],int imageSize,FILE *file,unsigned char *pixel);

void check(FILE *checkfile);

unsigned long *histogram(unsigned long*gryl_statistics,unsigned char *pixel,long size);

unsigned char *histogramMatching(unsigned long *gryl_statistics1,unsigned long *gryl_statistics2);

double cdf(unsigned char *gryl_statistics,int size,int x);

void showImage (char window_name[], Mat Mat_name);

void closeImage(char window_name[]);

Mat drawHistogram(unsigned long *gryl_statistics, Mat histogram,int max);

long findMax(unsigned long *gryl_statistics);

unsigned char *match(unsigned char *mapping,unsigned char *hs_pixel,unsigned char *hs_new_pixel,int size);

Mat padding(Mat oldimage,Mat padimage,int padsize,int resize,int mode);

unsigned char* storeMat2Pixel(Mat image,unsigned char* pixel,int size);

Mat conv(Mat paded_image, Mat out_image, double* mask, int image_length, int mask_length,double sum);

double* highboostMask(double* mask,int A,int masksize);

Mat localEnhencement(Mat padedimage, int imglength, int masklength);

double* gaussian(int masklength, double sigma);