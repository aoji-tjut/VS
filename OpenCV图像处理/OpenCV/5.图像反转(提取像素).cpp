//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	//Mat dst1;
//	//int rows, cols, row, col;
//	//int channels1, channels2;
//	//cvtColor(src, dst1, CV_RGB2GRAY);
//	//namedWindow("dst1", CV_WINDOW_AUTOSIZE);
//	//imshow("dst1", dst1);
//	//rows = dst1.rows;
//	//cols = dst1.cols;
//	//channels1 = dst1.channels();
//
//
//	//Mat dst2;
//	//src.copyTo(dst2);
//	//namedWindow("dst2", CV_WINDOW_AUTOSIZE);
//	//imshow("dst2", dst2);
//	//rows = dst2.rows;
//	//cols = dst2.cols;
//	//channels2 = dst2.channels();
//	//for (row = 0; row < rows; row++)
//	//{
//	//	for (col = 0; col < cols; col++)
//	//	{
//	//		if (channels1 == 1)//��ɫ��ͨ��
//	//		{
//	//			int gray = dst1.at<uchar>(row, col);//��ͨ��ȡ������ֵuchar
//	//			dst1.at<uchar>(row, col) = 255 - gray;//���ط�ת
//	//		}
//	//		if (channels2 == 3)//RGB��ͨ��
//	//		{
//	//			//��ͨ����ȡ����ֵVec3b
//	//			int b = dst2.at<Vec3b>(row, col)[0];
//	//			int g = dst2.at<Vec3b>(row, col)[1];
//	//			int r = dst2.at<Vec3b>(row, col)[2];
//	//			//���ط�ת
//	//			dst2.at<Vec3b>(row, col)[0] = 255 - b;
//	//			dst2.at<Vec3b>(row, col)[1] = 255 - g;
//	//			dst2.at<Vec3b>(row, col)[2] = 255 - r;
//	//		}
//	//	}
//	//}
//	//namedWindow("dst1_��ת", CV_WINDOW_AUTOSIZE);
//	//imshow("dst1_��ת", dst1);
//	//namedWindow("dst2_��ת", CV_WINDOW_AUTOSIZE);
//	//imshow("dst2_��ת", dst2);
//
//	Mat dst;
//	bitwise_not(src, dst);//dstΪsrc���ط�ת���ͼ��
//	namedWindow("dst", CV_WINDOW_AUTOSIZE);
//	imshow("dst", dst);//~dst
//
//
//
//
//
//
//
//	waitKey(0);
//	return 0;
//}