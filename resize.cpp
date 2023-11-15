#include "Image.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include "processing.hpp"

using namespace std;

int main(int argc, char **argv)
{

  Image img;

  // The program expects 4 or 5 arguments, and if incorrect, 
  //prints usage and exits with error code 1
  if (argc < 4 || argc > 5)
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  // tests if input file opens
  ifstream in_file;
  in_file.open(argv[1]);
  if (!in_file.is_open())
  {
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  // initilaizes image
  Image_init(&img, in_file);

  in_file.close();

  // tests if the output image can open
  ofstream out_file;
  out_file.open(argv[2]);
  if (!out_file.is_open())
  {
    cout << "Error opening file: " << argv[2] << endl;
    return 1;
  }

  // test if width of the input image is valid
  int width = std::atoi(argv[3]);
  if (width < 0 || width > Image_width(&img))
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }

  // test if the hight is valid
  int height = std::atoi(argv[4]);
  if (height < 0 || height > Image_height(&img))
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }

  // Compute energy matrix
  Matrix energy;
  Matrix_init(&energy, Image_width(&img), Image_height(&img));
  compute_energy_matrix(&img, &energy);

  // Compute vertical cost matrix
  Matrix cost;
  Matrix_init(&cost, Image_width(&img), Image_height(&img));
  compute_vertical_cost_matrix(&energy, &cost);

  // Find and remove minimal vertical seam
  int seam[MAX_MATRIX_HEIGHT];
  find_minimal_vertical_seam(&cost, seam);
  remove_vertical_seam(&img, seam);

  // Display the modified image
  Image_print(&img, out_file);

  out_file.close();

  return 0;
}