//#include<opencv.hpp>
//#include<Windows.h>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	cout << " src:" << "  " << "通道数：" << src.channels() << "  " << "深度" << src.depth() <<
//		"  " << "行数：" << src.rows << "  " << "列数：" << src.cols << endl;
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	//创建一个与src相同属性的白色图像
//	Mat dst1 = Mat(src.size(), src.type());
//	dst1 = Scalar(255, 255, 255);//强行设置颜色BGR
//	cout << "dst1:" << "  " << "通道数：" << dst1.channels() << "  " << "深度" << dst1.depth() <<
//		"  " << "行数：" << dst1.rows << "  " << "列数：" << dst1.cols << endl;
//	namedWindow("dst1", CV_WINDOW_AUTOSIZE);
//	imshow("dst1", dst1);
//	
//	//创建一个src的拷贝图像
//	Mat dst2 = src.clone();//clone()==copyto()
//	cout << "dst2:" << "  " << "通道数：" << dst2.channels() << "  " << "深度" << dst2.depth() <<
//		"  " << "行数：" << dst2.rows << "  " << "列数：" << dst2.cols << endl;	
//	namedWindow("dst2", CV_WINDOW_AUTOSIZE);
//	imshow("dst2", dst2);
//
//	//创建一个由src转换的灰度图像
//	Mat dst3;
//	cvtColor(src, dst3, CV_RGB2GRAY);
//	cout << "dst3:" << "  " << "通道数：" << dst3.channels() << "  " << "深度" << dst3.depth() <<
//		"  " << "行数：" << dst3.rows << "  " << "列数：" << dst3.cols << endl;	
//	namedWindow("dst3", CV_WINDOW_AUTOSIZE);
//	imshow("dst3", dst3);
//
//	//创建一个300*300、8位、uchar、3通道、蓝色图像
//	Mat dst4(300, 300, CV_8UC3, Scalar(255, 0, 0));//Scalar参数个数与通道数保持一致
//	cout << "dst4:" << "  " << "通道数：" << dst4.channels() << "  " << "深度" << dst4.depth() <<
//		"  " << "行数：" << dst4.rows << "  " << "列数：" << dst4.cols << endl;
//	namedWindow("dst4", CV_WINDOW_AUTOSIZE);
//	imshow("dst4", dst4);
//
//	//创建一个src的高对比度图像
//	Mat dst5;
//	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	filter2D(src, dst5, src.depth(), kernel);
//	cout << "dst5:" << "  " << "通道数：" << dst5.channels() << "  " << "深度" << dst5.depth() <<
//		"  " << "行数：" << dst5.rows << "  " << "列数：" << dst5.cols << endl;
//	namedWindow("dst5", CV_WINDOW_AUTOSIZE);
//	imshow("dst5", dst5);
//
//	//cout <<dst5;//输出每个像素的RGB值
//
//	waitKey(0);
//	return 0;
//}