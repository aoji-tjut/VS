//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, hsv, hue;
//int size = 90;
//const char* titile = "Back Projection";
//
//void HistBackProjection(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//	
//	cvtColor(src, hsv, CV_BGR2HSV);
//	hue.create(hsv.size(), hsv.depth());//��ȡhsv��hueͨ�� ��Ϊhue�ǵ�ͨ�� ����hsv.depth()����hue.type()
//	int nchannels[] = { 0, 0 };
//	mixChannels(&hsv, 1, &hue, 1, nchannels, 1);
//
//	namedWindow(titile);
//	createTrackbar("Histogram Bins", titile, &size, 180, HistBackProjection);
//	HistBackProjection(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void HistBackProjection(int, void*)
//{
//	float range[] = { 0, 180 };//ɫ����Χ
//	const float* histRange[] = { range };
//	Mat hist;
//	calcHist(&hue, 1, 0, Mat(), hist, 1, &size, histRange);//����ֱ��ͼ
//	normalize(hist, hist, 0, 255, NORM_MINMAX);//��һ��
//
//	Mat back_projection;
//	calcBackProject(&hue, 1, 0, hist, back_projection, histRange);//ֱ��ͼ����ӳ��
//	
//	imshow(titile, back_projection);
//}