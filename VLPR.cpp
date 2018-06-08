#include "stdafx.h"  
  
#include "cv.h"  
#include "highgui.h"  
  
using namespace std;  
using namespace cv;  
  
IplImage *g_pGrayImage = NULL;    
IplImage *g_pBinaryImage = NULL;    
const char *pstrWindowsBinaryTitle = "二值图";    
  
void on_trackbar(int pos)    
{    
    // 转为二值图    
    cvThreshold(g_pGrayImage, g_pBinaryImage, pos, 255, CV_THRESH_BINARY);    
    // 显示二值图    
    cvShowImage(pstrWindowsBinaryTitle, g_pBinaryImage);    
}   
  
int detectionChange(Mat& mat1, Mat& mat2, int number);  
void verProjection_calculate(Mat& mat1, int* vArr, int number);  
int** verProjection_cut(int* vArr, int width, int* number);  
float pixelPercentage(Mat& mat1);  
  
  
int _tmain(int argc, _TCHAR* argv[])  
{  
     const char *pstrWindowsSrcTitle = "原图";    
    const char *pstrWindowsToolBarName = "二值图阈值";    
    
    // 从文件中加载原图    
    IplImage *pSrcImage = cvLoadImage("plate.jpg", CV_LOAD_IMAGE_UNCHANGED);    
  
    if (pSrcImage==NULL)  
        return -1;  
    
    // 转为灰度图    
    g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);    
    cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);    
    
    // 创建二值图    
    g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);    
    
    // 显示原图    
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);    
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);    
    // 创建二值图窗口    
    cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);    
    
    // 滑动条      
    //int nThreshold = 0;    
    //cvCreateTrackbar(pstrWindowsToolBarName, pstrWindowsBinaryTitle, &nThreshold, 254, on_trackbar);      
    //on_trackbar(1);    
  
    // 转为二值图    
    cvThreshold(g_pGrayImage, g_pBinaryImage, 190, 255, CV_THRESH_BINARY);    
    // 显示二值图    
    cvShowImage(pstrWindowsBinaryTitle, g_pBinaryImage);    
  
    // 字符分割  
    Mat img_3;  
    detectionChange((Mat)g_pBinaryImage, img_3, 7);    
    imshow(" 边缘分离 ",img_3);  
  
  
    int width, reWidth=30, wWidth=20, pic_width;    
    int height, reHeight=100, wHeight = 20;   
    int pic_ArrNumber;    
    int vArr[100];    
    int **pic_Arr;  
    Mat img_4 = img_3;  
    // 调整图片的大小。  
    resize(img_3,img_4,Size(100,30));  
    verProjection_calculate(img_4, vArr, reHeight);    
    pic_Arr = verProjection_cut(vArr, reHeight, &pic_ArrNumber);    
  
    int i;  
    for(i=0; i< pic_ArrNumber; i++){    
        printf("pic_Arr[%d]:%d, %d\n", i, pic_Arr[i][0], pic_Arr[i][1]);                                                                 
    }    
    char str[20]={0};  
    sprintf(str, "%d", i+3);    
    namedWindow(str);    
    imshow("缩小的图像", img_4);    
  
  
    Mat img_5;   
    IplImage pI_1 = (Mat)img_4;    
    IplImage pI_2;  
    float percentage = 0.0;    
    CvScalar s1;    
    char str1[20]={0};  
    for(i=0; i< pic_ArrNumber; i++){    
        pic_width = pic_Arr[i][1] - pic_Arr[i][0];    
        // 字体宽度的度量。  
        if(pic_width < 3){    
            continue;    
        }    
     
        img_5 = cv::Mat(reWidth, pic_Arr[i][1] - pic_Arr[i][0], CV_8UC1, 1);    
        pI_2 = img_5;    
        for(int j=0; j<reWidth; j++){    
            for(int k=pic_Arr[i][0]; k<pic_Arr[i][1]; k++){    
                s1 = cvGet2D(&pI_1, j, k);    
                cvSet2D(&pI_2, j, k-pic_Arr[i][0], s1);     
            }    
        }    
        percentage = pixelPercentage(img_5);    
        if(percentage < 0.1){    
            continue;    
        }    
        // 又一次判定 字符的宽度。  
        if(pic_width < 3){    
            printf("the %d is 1\n", i);    
            continue;    
        }    
        Mat img_w = img_5;  
        // 调整图片的大小。  
        resize(img_5,img_w,Size(10,40));  
        sprintf(str1, "%d", i+10);    
        namedWindow(str1);    
        imshow(str1, img_w);    
    }    
  
  
  
  
    cvWaitKey(0);    
    cvDestroyWindow(pstrWindowsSrcTitle);    
    cvDestroyWindow(pstrWindowsBinaryTitle);    
    cvReleaseImage(&pSrcImage);    
    cvReleaseImage(&g_pGrayImage);    
    cvReleaseImage(&g_pBinaryImage);    
  
    return 0;  
}  
  
  
int detectionChange(Mat& mat1, Mat& mat2, int number){    
    IplImage pI_1 = mat1, pI_2;    
    CvScalar s1, s2;    
    int width = mat1.rows;    
    int height = mat1.cols;    
    int sum = 0, sum_2 = 0, width_1 = 0, width_2 = 0;    
    int i, j;    
     
    for(i=0; i<width; i++){    
        sum = 0;    
        sum_2 = 0;    
        for(j=0; j<height-1; j++){    
            s1 = cvGet2D(&pI_1, i, j);    
            s2 = cvGet2D(&pI_1, i, j+1);    
            if(((int)s1.val[0]) != ((int)s2.val[0])){    
                sum += 1;    
                sum_2 = 0;    
            }else{    
                sum_2 += 1;     
            }    
            if(sum_2 != 0){    
                if(height / sum_2 < 5){    
                    sum = 0;    
                    break;    
                }    
            }    
        }    
        if(sum >= number){    
            width_1 = i;    
            break;    
        }else{    
            width_1 = i;        
        }    
    }    
     
    for(i=width-1; i> 0; i--){    
        sum = 0;    
        sum_2 = 0;    
        for(j=0; j<height-1; j++){    
            s1 = cvGet2D(&pI_1, i, j);    
            s2 = cvGet2D(&pI_1, i, j+1);    
            if(((int)s1.val[0]) != ((int)s2.val[0])){    
                sum += 1;    
                sum_2 = 0;    
            }else{    
                sum_2 += 1;     
            }    
            if(sum_2 != 0){    
                if(height / sum_2 < 1){    
                    sum = 0;    
                    break;    
                }    
            }    
        }    
        if(sum >= number){    
            width_2 = i;    
            break;      
        }else{    
            width_2 = i;    
        }    
    }    
    if(width_2 <= width_1){    
        width_2 = width;        
    }    
    mat2 = cv::Mat(width_2 - width_1 + 1, height, CV_8UC1, 1);    
    pI_2 = mat2;    
    for(i=width_1; i<= width_2; i++){    
        for(j=0; j<height; j++){    
            s1 = cvGet2D(&pI_1, i, j);    
            cvSet2D(&pI_2, i-width_1, j, s1);    
        }       
    }    
    return 1;  
}    
void verProjection_calculate(Mat& mat1, int* vArr, int number){    
    IplImage pI_1 = mat1;    
    CvScalar s1;    
    int width = mat1.rows;    
    int height = mat1.cols;    
    int i, j;    
     
    for(i=0; i< number; i++){    
        vArr[i] = 0;        
    }    
     
    for(j=0; j<height; j++){    
        for(i=0; i<width; i++){    
            s1 = cvGet2D(&pI_1, i, j);    
            if(s1.val[0] > 20){    
                vArr[j] += 1;                   
            }       
        }    
    }    
}    
     
