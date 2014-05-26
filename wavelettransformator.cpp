#include "wavelettransformator.hpp"

WaveletTransformator::WaveletTransformator(std::string path)
{
  image_ = imread(path, 1);
  ReduceSize(256);
}

WaveletTransformator::WaveletTransformator(cv::Mat &image)
{
  image.copyTo(image_);
  ReduceSize(256);
}

void WaveletTransformator::ReduceSize(int max_size)
{
  while (image_.rows > max_size && image_.cols > max_size)
      pyrDown(image_, image_);
}
