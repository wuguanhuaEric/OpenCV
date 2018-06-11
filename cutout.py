# coding=utf-8  
  
import cv2  
import  numpy as np  
  
img=cv2.imread('lp.jpg')  
img_back=cv2.imread('back.jpg')  
#�ճ�����  
rows,cols,channels = img_back.shape  
img_back=cv2.resize(img_back,None,fx=0.7,fy=0.7)  
cv2.imshow('img_back',img_back)  
  
rows,cols,channels = img.shape  
img=cv2.resize(img,None,fx=0.4,fy=0.4)  
cv2.imshow('img',img)  
rows,cols,channels = img.shape#rows��cols���һ��Ҫ��ǰ��ͼƬ�ģ��������ͼƬ��Ҫ�õ�  
  
#ת��hsv  
hsv=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)  
#��ȡmask  
lower_blue=np.array([78,43,46])  
upper_blue=np.array([110,255,255])  
mask = cv2.inRange(hsv, lower_blue, upper_blue)  
cv2.imshow('Mask', mask)  
  
#��ʴ����  
erode=cv2.erode(mask,None,iterations=1)  
cv2.imshow('erode',erode)  
dilate=cv2.dilate(erode,None,iterations=1)  
cv2.imshow('dilate',dilate)  
  
#�����滻  
center=[50,50]#���±���ͼƬ�е�λ��  
for i in range(rows):  
    for j in range(cols):  
        if dilate[i,j]==0:#0�����ɫ�ĵ�  
            img_back[center[0]+i,center[1]+j]=img[i,j]#�˴��滻��ɫ��ΪBGRͨ��  
cv2.imshow('res',img_back)  
  
cv2.waitKey(0)  
cv2.destroyAllWindows()  
