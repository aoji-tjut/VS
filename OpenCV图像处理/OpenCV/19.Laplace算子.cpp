//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat blur;
//	GaussianBlur(src, blur, Size(3, 3), 0.0);
//
//	Mat gray;
//	cvtColor(blur, gray, CV_BGR2GRAY);
//
//	Mat dst;
//	Laplacian(gray, dst, CV_16S);//拉普帕斯
//	convertScaleAbs(dst, dst);//取绝对值
//	imshow("拉普拉斯算子", dst);
//
//	waitKey(0);
//	return 0;
//}