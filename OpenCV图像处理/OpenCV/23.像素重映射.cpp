//#include<opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Mat src, dst;
//Mat map_x, map_y;
//int index = 0;
//
//void update_map();
//
//int main()
//{
//	src = imread("image\\���౦��.JPG");
//	if (src.empty())
//	{
//		cout << "���ܼ���ͼ��" << endl;
//		return -1;
//	}
//	namedWindow("src", CV_WINDOW_AUTOSIZE);
//	imshow("src", src);
//
//	//������CV_32FC1
//	map_x.create(src.size(), CV_32FC1);
//	map_y.create(src.size(), CV_32FC1);
//
//	while (1)
//	{
//		index = waitKey(500);
//		if (index == 27)
//		{
//			break;
//		}
//		update_map();
//		//              xӳ��  yӳ��  �̶�����      Ĭ�ϱ�Ե����    ��Ե��ɫ���
//		remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_DEFAULT, Scalar(255, 255, 255));
//		imshow("dst", dst);
//	}
//
//	waitKey(0);
//	return 0;
//}
//
//void update_map()
//{
//	for (int row = 0; row < src.rows; row++)
//	{
//		for (int col = 0; col < src.cols; col++)
//		{
//			switch (index)
//			{
//			case 48://С����0	������Сһ��
//				if ((col>src.cols*0.25) && col<(src.cols*0.75) && //���ȴ����ķ�֮һС���ķ�֮��
//					(row>src.rows*0.25) && (row < src.rows*0.75))//��ȴ����ķ�֮һС���ķ�֮��
//				{
//					map_x.at<float>(row, col) = 2 * (col - src.cols*0.25);//x����ӳ��
//					map_y.at<float>(row, col) = 2 * (row - src.rows*0.25);//y����ӳ��
//				}
//				else//����������Ϊ0
//				{
//					map_x.at<float>(row, col) = 0;
//					map_y.at<float>(row, col) = 0;
//				}
//				break;
//			case 49://С����1	ˮƽ��ת
//				map_x.at<float>(row, col) = src.cols - col - 1;//n��Ϊ0~n-1
//				map_y.at<float>(row, col) = row;
//				break;
//			case 50://С����2	��ֱ��ת
//				map_x.at<float>(row, col) = col;
//				map_y.at<float>(row, col) = src.rows - row - 1;//n��Ϊ0~n-1
//				break;
//			case 51://С����3	ˮƽ��ֱ��ת
//				map_x.at<float>(row, col) = src.cols - col - 1;
//				map_y.at<float>(row, col) = src.rows - row - 1;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}