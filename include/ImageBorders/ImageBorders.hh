#ifndef IMAGEBORDERS_HH
#define IMAGEBORDERS_HH

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

#include<cmath>
#include<iostream>
#include<memory>

class ImageBorders : public cv::Mat {

public:

  static std::unique_ptr<ImageBorders> CreateBorders( const Mat& );

  // Implement further operation on the borders...
  
  ImageBorders() = default;
  ImageBorders(const ImageBorders&) = default;
  ImageBorders(ImageBorders&&) noexcept = default;
  ImageBorders& operator=(const ImageBorders&) = default;
  ImageBorders& operator=(ImageBorders&&) noexcept = default;

private:

  
  void ApplySobelFilter( const Mat&, bool ShowTime = true );
   
};

#endif
