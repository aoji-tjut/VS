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
//	Mat gray;
//	cvtColor(src, gray, CV_RGB2GRAY);
//	imshow("gray", gray);
//
//	Mat dst;
//	equalizeHist(gray, dst);//ֱ��ͼ���⻯(��߶Աȶ�)
//	imshow("dst", dst);
//
//	waitKey(0);
//	return 0;
//}