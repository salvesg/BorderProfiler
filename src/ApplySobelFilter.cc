//! includes

#include<filesystem>

#include "ImageBorders/ImageBorders.hh"

using std::cout;
using std::endl;

void usage( char* Program )
{
  cout << endl 
       << " Program to detect the borders of an image (equivalent to a Sobel Filter)." << endl
       << " It can return the resulting image as <image_name>_borders.<ext> if an " << endl
       << " output path is specifeid. If not the result is displayed." << endl
       << " Usage: " << endl << endl
       << "  " << Program << " <image_path> [ <output_path ]" << endl << endl;
}

int main( int argc, char* argv[] )
{

  // === Check correct usage ===
  if( argc < 2 || argc > 3 )
  {
    usage(argv[0]);
    return 1;
  }

  // === Load and check input image ===
  std::filesystem::path inpath( argv[1] );
  cv::Mat input_image = cv::imread( inpath.string(), cv::IMREAD_GRAYSCALE );

  if(input_image.empty())
  {
    std::cerr << "Error: Cannot load image or it is empty!" << endl;
    return 2;
  }
  
  // === Create the borders through custom class ===
  auto borders = ImageBorders::CreateBorders(input_image);

  // === Save or display produced output ===
  if( argc == 3 )
    {
      std::filesystem::path outpath(argv[2]);
      std::string outfile_name = inpath.stem().string() + "_border" + inpath.extension().string();
      outpath /= outfile_name; 
      cv::imwrite(outpath.string(), *borders);
    }
  else
    {
      cv::namedWindow( "Borders", cv::WINDOW_AUTOSIZE );
      cv::imshow( "Borders", *borders);
      cv::waitKey();
    }
  
  return 0;
  
}

// Mat A, B;

  // A = (Mat_<uchar>(3,3) << 1, 2, 1, 3, 5, 2, 4, 1, 2);

  // cout << "A = \n " << A << endl << endl;  

  // ApplySobelFilter(A, B);

  // cout << "B = \n " << B << endl << endl;  
  
  // return 0;
  

