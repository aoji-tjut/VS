//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, gray, blur, bin, dst;
//const char* title = "汽车识别";
//int value = 50;
//int max_value = 255;
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\汽车.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	
//	cvtColor(src, gray, CV_BGR2GRAY);
//	GaussianBlur(gray, ::blur, Size(3, 3), 0);
//
//	namedWindow(title);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//
//	src.copyTo(dst);
//	threshold(::blur, bin, value, max_value, THRESH_BINARY);
//	Mat element = getStructuringElement(MORPH_RECT, Size(9, 9));
//	morphologyEx(bin, bin, CV_MOP_OPEN, element);
//	imshow("bin", bin);
//
//	findContours(bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//	vector<vector<Point>> ploy(contours.size());
//	vector<Rect> rect(contours.size());
//
//	for (int i = 0; i < contours.size(); i++)
//	{
//		approxPolyDP(Mat(contours[i]), ploy[i], 3, true);
//		rect[i] = boundingRect(ploy[i]);
//	}
//	for (int i = 0; i < contours.size(); i++)
//	{
//		rectangle(dst, rect[i], Scalar(0,0,255), 2, LINE_AA);
//	}
//
//	imshow(title, dst);
//}