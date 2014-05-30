#include <cstdio>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "haartransformator.hpp"
#include "daubechiestransformator.hpp"

cv::Mat original;
int threshval = 5000;

void MakeD2();
void MakeD4();

void MakeD2()
{
  HaarTransformator decompositor(original);
  cv::Mat_<cv::Vec3f> decomposed;
  decompositor.Decompose(decomposed, false);

  HaarTransformator compressor(decomposed);
  compressor.Compress(decomposed, threshval);
//  cv::imshow("Compressed", decomposed);

  HaarTransformator reconstructor(decomposed);
  cv::Mat reconstruct;
  reconstructor.Reconstruct(reconstruct, false);
  cv::imshow("D2 Transform", reconstruct);
}

void MakeD4()
{
  D4Transformator decompositor(original);
  cv::Mat_<cv::Vec3f> decomposed;
  decompositor.Decompose(decomposed, false);

  D4Transformator compressor(decomposed);
  compressor.Compress(decomposed, threshval);
//  cv::imshow("Compressed", decomposed);

  D4Transformator reconstructor(decomposed);
  cv::Mat reconstruct;
  reconstructor.Reconstruct(reconstruct, false);
  cv::imshow("D4 Transform", reconstruct);
}

static void on_trackbar_d4(int, void*)
{
  if (threshval < 2) threshval = 2;
  cv::setTrackbarPos("leaved", "D2 Transform", threshval);

  MakeD2();
  MakeD4();
}

static void on_trackbar_d2(int, void*)
{
  if (threshval < 2) threshval = 2;
  cv::setTrackbarPos("leaved", "D4 Transform", threshval);

  MakeD2();
  MakeD4();
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << "image leave_coeff" << std::endl;
    return -1;
  }

  original = cv::imread(argv[1], 1);

  cv::namedWindow("D2 Transform", 1);
  cv::createTrackbar("leaved", "D2 Transform", &threshval,
                     threshval, on_trackbar_d2);

  cv::namedWindow("D4 Transform", 1);
  cv::createTrackbar("leaved", "D4 Transform", &threshval,
                     threshval, on_trackbar_d4);
  on_trackbar_d4(threshval, 0);

  cv::waitKey(0);
  return 0;
}
