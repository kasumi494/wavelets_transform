#ifndef WAVELETTRANSFORMATOR_HPP
#define WAVELETTRANSFORMATOR_HPP

#include <opencv2/core/mat.hpp>

class WaveletTransformator {
public:
  WaveletTransformator(std::string path);
  WaveletTransformator(cv::Mat &image);

  virtual cv::Mat Decompose(bool isShow) = 0;
  virtual cv::Mat Reconstruct(bool isShow) = 0;

private:
  void ReduceSize(int max_size);

  cv::Mat image_;
  int lim_size_;
};

#endif // WAVELETTRANSFORMATOR_HPP
