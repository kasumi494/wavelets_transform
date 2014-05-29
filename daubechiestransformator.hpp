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
  void decompose_row(cv::Mat_<cv::Vec3f> &output, int lim);
  void decompose_col(cv::Mat_ <cv::Vec3f> &output, int lim);

  void reconstruct_row(cv::Mat_ <cv::Vec3f> &output, int lim);
  void reconstruct_col(cv::Mat_<cv::Vec3f> &output, int lim);

  static const float c_[4];
};

#endif // DAUBECHIESTRANSFORMATOR_HPP
