//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void callback(int, void*);//�ص�����
//
//Mat src;
//int fault = 0;
//int max = 4;
//const char* title = "���";
//
//int main()
//{
//	namedWindow(title, CV_WINDOW_AUTOSIZE);//��������
//	createTrackbar("", title, &fault, ::max, callback);//��������
//	callback(0, 0);//���ûص�����
//	
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	switch (fault)//Ҫ�ı����
//	{
//	case 0:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//		break;
//	case 1:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//		break;
//	case 2:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\man.JPG");
//		break;
//	case 3:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\��.JPG");
//		break;
//	case 4:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//		break;
//	}
//
//	imshow(title, src);//ˢ����ʾͼƬ
//}