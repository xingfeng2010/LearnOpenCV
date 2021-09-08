#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    cout << "begin test" << endl;

    //读取图像，ps:opencv默认读取的是彩色图，其色彩格式BGR
    Mat color = imread("image4.jpg");
    //加载灰度图
    Mat gray = imread("image4.jpg",IMREAD_GRAYSCALE);
    cout << "read normal 111" << endl;

    if (!color.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    namedWindow("Image(BGR)",WINDOW_AUTOSIZE);
    imshow("Image(BGR)", color);
    imshow("Image(Gray)", gray);
    //wait for any key press
    waitKey(0);
    return 0;
}
