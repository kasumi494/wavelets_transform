#ifndef HAARTRANSFORMATOR_HPP
#define HAARTRANSFORMATOR_HPP

#include "wavelettransformator.hpp"

class HaarTransformator : public WaveletTransformator {
public:
  HaarTransformator(std::string path): WaveletTransformator(path) {}
  HaarTransformator(cv::Mat &image): WaveletTransformator(image) {}

  virtual void Decompose(cv::Mat &output, bool isShow);
  virtual void Reconstruct(cv::Mat &output, bool isShow);

private:
  void do_Haar_decomposition_row(cv::Mat_<cv::Vec3f> &output, int lim_size);
  void do_Haar_decomposition_col(cv::Mat_ <cv::Vec3f> &output, int lim_size);

  void do_Haar_reconstruction_row(cv::Mat_ <cv::Vec3f> &output, int lim_size);
  void do_Haar_reconstruction_col(cv::Mat_<cv::Vec3f> &output, int lim_size);
};

#endif // HAARTRANSFORMATOR_HPP
