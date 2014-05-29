#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "haartransformator.hpp"

using namespace cv;

/// 1 / sqrt(2)
const float kInvSqrtOf2 = 0.7071067811865475244008443621048490393f;
void ShowNormalized(const Mat &image);

void HaarTransformator::Decompose(Mat &output, bool isShow)
{
  Mat_<Vec3f> tmp = image_.clone();
  tmp /= sqrt(image_.total());

  for (int lim_size = tmp.cols; lim_size >= 2; lim_size /= 2) {
    do_Haar_decomposition_row(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  for (int lim_size = tmp.rows; lim_size >= 2; lim_size /= 2) {
    do_Haar_decomposition_col(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  tmp.copyTo(output);
}

void HaarTransformator::Reconstruct(Mat &output, bool isShow)
{
  Mat_<Vec3f> tmp = image_.clone();
  int half_cols = cvRound(image_.cols * 0.5f);
  int half_rows = cvRound(image_.rows * 0.5f);

  for (int lim_size = 1; lim_size <= half_rows; lim_size *= 2) {
    do_Haar_reconstruction_col(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  for (int lim_size = 1; lim_size <= half_cols; lim_size *= 2) {
    do_Haar_reconstruction_row(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  tmp *= sqrt(image_.total());
  normalize(tmp, output, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  output.convertTo(output, CV_8U);
}

void HaarTransformator::do_Haar_decomposition_row(Mat_<Vec3f> &output,
                                                  int lim_size)
{
  int half_lim = cvRound(lim_size * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim_size);

  for (int k = 0; k < output.rows; ++k) {
    for (int i = 0; i < half_lim; ++i) {
      tmp(i)              = output(k, 2 * i) + output(k, 2 * i + 1);
      tmp(half_lim + i)   = output(k, 2 * i) - output(k, 2 * i + 1);
    }

    for (int i = 0; i < lim_size; ++i)
      output(k, i) = tmp(i) * kInvSqrtOf2;
  }
}

void HaarTransformator::do_Haar_decomposition_col(cv::Mat_<Vec3f> &output,
                                                  int lim_size)
{
  int half_lim = cvRound(lim_size * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim_size);

  for (int k = 0; k < output.cols; ++k) {
    for (int i = 0; i < half_lim; ++i) {
      tmp(i)              = output(2 * i, k) + output(2 * i + 1, k);
      tmp(half_lim + i)   = output(2 * i, k) - output(2 * i + 1, k);
    }

    for (int i = 0; i < lim_size; ++i)
      output(i, k) = tmp(i) * kInvSqrtOf2;
  }
}

void HaarTransformator::do_Haar_reconstruction_row(cv::Mat_<Vec3f> &output,
                                                   int lim_size)
{
  int double_size = lim_size * 2;
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, double_size);

  for (int i = 0; i < output.rows; ++i) {
    for (int k = 0; k < lim_size; ++k) {
      tmp(2 * k)      = output(i, k) + output(i, k + lim_size);
      tmp(2 * k + 1)  = output(i, k) - output(i, k + lim_size);
    }

    for (int k = 0; k < double_size; ++k)
      output(i, k) = tmp(k) * kInvSqrtOf2;
  }
}

void HaarTransformator::do_Haar_reconstruction_col(cv::Mat_<Vec3f> &output,
                                                   int lim_size)
{
  int double_size = lim_size * 2;
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, double_size);

  for (int i = 0; i < output.cols; ++i) {
    for (int k = 0; k < lim_size; ++k) {
      tmp(2 * k)      = output(k, i) + output(k + lim_size, i);
      tmp(2 * k + 1)  = output(k, i) - output(k + lim_size, i);
    }

    for (int k = 0; k < double_size; ++k)
      output(k, i) = tmp(k) * kInvSqrtOf2;
  }
}
