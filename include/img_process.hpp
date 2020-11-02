#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

unsigned char * readImage(char fileIn_path[],int imageSize,FILE *file,unsigned char *pixel);
void check(FILE *checkfile);
unsigned int *histogram(unsigned int *gryl_statistics,unsigned char *pixel,int size);
unsigned char *histogramMatching(unsigned int *gryl_statistics1,unsigned int *gryl_statistics2);
double cdf(unsigned char *gryl_statistics,int size,int x);
void showImage (char window_name[], Mat Mat_name);
void closeImage(char window_name[]);
Mat drawHistogram(unsigned int *gryl_statistics, Mat histogram,int max);
int findMax(unsigned int *gryl_statistics);
unsigned char *match(unsigned char *mapping,unsigned char *hs_pixel,unsigned char *hs_new_pixel,int size);