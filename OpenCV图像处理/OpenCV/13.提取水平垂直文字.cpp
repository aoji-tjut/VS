//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\线.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("原图", src);
//
//	Mat gray;
//	cvtColor(src, gray, CV_BGR2GRAY);
//	imshow("灰度图", gray);
//
//	Mat binary;														//15小空心大实心		0负黑正白
//	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);//转换为二值图像
//	imshow("二值图", binary);
//
//	Mat h_line = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1));//水平结构元素
//	Mat v_line = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));//垂直结构元素
//	Mat text = getStructuringElement(MORPH_RECT, Size(7, 7));//去除干扰
//
//	Mat temp;
//	Mat dst1;
//	morphologyEx(binary, dst1, CV_MOP_OPEN, h_line);
//	bitwise_not(dst1, dst1);
//	imshow("水平", dst1);
//
//	Mat dst2;
//	morphologyEx(binary, dst2, CV_MOP_OPEN, v_line);
//	bitwise_not(dst2, dst2);
//	imshow("垂直", dst2);
//
//	Mat dst3;
//	morphologyEx(binary, dst3, CV_MOP_OPEN, text);
//	bitwise_not(dst3, dst3);
//	imshow("文字", dst3);
//
//
//
//	waitKey(0);
//	return 0;
//}