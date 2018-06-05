#include <cv.h>  
#include <highgui.h>  
  
using namespace std;  
using namespace cv;  
  
#define QUAN_VAL          (100)  
  
void CreateLookupTable(Mat& table, uchar quan_val)  
{  
    table.create(1, 256, CV_8UC1);  
  
    uchar *p = table.data;  
    for (int i = 0; i < 256; ++i)  
    {  
        p[i] = quan_val*(i / quan_val);  
    }  
}  
  
int main(int argc, char *argv[])  
{  
    Mat img;  
    Mat out;  
  
    img = imread("F:/Photo/OpenCV_Photo/tsukuba_l.png", 1);  
  
    Mat table;//������ұ�  
    //�����Ҷȼ�����100�Ĳ��ұ�  
    CreateLookupTable(table, QUAN_VAL);  
    //ʹ�ò��ұ�ֱ�Ӽ���������Ҷȼ����ͼ�񲢽��䱣�浽out1��  
    LUT(img, table, out);  
  
    namedWindow("Դͼ��", CV_WINDOW_NORMAL);  
    imshow("Դͼ��", img);  
    namedWindow("���ò�ѯ��Ҷȵȼ��任��", CV_WINDOW_NORMAL);  
    imshow("���ò�ѯ��Ҷȵȼ��任��", out);  
  
    waitKey(0);  
  
    return 0;  
}  