//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\��.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("ԭͼ", src);
//
//	Mat gray;
//	cvtColor(src, gray, CV_BGR2GRAY);
//	imshow("�Ҷ�ͼ", gray);
//
//	Mat binary;														//15С���Ĵ�ʵ��		0��������
//	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);//ת��Ϊ��ֵͼ��
//	imshow("��ֵͼ", binary);
//
//	Mat h_line = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1));//ˮƽ�ṹԪ��
//	Mat v_line = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));//��ֱ�ṹԪ��
//	Mat text = getStructuringElement(MORPH_RECT, Size(7, 7));//ȥ������
//
//	Mat temp;
//	Mat dst1;
//	morphologyEx(binary, dst1, CV_MOP_OPEN, h_line);
//	bitwise_not(dst1, dst1);
//	imshow("ˮƽ", dst1);
//
//	Mat dst2;
//	morphologyEx(binary, dst2, CV_MOP_OPEN, v_line);
//	bitwise_not(dst2, dst2);
//	imshow("��ֱ", dst2);
//
//	Mat dst3;
//	morphologyEx(binary, dst3, CV_MOP_OPEN, text);
//	bitwise_not(dst3, dst3);
//	imshow("����", dst3);
//
//
//
//	waitKey(0);
//	return 0;
//}