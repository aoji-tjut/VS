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
//	Mat blur;
//	GaussianBlur(src, blur, Size(3, 3), 0.0);
//
//	Mat gray;
//	cvtColor(blur, gray, CV_BGR2GRAY);
//
//	Mat dst;
//	Laplacian(gray, dst, CV_16S);//������˹
//	convertScaleAbs(dst, dst);//ȡ����ֵ
//	imshow("������˹����", dst);
//
//	waitKey(0);
//	return 0;
//}