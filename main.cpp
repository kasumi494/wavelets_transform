#include <cstdio>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "haartransformator.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << "image {show}" << std::endl;
        return -1;
    }

    cv::Mat original = cv::imread(argv[1], 1);
//    cv::imshow("Original", original);

    HaarTransformator haar_1(original);
    haar_1.Show();
    cv::Mat_<cv::Vec3f> output_haar;
    haar_1.Decompose(output_haar, false);
//    cv::imshow("Decomposition", output_haar);

    HaarTransformator haar_compressed(output_haar);
    haar_compressed.Compress(output_haar);
//    cv::imshow("Compressed", output_haar);

    HaarTransformator haar_2(output_haar);
    cv::Mat reconstruct;
    haar_2.Reconstruct(reconstruct, false);
    cv::imshow("Reconstruction", reconstruct);

    cv::waitKey(0);
    return 0;
}
