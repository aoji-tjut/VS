//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;dd
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat dst1;
//	pyrUp(src, dst1, Size(src.cols * 2, src.rows * 2));
//	imshow("�ϲ���", dst1);
//
//	Mat dst2;
//	pyrDown(src, dst2, Size(src.cols / 2, src.rows / 2));
//	imshow("�²���", dst2);
//
//	Mat gray, g1, g2, dst3;
//	cvtColor(src, gray, CV_BGR2GRAY);
//	GaussianBlur(gray, g1, Size(5, 5), 0, 0);
//	GaussianBlur(g1, g2, Size(5, 5), 0, 0);
//	subtract(g1, g2, dst3, Mat());
//	normalize(dst3, dst3, 255, 0, NORM_MINMAX);//��һ����ʾ
//	imshow("��˹��ͬDOG", dst3);
//
//	waitKey(0);
//	return 0;
//}