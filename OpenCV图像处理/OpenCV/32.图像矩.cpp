//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, gray, blur, canny, dst;
//const char* title = "图像矩";
//int value = 19;
//int max_value = 255;
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\乱糟糟.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	
//	namedWindow(title);
//	cvtColor(src, gray, CV_BGR2GRAY);
//	GaussianBlur(gray, ::blur, Size(3, 3), 0);
//	createTrackbar("value", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	Canny(::blur, canny, value, value * 2);
//	
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//	vector<Moments> contours_moments(contours.size());//图像矩
//	vector<Point2f> centers(contours.size());//中心
//	//找
//	for (int i = 0; i < contours.size(); i++)
//	{
//		contours_moments[i] = moments(contours[i]);//计算图像矩
//		//计算中心
//		centers[i] = Point(static_cast<float>(contours_moments[i].m10 / contours_moments[i].m00),//x坐标
//			static_cast<float>(contours_moments[i].m01 / contours_moments[i].m00));//y坐标
//	}
//
//	src.copyTo(dst);
//	//画
//	for (int i = 0; i < contours.size(); i++)
//	{
//		//计算区域面积、轮廓弧长
//		printf("contours%d area:%.2f  arc length:%.2f\n",
//			i, contourArea(contours[i]), arcLength(contours[i], true));
//		//计算中心x、y坐标
//		printf("centers point: x=%.2f y=%.2f\n\n", centers[i].x, centers[i].y);
//		//轮廓
//		drawContours(dst, contours, i, Scalar(255, 0, 0));
//		//中心
//		circle(dst, centers[i], 2, Scalar(0, 0, 255), -1, LINE_AA);
//	}
//
//	imshow(title, dst);
//}