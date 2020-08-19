//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//RNG rng(time(NULL));
//Mat src, gray, blur,canny, bin, dst_ploy;
//const char* title = "poly";
//int value = 60;
//int max_value = 255;
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
//	cvtColor(src, gray, CV_BGR2GRAY);
//	GaussianBlur(gray, ::blur, Size(5, 5), 0);
//
//	namedWindow(title);
//	createTrackbar("vaule", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	vector<vector<Point>> contours;//轮廓
//	vector<Vec4i> hierarchy;//层次
//
//	src.copyTo(dst_ploy);
//	threshold(::blur, bin, value, max_value, THRESH_BINARY);
//	findContours(bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);//寻找轮廓
//
//	vector<vector<Point>> contours_ploy(contours.size());//外接多边形
//	vector<Rect> ploy_rects(contours.size());//最小矩形
//	vector<Point2f> centers(contours.size());//圆心
//	vector<float> radius(contours.size());//半径
//
//	//寻找多边形
//	for (int i = 0; i < contours.size(); i++)
//	{
//		//轮廓点集  多边形点集  轮廓之间最大距离  是否封闭
//		approxPolyDP(Mat(contours[i]), contours_ploy[i], 3, true);//多边形拟合
//		ploy_rects[i] = boundingRect(contours_ploy[i]);//最小外接矩形
//		//多边形点集  圆心  半径
//		minEnclosingCircle(contours_ploy[i], centers[i], radius[i]);//最小外接圆
//	}
//
//	//绘制多边形
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		rectangle(dst_ploy, ploy_rects[i], color, 1, LINE_AA);
//		circle(dst_ploy, centers[i], radius[i], color, 1, LINE_AA);
//	}
//
//	imshow(title, dst_ploy);
//}