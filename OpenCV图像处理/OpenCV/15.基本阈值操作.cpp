//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void threshold_callback(int, void*);
//Mat src;
//Mat gray;
//Mat dst;
//int threshold_value = 128;
//int threshold_max = 255;
//int type_value = 0;
//int type_max = 4;
//const char* dst_title = "���ͼ��";
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
//	cout << "0  THRESH_BINARY        ��ֵ��" << endl;
//	cout << "1  THRESH_BINARY_INV    ����ֵ��" << endl;
//	cout << "2  THRESH_TRUNC         �ض�" << endl;
//	cout << "3  THRESH_TOZERO        ȡ��" << endl;
//	cout << "4  THRESH_TOZERO_INV    ��ȡ��" << endl;
//
//	cvtColor(src, gray, CV_RGB2GRAY);
//
//	namedWindow(dst_title, CV_WINDOW_AUTOSIZE);
//	createTrackbar("���ͣ�", dst_title, &type_value, type_max, threshold_callback);
//	createTrackbar("��ֵ��", dst_title, &threshold_value, threshold_max, threshold_callback);
//	threshold_callback(0, 0);
//
//	//adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 10);//����Ӧ��ֵ��
//	
//	
//	waitKey(0);
//	return 0;
//}
//
//void threshold_callback(int, void*)
//{
//	threshold(gray, dst, threshold_value, threshold_max, type_value);//�ֶ�������ֵ
//	//�Զ���������ǻҶ�ͼ��
//	//threshold(gray, dst, 0, 255, type_value | THRESH_OTSU);//�Զ�������ֵ
//	//threshold(gray, dst, 0, 255, type_value | THRESH_TRIANGLE);//�Զ�������ֵ
//	imshow(dst_title, dst);
//}