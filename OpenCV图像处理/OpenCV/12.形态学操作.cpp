//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src1 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\������.JPG");
//	if (src1.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src1", CV_WINDOW_AUTOSIZE);
//	imshow("src1", src1);
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15)); 
//	Mat kernel_grad = getStructuringElement(MORPH_RECT, Size(3, 3));
//
//	Mat dst1;
//	morphologyEx(src1, dst1, CV_MOP_OPEN, kernel);//������ �ȸ�ʴ������ ȥ���׵�
//	imshow("������", dst1);
//
//	Mat src2 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\�ղ���.JPG");
//	if (src2.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	imshow("src2", src2);
//
//	Mat dst2;
//	morphologyEx(src2, dst2, CV_MOP_CLOSE, kernel);//�ղ��� �����ͺ�ʴ ȥ���ڵ�
//	imshow("�ղ���", dst2);
//
//	Mat src3 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//	if (src3.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	imshow("src3", src3);
//
//	Mat dst3;
//	morphologyEx(src3, dst3, CV_MOP_GRADIENT, kernel_grad);//��̬ѧ�ݶ� ���ͼ���ʴ �õ�������
//	imshow("�ݶ�", dst3);
//
//	Mat dst4;
//	morphologyEx(src1, dst4, CV_MOP_TOPHAT, kernel);//��ñ ԭͼ-������ ��������
//	imshow("��ñ", dst4);
//
//	Mat dst5;
//	morphologyEx(src2, dst5, CV_MOP_BLACKHAT, kernel);//��ñ ������-ԭͼ ���밵��
//	imshow("��ñ", dst5);
//
//	waitKey(0);
//	return 0;
//}