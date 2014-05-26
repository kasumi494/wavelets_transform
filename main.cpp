#include <cstdio>
#include <iostream>

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

    HaarTransformator haar(argv[1]);

    cv::Mat output_haar;
    haar.Decompose(output_haar, true);
    cv::imshow("Output", output_haar);
    cv::waitKey(0);

    return 0;
}
