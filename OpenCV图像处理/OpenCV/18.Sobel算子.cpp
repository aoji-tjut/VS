//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat dst;
//	GaussianBlur(src, dst, Size(3, 3), 0);
//
//	Mat gray;
//	cvtColor(dst, gray, CV_BGR2GRAY);
//
//	Mat grad_x, grad_y;
//	//�����㷨
//	Sobel(gray, grad_x, -1, 1, 0);//x����1�׵�
//	Sobel(gray, grad_y, -1, 0, 1);//y����1�׵�
//	//��ǿ�㷨
//	//Scharr(gray, grad_x, -1, 1, 0);//x����1�׵�
//	//Scharr(gray, grad_y, -1, 0, 1);//y����1�׵�
//	//ȡ����ֵ
//	convertScaleAbs(grad_x, grad_x);
//	convertScaleAbs(grad_y, grad_y);
//
//	imshow("X�����ݶ�", grad_x);
//	imshow("Y�����ݶ�", grad_y);
//
//	addWeighted(grad_x, 0.5, grad_y, 0.5, 0.0, dst);
//	imshow("�ݶȻ��", dst);
//
//
//	waitKey(0);
//	return 0;
//}