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
//	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//得到一个形状
//
//	Mat dst1;
//	dilate(src, dst1, element);//膨胀 增加白减少黑
//	imshow("膨胀", dst1);
//
//	Mat dst2;
//	erode(src, dst2, element);//腐蚀 增加黑减少白
//	imshow("腐蚀", dst2);
//
//	Mat dst3;
//	addWeighted(dst1, 0.5, dst2, 0.5, 0.0, dst3);
//	imshow("混合", dst3);
//
//	waitKey(0);
//	return 0;
//}