//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//void change();
//void callback(int, void*);
//
//Mat src;
//Mat dst;
//int alpha = 0;//�Աȶ�
//int beta = 0;//����
//int rows;
//int cols;
//const char* title = "�Աȶ����ȵ���";
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
//	rows = src.rows;
//	cols = src.cols;
//
//	dst = Mat::zeros(src.size(), src.type());//����һ����src��С������ͬ�Ŀհ�ͼ��
//
//	namedWindow(title, CV_WINDOW_AUTOSIZE);
//	createTrackbar("�Աȶȣ�", title, &alpha, 50,callback);
//	createTrackbar("���ȣ�", title, &beta, 100, callback);
//	callback(0, 0);
//
//	//convertScaleAbs��Mat::convertTo
//
//	waitKey(0);
//	return 0;
//}
//
//void change()
//{
//	float alpha = ::alpha * 1.0 / 10;
//
//	for (int row = 0; row < rows; row++)
//	{
//		for (int col = 0; col < cols; col++)
//		{
//			if (src.channels() == 1)
//			{
//				float gray = src.at<uchar>(row, col);
//				dst.at<uchar>(row, col) = saturate_cast<uchar>(gray*alpha + beta);
//				//saturate_cast��ֹ�����������֤��0-255
//			}
//			else if (src.channels() == 3)
//			{
//				float b = src.at<Vec3b>(row, col)[0];
//				float g = src.at<Vec3b>(row, col)[1];
//				float r = src.at<Vec3b>(row, col)[2];
//				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
//				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
//				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
//			}
//		}
//	}
//}
//
//void callback(int, void*)
//{
//	change();
//	imshow(title, dst);
//}
