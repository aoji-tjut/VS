//#include<opencv.hpp>
//#include<iostream>
//#include<time.h>
//using namespace std;
//using namespace cv;
//
//RNG rng(time(NULL));
//Mat src, gray, blur,canny, bin, dst_ploy;
//const char* title = "poly";
//int value = 60;
//int max_value = 255;
//
//void callback(int, void*);
//
//int main()
//{
//	src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\������.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//	
//	cvtColor(src, gray, CV_BGR2GRAY);
//	GaussianBlur(gray, ::blur, Size(5, 5), 0);
//
//	namedWindow(title);
//	createTrackbar("vaule", title, &value, max_value, callback);
//	callback(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void callback(int, void*)
//{
//	vector<vector<Point>> contours;//����
//	vector<Vec4i> hierarchy;//���
//
//	src.copyTo(dst_ploy);
//	threshold(::blur, bin, value, max_value, THRESH_BINARY);
//	findContours(bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);//Ѱ������
//
//	vector<vector<Point>> contours_ploy(contours.size());//��Ӷ����
//	vector<Rect> ploy_rects(contours.size());//��С����
//	vector<Point2f> centers(contours.size());//Բ��
//	vector<float> radius(contours.size());//�뾶
//
//	//Ѱ�Ҷ����
//	for (int i = 0; i < contours.size(); i++)
//	{
//		//�����㼯  ����ε㼯  ����֮��������  �Ƿ���
//		approxPolyDP(Mat(contours[i]), contours_ploy[i], 3, true);//��������
//		ploy_rects[i] = boundingRect(contours_ploy[i]);//��С��Ӿ���
//		//����ε㼯  Բ��  �뾶
//		minEnclosingCircle(contours_ploy[i], centers[i], radius[i]);//��С���Բ
//	}
//
//	//���ƶ����
//	for (int i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
//		rectangle(dst_ploy, ploy_rects[i], color, 1, LINE_AA);
//		circle(dst_ploy, centers[i], radius[i], color, 1, LINE_AA);
//	}
//
//	imshow(title, dst_ploy);
//}