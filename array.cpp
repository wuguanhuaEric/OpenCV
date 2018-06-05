#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void Flip(Mat &img)
{
    int rows=img.rows;
    int cols=img.cols;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols/2; j++)
        {
            uchar t;
            if(img.channels()==1)
            {
                t=img.at<uchar>(i,j);
                img.at<uchar>(i,j)=img.at<uchar>(i,cols-1-i);
                img.at<uchar>(i,cols-1-i)=t;
            }
            else if(img.channels()==3)
            {
                for(int k=0; k<3; k++)
                {
                    t=img.at<Vec3b>(i,j)[k];
                    img.at<Vec3b>(i,j)[k]=img.at<Vec3b>(i,cols-1-j)[k];
                    img.at<Vec3b>(i,cols-1-j)[k]=t;
                }
            }
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