//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, gray;
//const char* title = "Tomasi�ǵ���";
//int value = 80;
//int max_value = 255;
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("image\\house.JPG");
//	cvtColor(src, gray, CV_BGR2GRAY);
//
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
//	if (value <= 1)
//	{
//		value = 1;
//	}
//
//	Mat dst = src.clone();
//	vector<Point2f> corners;//��Žǵ�
//	//�Ҷ�ͼ �ǵ� �ǵ�������� ��С����ֵ �ǵ�֮����С����
//	goodFeaturesToTrack(gray, corners, value, 0.01, 10);
//	for (int i = 0; i < corners.size(); i++)
//	{
//		circle(dst, corners[i], 2, Scalar(0, 0, 255), -1, LINE_AA);
//	}
//
//	imshow(title, dst);
//}