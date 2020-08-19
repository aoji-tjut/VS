//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat base = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	Mat base_copy = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	Mat test1 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\man.JPG");
//	Mat test2 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//	imshow("base", base);
//	imshow("base_copy", base_copy);
//	imshow("test1", test1);
//	imshow("test2", test2);
//
//	//BGR转换到HSV
//	cvtColor(base, base, CV_BGR2HSV);
//	cvtColor(base_copy, base_copy, CV_BGR2HSV);
//	cvtColor(test1, test1, CV_BGR2HSV);
//	cvtColor(test2, test2, CV_BGR2HSV);
//
//	int h_bin = 50;//色调定义域
//	int s_bin = 60;//饱和度定义域
//	int histSize[] = { h_bin, s_bin };//定义域指针
//	float h_range[] = { 0, 180 };//色调值域指针
//	float s_range[] = { 0, 256 };//饱和度值域指针
//	const float* histRange[] = { h_range, s_range };//值域二级指针
//	int channels[] = { 0, 1 };//通道指针
//	MatND hist_base, hist_base_copy, hist_test1, hist_test2;//多维直方图
//
//	//计算直方图
//	calcHist(&base, 1, channels, Mat(), hist_base, 2, histSize, histRange);
//	calcHist(&base_copy, 1, channels, Mat(), hist_base_copy, 2, histSize, histRange);
//	calcHist(&test1, 1, channels, Mat(), hist_test1, 2, histSize, histRange);
//	calcHist(&test2, 1, channels, Mat(), hist_test2, 2, histSize, histRange);
//
//	//归一化到0~1
//	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX);
//	normalize(hist_base_copy, hist_base_copy, 0, 1, NORM_MINMAX);
//	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1);
//	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1);
//
//	//直方图比较
//	double basebase_copy = compareHist(hist_base, hist_base_copy, CV_COMP_CORREL);
//	double basetest1 = compareHist(hist_base, hist_test1, CV_COMP_CORREL);
//	double basetest2 = compareHist(hist_base, hist_test2, CV_COMP_CORREL);
//	cout << "比较结果越接近1越相似" << endl;
//	cout << "base-base_copy:" << basebase_copy << endl;
//	cout << "base-test1:" << basetest1 << endl;
//	cout << "base-test2:" << basetest2 << endl;
//	
//	waitKey(0);
//	return 0;
//}