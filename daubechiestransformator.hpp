#ifndef DAUBECHIESTRANSFORMATOR_HPP
#define DAUBECHIESTRANSFORMATOR_HPP

#include "wavelettransformator.hpp"

class D4Transformator : public WaveletTransformator {
public:
  D4Transformator(std::string path): WaveletTransformator(path) {}
  D4Transformator(cv::Mat &image): WaveletTransformator(image) {}

  virtual void Decompose(cv::Mat &output, bool isShow);
  virtual void Reconstruct(cv::Mat &output, bool isShow);

private:
  void decompose_row(cv::Mat_<cv::Vec3f> &output, int lim_size);
  void decompose_col(cv::Mat_ <cv::Vec3f> &output, int lim_size);

  void reconstruct_row(cv::Mat_ <cv::Vec3f> &output, int lim_size);
  void reconstruct_col(cv::Mat_<cv::Vec3f> &output, int lim_size);

  const float coefficients_[4]  = {0.48296291314453414337,
                                   0.83651630373780790557,
                                   0.22414386804201338102
                                  -0.12940952255126038117};
};

#endif // DAUBECHIESTRANSFORMATOR_HPP
