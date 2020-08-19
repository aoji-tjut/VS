//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	Mat dst;
//
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	
//	namedWindow("dog_RGB", CV_WINDOW_AUTOSIZE);
//	imshow("dog_RGB", src);
//	
//	namedWindow("dog_GRAY", CV_WINDOW_AUTOSIZE);
//	cvtColor(src, dst, CV_RGB2GRAY);//颜色转换，RGB->GRAY
//	imshow("dog_GRAY", dst);
//
//	//Mat dst2;
//	//src.convertTo(dst2, CV_32F);//转换为32位浮点型	CV_(位数)+(数据类型)+(通道数)
//
//	imwrite("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog_gray.JPG", dst);//保存图片
//
//	waitKey(0);
//	return 0;
//}