int** verProjection_cut(int* vArr, int width, int* number){    
    int **a;    
    int i, flag = 0;    
    int num = 0;    
    int threshold = 2;    
     
    a = (int**)malloc(width / 2 * sizeof(int*));    
     
    for(i=0; i<width-1; i++){    
        if((vArr[i] <= threshold) && (vArr[i+1] > threshold)){    
            a[num] = (int* )malloc(2 * sizeof(int));    
            a[num][0] = i;    
            flag = 1;    
        }else if((vArr[i] > threshold) && (vArr[i+1] <= threshold) && (flag != 0)){    
            a[num][1] = i;    
            num += 1;    
            flag = 0;    
        }    
    }    
    *number = num;    
     
    return a;    
}  
  
float pixelPercentage(Mat& mat1){    
    IplImage pI_1 = mat1;    
    CvScalar s1;    
    int width = mat1.rows;    
    int height = mat1.cols;    
    int i, j;    
    float sum = 0, allSum = 0, tmp;    
     
    for(i=0; i<width; i++){    
        for(j=0; j<height; j++){    
            s1 = cvGet2D(&pI_1, i, j);    
            if(s1.val[0] > 20){    
                sum += 1;    
            }    
            allSum += 1;    
        }       
    }    
    tmp = sum / allSum;    
     
    return tmp;    
}   