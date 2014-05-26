#ifndef WAVELETTRANSFORMATOR_HPP
#define WAVELETTRANSFORMATOR_HPP

#include <opencv2/core/mat.hpp>

class WaveletTransformator {
public:
  WaveletTransformator();

  virtual cv::Mat Decompose(bool isShow) = 0;
  virtual cv::Mat Reconstruct(bool isShow) = 0;
};

#endif // WAVELETTRANSFORMATOR_HPP
