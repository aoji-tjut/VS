//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void callback(int, void*);//回调函数
//
//Mat src;
//int fault = 0;
//int max = 4;
//const char* title = "输出";
//
//int main()
//{
//	namedWindow(title, CV_WINDOW_AUTOSIZE);//建立窗口
//	createTrackbar("", title, &fault, ::max, callback);//创建滚条
//	callback(0, 0);//调用回调函数
//	
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	switch (fault)//要改变的量
//	{
//	case 0:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//		break;
//	case 1:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//		break;
//	case 2:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\man.JPG");
//		break;
//	case 3:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\线.JPG");
//		break;
//	case 4:src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//		break;
//	}
//
//	imshow(title, src);//刷新显示图片
//}