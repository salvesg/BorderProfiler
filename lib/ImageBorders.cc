// =================================== //
//   Implementation of ImageBorders    //
// =================================== //

#include "ImageBorders/ImageBorders.hh"


ImageBorders::ImageBorders( const cv::Mat& input )
{
  /**
   * Construct borders directly from the input image (cv::Mat object)
   */
  
  try {
    ApplySobelFilter( input ); 
  }
  catch( const std::runtime_error& e) {
    std::cout << " Type error: " << e.what(); 
  }
}

void ImageBorders::Display()
{
      cv::namedWindow( "Borders", cv::WINDOW_AUTOSIZE );
      cv::imshow( "Borders", _borders );
      cv::waitKey();  
}


void ImageBorders::ApplySobelFilter( const cv::Mat& input, bool ShowTime )
{
  /**
   * Apply the Sobel filter to the input image
   */
  
  // === Make sure is correct type ===
  if( input.type() != CV_8U )
  {
    throw std::runtime_error("Input image must have pixel type 8bit unsigned char (CV_8U) ");
  }

  // The object is created with pixel type float to 
  // allow more exact arithmetics (avoid saturating uchar)
  _borders.create( input.size(), CV_32F);
  
  float Result_Gx, Result_Gy;
  
  double t = (double)cv::getTickCount();
  
 
  // Loop limits set to avoid image top/bottom/right/left borders
#pragma omp parallel for private(Result_Gx, Result_Gy)
  for( int i = 1; i < input.rows - 1; i++) // Loping on rows
  {
    const uchar* upper_row   = input.ptr<uchar>(i - 1);
    const uchar* current_row = input.ptr<uchar>(i);
    const uchar* lower_row   = input.ptr<uchar>(i + 1);
    
    float* target_row = _borders.ptr<float>(i);
    
    for( int j = 1; j < input.cols - 1; j++ ) // Loping on columns
    {

      // Simplied application of (1,3)x(3,1) decomposed Sobel operators
      // See https://en.wikipedia.org/wiki/Sobel_operator#Formulation 
      
      Result_Gx = static_cast<float>( (upper_row[j+1] - upper_row[j-1])
				      + 2* (current_row[j+1] - current_row[j-1])
				      + (lower_row[j+1] - lower_row[j-1]) );
      
      Result_Gy = static_cast<float>( (lower_row[j-1] - upper_row[j-1])
				      + 2 * (lower_row[j] - upper_row[j])
				      + (lower_row[j+1] - upper_row[j+1]) );
      
      // Other allowed observable is abs(Result_Gx) + abs(Result_Gy) 
      target_row[j] = sqrt( pow( Result_Gx, 2) + pow(Result_Gy, 2) );
    }
  }

  // === Safely convert the floats to uchars for correct display
  cv::normalize(_borders, _borders, 0, 255, cv::NORM_MINMAX);
  _borders.convertTo(_borders, CV_8U);
  
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
  
  if( ShowTime )
  {
    std::cout << "Borders created! Elapsed time " << t << " seconds." << std::endl;
  }
    
}
