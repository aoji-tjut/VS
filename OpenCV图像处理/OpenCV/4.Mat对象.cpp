//#include<opencv.hpp>
//#include<Windows.h>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	cout << " src:" << "  " << "ͨ������" << src.channels() << "  " << "���" << src.depth() <<
//		"  " << "������" << src.rows << "  " << "������" << src.cols << endl;
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	//����һ����src��ͬ���Եİ�ɫͼ��
//	Mat dst1 = Mat(src.size(), src.type());
//	dst1 = Scalar(255, 255, 255);//ǿ��������ɫBGR
//	cout << "dst1:" << "  " << "ͨ������" << dst1.channels() << "  " << "���" << dst1.depth() <<
//		"  " << "������" << dst1.rows << "  " << "������" << dst1.cols << endl;
//	namedWindow("dst1", CV_WINDOW_AUTOSIZE);
//	imshow("dst1", dst1);
//	
//	//����һ��src�Ŀ���ͼ��
//	Mat dst2 = src.clone();//clone()==copyto()
//	cout << "dst2:" << "  " << "ͨ������" << dst2.channels() << "  " << "���" << dst2.depth() <<
//		"  " << "������" << dst2.rows << "  " << "������" << dst2.cols << endl;	
//	namedWindow("dst2", CV_WINDOW_AUTOSIZE);
//	imshow("dst2", dst2);
//
//	//����һ����srcת���ĻҶ�ͼ��
//	Mat dst3;
//	cvtColor(src, dst3, CV_RGB2GRAY);
//	cout << "dst3:" << "  " << "ͨ������" << dst3.channels() << "  " << "���" << dst3.depth() <<
//		"  " << "������" << dst3.rows << "  " << "������" << dst3.cols << endl;	
//	namedWindow("dst3", CV_WINDOW_AUTOSIZE);
//	imshow("dst3", dst3);
//
//	//����һ��300*300��8λ��uchar��3ͨ������ɫͼ��
//	Mat dst4(300, 300, CV_8UC3, Scalar(255, 0, 0));//Scalar����������ͨ��������һ��
//	cout << "dst4:" << "  " << "ͨ������" << dst4.channels() << "  " << "���" << dst4.depth() <<
//		"  " << "������" << dst4.rows << "  " << "������" << dst4.cols << endl;
//	namedWindow("dst4", CV_WINDOW_AUTOSIZE);
//	imshow("dst4", dst4);
//
//	//����һ��src�ĸ߶Աȶ�ͼ��
//	Mat dst5;
//	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	filter2D(src, dst5, src.depth(), kernel);
//	cout << "dst5:" << "  " << "ͨ������" << dst5.channels() << "  " << "���" << dst5.depth() <<
//		"  " << "������" << dst5.rows << "  " << "������" << dst5.cols << endl;
//	namedWindow("dst5", CV_WINDOW_AUTOSIZE);
//	imshow("dst5", dst5);
//
//	//cout <<dst5;//���ÿ�����ص�RGBֵ
//
//	waitKey(0);
//	return 0;
//}