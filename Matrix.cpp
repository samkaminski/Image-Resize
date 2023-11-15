#include <cassert>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix *mat, int width, int height)
{
  // Ensure that the input pointer 'mat' is not nullptr
  assert(mat != nullptr);

  // Ensure that 'width' is within a valid range (greater than 
  //0 and within maximum allowed width)
  assert(width > 0 && width <= MAX_MATRIX_WIDTH);

  // Ensure that 'height' is within a valid range 
  //(greater than 0 and within maximum allowed height)
  assert(height > 0 && height <= MAX_MATRIX_HEIGHT);

  // Set the 'width' and 'height' properties of the Matrix struct
  mat->width = width;
  mat->height = height;

  // Initialize each element in the 'data' array to zero
  for (int i = 0; i < width * height; i++)
  {
    mat->data[i] = 0;
  }
}


// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix *mat, std::ostream &os)
{
  assert(mat != nullptr);

  // header
  os << mat->width << " " << mat->height << std::endl;

  // Iterate over each row in the matrix
  for (int row = 0; row < mat->height; row++)
  {

    // Iterate over each column in the matrix
    for (int column = 0; column < mat->width; column++)
    {

      // calculates index
      int index = mat->width * row + column;
      // prints data in matrix
      os << mat->data[index] << " ";
    }
    os << std::endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix *mat)
{
  assert(mat != nullptr);
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix *mat)
{
  assert(mat != nullptr);
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix *mat, const int *ptr)
{
  assert(mat != nullptr && ptr != nullptr);
   //^^ this checks if the ptr is null or not

  assert(ptr >= &mat->data[0] && ptr <= &mat->data[0] + 
  Matrix_width(mat) * Matrix_height(mat));
  //^^ this makes sure the ptr is in the matrix

  int index = ptr - &mat->data[0]; // Distance between ptr and the start of data
  return index / Matrix_width(mat);
}
// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix *mat, const int *ptr)
{
  assert(mat != nullptr && ptr != nullptr); 
  //^^ this checks if the ptr is null or not

  assert(ptr >= &mat->data[0] && ptr <= &mat->data[0] + 
  Matrix_width(mat) * Matrix_height(mat));
  //^^this makes sure the ptr is in the matrix

  int index = ptr - &mat->data[0];// Distance between ptr and the start of data
  return index % Matrix_width(mat); 
  //^^ whatever the remainder is will be the column
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int *Matrix_at(Matrix *mat, int row, int column)
{
  assert(mat != nullptr); // checks if matrix is null

  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  //^^checks if the row and column are in the matrix

  // calulates the index through the row and column given
  int index = (row * Matrix_width(mat)) + column;
  return &mat->data[index];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int *Matrix_at(const Matrix *mat, int row, int column)
{
  assert(mat != nullptr); // checks if matrix is null

  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  //^^checks if the row and column are in the matrix

  // calulates the index through the row and column given
  int index = (row * Matrix_width(mat)) + column;
  return &mat->data[index];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix *mat, int value)
{
  if (mat == nullptr)
  { // checks if matrix is null
    assert(false);
  }

  // Iterate over each row in the matrix
  for (int row = 0; row < Matrix_height(mat); row++)
  {

    // Iterate over each column in the matrix
    for (int column = 0; column < Matrix_width(mat); column++)
    {
      // sets the index to the value given
      *Matrix_at(mat, row, column) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix *mat, int value)
{
  assert(mat != nullptr); // checks if matrix is null

  // Iterate over each row in the matrix
  for (int row = 0; row < Matrix_height(mat); row++)
  {

    // Iterate over each column in the matrix
    for (int column = 0; column < Matrix_width(mat); column++)
    {

      // gets the index of the data to interate though the 1D matrix

      // checks to see if the the row is the top or
      // bottom row and if they are not check if it is the first or last collumn
      if (row == 0 || row == Matrix_height(mat) - 1 || 
      column == 0 || column == Matrix_width(mat) - 1)
      {
        // if true set the value at that index to the value
        *Matrix_at(mat, row, column) = value;
        //^^sets the index to the value given
      }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix *mat)
{
  assert(mat != nullptr); // checks if matrix is null

  // counter to check of the previous
  // max is smaller than the current value
  int max = *Matrix_at(mat, 0, 0);

  // Iterate over each row in the matrix
  for (int row = 0; row < Matrix_height(mat); row++)
  {

    // Iterate over each column in the matrix
    for (int column = 0; column < Matrix_width(mat); column++)
    {

      // checks if the current value is greater than current max
      if (*Matrix_at(mat, row, column) > max)
      {
        max = *Matrix_at(mat, row, column);
        // if true sets current value as max
      }
    }
  }
  return max; // returns max of data
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix *mat, int row,
                                      int column_start, int column_end)
{
  assert(mat != nullptr); // checks if matrix is null

  // checks if the row and column are in the matrix

  // sets the min at the first element of the column by calculating the index
  int min = *Matrix_at(mat, row, column_start);

  // sets the min column at the start
  int min_column = column_start;

  // Iterate over each column in the matrix
  for (int column = column_start + 1; column < column_end; column++)
  {

    // checks if the current value is less than current min
    if (*Matrix_at(mat, row, column) < min)
    {

      min = *Matrix_at(mat, row, column); // if true sets current value as min
      min_column = column;                // updates the column with the min
    }
  }

  return min_column; // returns the column with the min of data
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix *mat, int row,
                            int column_start, int column_end)
{
  assert(mat != nullptr); // checks if matrix is null

  // sets the min at the first element of the column by calculating the index
  int min = *Matrix_at(mat, row, column_start);
  // sets the min column at the start

  // Iterate over each column in the matrix
  for (int column = column_start + 1; column < column_end; column++)
  {

    // gets the index of the data to interate though the 1D matrix

    // checks if the current value is less than current min
    if (*Matrix_at(mat, row, column) < min)
    {
      min = *Matrix_at(mat, row, column); // if true sets current value as min
    }
  }

  return min; // returns the min of data in the region of the row
}
