//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat kernel;
//Mat src, gray, canny, dst;
//int image = 0;
//int max_image = 5;
//int size = 0;
//int max_size = 50;
//int morphology = 0;
//int max_morphology = 6;
//int blur = 0;
//int max_blur = 3;
//const char* title_operator = "Operator";
//vector<vector<Point>> contours;
//vector<Vec4i> hierarchy;
//int contour = 128;
//int max_contour = 255;
//
//void callback(int, void*);
//void Image();
//void Kernel();
//void Morphology();
//void Hist();
//void Blur();
//void Contour();
//
//int main()
//{
//	cout << "* * * * * OpenCV：" << CV_VERSION << " * * * * *" << endl;
//	cout << "*           Morphology          *" << endl;
//	cout << "*             0腐蚀             *" << endl;
//	cout << "*             1膨胀             *" << endl;
//	cout << "*              2开              *" << endl;          
//	cout << "*              3闭              *" << endl;
//	cout << "*             4梯度             *" << endl;
//	cout << "*             5顶帽             *" << endl;
//	cout << "*             6黑帽             *" << endl;
//	cout << "* * * * * * * * * * * * * * * * *" << endl;
//	cout << "*              Blur             *" << endl;
//	cout << "*           0均值滤波           *" << endl;
//	cout << "*           1高斯滤波           *" << endl;
//	cout << "*           2中值滤波           *" << endl;
//	cout << "*           3双边滤波           *" << endl;
//	cout << "* * * * * * * * * * * * * * * * *" << endl;
//
//	namedWindow(title_operator);
//	createTrackbar("Image", title_operator, &image, max_image, callback);
//	createTrackbar("Size", title_operator, &size, max_size, callback);
//	createTrackbar("Morphology", title_operator, &morphology, max_morphology, callback);
//	createTrackbar("Blur", title_operator, &::blur, max_blur, callback);
//	createTrackbar("Contour", title_operator, &::contour, max_contour, callback);
//	callback(0, 0);
//	moveWindow(title_operator, 0, 0);
//
//	waitKey(0);
//	return 0; 
//}
//
//void callback(int, void*)
//{
//	Image();
//	Kernel();
//	Morphology();
//	Hist();
//	Blur();
//	Contour();
//}
//
//void Image()
//{
//	switch (image)
//	{
//	case 0:src = imread("image\\dog.JPG");
//		break;
//	case 1:src = imread("image\\night.JPG");
//		break;
//	case 2:src = imread("image\\man.JPG");
//		break;
//	case 3:src = imread("image\\线.JPG");
//		break;
//	case 4:src = imread("image\\乱糟糟.JPG");
//		break;
//	case 5:src = imread("image\\热气球.JPG");
//		break;
//	}
//}
//
//void Kernel()
//{
//	kernel = getStructuringElement(CV_SHAPE_RECT, Size(size + 1, size + 1));
//}
//
//void Morphology()
//{
//	morphologyEx(src, dst, morphology, kernel);
//	imshow("Morphology", dst);
//}
//
//void Hist()
//{
//	static vector<Mat> bgr_plans;
//	split(dst, bgr_plans);//bgr图像分通道显示
//
//	static Mat b_hist, g_hist, r_hist;//三种颜色的直方图
//	int size = 256;//定义域范围
//	int histSize[] = { size };//定义域范围指针
//	float range[] = { 0, 256 };//值域范围0~255指针
//	const float* histRanges[] = { range };//值域范围二级指针  range是指针类型
//	//计算直方图	直方图维数=图像通道数
//	//输入图指针 数目 通道数指针(灰图0) 固定 输出直方图数据 维数 定义域范围指针 值域范围二级指针 
//	calcHist(&bgr_plans[0], 1, 0, Mat(), b_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[1], 1, 0, Mat(), g_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[2], 1, 0, Mat(), r_hist, 1, histSize, histRanges);
//
//	int hist_heigh = 512;//直方图高度
//	int hist_width = 1024;//直方图宽度
//	int bin_width = hist_width / size;//一个bin宽度是1024/256=4
//	Mat histImage(hist_heigh, hist_width, CV_8UC3, Scalar(0, 0, 0));//建立直方图 高度 宽度
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
//	imshow("Morphology Hist Image", histImage);
//}
//
//void Blur()
//{
//	switch (::blur)
//	{
//	case 0:cv::blur(src, dst, Size(size + 1, size + 1));//均值滤波
//		break;
//	case 1:GaussianBlur(src, dst, Size(2 * size + 1, 2 * size + 1), 0);//高斯滤波
//		break;
//	case 2: medianBlur(src, dst, 2 * size + 1);//中值滤波 椒盐噪声
//		break;
//	case 3:bilateralFilter(src, dst, size + 1, (size + 1) * 2, (size + 1) / 2);//双边滤波 美图 效率低
//		break;
//	}
//	imshow("Blur", dst);
//}
//
//void Contour()
//{
//	Mat contour(src.size(), src.type(), Scalar(0, 0, 0));
//	cvtColor(src, gray, CV_BGR2GRAY);
//	Canny(gray, canny, ::contour, ::contour * 2);
//	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		drawContours(contour, contours, i, Scalar(0, 0, 255), 2, LINE_AA, hierarchy, 0);
//	}
//	imshow("Contour", contour);
//}