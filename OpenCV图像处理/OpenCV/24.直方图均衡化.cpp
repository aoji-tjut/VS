//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
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
//	equalizeHist(gray, dst);//直方图均衡化(提高对比度)
//	imshow("dst", dst);
//
//	waitKey(0);
//	return 0;
//}