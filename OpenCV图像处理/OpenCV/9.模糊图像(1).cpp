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
//	Mat dst1;
//	blur(src, dst1, Size(3, 3));//��ֵ�˲���� �ƻ�ͼ��ϸ��		Size(x����,y����) x,yΪ����
//	imshow("��ֵ�˲�", dst1);
//
//	Mat dst2;
//	GaussianBlur(src, dst2, Size(3, 3), 0, 0);//��˹�˲����ã� ������˹����̬�ֲ�������
//	imshow("��˹�˲�", dst2);
//
//	waitKey(0);
//	return 0;
//}