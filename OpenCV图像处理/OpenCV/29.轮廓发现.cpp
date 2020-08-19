//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//Mat src, gray, canny, dst;
//int value = 100;
//int max_value = 255;
//vector<vector<Point>> contours;//����
//vector<Vec4i> hierarchy;//���
//RNG rng(time(NULL));
//const char* title = "dst";
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\������.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	namedWindow(title, CV_WINDOW_AUTOSIZE);
//	cvtColor(src, gray, CV_BGR2GRAY);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	dst = Mat::zeros(src.size(), CV_8UC3);
//
//	Canny(gray, canny, value, max_value);
//	//���������ֵͼ��  ȫ�����ֵ�����ͼ��  ���˽ṹ  ����ģʽ  ���ַ���
//	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);//�������� ��һ������Ϊ�������ͼ�� ��Ҫ��ʼ��
//	
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		 
//		//���ͼ�� ȫ�����ֵ�����ͼ�� ���� ��ɫ �߿� ������ ���˽ṹ ������
//		drawContours(dst, contours, i, color, 1, LINE_8, hierarchy, 0);//�������� ��һ������Ϊ�������ͼ�� ��Ҫ��ʼ��
//	}
//
//	imshow(title, dst);
//}