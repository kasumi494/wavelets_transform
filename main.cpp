#include <cstdio>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "haartransformator.hpp"
#include "daubechiestransformator.hpp"

int main(int argc, char **argv)
{
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << "image leave_coeff" << std::endl;
    return -1;
  }

  cv::Mat original = cv::imread(argv[1], 1);
  cv::imshow("Original", original);

  D4Transformator d4_1(original);
  cv::Mat_<cv::Vec3f> output_d4;
  d4_1.Decompose(output_d4, false);

  D4Transformator compressed_d4(output_d4);
  compressed_d4.Compress(output_d4, (size_t)atoi(argv[2]));
//  cv::imshow("Compressed", output_d4);

  D4Transformator d4_2(output_d4);
  cv::Mat reconstruct_d4;
  d4_2.Reconstruct(reconstruct_d4, false);
  cv::imshow("Reconstruction D4", reconstruct_d4);


  HaarTransformator haar_1(original);
  cv::Mat_<cv::Vec3f> output_haar;
  haar_1.Decompose(output_haar, false);

  HaarTransformator haar_compressed(output_haar);
  haar_compressed.Compress(output_haar, (size_t)atoi(argv[2]));
//  cv::imshow("Compressed", output_haar);

  HaarTransformator haar_2(output_haar);
  cv::Mat reconstruct;
  haar_2.Reconstruct(reconstruct, false);
  cv::imshow("Reconstruction D2", reconstruct);

  cv::waitKey(0);
  return 0;
}
