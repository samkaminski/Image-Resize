#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic)
{
  // First test case
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image

  // Second test case
  //  Create an Image in dynamic memory
  Image *img1 = new Image;

  // Define pixel colors
  const Pixel red1 = {255, 0, 0};
  const Pixel green1 = {0, 255, 0};
  const Pixel blue1 = {0, 0, 255};
  const Pixel white1 = {255, 255, 255};

  // Initialize the Image with dimensions (2x2)
  Image_init(img1, 2, 2);

  // Set pixels with different colors
  Image_set_pixel(img1, 0, 0, red1);
  Image_set_pixel(img1, 0, 1, green1);
  Image_set_pixel(img1, 1, 0, blue1);
  Image_set_pixel(img1, 1, 1, white1);

  // Capture the output of Image_print
  ostringstream s1;
  Image_print(img1, s1);

  // Define the correct output
  ostringstream correct1;
  correct1 << "P3\n2 2\n255\n";
  correct1 << "255 0 0 0 255 0 \n";
  correct1 << "0 0 255 255 255 255 \n";

  // Verify if the captured output matches the correct output
  ASSERT_EQUAL(s1.str(), correct1.str());

  // Delete the Image from dynamic memory to free resources
  delete img1;
}
TEST(test_image_init)
{
  // First test
  istringstream input(
      "P3\n"
      "3 2\n"
      "255\n"
      "255 0 0 0 255 0 0 0 255\n"
      "0 255 255 255 0 255 255 255 0\n");

  Image img;
  Image_init(&img, input);

  // Check if the image dimensions are correctly set
  ASSERT_EQUAL(img.width, 3);
  ASSERT_EQUAL(img.height, 2);

  // Check a few pixels for correct color values
  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 0, 0), 255);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 0, 0), 0);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 1, 1), 255);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 1, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 1, 1), 255);

  // Second test
  istringstream input1(
      "P3\n"
      "4 3\n"
      "255\n"
      "255 0 0 0 255 0 0 0 255 0 0 0\n"
      "0 255 255 255 0 255 255 255 0 255 255 255\n");

  // Initialize an Image from the input stream
  Image img1;
  Image_init(&img1, input1);

  // Check if the image dimensions are correctly set
  ASSERT_EQUAL(img1.width, 4);
  ASSERT_EQUAL(img1.height, 3);

  // Check a few pixels for correct color values
  ASSERT_EQUAL(*Matrix_at(&img1.red_channel, 0, 0), 255);
  ASSERT_EQUAL(*Matrix_at(&img1.green_channel, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&img1.blue_channel, 0, 0), 0);

  ASSERT_EQUAL(*Matrix_at(&img1.red_channel, 1, 1), 255);
  ASSERT_EQUAL(*Matrix_at(&img1.green_channel, 1, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&img1.blue_channel, 1, 1), 255);

  // Third test
  //  Create an input stream with minimal image data (1x1 pixel)
}
TEST(test_image_print)
{
  // First test
  //  Create a sample Image with known dimensions (2x2)
  Image img;
  Image_init(&img, 2, 2);

  // Set pixel values with known colors
  Image_set_pixel(&img, 0, 0, {255, 0, 0});   // Red
  Image_set_pixel(&img, 0, 1, {0, 255, 0});   // Green
  Image_set_pixel(&img, 1, 0, {0, 0, 255});   // Blue
  Image_set_pixel(&img, 1, 1, {255, 255, 0}); // Yellow

  // Create a stringstream to capture the printed output
  std::stringstream output;

  // Call the Image_print function to print the image
  Image_print(&img, output);

  // Define the expected output for the sample image
  std::string expectedOutput =
      "P3\n"
      "2 2\n"
      "255\n"
      "255 0 0 0 255 0 \n"
      "0 0 255 255 255 0 \n";

  // Check if the printed output matches the expected output
  assert(output.str() == expectedOutput);

  //Second test
  // Create a single-pixel Image with 1x1 dimensions
    Image img1;
    Image_init(&img1, 1, 1);

    // Set the pixel color to a known value
    Image_set_pixel(&img1, 0, 0, {255, 0, 0}); // Red

    // Create a stringstream to capture the printed output
    std::stringstream output1;

    // Call the Image_print function to print the image
    Image_print(&img1, output1);

    // Define the expected output for the single-pixel image
    string expectedOutput1 =
        "P3\n"
        "1 1\n"
        "255\n"
        "255 0 0 \n";

    // Check if the printed output matches the expected output
    assert(output1.str() == expectedOutput1);

    //Third test
    // Create a non-square Image with dimensions 3x2
}
TEST(test_image_width)
{
  // Create a sample Image with known dimensions (e.g., 4x6)
  // First test
  Image img;
  Image_init(&img, 4, 6); // Assuming Image_init initializes the image

  // Call the Image_width function to get the width of the Image
  int width = Image_width(&img);

  // Check if the actual width matches the expected width (4)
  ASSERT_EQUAL(width, 4);

  // Second test
  // Create a single-pixel Image (1x1)
  Image img1;
  Image_init(&img1, 1, 1);

  // Call the Image_width function to get the width
  int width1 = Image_width(&img1);

  // Check if the actual width matches the expected width (which is 1)
  ASSERT_EQUAL(width1, 1);

  // Third test
  //  Create a rectangular Image with known dimensions (3x4)
}
TEST(test_image_height)
{
  // Create an Image with known dimensions (e.g., 3x4)
  // First test case
  Image img;
  Image_init(&img, 3, 4);

  // Call the Image_height function to get the height of the Image
  int height = Image_height(&img);

  // Check if the actual height matches the expected height (4)
  ASSERT_EQUAL(height, 4);

  // Second test
  //  Create an Image with only the red_channel (1x3)
  Image img1;
  Image_init(&img1, 1, 3);

  // Call the Image_height function to get the height of the red_channel
  int height1 = Image_height(&img1);

  // Check if the actual height matches the expected height (which is 3)
  ASSERT_EQUAL(height1, 3);

  // Third test
  // Tests image with minimum height
}
TEST(test_image_get_pixel)
{
  // Create an Image with known dimensions (e.g., 3x3)
  // First test case
  Image img;
  Image_init(&img, 3, 3);

  // Fill the Image's color channels with known pixel values
  Pixel pixel1, pixel2, pixel3;
  pixel1.r = 100;
  pixel1.g = 150;
  pixel1.b = 200;

  pixel2.r = 50;
  pixel2.g = 75;
  pixel2.b = 100;

  pixel3.r = 25;
  pixel3.g = 38;
  pixel3.b = 50;

  // Fill the Red, Green, and Blue channels with the same known values
  for (int r = 0; r < Image_height(&img); r++)
  {
    for (int c = 0; c < Image_width(&img); c++)
    {
      *Matrix_at(&img.red_channel, r, c) = pixel1.r;
      *Matrix_at(&img.green_channel, r, c) = pixel1.g;
      *Matrix_at(&img.blue_channel, r, c) = pixel1.b;
    }
  }

  // Set a specific pixel in the Image (e.g., row 1, column 2)
  int target_row = 1;
  int target_column = 2;
  *Matrix_at(&img.red_channel, target_row, target_column) = pixel2.r;
  *Matrix_at(&img.green_channel, target_row, target_column) = pixel2.g;
  *Matrix_at(&img.blue_channel, target_row, target_column) = pixel2.b;

  // Call Image_get_pixel to retrieve the pixel at the specified location
  Pixel retrieved_pixel = Image_get_pixel(&img, target_row, target_column);

  // Check if the retrieved pixel matches the expected pixel (pixel2)
  ASSERT_EQUAL(retrieved_pixel.r, pixel2.r);
  ASSERT_EQUAL(retrieved_pixel.g, pixel2.g);
  ASSERT_EQUAL(retrieved_pixel.b, pixel2.b);

  // Second test
  //  Create a sample Image with known dimensions (1x1)
  Image img1;
  Image_init(&img1, 1, 1);

  // Fill the Image with a known pixel value (e.g., pure red)
  Pixel red_pixel1;
  red_pixel1.r = 255;
  red_pixel1.g = 0;
  red_pixel1.b = 0;
  Image_fill(&img1, red_pixel1);

  // Call the Image_get_pixel function to get the pixel at row 0, column 0
  Pixel pixela = Image_get_pixel(&img1, 0, 0);
  // Note: Row and column indices are 0-based

  // Check if the retrieved pixel matches the expected pixel value (pure red)
  ASSERT_EQUAL(pixela.r, 255);
  ASSERT_EQUAL(pixela.g, 0);
  ASSERT_EQUAL(pixela.b, 0);

  // Third test
}
TEST(test_image_set_pixel)
{
  // Create an Image with known dimensions (e.g., 3x3)
  // First test
  Image img;
  Image_init(&img, 3, 3);

  // Define a valid row and column within the Image dimensions
  const int row = 1;
  const int column = 2;

  // Define a valid color (Pixel) to set at the specified row and column
  Pixel color;
  color.r = 255; // Red component
  color.g = 128; // Green component
  color.b = 0;   // Blue component

  // Call the Image_set_pixel function to set the specified pixel with the color
  Image_set_pixel(&img, row, column, color);

  // Check if the pixel at the specified row and column has the correct color
  ASSERT_EQUAL(*Matrix_at(&img.red_channel, row, column), color.r);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, row, column), color.g);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, row, column), color.b);

  // Second test
  Image img1;
  Image_init(&img1, 3, 3);

  // Define a valid color (Pixel) to set at the top-left corner
  Pixel color1;
  color1.r = 255; // Red component
  color1.g = 128; // Green component
  color1.b = 0;   // Blue component

  // Call the Image_set_pixel function to set
  // the top-left corner pixel with the color
  Image_set_pixel(&img1, 0, 0, color1);

  // Check if the pixel at the top-left corner has the correct color
  assert(*Matrix_at(&img1.red_channel, 0, 0) == color1.r);
  assert(*Matrix_at(&img1.green_channel, 0, 0) == color1.g);
  assert(*Matrix_at(&img1.blue_channel, 0, 0) == color1.b);

  // Third test
  //  Create an Image with known dimensions (e.g., 3x3)
}
TEST(test_image_fill)
{
  // First test
  const int image_width1 = 3;
  const int image_height1 = 3;
  const Pixel fill_color1 = {255, 128, 64}; 
  //^^ Example fill color (e.g., orange)

  // Create an Image with known dimensions (3x3)
  Image img1;
  Image_init(&img1, image_width1, image_height1);

  // Call the Image_fill function to fill the 
  //entire image with the specified color
  Image_fill(&img1, fill_color1);

  // Check if all pixels in the image have been 
  //correctly filled with the fill color
  for (int r1 = 0; r1 < Image_height(&img1); r1++)
  {
    for (int c1 = 0; c1 < Image_width(&img1); c1++)
    {
      Pixel pixel1 = Image_get_pixel(&img1, r1, c1);

      // Check if the pixel's RGB components match the fill color
      ASSERT_EQUAL(pixel1.r, fill_color1.r);
      ASSERT_EQUAL(pixel1.g, fill_color1.g);
      ASSERT_EQUAL(pixel1.b, fill_color1.b);
    }
  }

  // Second test
  //  Define image dimensions (e.g., 3x3)
  const int image_width = 3;
  const int image_height = 3;

  // Create an Image with known dimensions (3x3)
  Image img;
  Image_init(&img, image_width, image_height);

  // Define an array of different fill colors
  Pixel fill_colors[] = {
      {255, 0, 0},   // Red
      {0, 255, 0},   // Green
      {0, 0, 255},   // Blue
      {255, 255, 0}, // Yellow
      {255, 0, 255}, // Magenta
      {0, 255, 255}  // Cyan
  };

  int color_index = 0;

  // Call the Image_fill function with each fill color
  for (int r = 0; r < Image_height(&img); r++)
  {
    for (int c = 0; c < Image_width(&img); c++)
    {
      // Fill the image with the current color
      Image_fill(&img, fill_colors[color_index]);

      // Check if all pixels in the image have been
      // correctly filled with the current color
      for (int i = 0; i < Image_height(&img); i++)
      {
        for (int j = 0; j < Image_width(&img); j++)
        {
          Pixel pixel = Image_get_pixel(&img, i, j);

          // Check if the pixel's RGB components match the current fill color
          assert(pixel.r == fill_colors[color_index].r);
          assert(pixel.g == fill_colors[color_index].g);
          assert(pixel.b == fill_colors[color_index].b);
        }
      }

      // Move to the next color
      color_index = (color_index + 1) % (sizeof(fill_colors) / 
      sizeof(fill_colors[0]));
    }
  }
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
