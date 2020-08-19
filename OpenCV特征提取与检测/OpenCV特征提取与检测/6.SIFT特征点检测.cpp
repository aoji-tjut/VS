//#include<iostream>
//#include<opencv.hpp>
//#include<xfeatures2d.hpp>
//
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//Mat src, dst;
//int value = 500;
//int max_value = 5000;
//const char* title = "SIFT特征点检测";
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("image\\热气球.JPG");
//	namedWindow(title);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	Ptr<SIFT> detector = SIFT::create(value);
//	vector<KeyPoint> keypoints;
//	detector->detect(src, keypoints);
//	Mat dst = src.clone();
//	drawKeypoints(src, keypoints, dst);
//	imshow("SIFT特征点检测", dst);
//}