#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("image\\board.JPG");
	if (src.empty())
	{
		cout << "不能加载图像" << endl;
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

	Mat blur,gray;
	GaussianBlur(src, blur, Size(9, 9), 0);
	cvtColor(blur, gray, CV_BGR2GRAY);
	
	Mat dst;
	src.copyTo(dst);

	vector<Vec3f> circles;//存放检测出的圆矢量集合
	//灰图 圆 固定方法 1原图 最短圆心距 canny高阈值 阈值(圆要求) 最小半径 最大半径
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 10, 200, 20, 10, 30);//检测圆

	//绘图
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));//圆心
		int radius = cvRound(circles[i][2]);//半径
		//把检测出的圆在dst上显示出来
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);//圆
		circle(dst, center, 1, Scalar(0, 255, 0), 2, LINE_AA);//圆心
	}
	imshow("dst", dst);



	waitKey(0);
	return 0;
}