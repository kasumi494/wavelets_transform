#ifndef WAVELETTRANSFORMATOR_HPP
#define WAVELETTRANSFORMATOR_HPP

#include <opencv2/core/mat.hpp>

class WaveletTransformator {
public:
  WaveletTransformator(std::string path);
  WaveletTransformator(cv::Mat &image);
  ~WaveletTransformator() {}

  virtual void Decompose(cv::Mat &output, bool isShow) = 0;
  virtual void Reconstruct(cv::Mat & output, bool isShow) = 0;
  void Compress(cv::Mat_<cv::Vec3f> &output, size_t leave_count);

  void Show();

protected:
  void ReduceSize(int max_size);
  void ShowNormalized(const cv::Mat &image);

  cv::Mat image_;
};

#endif // WAVELETTRANSFORMATOR_HPP
