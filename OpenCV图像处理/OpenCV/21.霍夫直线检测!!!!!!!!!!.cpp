//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\building.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src); 
//
//	Mat canny;
//	Canny(src, canny, 150, 300);//边缘检测输出二值图像
//	imshow("canny", canny);
//
//	Mat dst;
//	src.copyTo(dst);
//	
//	vector<Vec4i> lines;//存放检测出的线段矢量集合
//	//二值图 直线 扫描步长 角度步长 阈值 最小直线长 同一行两点之间连线最大距离
//	HoughLinesP(canny, lines, 1, CV_PI / 180, 50, 10, 10);//检测直线
//
//	//绘图
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		Vec4i _line = lines[i];
//		line(dst, Point(_line[0], _line[1]), Point(_line[2], _line[3]), Scalar(0, 0, 255), 1, LINE_AA);//灰度图RGB色彩空间画线
//	}
//	imshow("dst", dst);
//
//
//
//	waitKey(0);
//	return 0;
//}