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
//	Mat dst;
//	GaussianBlur(src, dst, Size(3, 3), 0);
//
//	Mat gray;
//	cvtColor(dst, gray, CV_BGR2GRAY);
//
//	Mat grad_x, grad_y;
//	//经典算法
//	Sobel(gray, grad_x, -1, 1, 0);//x方向1阶导
//	Sobel(gray, grad_y, -1, 0, 1);//y方向1阶导
//	//加强算法
//	//Scharr(gray, grad_x, -1, 1, 0);//x方向1阶导
//	//Scharr(gray, grad_y, -1, 0, 1);//y方向1阶导
//	//取绝对值
//	convertScaleAbs(grad_x, grad_x);
//	convertScaleAbs(grad_y, grad_y);
//
//	imshow("X方向梯度", grad_x);
//	imshow("Y方向梯度", grad_y);
//
//	addWeighted(grad_x, 0.5, grad_y, 0.5, 0.0, dst);
//	imshow("梯度混合", dst);
//
//
//	waitKey(0);
//	return 0;
//}