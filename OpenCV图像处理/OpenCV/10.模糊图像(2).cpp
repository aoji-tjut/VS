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
//	Mat dst1;
//	medianBlur(src, dst1, 3);//中值滤波 处理椒盐噪声(黑点白点) 保护边缘信息
//	imshow("中值滤波", dst1);
//
//	Mat dst2;
//	bilateralFilter(src, dst2, 10, 100, 3);//双边滤波 美图
//	imshow("双边滤波", dst2);
//
//	Mat dst3;
//	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);//掩膜操作
//	filter2D(dst2, dst3, dst2.depth(), kernel);//增强对比
//	imshow("双边滤波增强对比", dst3);
//
//	waitKey(0);
//	return 0;
//}