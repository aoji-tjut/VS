//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat dst, kernel;
//	kernel = (Mat_<int>(2, 2) << 1, 0, -1, 0);
//	filter2D(src, dst, -1, kernel);
//	imshow("robert算子x方向", dst);
//	kernel = (Mat_<int>(2, 2) << 0, 1, -1, 0);
//	filter2D(src, dst, -1, kernel);
//	imshow("robert算子y方向", dst);
//	kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
//	filter2D(src, dst, -1, kernel);
//	imshow("sobel算子x方向", dst);
//	kernel = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
//	filter2D(src, dst, -1, kernel);
//	imshow("sobel算子y方向", dst);
//	kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
//	filter2D(src, dst, -1, kernel);
//	imshow("拉普拉斯算子", dst);
//	kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	filter2D(src, dst, -1, kernel);
//	imshow("锐化算子", dst);
//	
//	//自定义卷积模糊
//	int index = 0;
//	int size = 3;
//	while (1)
//	{
//		if (waitKey(500) == 27)//Esc
//		{
//			break;
//		}
//		size = (index % 5) * 2 + 5;
//		Mat kernel = Mat::ones(Size(size, size), CV_32F) / (float)(size*size);
//		filter2D(src, dst, -1, kernel);
//		index++;
//		imshow("自定义", dst);
//	}
//
//	waitKey(0);
//	return 0;
//}