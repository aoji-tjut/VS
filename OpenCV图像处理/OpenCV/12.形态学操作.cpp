//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src1 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\开操作.JPG");
//	if (src1.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src1", CV_WINDOW_AUTOSIZE);
//	imshow("src1", src1);
//
//	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15)); 
//	Mat kernel_grad = getStructuringElement(MORPH_RECT, Size(3, 3));
//
//	Mat dst1;
//	morphologyEx(src1, dst1, CV_MOP_OPEN, kernel);//开操作 先腐蚀后膨胀 去除白点
//	imshow("开操作", dst1);
//
//	Mat src2 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\闭操作.JPG");
//	if (src2.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	imshow("src2", src2);
//
//	Mat dst2;
//	morphologyEx(src2, dst2, CV_MOP_CLOSE, kernel);//闭操作 先膨胀后腐蚀 去除黑点
//	imshow("闭操作", dst2);
//
//	Mat src3 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//	if (src3.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	imshow("src3", src3);
//
//	Mat dst3;
//	morphologyEx(src3, dst3, CV_MOP_GRADIENT, kernel_grad);//形态学梯度 膨胀减腐蚀 得到轮廓线
//	imshow("梯度", dst3);
//
//	Mat dst4;
//	morphologyEx(src1, dst4, CV_MOP_TOPHAT, kernel);//顶帽 原图-开运算 分离亮点
//	imshow("顶帽", dst4);
//
//	Mat dst5;
//	morphologyEx(src2, dst5, CV_MOP_BLACKHAT, kernel);//黑帽 闭运算-原图 分离暗点
//	imshow("黑帽", dst5);
//
//	waitKey(0);
//	return 0;
//}