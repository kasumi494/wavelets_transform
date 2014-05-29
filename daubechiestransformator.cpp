#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "daubechiestransformator.hpp"
using namespace cv;

const float D4Transformator::c_[4] = {0.48296291314453414337f,
                                      0.83651630373780790557f,
                                      0.22414386804201338102f,
                                      -0.12940952255126038117f
                                     };

void D4Transformator::Decompose(cv::Mat &output, bool isShow)
{
  Mat_<Vec3f> tmp = image_.clone();
  tmp /= sqrt(image_.total());

  for (int lim_size = tmp.cols; lim_size >= 4; lim_size /= 2) {
    decompose_row(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  for (int lim_size = tmp.rows; lim_size >= 4; lim_size /= 2) {
    decompose_col(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  tmp.copyTo(output);
}


void D4Transformator::Reconstruct(cv::Mat &output, bool isShow)
{
  Mat_<Vec3f> tmp = image_.clone();

  for (int lim_size = 4; lim_size <= tmp.rows; lim_size *= 2) {
    reconstruct_col(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  for (int lim_size = 4; lim_size <= tmp.cols; lim_size *= 2) {
    reconstruct_row(tmp, lim_size);
    if (isShow) ShowNormalized(tmp);
  }

  tmp *= sqrt(image_.total());
  tmp.copyTo(output);
  normalize(tmp, output, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
  output.convertTo(output, CV_8U);
}


void D4Transformator::decompose_row(cv::Mat_<cv::Vec3f> &output, int lim)
{
  int half = std::floor(lim * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim);

  for (int k = 0; k < output.rows; ++k) {
    int j[4] = {0, 1, 2, 3};

    for (int i = 0; i < half; ++i) {
      tmp(i) = output(k, j[0]) * c_[0] + output(k, j[1]) * c_[1] +
               output(k, j[2]) * c_[2] + output(k, j[3]) * c_[3];

      tmp(half + i) = output(k, j[0]) * c_[3] - output(k, j[1]) * c_[2] +
                      output(k, j[2]) * c_[1] - output(k, j[3]) * c_[0];

      for (int w = 0; w < 4; ++w)
        j[w] = (j[w] + 2) % lim;
    }

    for (int i = 0; i < lim; ++i)   output(k, i) = tmp(i);
  }
}


void D4Transformator::decompose_col(cv::Mat_<cv::Vec3f> &output, int lim)
{
  int half = std::floor(lim * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim);
  int l_lim = lim - 3;

  for (int k = 0; k < output.cols; ++k) {
    int i, j;
    for (i = 0, j = 0; j < l_lim; j += 2, ++i) {
      tmp(i) = output(j, k)     * c_[0] + output(j + 1, k) * c_[1] +
               output(j + 2, k) * c_[2] + output(j + 3, k) * c_[3];

      tmp(half + i) = output(j, k)     * c_[3] - output(j + 1, k) * c_[2] +
                      output(j + 2, k) * c_[1] - output(j + 3, k) * c_[0];
    }

    tmp(i) = output(lim - 2, k) * c_[0] + output(lim - 1, k) * c_[1] +
             output(0, k) * c_[2] + output(1, k) * c_[3];

    tmp(i + half) = output(lim - 2, k) * c_[3] - output(lim - 1, k) * c_[2] +
                    output(0, k) * c_[1] - output(1, k) * c_[0];

    for (int i = 0; i < lim; ++i)   output(i, k) = tmp(i);
  }
}


void D4Transformator::reconstruct_row(cv::Mat_<cv::Vec3f> &output, int lim)
{
  int half = std::floor(lim * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim);

  for (int k = 0; k < output.rows; ++k) {
    tmp(0) = output(k, half - 1) * c_[2] + output(k, lim - 1) * c_[1] +
             output(k, 0) * c_[0] + output(k, half) * c_[3];

    tmp(1) = output(k, half - 1) * c_[3] - output(k, lim - 1) * c_[0] +
             output(k, 0) * c_[1] - output(k, half) * c_[2];

    for (int i = 0; i < half - 1; ++i) {
      int w = 2 * i;
      tmp(w + 2) = output(k, i) * c_[2] + output(k, i + half) * c_[1] +
                   output(k, i + 1) * c_[0] + output(k, i + half + 1) * c_[3];

      tmp(w + 3) = output(k, i) * c_[3] - output(k, i + half) * c_[0] +
                   output(k, i + 1) * c_[1] - output(k, i + half + 1) * c_[2];
    }

    for (int i = 0; i < lim; ++i)   output(k, i) = tmp(i);
  }
}


void D4Transformator::reconstruct_col(cv::Mat_<cv::Vec3f> &output, int lim)
{
  int half = std::floor(lim * 0.5f);
  Mat_ <Vec3f> tmp = Mat_ <Vec3f>(1, lim);

  for (int k = 0; k < output.cols; ++k) {
    tmp(0) = output(half - 1, k) * c_[2] + output(lim - 1, k) * c_[1] +
             output(0, k) * c_[0] + output(half, k) * c_[3];

    tmp(1) = output(half - 1, k) * c_[3] - output(lim - 1, k) * c_[0] +
             output(0, k) * c_[1] - output(half, k) * c_[2];

    for (int i = 0; i < half - 1; ++i) {
      int w = 2 * i;
      tmp(w + 2) = output(i, k) * c_[2] + output(i + half, k) * c_[1] +
                   output(i + 1, k) * c_[0] + output(i + half + 1, k) * c_[3];

      tmp(w + 3) = output(i, k) * c_[3] - output(i + half, k) * c_[0] +
                   output(i + 1, k) * c_[1] - output(i + half + 1, k) * c_[2];
    }

    for (int i = 0; i < lim; ++i)   output(i, k) = tmp(i);
  }
}
