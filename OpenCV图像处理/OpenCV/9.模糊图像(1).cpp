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
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat dst1;
//	blur(src, dst1, Size(3, 3));//均值滤波（差） 破坏图像细节		Size(x方向,y方向) x,y为奇数
//	imshow("均值滤波", dst1);
//
//	Mat dst2;
//	GaussianBlur(src, dst2, Size(3, 3), 0, 0);//高斯滤波（好） 消除高斯（正态分布）噪声
//	imshow("高斯滤波", dst2);
//
//	waitKey(0);
//	return 0;
//}