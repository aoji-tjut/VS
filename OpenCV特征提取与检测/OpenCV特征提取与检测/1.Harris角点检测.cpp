//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, gray;
//const char* title = "Harris角点检测";
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
//	Mat harris, norm, scale, dst;
//	harris = Mat::zeros(src.size(), CV_32FC1);//CV_32FC1为固定类型
//
//	//灰度 输出 邻域大小 Sobel孔径大小  Harris参数
//	cornerHarris(gray, harris, 2, 3, 0.04);
//	normalize(harris, norm, 0, 255, NORM_MINMAX);
//	convertScaleAbs(norm, scale);//取绝对值 转到CV_8U
//	
//	dst = src.clone();
//	for (int row = 0; row < scale.rows; row++)
//	{
//		for (int col = 0; col < scale.cols; col++)
//		{
//			if (scale.at<uchar>(row, col) > value)
//			{
//				circle(dst, Point(col, row), 2, Scalar(0, 0, 255), 1, LINE_AA);
//			}
//		}
//	}
//
//	imshow(title, dst);
//}