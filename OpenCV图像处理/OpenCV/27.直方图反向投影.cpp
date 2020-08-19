//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, hsv, hue;
//int size = 90;
//const char* titile = "Back Projection";
//
//void HistBackProjection(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//	
//	cvtColor(src, hsv, CV_BGR2HSV);
//	hue.create(hsv.size(), hsv.depth());//获取hsv的hue通道 因为hue是单通道 所以hsv.depth()就是hue.type()
//	int nchannels[] = { 0, 0 };
//	mixChannels(&hsv, 1, &hue, 1, nchannels, 1);
//
//	namedWindow(titile);
//	createTrackbar("Histogram Bins", titile, &size, 180, HistBackProjection);
//	HistBackProjection(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void HistBackProjection(int, void*)
//{
//	float range[] = { 0, 180 };//色调范围
//	const float* histRange[] = { range };
//	Mat hist;
//	calcHist(&hue, 1, 0, Mat(), hist, 1, &size, histRange);//计算直方图
//	normalize(hist, hist, 0, 255, NORM_MINMAX);//归一化
//
//	Mat back_projection;
//	calcBackProject(&hue, 1, 0, hist, back_projection, histRange);//直方图反向映射
//	
//	imshow(titile, back_projection);
//}