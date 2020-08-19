//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void threshold_callback(int, void*);
//Mat src;
//Mat gray;
//Mat dst;
//int threshold_value = 128;
//int threshold_max = 255;
//int type_value = 0;
//int type_max = 4;
//const char* dst_title = "输出图像";
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
//	cout << "0  THRESH_BINARY        二值化" << endl;
//	cout << "1  THRESH_BINARY_INV    反二值化" << endl;
//	cout << "2  THRESH_TRUNC         截断" << endl;
//	cout << "3  THRESH_TOZERO        取零" << endl;
//	cout << "4  THRESH_TOZERO_INV    反取零" << endl;
//
//	cvtColor(src, gray, CV_RGB2GRAY);
//
//	namedWindow(dst_title, CV_WINDOW_AUTOSIZE);
//	createTrackbar("类型：", dst_title, &type_value, type_max, threshold_callback);
//	createTrackbar("阈值：", dst_title, &threshold_value, threshold_max, threshold_callback);
//	threshold_callback(0, 0);
//
//	//adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 10);//自适应二值化
//	
//	
//	waitKey(0);
//	return 0;
//}
//
//void threshold_callback(int, void*)
//{
//	threshold(gray, dst, threshold_value, threshold_max, type_value);//手动调整阈值
//	//自动计算必须是灰度图像
//	//threshold(gray, dst, 0, 255, type_value | THRESH_OTSU);//自动计算阈值
//	//threshold(gray, dst, 0, 255, type_value | THRESH_TRIANGLE);//自动计算阈值
//	imshow(dst_title, dst);
//}