//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, temp, dst;
//int type = 0;
//int max_type = 5;
//const char* title = "template match";
//
//void callback(int, void*);
//
//int main()
//{
//	cout << "type=2����" << endl;
//
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//
//	temp = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\ģ��.JPG");
//	imshow("template", temp);
//	
//	namedWindow(title);
//	createTrackbar("match type", title, &type, max_type, callback);
//	callback(0, 0);
//
//
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	int width = src.cols - temp.cols + 1;
//	int heigh = src.rows - temp.rows + 1;
//	Mat result(heigh, width, CV_32FC1);//��ȸ߶����͹̶�
//
//	matchTemplate(src, temp, result, type);//ģ��ƥ��
//	normalize(result, result, 0, 1, NORM_MINMAX);
//
//	Point minloc, maxloc, temploc;
//	double min, max;
//	minMaxLoc(result, &min, &max, &minloc, &maxloc);
//	if (type == CV_TM_SQDIFF || type == CV_TM_SQDIFF_NORMED)//����������⴦��
//	{
//		temploc = minloc;
//	}
//	else
//	{
//		temploc = maxloc;
//	}
//
//	src.copyTo(dst);
//	rectangle(result, Rect(temploc.x, temploc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, LINE_AA);
//	rectangle(dst, Rect(temploc.x, temploc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, LINE_AA);
//
//	imshow(title, result);
//	imshow("dst", dst);
//}