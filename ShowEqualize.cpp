#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * 图像颜色均衡（直方图均衡化）
 * @param inputImagePath 原始图像路径
 * 图像均衡试图获得具有均匀分布值的直方图。均衡的结果是图像对比度增加。均衡能够使对比度比较低的局部区域获得高对比度，从而分散最频繁的强度。
 * 当图像非常暗或者非常亮，并且背景和前景之间存在非常小的差异时，此方法非常有用。通过使用直方图均衡化，可以增加对比度，并且提升暴露过度或暴露不足的细节。
 * 该技术在医学图像中非常有用（如：X射线）
 *
 * 缺点：
 *  背景噪声的增加以及随之而来的有用信号的减少。
 */
void showEqualizeImage(char *inputImagePath) {
    //加载原图
    Mat src = imread(inputImagePath);
    if (src.empty()) {
        cout << "图像数据不存在" << endl;
        return;
    }
    //定义一个最终显示结果的矩阵
    Mat result;
    //将BGR图像转换为YCBCR
    Mat ycrcb;
    cvtColor(src, ycrcb, COLOR_BGR2YCrCb);
    //将ycrcb拆分成三个不同的通道，可以单独拿到Y分量
    vector<Mat> channels;
    split(ycrcb, channels);
    //直方图均衡，只均衡Y分量
    equalizeHist(channels[0],channels[0]);
    //将均衡后的y分量合并到Ycrcb图像中
    merge(channels, ycrcb);
    //将ycrcb转换为BGR
    cvtColor(ycrcb, result, COLOR_YCrCb2BGR);
    imshow("src", src);
    imshow("equalizeHist",result);
    src.release();
    ycrcb.release();
    result.release();
    waitKey(0);
    destroyWindow("equalizeHist");
}

int main() {
    cout << "begin test" << endl;

    char *path = "gray.png";
    showEqualizeImage(path);

    return 0;
}
