//#include<opencv.hpp>
//#include<iostream>
//#include<ctime>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\ֽ��.JPG");
//	namedWindow("��src");
//	moveWindow("��src", 0, 0);
//	imshow("��src", src);
//
//	//���������
//	Mat black = src.clone();
//	for (int row = 0; row < black.rows; row++)
//	{
//		for (int col = 0; col < black.cols; col++)
//		{
//			if (black.at<Vec3b>(row, col) == Vec3b(255, 255, 255))
//			{
//				black.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
//			}
//		}
//	}
//	imshow("��black", black);
//
//	//��
//	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
//	Mat laplace, sharpen;
//	filter2D(black, laplace, CV_32F, kernel);
//	black.convertTo(black, CV_32F);
//	sharpen = black - laplace;
//	laplace.convertTo(laplace, CV_8UC3);
//	sharpen.convertTo(sharpen, CV_8UC3);
//	imshow("��sharpen", sharpen);
//
//	//��ֵ��
//	Mat gray, bin;
//	cvtColor(sharpen, gray, CV_BGR2GRAY);
//	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
//	imshow("��bin", bin);
//
//	//����任+��һ��
//	Mat dist;
//	distanceTransform(bin, dist, DIST_L1, 3);//��ȡ��������
//	normalize(dist, dist, 0, 1, NORM_MINMAX);
//	imshow("��dist", dist);
//
//	//��ֵ��
//	Mat dist_bin;
//	threshold(dist, dist_bin, 0.3, 1, THRESH_BINARY);
//	imshow("��dist_bin", dist_bin);
//
//	//��ʴ
//	Mat erode;
//	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
//	cv::erode(dist_bin, erode, element);
//	imshow("��erode", erode);
//
//	//������
//	Mat erode_8u;
//	erode.convertTo(erode_8u, CV_8U);
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(erode_8u, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//Ѱ�����������
//	
//	//���
//	RNG rng(time(NULL));
//	Mat marker = Mat::zeros(src.size(), CV_32SC1);//CV_32SC1�Ƿ�ˮ��任Ҫ���type
//	for (int i = 0; i < contours.size(); i++)
//	{
//		drawContours(marker, contours, i, Scalar(i+1), -1);//������ɫ��0,ʹ��ɫ��i+1��ʼ�������ɫ
//	}
//	circle(marker, Point(1, 1), 1, Scalar(255), -1);//�ֳ�����
//	imshow("��marker", marker*1000);
//
//	//��ˮ��任
//	watershed(src, marker);
//	Mat watershed = Mat::zeros(marker.size(), CV_8UC1);
//	marker.convertTo(watershed, CV_8UC1);
//	imshow("��watershed", watershed);
//
//	//��ɫ��ʾ ������ֽ����ɫ
//	Mat dst_color = Mat::zeros(src.size(), CV_8UC3);
//	for (int i = 0; i < contours.size(); i++)
//	{
//		int b = rng.uniform(0, 256);
//		int g = rng.uniform(0, 256);
//		int r = rng.uniform(0, 256);
//		for (int row = 0; row < watershed.rows; row++)
//		{
//			for (int col = 0; col < watershed.cols; col++)
//			{
//				if (watershed.at<uchar>(row, col) == i + 1)//֮ǰ��ɫ��1��ʼ������Ҳ��1�ж�
//				{
//					dst_color.at<Vec3b>(row, col) = Vec3b(b, g, r);
//				}
//
//				if (watershed.at<uchar>(row, col) == 255)
//				{
//					dst_color.at<Vec3b>(row, col) = Vec3b(255, 255, 255);
//				}
//			}
//		}
//	}
//	imshow("��dst_color", dst_color);
//	
//	waitKey(0);
//	return 0;
//}