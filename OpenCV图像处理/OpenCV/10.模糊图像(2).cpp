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
//	medianBlur(src, dst1, 3);//��ֵ�˲� ����������(�ڵ�׵�) ������Ե��Ϣ
//	imshow("��ֵ�˲�", dst1);
//
//	Mat dst2;
//	bilateralFilter(src, dst2, 10, 100, 3);//˫���˲� ��ͼ
//	imshow("˫���˲�", dst2);
//
//	Mat dst3;
//	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);//��Ĥ����
//	filter2D(dst2, dst3, dst2.depth(), kernel);//��ǿ�Ա�
//	imshow("˫���˲���ǿ�Ա�", dst3);
//
//	waitKey(0);
//	return 0;
//}