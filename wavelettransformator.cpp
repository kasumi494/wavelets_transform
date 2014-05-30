#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "wavelettransformator.hpp"

bool GetMin(float i, float j) { return (fabs(i) < fabs(j)); }
bool GetMax(float i, float j) { return (fabs(i) > fabs(j)); }

void partial_sort(std::vector<float> &array, int max_count)
{
  std::vector <float>::iterator itMax;
  std::vector <float>::iterator it = array.begin();
  std::vector <float>::iterator it_end = array.end();

  for (int i = 0; i < max_count; ++i, ++it) {
    itMax = std::max_element(it, it_end, GetMin);
    std::swap(*itMax, *it);
  }
}

WaveletTransformator::WaveletTransformator(std::string path)
{
  image_ = cv::imread(path, 1);
  ReduceSize(512);
}

WaveletTransformator::WaveletTransformator(cv::Mat &image)
{
  image.copyTo(image_);
  ReduceSize(512);
}

void WaveletTransformator::Compress(cv::Mat_<cv::Vec3f> &output,
                                    size_t leave_count)
{
  /// Start Quantize
  cv::Mat reshaped_image = image_.clone();
  reshaped_image = reshaped_image.reshape(0, 1);
  std::vector <cv::Mat_ <float> > channels;
  cv::split(reshaped_image, channels);

  /// Get tresholds
  float tresholds[3] = {.0f, .0f, .0f};
  for (int i = 0; i < 3; ++i) {
    std::vector <float> tmp;
    channels[i].row(0).copyTo(tmp);

    if (leave_count < 100)  partial_sort(tmp, leave_count + 1);
    else  std::sort(tmp.begin(), tmp.end(), GetMax);

    /// First 60 coefficients (+ first: mean value)
    tresholds[i] = fabs(tmp[leave_count]);
  }

  /// Cut by treshold
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < channels[i].total(); ++j) {
      float tmp = channels[i](j);
      if (fabs(tmp) < tresholds[i]) channels[i](j) = .0f;
    }
  }

  cv::merge(channels, output);
  output = output.reshape(0, image_.rows);
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

void WaveletTransformator::ShowNormalized(const cv::Mat &image)
{
  cv::Mat tmp;
  cv::normalize(image, tmp, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  tmp.convertTo(tmp, CV_8UC3);
  imshow("Output", tmp);
  cv::waitKey(0);
}
