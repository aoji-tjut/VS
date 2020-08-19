//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("C:\\Users\\acer\\Desktop\\OpenCV_Src\\海绵宝宝.JPG");
//	if (src.empty())
//	{
//		cout << "不能加载图像" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	vector<Mat> bgr_plans;
//	split(src, bgr_plans);//bgr图像分通道显示
//	
//	Mat b_hist, g_hist, r_hist;//三种颜色通道的直方图
//	int size = 256;//定义域范围0-255
//	int histSize[] = { size };//定义域(x轴)范围指针
//	float range[] = { 0, 256 };//值域(y轴)范围0-255指针
//	const float* histRanges[] = { range };//值域范围二级指针
//	//计算直方图	直方图维数=图像通道数
//	//输入图指针 数目 通道数指针(灰图0) 无掩膜 输出直方图数据 维数 定义域范围指针 值域范围指针的指针 
//	calcHist(&bgr_plans[0], 1, 0, Mat(), b_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[1], 1, 0, Mat(), g_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[2], 1, 0, Mat(), r_hist, 1, histSize, histRanges);
//
//	int hist_heigh = 512;//直方图高度
//	int hist_width = 1024;//直方图宽度
//	int bin_width = hist_width / size;//一个bin宽度是1024/256=4
//	Mat histImage(hist_heigh, hist_width, CV_8UC3, Scalar(0, 0, 0));//建立直方图 高度(cols) 宽度(rows)
//
//	//归一化到0~hist_heigh 
//	normalize(b_hist, b_hist, 0, hist_heigh, NORM_MINMAX);
//	normalize(g_hist, g_hist, 0, hist_heigh, NORM_MINMAX);
//	normalize(r_hist, r_hist, 0, hist_heigh, NORM_MINMAX);
//
//	//绘制直方图
//	for (int i = 1; i < size; i++)
//	{
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(b_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 1, LINE_AA);//蓝
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(g_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 1, LINE_AA);//绿
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(r_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 1, LINE_AA);//红
//	}
//	
//	imshow("直方图", histImage);
//
//	waitKey(0);
//	return 0;
//}