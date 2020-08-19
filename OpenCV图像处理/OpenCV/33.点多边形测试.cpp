//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	//Mat src = Mat::zeros(400, 400, CV_8UC1);
//	//rectangle(src, Point(100, 100), Point(300, 300), Scalar(255), 1, LINE_AA);
//	
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\��Ҷ.JPG");
//	namedWindow("src");
//	moveWindow("src", 0, 0);
//	imshow("src", src);
//
//	cvtColor(src, src, CV_BGR2GRAY);
//	threshold(src, src, 128, 255, THRESH_BINARY);
//
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//	//�����
//	Mat src_dist = Mat::zeros(src.size(), CV_32FC1);
//	for (int row = 0; row < src_dist.rows; row++)
//	{
//		for (int col = 0; col < src_dist.cols; col++)
//		{
//			double dist = pointPolygonTest(contours[1], Point2f(static_cast<float>(col), static_cast<float>(row)), true);
//			//true:����ʵ�ʾ���ֵ��>0�ڲ���<0�ⲿ
//			//false:����1��-1��0��1�ڲ���-1�ⲿ
//			src_dist.at<float>(row, col) = static_cast<float>(dist);
//		}
//	}
//
//	//�������С����ֵ
//	double min_value, max_value;
//	minMaxLoc(src_dist, &min_value, &max_value, 0, 0, Mat());
//
//	//��ͼ
//	Mat dst1 = Mat::zeros(src.size(), CV_8UC3);
//	Mat dst2 = Mat::zeros(src.size(), CV_8UC3);
//	for (int row = 0; row < dst1.rows; row++)
//	{
//		for (int col = 0; col < dst1.cols; col++)
//		{
//			float dist = src_dist.at<float>(row, col);
//			if (dist > 0)//�������
//			{
//				dst1.at<Vec3b>(row, col)[0] = (uchar)(abs(dist / max_value) * 255);//ԽԶԽ��
//				dst2.at<Vec3b>(row, col)[0] = (uchar)(abs(1.0 - (dist / max_value)) * 255);//Խ��Խ��
//			}
//			else if (dist < 0)//�������
//			{
//				dst1.at<Vec3b>(row, col)[2] = (uchar)(abs(dist / min_value) * 255);//ԽԶԽ��
//				dst2.at<Vec3b>(row, col)[2] = (uchar)(abs(1.0 - (dist / min_value)) * 255);//Խ��Խ��
//			}
//			else//������� ��ɫ
//			{
//				dst1.at<Vec3b>(row, col)[0] = (uchar)(abs(255 - dist));
//				dst1.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist));
//				dst1.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist));
//				dst2.at<Vec3b>(row, col)[0] = (uchar)(abs(255 - dist));
//				dst2.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist));
//				dst2.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist));
//			}
//		}
//	}
//
//	imshow("dst1", dst1);
//	imshow("dst2", dst2);
//
//	waitKey(0);
//	return 0;
//}