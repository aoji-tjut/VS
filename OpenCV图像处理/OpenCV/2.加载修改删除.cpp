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
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	
//	namedWindow("dog_RGB", CV_WINDOW_AUTOSIZE);
//	imshow("dog_RGB", src);
//	
//	namedWindow("dog_GRAY", CV_WINDOW_AUTOSIZE);
//	cvtColor(src, dst, CV_RGB2GRAY);//��ɫת����RGB->GRAY
//	imshow("dog_GRAY", dst);
//
//	//Mat dst2;
//	//src.convertTo(dst2, CV_32F);//ת��Ϊ32λ������	CV_(λ��)+(��������)+(ͨ����)
//
//	imwrite("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog_gray.JPG", dst);//����ͼƬ
//
//	waitKey(0);
//	return 0;
//}