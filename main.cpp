#include <cstdio>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/// 1 / sqrt(2)
const float kInvSqrtOf2 = 0.7071067811865475244008444f;

void showNormalizeMat(Mat &input)
{
    Mat tmp;
    normalize(input, tmp, 0, 255, NORM_MINMAX, -1, Mat());
    tmp.convertTo(tmp, CV_8UC3);
    imshow("Output", tmp);
    waitKey(0);
}

void do_Haar_decomposition_row(Mat_ <Vec3f> &output, int lim_size)
{
    int half_lim = std::floor(lim_size * 0.5f);
    Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim_size);

    for (int k = 0; k < output.rows; ++k) {
        for (int i = 0; i < half_lim; ++i) {
            tmp(i)              = output(k, 2 * i) + output(k, 2 * i + 1);
            tmp(half_lim + i)   = output(k, 2 * i) - output(k, 2 * i + 1);
        }

        for (int i = 0; i < lim_size; ++i)
            output(k, i) = tmp(i) * kInvSqrtOf2;
    }
}

void do_Haar_decomposition_col(Mat_ <Vec3f> &output, int lim_size)
{
    int half_lim = std::floor(lim_size * 0.5f);
    Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim_size);

    for (int k = 0; k < output.cols; ++k) {
        for (int i = 0; i < half_lim; ++i) {
            tmp(i)              = output(2 * i, k) + output(2 * i + 1, k);
            tmp(half_lim + i)   = output(2 * i, k) - output(2 * i + 1, k);
        }

        for (int i = 0; i < lim_size; ++i)
            output(i, k) = tmp(i) * kInvSqrtOf2;
    }
}

void Haar_Decomposition(Mat input, Mat &output, const bool isShow)
{
    Mat_ <Vec3f> tmp = input.clone();
    tmp /= sqrt(input.rows * input.cols);

    for (int lim_size = tmp.cols; lim_size >= 2; lim_size /= 2) {
        do_Haar_decomposition_row(tmp, lim_size);

        if (isShow) showNormalizeMat(tmp);
    }

    for (int lim_size = tmp.rows; lim_size >= 2; lim_size /= 2) {
        do_Haar_decomposition_col(tmp, lim_size);

        if (isShow) showNormalizeMat(tmp);
    }

    tmp.copyTo(output);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << "image {show}" << std::endl;
        return -1;
    }

    Mat input_image = imread(argv[1], 1);
    while (input_image.rows > 256 && input_image.cols > 256)
        pyrDown(input_image, input_image);

    Mat output_haar;

    Haar_Decomposition(input_image, output_haar, true);
    imshow("Output", output_haar);
    waitKey(0);

    return 0;
}
