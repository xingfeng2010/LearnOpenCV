#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * 绘制直方图:直方图是变量分布的统计图形表示，它让我们能够理解数据的密度估计和概率分布。
 * 直方图通过将整个变量值范围划分为小的值范围，然后计算每个间隔中落入多少个值来创建
 * @param inputImagePath 绘制直方图的原图路径
 */
void showCalcHist(char *inputImagePath) {
    cout << "enter showCalcHist" << endl;
    //加载原图
    Mat src = imread(inputImagePath);
    if (src.empty()) {
        cout << "图像数据不存在" << endl;
        return;
    }

    cout << "load image success" << endl;
    //将原图进行拆分,并存入向量集合中
    vector<Mat> bgr;
    //将输入图像划分为三个通道R\G\B
    split(src, bgr);

    //设置直方图有256个区间，因为图像的灰度值变化为0~255
    int numbers = 256;
    //定义变量范围，并定义三个矩阵来存储每个直方图
    float range[] = {0, 256};
    const float *histRange = {range};
    Mat b_hist, g_hist, r_hist;
    /*
    * calcHist用来计算图像直方图：
    * 参数详解：
       const Mat* images：输入图像
        int nimages：输入图像的个数
       const int* channels：需要统计直方图的第几通道
       InputArray mask：掩膜，，计算掩膜内的直方图  ...Mat()
       OutputArray hist:输出的直方图数组
       int dims：需要统计直方图通道的个数
       const int* histSize：指的是直方图分成多少个区间，就是 bin的个数
       const float** ranges： 统计像素值得区间
       bool uniform=true::是否对得到的直方图数组进行归一化处理
       bool accumulate=false：在多个图像时，是否累计计算像素值得个数
    */
    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numbers, &histRange);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numbers, &histRange);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numbers, &histRange);

    cout << "calcHist success" << endl;

    //计算出每个通道的直方图后绘制直方图，并显示给用户
    int width = 512;
    int height = 320;
    //创建一个灰度图
    Mat histImage(height, width, CV_8UC3, Scalar(20, 20, 20));
    normalize(b_hist, b_hist, 0, height, NORM_MINMAX);
    normalize(g_hist, g_hist, 0, height, NORM_MINMAX);
    normalize(r_hist, r_hist, 0, height, NORM_MINMAX);

    cout << "normalize success" << endl;
    int binStep = cvRound((float) width / (float) numbers);
    cout << "cvRound success" << endl;
    for (int i = 0; i < numbers; i++) {
        try {
            line(
                    histImage,
                    Point(binStep*(i-1),height- cvRound(b_hist.at<float>(i-1))),
                    Point(binStep*(i),height- cvRound(b_hist.at<float>(i))),
                    Scalar(255,0,0)
            );

            line(
                    histImage,
                    Point(binStep*(i-1),height- cvRound(g_hist.at<float>(i-1))),
                    Point(binStep*(i),height- cvRound(g_hist.at<float>(i))),
                    Scalar(0,255,0)
            );
            line(
                    histImage,
                    Point(binStep * (i - 1), height - cvRound(r_hist.at<float>(i - 1))),
                    Point(binStep * (i), height - cvRound(r_hist.at<float>(i))),
                    Scalar(0, 0, 255)
            );
        } catch (Exception exception) {
            cout << exception.err << endl;
        }
    }

//    //展示原图
    imshow("src", src);
//    //展示直方图
    imshow("histWindow", histImage);
    //销毁原始图像
    src.release();
    waitKey(0);
    destroyWindow("src");
    destroyWindow("histWindow");
}

int main() {
    cout << "begin test" << endl;

    char *path = "demo.png";
    showCalcHist(path);

    return 0;
}
