#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void Flip(Mat &img)
{
    int rows=img.rows;
    int cols=img.cols*img.channels();
    for(int i=0; i<rows/2; i++)
    {
        uchar *p=img.ptr<uchar>(i);
        uchar *q=img.ptr<uchar>(rows-1-i);
        uchar t;
        for(int j=0; j<cols;j++)
        {
            t=*p;
            *p++=*q;
            *q++=t;
        }
    }
}

int main()
{
    Mat img1=imread("test.jpg");  //将任意一张名为test.jpg的图片放置于工程文件夹test中
    imshow("First",img1);
    if(!img1.data)
    {
        cout<<"error! The image is not built!"<<endl;
        return -1;
    }
    Flip(img1);
    imshow("Second",img1);
    waitKey();
    return 0;
}