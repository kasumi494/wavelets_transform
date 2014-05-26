#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "wavelettransformator.hpp"

WaveletTransformator::WaveletTransformator(std::string path)
{
  image_ = cv::imread(path, 1);
  ReduceSize(256);
}

WaveletTransformator::WaveletTransformator(cv::Mat &image)
{
  image.copyTo(image_);
  ReduceSize(256);
}

void WaveletTransformator::Show()
{
  cv::Mat tmp;
  cv::normalize(image_, tmp, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  tmp.convertTo(tmp, CV_8UC3);
  imshow("Output", tmp);
  cv::waitKey(0);
}

void WaveletTransformator::ReduceSize(int max_size)
{
  while (image_.rows > max_size && image_.cols > max_size)
      pyrDown(image_, image_);
}
