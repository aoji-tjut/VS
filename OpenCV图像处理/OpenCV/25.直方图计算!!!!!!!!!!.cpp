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
//	vector<Mat> bgr_plans;
//	split(src, bgr_plans);//bgrͼ���ͨ����ʾ
//	
//	Mat b_hist, g_hist, r_hist;//������ɫͨ����ֱ��ͼ
//	int size = 256;//������Χ0-255
//	int histSize[] = { size };//������(x��)��Χָ��
//	float range[] = { 0, 256 };//ֵ��(y��)��Χ0-255ָ��
//	const float* histRanges[] = { range };//ֵ��Χ����ָ��
//	//����ֱ��ͼ	ֱ��ͼά��=ͼ��ͨ����
//	//����ͼָ�� ��Ŀ ͨ����ָ��(��ͼ0) ����Ĥ ���ֱ��ͼ���� ά�� ������Χָ�� ֵ��Χָ���ָ�� 
//	calcHist(&bgr_plans[0], 1, 0, Mat(), b_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[1], 1, 0, Mat(), g_hist, 1, histSize, histRanges);
//	calcHist(&bgr_plans[2], 1, 0, Mat(), r_hist, 1, histSize, histRanges);
//
//	int hist_heigh = 512;//ֱ��ͼ�߶�
//	int hist_width = 1024;//ֱ��ͼ���
//	int bin_width = hist_width / size;//һ��bin�����1024/256=4
//	Mat histImage(hist_heigh, hist_width, CV_8UC3, Scalar(0, 0, 0));//����ֱ��ͼ �߶�(cols) ���(rows)
//
//	//��һ����0~hist_heigh 
//	normalize(b_hist, b_hist, 0, hist_heigh, NORM_MINMAX);
//	normalize(g_hist, g_hist, 0, hist_heigh, NORM_MINMAX);
//	normalize(r_hist, r_hist, 0, hist_heigh, NORM_MINMAX);
//
//	//����ֱ��ͼ
//	for (int i = 1; i < size; i++)
//	{
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(b_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 1, LINE_AA);//��
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(g_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 1, LINE_AA);//��
//		line(histImage, Point((i - 1)*bin_width, hist_heigh - cvRound(r_hist.at<float>(i - 1))),
//			Point((i)*bin_width, hist_heigh - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 1, LINE_AA);//��
//	}
//	
//	imshow("ֱ��ͼ", histImage);
//
//	waitKey(0);
//	return 0;
//}