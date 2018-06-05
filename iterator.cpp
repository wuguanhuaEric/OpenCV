#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void Flip(Mat &img)
{
    uchar t;
    if(img.channels()==1)
    {
        Mat_<uchar>::iterator it=img.begin<uchar>();
        Mat_<uchar>::iterator itend=img.end<uchar>();
        itend--;  //通过end成员函数得到的迭代器已超出集合，所以在这里自减
        for(;it<itend;it++,itend--)
        {
            t=*it;*it=*itend;*itend=t;
        }
    }
    else if(img.channels()==3)
    {
        Mat_<Vec3b>::iterator it=img.begin<Vec3b>();
        Mat_<Vec3b>::iterator itend=img.end<Vec3b>();
        itend--;
        for(;it<itend;it++,itend--)
            for(int k=0; k<3; k++)
            {
                t=(*it)[k];(*it)[k]=(*itend)[k];(*itend)[k]=t;
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