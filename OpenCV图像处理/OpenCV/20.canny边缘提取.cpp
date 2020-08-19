//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void callback(int, void*);
//
//Mat src, gray, gray_blur, dst_gray, dst, dst2;
//const char* title = "Canny边缘检测";
//int value = 0;
//int max = 255;
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	cvtColor(src, gray, CV_BGR2GRAY);
//	medianBlur(gray, gray_blur, 5);
//	namedWindow(title, CV_WINDOW_AUTOSIZE);
//	createTrackbar("低阈值：", title, &value, ::max, callback);
//	callback(0, 0);
//
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	Canny(gray_blur, dst, value, value * 2);//其实此算法自带模糊
//	imshow(title, ~dst);
//}