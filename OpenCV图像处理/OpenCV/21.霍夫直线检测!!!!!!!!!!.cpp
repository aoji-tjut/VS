//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\building.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src); 
//
//	Mat canny;
//	Canny(src, canny, 150, 300);//��Ե��������ֵͼ��
//	imshow("canny", canny);
//
//	Mat dst;
//	src.copyTo(dst);
//	
//	vector<Vec4i> lines;//��ż������߶�ʸ������
//	//��ֵͼ ֱ�� ɨ�貽�� �ǶȲ��� ��ֵ ��Сֱ�߳� ͬһ������֮������������
//	HoughLinesP(canny, lines, 1, CV_PI / 180, 50, 10, 10);//���ֱ��
//
//	//��ͼ
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		Vec4i _line = lines[i];
//		line(dst, Point(_line[0], _line[1]), Point(_line[2], _line[3]), Scalar(0, 0, 255), 1, LINE_AA);//�Ҷ�ͼRGBɫ�ʿռ仭��
//	}
//	imshow("dst", dst);
//
//
//
//	waitKey(0);
//	return 0;
//}