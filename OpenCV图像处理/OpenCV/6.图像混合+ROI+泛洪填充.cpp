//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int loDiff = 0;
//int upDiff = 0;
//int loDiff_max = 255;
//int upDiff_max = 255;
//const char* title = "FloodFill";
//
//void Add();
//void RoiAdd();
//void BlueChannelRoiAdd();
//void Fill(int, void*);
//void callback(int, void*);
//
//int main()
//{
//	Add();
//	RoiAdd();
//	BlueChannelRoiAdd();
//	namedWindow(title);
//	createTrackbar("�������ֵ", title, &loDiff, loDiff_max, Fill);
//	createTrackbar("�������ֵ", title, &upDiff, upDiff_max, Fill);
//	Fill(0,0);
//
//	waitKey(0);
//	return 0;
//}
//
//void Add()
//{
//	Mat src1 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\dog.JPG");
//	Mat src2 = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\night.JPG");
//	Mat dst;
//	addWeighted(src1, 0.5, src2, 0.5, 0.0, dst);//ͼ���ϱ����С��ͬ
//	imshow("add", dst);
//}
//
//void RoiAdd()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\tower.JPG");
//	Mat hand = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\ģ��.JPG");
//	Mat roi = src(Rect(0, 0, hand.cols, hand.rows));//�ֲ�������Χ
//	addWeighted(roi, 1.0, hand, 0.5, 0.0, roi);
//	imshow("roi", src);
//}
//
//void BlueChannelRoiAdd()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\girl.JPG");
//	Mat logo = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\logo.JPG");
//	vector<Mat> src_channel, logo_channel;
//	split(src, src_channel);//����srcͨ��
//	split(logo, logo_channel);//����logoͨ��
//	Mat src_blue = src_channel.at(0);//��ȡsrc��ɫͨ��
//	Mat logo_blue = logo_channel.at(0);//��ȡlogo��ɫͨ��
//	Mat roi = src_blue(Rect(0, 0, logo_blue.cols, logo_blue.rows));//����roi����Ϊsrc��ɫͨ�������Ͻ�logo��С
//	addWeighted(roi, 1.0, logo_blue, 0.5, 0.0, roi);//Ҫ������Ŀ��ͼ��ͨ������ͬ
//
//	merge(src_channel, src);//�ϲ�ͨ��
//	imshow("roi_bule", src);
//}
//
//void Fill(int, void*)
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\girl.JPG");
//	Mat mask;
//	mask.zeros(src.rows + 2, src.cols + 2, CV_8UC1);//mask�����2����8λ��ͨ��
//	//Ŀ��ͼ�� ��Ĥ ��� �����ɫ ��С�߽���� ������� �������
//	floodFill(src, mask, Point(src.cols / 2, src.rows / 2), Scalar(0, 255, 255), 0,
//		Scalar(loDiff, loDiff, loDiff), Scalar(upDiff, upDiff, upDiff), FLOODFILL_FIXED_RANGE);
//	imshow(title, src);
//}