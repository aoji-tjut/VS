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
//	createTrackbar("负差最大值", title, &loDiff, loDiff_max, Fill);
//	createTrackbar("正差最大值", title, &upDiff, upDiff_max, Fill);
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
//	addWeighted(src1, 0.5, src2, 0.5, 0.0, dst);//图像混合必须大小相同
//	imshow("add", dst);
//}
//
//void RoiAdd()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\tower.JPG");
//	Mat hand = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\模板.JPG");
//	Mat roi = src(Rect(0, 0, hand.cols, hand.rows));//局部操作范围
//	addWeighted(roi, 1.0, hand, 0.5, 0.0, roi);
//	imshow("roi", src);
//}
//
//void BlueChannelRoiAdd()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\girl.JPG");
//	Mat logo = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\logo.JPG");
//	vector<Mat> src_channel, logo_channel;
//	split(src, src_channel);//分离src通道
//	split(logo, logo_channel);//分离logo通道
//	Mat src_blue = src_channel.at(0);//提取src蓝色通道
//	Mat logo_blue = logo_channel.at(0);//提取logo蓝色通道
//	Mat roi = src_blue(Rect(0, 0, logo_blue.cols, logo_blue.rows));//设置roi区域为src蓝色通道的左上角logo大小
//	addWeighted(roi, 1.0, logo_blue, 0.5, 0.0, roi);//要求两个目标图像通道数相同
//
//	merge(src_channel, src);//合并通道
//	imshow("roi_bule", src);
//}
//
//void Fill(int, void*)
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\girl.JPG");
//	Mat mask;
//	mask.zeros(src.rows + 2, src.cols + 2, CV_8UC1);//mask必须大2像素8位单通道
//	//目标图像 掩膜 起点 填充颜色 最小边界矩形 最低像素 最高像素
//	floodFill(src, mask, Point(src.cols / 2, src.rows / 2), Scalar(0, 255, 255), 0,
//		Scalar(loDiff, loDiff, loDiff), Scalar(upDiff, upDiff, upDiff), FLOODFILL_FIXED_RANGE);
//	imshow(title, src);
//}