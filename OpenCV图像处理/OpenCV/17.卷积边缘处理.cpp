//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	
//	//��Ե�����С
//	int top = (int)(0.05 * src.rows);
//	int bottom = (int)(0.05 * src.rows);
//	int left = (int)(0.05 * src.cols);
//	int right = (int)(0.05 * src.cols);
//	
//	Mat dst;
//	RNG rng(time(NULL));
//	int type = BORDER_DEFAULT;
//	char c;
//	while (1)
//	{
//		c = waitKey(500);
//		if (c == 27)//Esc
//		{
//			break;
//		}
//
//		if (c == 'r')
//		{
//			type = BORDER_REPLICATE;
//		}
//		else if (c == 'w')
//		{
//			type = BORDER_WRAP;
//		}
//		else if (c == 'c')
//		{
//			type = BORDER_CONSTANT;
//		}
//		else if (c == 'd')
//		{
//			type = BORDER_DEFAULT;//���
//		}
//		copyMakeBorder(src, dst, top, bottom, left, right, type, Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)));
//		imshow("dst", dst);
//	}
//
//
//	waitKey(0);
//	return 0;
//}