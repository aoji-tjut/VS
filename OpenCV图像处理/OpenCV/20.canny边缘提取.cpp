//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void callback(int, void*);
//
//Mat src, gray, gray_blur, dst_gray, dst, dst2;
//const char* title = "Canny��Ե���";
//int value = 0;
//int max = 255;
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	cvtColor(src, gray, CV_BGR2GRAY);
//	medianBlur(gray, gray_blur, 5);
//	namedWindow(title, CV_WINDOW_AUTOSIZE);
//	createTrackbar("����ֵ��", title, &value, ::max, callback);
//	callback(0, 0);
//
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	Canny(gray_blur, dst, value, value * 2);//��ʵ���㷨�Դ�ģ��
//	imshow(title, ~dst);
//}