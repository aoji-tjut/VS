//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\���౦��.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//�õ�һ����״
//
//	Mat dst1;
//	dilate(src, dst1, element);//���� ���Ӱ׼��ٺ�
//	imshow("����", dst1);
//
//	Mat dst2;
//	erode(src, dst2, element);//��ʴ ���Ӻڼ��ٰ�
//	imshow("��ʴ", dst2);
//
//	Mat dst3;
//	addWeighted(dst1, 0.5, dst2, 0.5, 0.0, dst3);
//	imshow("���", dst3);
//
//	waitKey(0);
//	return 0;
//}