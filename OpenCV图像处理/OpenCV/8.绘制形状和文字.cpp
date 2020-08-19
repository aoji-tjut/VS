//#include<opencv.hpp>
//#include<time.h>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void MyLine();
//void MyRect();
//void MyEllipse();
//void MyCircle();
//void MyText();
//void RandomLine();
//
//Mat src1 = Mat(500, 500, CV_8UC3, Scalar(0, 0, 0));
//Mat src2 = Mat(500, 500, CV_8UC3, Scalar(0, 0, 0));
//
//int main()
//{
//	MyLine();
//	MyRect();
//	MyEllipse();
//	MyCircle();
//	MyText();
//	namedWindow("src1", CV_WINDOW_AUTOSIZE);
//	imshow("src1", src1);
//	RandomLine();
//
//
//
//	waitKey(0);
//	return 0;
//}
//
//void MyLine()
//{
//	Point p1 = Point(0, 0);
//	Point p2 = Point(510, 510);
//	Point p3 = Point(510, 0);
//	Point p4 = Point(0, 510);
//	Scalar color = Scalar(0, 0, 255);
//	line(src1, p1, p2, color, 5);
//	line(src1, p3, p4, color, 5);
//}
//
//void MyRect()
//{
//	Rect rect = Rect(src1.cols / 4, src1.rows / 4, src1.cols / 2, src1.rows / 2);
//	Scalar color = Scalar(0, 255, 0);
//	rectangle(src1, rect, color, 5);
//}
//
//void MyEllipse()
//{
//				 //中心								//长轴短轴						//角度90//弧度0-360
//	ellipse(src1, Point(src1.cols / 2, src1.rows / 2), Size(src1.cols / 8, src1.rows / 4), 90, 0, 360, Scalar(255, 0, 0), 5);
//}
//
//void MyCircle()
//{
//	circle(src1, Point(src1.cols / 2, src1.rows / 2), src1.rows / 4, Scalar(0, 255, 255), 5);
//}
//
//void MyText()
//{
//	putText(src1, "Hello OpenCV", Point(150,260), CV_FONT_NORMAL, 1.0, Scalar(255, 255, 0), 2);
//}
//
//void RandomLine()
//{
//	RNG rng(time(NULL));
//	Point p1, p2;
//	namedWindow("src1", CV_WINDOW_AUTOSIZE);
//	while (1)
//	{
//		if (waitKey(50) > 0)
//			break;
//		p1.x = rng.uniform(0, src2.cols);
//		p1.y = rng.uniform(0, src2.rows);
//		p2.x = rng.uniform(0, src2.cols);
//		p2.y = rng.uniform(0, src2.rows);
//		Scalar color = Scalar(rng.uniform(0, 256),rng.uniform(0, 256),rng.uniform(0, 256));
//		line(src2, p1, p2, color, 2, LINE_AA);
//		imshow("src2", src2);
//	}
//}