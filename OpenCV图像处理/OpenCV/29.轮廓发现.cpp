//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//Mat src, gray, canny, dst;
//int value = 100;
//int max_value = 255;
//vector<vector<Point>> contours;//轮廓
//vector<Vec4i> hierarchy;//层次
//RNG rng(time(NULL));
//const char* title = "dst";
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\热气球.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	namedWindow(title, CV_WINDOW_AUTOSIZE);
//	cvtColor(src, gray, CV_BGR2GRAY);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	dst = Mat::zeros(src.size(), CV_8UC3);
//
//	Canny(gray, canny, value, max_value);
//	//输入输出二值图像  全部发现的轮廓图像  拓扑结构  返回模式  发现方法
//	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);//发现轮廓 第一个参数为输入输出图像 需要初始化
//	
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		 
//		//输出图像 全部发现的轮廓图像 索引 颜色 线宽 线类型 拓扑结构 最大层数
//		drawContours(dst, contours, i, color, 1, LINE_8, hierarchy, 0);//绘制轮廓 第一个参数为输入输出图像 需要初始化
//	}
//
//	imshow(title, dst);
//}