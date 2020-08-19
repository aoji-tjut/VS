//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//Mat src, canny, dst_contours, dst_convexs;
//RNG rng(time(NULL));
//int value = 128;
//int max_value = 255;
//vector<vector<Point>> contours;//����
//vector<Vec4i> hierarchy;//���
//
//void callback(int, void*);
//
//int main()
//{
//	
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\logo.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	dst_contours = Mat::zeros(src.size(), CV_8UC3);
//	dst_convexs = Mat::zeros(src.size(), CV_8UC3);
//	const char* title = "src";
//	namedWindow(title);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	Canny(src, canny, value, value * 2);//�Դ�ģ��
//	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//	vector<vector<Point>> convexs(contours.size());//͹��
//	for (int i = 0; i < contours.size(); i++)
//	{
//		convexHull(contours[i], convexs[i]);//�õ�͹����ѡ��
//	}
//
//	//����
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		drawContours(dst_contours, contours, i, color, 2, LINE_8);//������
//		drawContours(dst_convexs, convexs, i, color, 2, LINE_8);//��͹��
//	}
//	imshow("����", dst_contours);
//	imshow("͹��", dst_convexs);
//}