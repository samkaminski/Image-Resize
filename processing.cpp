#include <cassert>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image *img)
{

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image *img)
{

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2)
{
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr * dr + dg * dg + db * db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// ------------------------------------------------------------------
// You may change code below this line!

// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image *img, Matrix *energy)
{
  assert(img != nullptr);
  assert(energy != nullptr);

  Matrix_init(energy, Image_width(img), Image_height(img));

  for (int row = 1; row < Image_height(img) - 1; ++row)
  {
    for (int column = 1; column < Image_width(img) - 1; ++column)
    {

      // calculate the north south east and west pixels
      Pixel north = Image_get_pixel(img, row - 1, column);
      Pixel south = Image_get_pixel(img, row + 1, column);
      Pixel east = Image_get_pixel(img, row, column - 1);
      Pixel west = Image_get_pixel(img, row, column + 1);

      // calculates energy value
      int energy_value = squared_difference(north, south) + 
      squared_difference(west, east);

      // puts value into matix
      *Matrix_at(energy, row, column) = energy_value;
    }
  }
  // filling the edges of the boarders with the max energy value
  int max = Matrix_max(energy);
  Matrix_fill_border(energy, max);
}

// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix *energy, Matrix *cost)
{
  assert(energy != nullptr);
  assert(cost != nullptr);

  // initializes cost
  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));

  // this sets the top row to the matching energy values
  for (int column = 0; column < Matrix_width(energy); ++column)
  {
    *Matrix_at(cost, 0, column) = *Matrix_at(energy, 0, column);
  }
  for (int row = 1; row < Matrix_height(energy); ++row)
  {
    for (int column = 0; column < Matrix_width(energy); ++column)
    {
      // this handles the edge case of if it is the 
      //first column and calculates the min of the top 2
      if (column == 0)
      {
        *Matrix_at(cost, row, column) =
            *Matrix_at(energy, row, column) +
            Matrix_min_value_in_row(cost, row - 1,
                                    column,
                                    column + 2);
      }
      // this handles the edge case of if it is the last column 
      //and calculates the min of the top 2
      else if (column == Matrix_width(energy) - 1)
      {
        *Matrix_at(cost, row, column) =
            *Matrix_at(energy, row, column) +
            Matrix_min_value_in_row(cost, row - 1,
                                    column - 1,
                                    column + 1);
      }
      // this calculates the min of the top 3 for all the middle values
      else
      {
        *Matrix_at(cost, row, column) =
            *Matrix_at(energy, row, column) +
            Matrix_min_value_in_row(cost, row - 1,
                                    column - 1,
                                    column + 2);
      }
    }
  }
}

// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix *cost, int seam[])
{
  assert(cost != nullptr);

  // gets the min column of the last row
  int bottom_row_min_column = 
  Matrix_column_of_min_value_in_row(cost, Matrix_height(cost) - 1,
  0, Matrix_width(cost));

  // gets the index for the last row
  int last_row = Matrix_height(cost) - 1;

  // index the last row into array seam
  seam[last_row] = bottom_row_min_column;

  // loops through every row from bottom up
  for (int row = (last_row - 1); row >= 0; --row)
  {

    // this handles the edge case of if it is the first column
    // is the in and calculates the min column of the top most left 2
    // and puts it in the array with the row as the index
    int min_row_column;

    if (seam[row + 1] == 0)
    {
      min_row_column = Matrix_column_of_min_value_in_row(cost, row,
                                                         0, 2);
    }
    // this handles the edge case of if it is the last column is the 
    //in and calculates the min column of the top most right 2
    // and puts it in the array with the row as the index
    else if (seam[row + 1] == Matrix_width(cost) - 1)
    {
      min_row_column = Matrix_column_of_min_value_in_row(cost, row,
      seam[row + 1] - 1, Matrix_width(cost));
    }
    // this handles the middle columns and calculates the min column of the 
    //top most right 2 and puts it in the array with the row as the index
    else
    {
      min_row_column = Matrix_column_of_min_value_in_row(cost, row,
      seam[row + 1] - 1, seam[row + 1] + 2);
    }
    // this indexes the row with the min
    seam[row] = min_row_column;
  }
}

// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[])
{
  // Ensure the input image is not null
  assert(img != nullptr);

  // Get the width and height of the input image
  int width = Image_width(img) - 1; // Decrease width by 1 to remove a column
  int height = Image_height(img);

  // Create a new image with reduced width
  Image *new_img = new Image;
  Image_init(new_img, width, height);

  // Iterate over each row in the input image
  for (int row = 0; row < height; ++row)
  {
    int seam_value = seam[row]; // Get the column index to remove
    int updated_col = 0;

    // Iterate over each column in the input image
    for (int column = 0; column < Image_width(img); ++column)
    {
      // Check if the current column is the one to remove (the seam)
      if (column == seam_value)
      {
        continue; // Skip this column in the seam
      }
      else
      {
        // Get the pixel at the current row and column
        Pixel p = Image_get_pixel(img, row, column);

        // Set the pixel in the new image at the same row and the updated column
        Image_set_pixel(new_img, row, updated_col++, p);
      }
    }
  }

  // Update the input image to be the new image (now with one column removed)
  *img = *new_img;

  // Delete the dynamically allocated new_img to avoid memory leaks
  delete new_img;
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
// NOTE:     The size of an array local variable must be a compile-time
//           constant. You can use MAX_MATRIX_HEIGHT as the constant,
//           since an image's height can be no larger than that.
void seam_carve_width(Image *img, int newWidth)
{
  // Ensure that the input image is valid and the new width 
  //is not greater than the current width.
  assert(img != nullptr);
  assert(newWidth <= Image_width(img));

  int width = Image_width(img);
  // Loop until the width of the image is reduced to the desired new width.
  while (width > newWidth)
  {

    // Create a matrix to store energy values for each pixel in the image.
    Matrix *energy = new Matrix;
    Matrix_init(energy, Image_height(img), width);

    // Compute the energy matrix for the image.
    compute_energy_matrix(img, energy);

    // Create a matrix to store the cumulative vertical cost values.
    Matrix *cost = new Matrix;
    Matrix_init(cost, Image_height(img), width);
    // Compute the vertical cost matrix based on the energy matrix.
    compute_vertical_cost_matrix(energy, cost);

    // Create an array to store the minimal vertical seam.
    int *seam = new int[Image_height(img)];

    // Find the minimal vertical seam in the cost matrix.
    find_minimal_vertical_seam(cost, seam);

    // Remove the minimal vertical seam from the image,
    //effectively reducing its width.
    remove_vertical_seam(img, seam);
    // Decrease the width of the image and free memory.
    --width;
    delete[] seam;
    delete energy;
    delete cost;
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight)
{
  assert(img != nullptr); // Check if the input image pointer is valid

  // Rotate the image 90 degrees counterclockwise
  rotate_left(img);

  // Call the seam_carve_width function to resize the image width
  // Note: This function assumes that the image width 
  //is being adjusted to newHeight
  seam_carve_width(img, newHeight);

  // Rotate the image 90 degrees clockwise to restore its original orientation
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight)
{
  assert(img != nullptr); // Ensure that the input image is not null.

  // TODO: Replace this line with your implementation of seam carving for width.
  seam_carve_width(img, newWidth);

  // TODO: Replace this line with your implementation of seam carving for height.
  seam_carve_height(img, newHeight);
}
