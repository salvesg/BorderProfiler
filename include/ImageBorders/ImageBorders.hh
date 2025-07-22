#ifndef IMAGEBORDERS_HH
#define IMAGEBORDERS_HH

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

#include<omp.h>

#include<cmath>
#include<iostream>
#include<filesystem>
#include<memory>

namespace ImageBorderUtils {

  template <typename T>
  cv::Size ReturnSize(const T& image) { return image.size(); }
  
};


class ImageBorders {

public:

  // Public methods
  ImageBorders() = default;
  ImageBorders( const cv::Mat& );
  
  ImageBorders(const ImageBorders&)                = default;
  ImageBorders(ImageBorders&&) noexcept            = default;
  ImageBorders& operator=(const ImageBorders&)     = default;
  ImageBorders& operator=(ImageBorders&&) noexcept = default;

  // Method to display the borders
  void Display();

  // Mothod to save the borders
  void Save( const std::filesystem::path& out_file ){ cv::imwrite( out_file, _borders ); }
  
  // Geter functions
  cv::Mat& GetBorders(){ return _borders; }
  const cv::Mat& GetBorders() const { return _borders; }
  
  cv::Size size() const { return _borders.size(); }
  
private:

  // private members:
  cv::Mat _borders;
  
  // private methods
  void ApplySobelFilter( const cv::Mat&, bool ShowTime = true );

};

#endif
