#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic)
{
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix

  // Test case 2 for test_fill_basic
  // Test case: Fills a 4x4 Matrix with a value and checks
  // that Matrix_at returns that value for each element.
  Matrix *mat1 = new Matrix; // create a Matrix in dynamic memory

  const int width1 = 4;
  const int height1 = 4;
  const int value1 = 99; // Different value than the previous test
  Matrix_init(mat1, width1, height1);
  Matrix_fill(mat1, value1);

  for (int r1 = 0; r1 < height1; ++r1)
  {
    for (int c1 = 0; c1 < width1; ++c1)
    {
      ASSERT_EQUAL(*Matrix_at(mat1, r1, c1), value1);
    }
  }

  delete mat1; // delete the Matrix

  // Test case 3 for test_fill_basic
  // Test case: Fills a 0x0 Matrix
  // Edge case
  // THIS GIVES AN ERROR CHECK OFFICE HOURS FOR IT
  // Matrix *mat2 = new Matrix; // create a Matrix in dynamic memory

  // const int width2 = 0;
  // const int height2 = 0;
  // const int value2 = 100; 
  // Value to fill the matrix (can be any value)

  // Initialize the matrix with zero dimensions
  // Matrix_init(mat2, width2, height2);

  // Attempt to fill the matrix with the specified value
  // Matrix_fill(mat2, value2);

  // Check that no assertion errors occur, indicating that the function
  // should handle zero dimensions 
  //gracefully without accessing invalid memory.

  // delete mat2; // delete the Matrix

  // Test case 4 for test_fill_basic
  // Fills a 500x500 Matrix
  // Edge case
  Matrix *mat3 = new Matrix; // create a Matrix in dynamic memory

  const int width3 = 500;  // Very large width
  const int height3 = 500; // Very large height
  const int value3 = 499;  // Value to fill the matrix

  Matrix_init(mat3, width3, height3);
  Matrix_fill(mat3, value3);

  for (int r3 = 0; r3 < height3; ++r3)
  {
    for (int c3 = 0; c3 < width3; ++c3)
    {
      ASSERT_EQUAL(*Matrix_at(mat3, r3, c3), value3);
    }
  }

  delete mat3; // delete the Matrix

  // Test case 5 for test_fill_basic
  //  Tests 1x1
  Matrix *mat4 = new Matrix;
  const int value4 = 123;
  Matrix_init(mat4, 1, 1);
  Matrix_fill(mat4, value4);
  ASSERT_EQUAL(*Matrix_at(mat4, 0, 0), value4);
  delete mat4;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp 
//as needed.
TEST(test_matrix_init)
{
  // Test case 1
  const int width = 3;
  const int height = 4;
  Matrix mat; // Create a Matrix object (no need for dynamic allocation)

  // Initialize the matrix using the function under test
  Matrix_init(&mat, width, height);

  // Verify that the matrix has been initialized correctly
  ASSERT_EQUAL(mat.width, width);
  ASSERT_EQUAL(mat.height, height);

  // Verify that all elements in the matrix have been set to 0
  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      ASSERT_EQUAL(mat.data[r * width + c], 0);
    }
  }

  // Test case 2
  // Tests smallest possible dimensions
  const int width1 = 1;
  const int height1 = 1;
  Matrix mat1; 
  //^^ Create a Matrix object (no need for dynamic allocation)

  // Initialize the matrix using the function under test
  Matrix_init(&mat1, width1, height1);

  // Verify that the matrix has been initialized correctly
  ASSERT_EQUAL(mat1.width, width1);
  ASSERT_EQUAL(mat1.height, height1);

  // Verify that the single element in the matrix has been set to 0
  ASSERT_EQUAL(mat1.data[0], 0);

  // Test case 3
  // Tests largest possible dimensions
  // Edge case
  const int width2 = 500;
  const int height2 = 500;
  Matrix mat2; // Create a Matrix object 
  //(no need for dynamic allocation)

  // Initialize the matrix using the function under test
  Matrix_init(&mat2, width2, height2);

  // Verify that the matrix has been initialized correctly
  ASSERT_EQUAL(mat2.width, width2);
  ASSERT_EQUAL(mat2.height, height2);

  // Verify that all elements in the matrix have been set to 0
  for (int r2 = 0; r2 < height2; ++r2)
  {
    for (int c2 = 0; c2 < width2; ++c2)
    {
      ASSERT_EQUAL(mat2.data[r2 * width2 + c2], 0);
    }
  }
  // Test case 4
  //  Tests smallest width and largest height
  const int width3 = 1;
  const int height3 = 500;
  Matrix mat3; 
  //^^ Create a Matrix object (no need for dynamic allocation)

  // Initialize the matrix using the function under test
  Matrix_init(&mat3, width3, height3);

  // Verify that the matrix has been initialized correctly
  ASSERT_EQUAL(mat3.width, width3);
  ASSERT_EQUAL(mat3.height, height3);

  // Verify that all elements in the matrix have been set to 0
  for (int r3 = 0; r3 < height3; ++r3)
  {
    ASSERT_EQUAL(mat3.data[r3], 0);
    //^Since width is 1, we only need to check one element in each row.
  }

  // Test case 5
  //  Tests largest width and smallest height
  const int width4 = 500;
  const int height4 = 1;
  Matrix mat4; // Create a Matrix object 
  //(no need for dynamic allocation)

  // Initialize the matrix using the function under test
  Matrix_init(&mat4, width4, height4);

  // Verify that the matrix has been initialized correctly
  ASSERT_EQUAL(mat4.width, width4);
  ASSERT_EQUAL(mat4.height, height4);

  // Verify that all elements in the matrix have been set to 0
  for (int c4 = 0; c4 < width4; ++c4)
  {
    ASSERT_EQUAL(mat4.data[c4], 0);
    //^Since height is 1, we only need to check one element in each column.
  }
}
TEST(test_matrix_print)
{
  // Test case 1
  Matrix mat;
  Matrix_init(&mat, 2, 2);

  // Fill the Matrix with some data
  int data[4] = {1, 2, 3, 4};
  for (int i = 0; i < 4; i++)
  {
    mat.data[i] = data[i];
  }

  // Create a stringstream to capture the printed output
  stringstream output;

  // Call the Matrix_print function
  Matrix_print(&mat, output);

  // Define the corrected expected output string
  string expectedOutput =
      "2 2\n"
      "1 2 \n"
      "3 4 \n";

  // Check if the printed output matches the corrected expected output
  ASSERT_EQUAL(output.str(), expectedOutput);

  // Test case 2
  //  Create a single-element Matrix
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);
  mat1.data[0] = 50; // Set the single element to 50

  // Create a stringstream to capture the printed output
  std::stringstream output1;

  // Call the Matrix_print function
  Matrix_print(&mat1, output1);

  // Define the expected output for a single-element matrix
  std::string expectedOutput1 = "1 1\n50 \n";

  // Check if the printed output matches the expected output
  ASSERT_EQUAL(output1.str(), expectedOutput1);

  // Test case 3
  // Create a Matrix with dimensions 3x3 filled with zeros
  Matrix mat2;
  Matrix_init(&mat2, 3, 3);

  // Fill the Matrix with zeros
  for (int i2 = 0; i2 < 9; i2++)
  {
    mat2.data[i2] = 0;
  }

  // Create a stringstream to capture the printed output
  stringstream output2;

  // Call the Matrix_print function
  Matrix_print(&mat2, output2);

  // Define the expected output for a matrix filled with zeros
  std::string expectedOutput2 =
      "3 3\n"
      "0 0 0 \n"
      "0 0 0 \n"
      "0 0 0 \n";

  // Check if the printed output matches the expected output
  ASSERT_EQUAL(output2.str(), expectedOutput2);

  // Test case 4
  // Create a 3x2 matrix
  Matrix mat3;
  Matrix_init(&mat3, 2, 3);

  // Fill the matrix with zeros
  for (int i3 = 0; i3 < 6; i3++)
  {
    mat3.data[i3] = 0;
  }

  // Create a stringstream to capture the printed output
  stringstream output3;

  // Call the Matrix_print function
  Matrix_print(&mat3, output3);

  // Define the expected output for a matrix filled with zeros
  string expectedOutput3 =
      "2 3\n"
      "0 0 \n"
      "0 0 \n"
      "0 0 \n";

  // Check if the printed output matches the expected output
  ASSERT_EQUAL(output3.str(), expectedOutput3);

  // Test case 5
  //  Create a Matrix
  Matrix mat4;
  Matrix_init(&mat4, 2, 3); // 2 rows and 3 columns

  // Fill the Matrix with some data
  int data4[6] = {1, 2, 3, 4, 5, 6};
  for (int i4 = 0; i4 < 6; i4++)
  {
    mat4.data[i4] = data4[i4];
  }

  // Create a stringstream to capture the printed output
  stringstream output4;

  // Call the Matrix_print function
  Matrix_print(&mat4, output4);

  // Define the expected output string
  string expectedOutput4 =
      "2 3\n" // Width and height are swapped
      "1 2 \n"
      "3 4 \n"
      "5 6 \n";

  // Check if the printed output matches the expected output
  ASSERT_EQUAL(output4.str(), expectedOutput4);
}
TEST(test_matrix_width)
{
  // Create a Matrix with a known width
  Matrix mat;
  const int expectedWidth = 4;         // Set the expected width
  Matrix_init(&mat, expectedWidth, 3); 
  //^^ Set a different height for variation

  // Call the Matrix_width function
  int actualWidth = Matrix_width(&mat);

  // Check if the actual width matches the expected width
  ASSERT_EQUAL(actualWidth, expectedWidth);

  // Second test
  //  Create a single-element matrix (1x1)
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);

  // Call the Matrix_width function
  int actualWidth1 = Matrix_width(&mat1);

  // Check if the actual width is 1 for a single-element matrix
  ASSERT_EQUAL(actualWidth1, 1);

  // Third test
  // Create a matrix with a width of 500 
  //and a different height for variation
  Matrix mat2;
  const int expectedWidth2 = 500; // Set the expected width
  Matrix_init(&mat2, expectedWidth2, 10); 
  //^^ Set a different height for variation

  // Call the Matrix_width function
  int actualWidth2 = Matrix_width(&mat2);

  // Check if the actual width matches the expected width
  ASSERT_EQUAL(actualWidth2, expectedWidth2);

  // Fourth test
  const int matrix_width3 = 294;
  const int matrix_height3 = 5;

  // Create a Matrix with a width of 294 and height of 5
  Matrix mat3;
  Matrix_init(&mat3, matrix_width3, matrix_height3);

  //Call the Matrix_width function to get the width of the matrix
  int width3 = Matrix_width(&mat3);

  // Check if the actual width matches the expected width (294)
  ASSERT_EQUAL(width3, matrix_width3);
}
TEST(test_matrix_height)
{
  // Create a Matrix with a known height
  // First test
  Matrix mat;
  const int expectedHeight = 6;// Set the expected height
  Matrix_init(&mat, 4, expectedHeight); 
  //^^ Set a different width for variation

  // Call the Matrix_height function
  int actualHeight = Matrix_height(&mat);

  // Check if the actual height matches the expected height
  ASSERT_EQUAL(actualHeight, expectedHeight);

  // Second test
  //  Create a single-element matrix (1x1)
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);

  // Call the Matrix_height function
  int actualHeight1 = Matrix_height(&mat1);

  // Check if the actual height is 1 for a single-element matrix
  ASSERT_EQUAL(actualHeight1, 1);

  // Third test
  const int largeDimension2 = 500; // Set the dimension to 500
  // Create a matrix with large dimensions (500x500)
  Matrix mat2;
  Matrix_init(&mat2, 4, largeDimension2); 
  //^^ Set a different width for variation

  // Call the Matrix_height function
  int actualHeight2 = Matrix_height(&mat2);

  // Check if the actual height matches the large dimension
  ASSERT_EQUAL(actualHeight2, largeDimension2);

  // Fourth test
  // Create a matrix with typical dimensions (4x6)
  Matrix mat3;
  const int expectedHeight3 = 6; // Set the expected height
  Matrix_init(&mat3, 4, expectedHeight3); 
  //^^ Set the expected width

  // Call the Matrix_height function
  int actualHeight3 = Matrix_height(&mat3);

  // Check if the actual height matches the expected height
  ASSERT_EQUAL(actualHeight3, expectedHeight3);
}
TEST(test_matrix_row)
{
  // Create a Matrix with known dimensions (4x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 4, 3);

  // Fill the Matrix with data
  int data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  for (int i = 0; i < 12; i++)
  {
    mat.data[i] = data[i];
  }

  // Get a pointer to an element in the matrix 
  //(e.g., element at row 2, column 1)
  int *ptr = Matrix_at(&mat, 2, 1);

  // Call the Matrix_row function to get the row of the element
  int actualRow = Matrix_row(&mat, ptr);

  // Check if the actual row matches the expected row (2)
  ASSERT_EQUAL(actualRow, 2);

  // Second test
  //  Create a Matrix with known dimensions (3x3)
  Matrix mat1;
  Matrix_init(&mat1, 3, 3);

  // Fill the Matrix with data (positive integers)
  int data1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i1 = 0; i1 < 9; i1++)
  {
    mat1.data[i1] = data1[i1];
  }

  // Get a pointer to the first element 
  //(top-left corner) of the matrix
  int *firstElementPtr1 = &mat1.data[0];

  // Call the Matrix_row function with the 
  //pointer to the first element
  int row1 = Matrix_row(&mat1, firstElementPtr1);

  // Check if the actual row matches the expected 
  //row (which is 0)
  ASSERT_EQUAL(row1, 0);

  // Third test
  //  Create a Matrix with known dimensions (3x3)
  Matrix mat2;
  Matrix_init(&mat2, 3, 3);

  // Fill the Matrix with data (positive integers)
  int data2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i2 = 0; i2 < 9; i2++)
  {
    mat2.data[i2] = data2[i2];
  }

  // Obtain a pointer to the middle element of the matrix 
  //(row 1, column 1)
  int *ptr2 = Matrix_at(&mat2, 1, 1); // Middle element

  // Call the Matrix_row function to get 
  //the row of the middle element
  int row2 = Matrix_row(&mat2, ptr2);

  // Check if the actual row matches the 
  //expected row (which is 1)
  ASSERT_EQUAL(row2, 1);

  // Fourth test
  //  Create a Matrix with dimensions 3x4
  Matrix mat3;
  Matrix_init(&mat3, 3, 4);

  // Fill the Matrix with data (positive integers)
  int data3[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  for (int i3 = 0; i3 < 12; i3++)
  {
    mat3.data[i3] = data3[i3];
  }

  // Get a pointer to an element in the matrix 
  //(e.g., element at row 1, column 2)
  int *ptr3 = Matrix_at(&mat3, 1, 2);

  // Call the Matrix_row function to get the 
  //row of the element pointed to by ptr
  int row3 = Matrix_row(&mat3, ptr3);

  // Check if the actual row matches 
  //the expected row (which is 1)
  ASSERT_EQUAL(row3, 1);

  // Fifth test
  const int maxDimensions4 = 500;

  // Create a Matrix with maximum dimensions
  Matrix mat4;
  Matrix_init(&mat4, maxDimensions4, maxDimensions4);

  // Fill the Matrix with data (e.g., positive integers)
  int data4[maxDimensions4 * maxDimensions4];
  for (int i4 = 0; i4 < maxDimensions4 * maxDimensions4; i4++)
  {
    data4[i4] = i4 + 1; // Fill with sequential values
    mat4.data[i4] = data4[i4];
  }

  // Test the Matrix_row function with a pointer 
  //pointing to an element in the middle of the matrix
  int middleRowIndex4 = maxDimensions4 / 2;
  int middleColumnIndex4 = maxDimensions4 / 2;
  int *middleElementPtr4 = Matrix_at(&mat4, middleRowIndex4, 
  middleColumnIndex4);

  // Call the Matrix_row function to get the row of the middle element
  int middleElementRow4 = Matrix_row(&mat4, middleElementPtr4);

  // Check if the actual row matches the expected row 
  //(which is middleRowIndex)
  ASSERT_EQUAL(middleElementRow4, middleRowIndex4);
}
TEST(test_matrix_column)
{
  // Create a Matrix with known dimensions (5x4)
  // First test
  Matrix mat;
  Matrix_init(&mat, 5, 4);

  // Fill the Matrix with data
  int data[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
  16, 17, 18, 19, 20};
  for (int i = 0; i < 20; i++)
  {
    mat.data[i] = data[i];
  }

  // Get a pointer to an element in the matrix 
  //(e.g., element at row 2, column 3)
  int *ptr = Matrix_at(&mat, 2, 3);

  // Call the Matrix_column function to get the column of the element
  int actualColumn = Matrix_column(&mat, ptr);

  // Check if the actual column matches the expected column (3)
  ASSERT_EQUAL(actualColumn, 3);

  // Second test
  //  Create a Matrix with the smallest possible dimensions (1x1)
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);

  // Fill the Matrix with a single value (e.g., 42)
  *Matrix_at(&mat1, 0, 0) = 42;

  // Call the Matrix_column function to get the column of the element
  int actualColumn1 = Matrix_column(&mat1, Matrix_at(&mat1, 0, 0));

  // Check if the actual column matches the expected column (0)
  ASSERT_EQUAL(actualColumn1, 0);

  // Third test
  const int matrix_width2 = 500;
  const int matrix_height2 = 500;

  // Create a Matrix with largest possible dimensions (500x500)
  Matrix mat2;
  Matrix_init(&mat2, matrix_width2, matrix_height2);

  // Fill the Matrix with data (e.g., fill with a specific pattern)
  int value2 = 0;
  for (int r2 = 0; r2 < matrix_height2; r2++)
  {
    for (int c2 = 0; c2 < matrix_width2; c2++)
    {
      *Matrix_at(&mat2, r2, c2) = value2++;
    }
  }

  // Call the Matrix_at function to get a pointer to an element 
  //(e.g., row 250, column 300)
  int *ptr2 = Matrix_at(&mat2, 249, 299); 
  //^^ Note: Row and column indices are 0-based

  // Call the Matrix_column function to get the column of the element
  int actualColumn2 = Matrix_column(&mat2, ptr2);

  // Check if the actual column matches the expected column (299)
  ASSERT_EQUAL(actualColumn2, 299);
}
TEST(test_matrix_at)
{
  // Create a Matrix with known dimensions (4x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 4, 3);

  // Fill the Matrix with data (e.g., numbers 1 through 12)
  int data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  for (int i = 0; i < 12; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_at function to get a pointer to an element 
  //(e.g., row 2, column 3)
  int *ptr = Matrix_at(&mat, 1, 2); 
  //^^ Note: Row and column indices are 0-based

  // Check if the pointer points to the correct element 
  //(element at row 2, column 3)
  ASSERT_EQUAL(*ptr, 7);

  // Second test
  //  Create a Matrix with known dimensions (3x3)
  Matrix mat1;
  Matrix_init(&mat1, 3, 3);

  // Fill the Matrix with data (e.g., numbers 1 through 9)
  int data1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i1 = 0; i1 < 9; i1++)
  {
    mat1.data[i1] = data1[i1];
  }

  // Call the Matrix_at function to get a pointer to an element 
  //(e.g., row 2, column 3)
  int *ptr1 = Matrix_at(&mat1, 1, 2); 
  //^^ Note: Row and column indices are 0-based

  // Check if the pointer points to the correct element 
  //(element at row 2, column 3)
  ASSERT_EQUAL(*ptr1, 6);

  // Third test
  //  Create a Matrix with known dimensions (500x500)
  Matrix mat2;
  Matrix_init(&mat2, 500, 500);

  // Fill the Matrix with data (e.g., numbers 1 through 250000)
  for (int row2 = 0; row2 < 500; row2++)
  {
    for (int col2 = 0; col2 < 500; col2++)
    {
      mat2.data[row2 * 500 + col2] = row2 * 500 + col2 + 1;
    }
  }

  // Call the Matrix_at function to get a pointer
  // to an element at the upper bound (e.g., row 499, column 499)
  int *ptr2 = Matrix_at(&mat2, 499, 499);
  //^^ Note: Row and column indices are 0-based

  // Check if the pointer points to the correct element 
  //(element at row 499, column 499)
  ASSERT_EQUAL(*ptr2, 250000); 
  //^^ Expected value: 499 * 500 + 499 + 1 = 249500

  // Fourth test
  //  Create a Matrix with known dimensions (3x3)
  Matrix mat3;
  Matrix_init(&mat3, 3, 3);

  // Fill the Matrix with data (e.g., numbers 1 through 9)
  int data3[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i3 = 0; i3 < 9; i3++)
  {
    mat3.data[i3] = data3[i3];
  }

  // Call the Matrix_at function with lower-bound 
  //indices (1-based indexing)
  int *ptr3 = Matrix_at(&mat3, 1, 1); 
  //^^ Row and column indices start at 1

  // Check if the pointer points to the correct element 
  //(element at row 1, column 1)
  ASSERT_EQUAL(*ptr3, 5);
}
TEST(test_matrix_at_const)
{
  // Create a Matrix with known dimensions (3x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 3, 3);

  // Fill the Matrix with data 
  //(e.g., various positive and negative integers)
  int data[9] = {5, -2, 8, 0, 10, -1, 3, 7, 4};
  for (int i = 0; i < 9; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_at function with a
  // pointer-to-const to get an element 
  //(e.g., row 2, column 1)
  const int *ptr = Matrix_at(&mat, 1, 0); 
  //^^ Note: Row and column indices are 0-based

  // Check if the pointer-to-const points to the 
  //correct element (element at row 2, column 1)
  ASSERT_EQUAL(*ptr, 0);

  // Second test
  //  Create an empty Matrix (0x0)
  const int single_element_value1 = 20;

  // Create a Matrix with dimensions 1x1 and 
  //set the single element to the specified value
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);
  *Matrix_at(&mat1, 0, 0) = single_element_value1;

  // Call the Matrix_at function to get a 
  //pointer to the single element (row 0, column 0)
  const int *ptr1 = Matrix_at(&mat1, 0, 0);

  // Check if the pointer-to-const points 
  //to the correct single element
  ASSERT_EQUAL(*ptr1, single_element_value1);

  // Third test
  const int matrix_width2 = 3;
  const int matrix_height2 = 3;
  const int max_value2 = 500;

  // Create a Matrix with known dimensions (3x3)
  Matrix mat2;
  Matrix_init(&mat2, matrix_width2, matrix_height2);

  // Fill the Matrix with the maximum value (500)
  for (int r2 = 0; r2 < Matrix_height(&mat2); r2++)
  {
    for (int c2 = 0; c2 < Matrix_width(&mat2); c2++)
    {
      *Matrix_at(&mat2, r2, c2) = max_value2;
    }
  }

  // Call the Matrix_at function to get a
  // pointer-to-const to an element (e.g., row 2, column 1)
  const int *ptr2 = Matrix_at(&mat2, 1, 0);
  //^^ Note: Row and column indices are 0-based

  // Check if the pointer-to-const points to the 
  //correct element (element at row 2, column 1)
  ASSERT_EQUAL(*ptr2, max_value2);

  // Fourth test
  const int matrix_width3 = 3;
  const int matrix_height3 = 3;

  // Create a Matrix with known dimensions (3x3)
  Matrix mat3;
  Matrix_init(&mat3, matrix_width3, matrix_height3);

  // Fill the Matrix with negative values
  int data3[9] = {-5, -2, -8, 0, -10, -1, -3, -7, -4};
  for (int r3 = 0; r3 < Matrix_height(&mat3); r3++)
  {
    for (int c3 = 0; c3 < Matrix_width(&mat3); c3++)
    {
      *Matrix_at(&mat3, r3, c3) = data3[r3 * Matrix_width(&mat3) + c3];
    }
  }

  // Call the Matrix_at function to get an element 
  //(e.g., row 2, column 1)
  const int *ptr3 = Matrix_at(&mat3, 1, 0); 
  //^ Note: Row and column indices are 0-based

  // Check if the pointer-to-const points to the correct 
  //element (element at row 2, column 1)
  ASSERT_EQUAL(*ptr3, 0);
}
TEST(test_matrix_fill)
{
  // Create a Matrix with known dimensions (3x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 3, 3);

  // Fill the Matrix with data 
  //(e.g., various positive and negative integers)
  int data[9] = {5, -2, 8, 0, 10, -1, 3, 7, 4};
  for (int i = 0; i < 9; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_fill function to set all 
  //elements to a new value (e.g., 42)
  Matrix_fill(&mat, 42);

  // Check if all elements in the matrix are set to the new value (42)
  for (int r = 0; r < Matrix_height(&mat); r++)
  {
    for (int c = 0; c < Matrix_width(&mat); c++)
    {
      const int *ptr = Matrix_at(&mat, r, c);
      ASSERT_EQUAL(*ptr, 42);
    }
  }

  // Second test
  Matrix mat1; // Create an empty Matrix

  // Call the Matrix_fill function to set all elements 
  //to a new value (e.g., 42)
  Matrix_fill(&mat1, 42);

  // Since the matrix is empty, there's nothing to set,
  // so no assertions are needed.

  // Third test
  // Matrix with a single element
  const int original_value2 = 7; // Original value in the matrix
  const int new_value2 = 42;     // New value to fill the matrix with

  // Create a Matrix with dimensions 1x1
  Matrix mat2;
  Matrix_init(&mat2, 1, 1);

  // Set the single element in the matrix to the original value
  *Matrix_at(&mat2, 0, 0) = original_value2;

  // Call the Matrix_fill function to set all 
  //elements to the new value (42)
  Matrix_fill(&mat2, new_value2);

  // Check if the single element in the matrix is set 
  //to the new value (42)
  int updated_value2 = *Matrix_at(&mat2, 0, 0);
  ASSERT_EQUAL(updated_value2, new_value2);

  // Fourth test
  const int matrix_width3 = 3;
  const int matrix_height3 = 3;
  const int new_value3 = 42;

  // Create a Matrix with known dimensions (3x3) filled with zeros
  Matrix mat3;
  Matrix_init(&mat3, matrix_width3, matrix_height3);

  // Call the Matrix_fill function to set all 
  //elements to a new value (e.g., 42)
  Matrix_fill(&mat3, new_value3);

  // Check if all elements in the matrix are set to the new value (42)
  for (int r3 = 0; r3 < Matrix_height(&mat3); r3++)
  {
    for (int c3 = 0; c3 < Matrix_width(&mat3); c3++)
    {
      const int *ptr3 = Matrix_at(&mat3, r3, c3);
      ASSERT_EQUAL(*ptr3, new_value3);
    }
  }

  // Fifth test
  //  Max value
  const int max_value4 = 500;
  const int matrix_width4 = 3;
  const int matrix_height4 = 3;

  // Create a Matrix with known dimensions (3x3)
  Matrix mat4;
  Matrix_init(&mat4, matrix_width4, matrix_height4);

  // Call the Matrix_fill function to set all elements 
  //to the maximum value (500)
  Matrix_fill(&mat4, max_value4);

  // Check if all elements in the 
  //matrix are set to the maximum value (500)
  for (int r4 = 0; r4 < Matrix_height(&mat4); r4++)
  {
    for (int c4 = 0; c4 < Matrix_width(&mat4); c4++)
    {
      const int *ptr4 = Matrix_at(&mat4, r4, c4);
      ASSERT_EQUAL(*ptr4, max_value4);
    }
  }
}
TEST(test_matrix_fill_border)
{
  // Create a Matrix with known dimensions (4x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 4, 3);

  // Fill the Matrix with data 
  //(e.g., various positive and negative integers)
  int data[12] = {5, -2, 8, 0, 10, -1, 3, 7, 4, 1, 2, 3};
  for (int i = 0; i < 12; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_fill_border function to set 
  //the border elements to a new value (e.g., 42)
  Matrix_fill_border(&mat, 42);

  // Check if the border elements in the matrix 
  //are set to the new value (42)
  for (int r = 0; r < Matrix_height(&mat); r++)
  {
    for (int c = 0; c < Matrix_width(&mat); c++)
    {
      const int *ptr = Matrix_at(&mat, r, c);

      // Check if it's a border element 
      //(first/last row or first/last column)
      if (r == 0 || r == Matrix_height(&mat) - 1 || 
      c == 0 || c == Matrix_width(&mat) - 1)
      {
        ASSERT_EQUAL(*ptr, 42);
      }
      else
      {
        // Check if it's not a border element 
        //(should have original values)
        ASSERT_EQUAL(*ptr, data[r * Matrix_width(&mat) + c]);
      }
    }
  }

  // Second test
  //  Create a 1x1 Matrix
  Matrix mat1;
  Matrix_init(&mat1, 1, 1);

  // Call the Matrix_fill_border function to set the border 
  //element to a new value (e.g., 99)
  Matrix_fill_border(&mat1, 99);

  // Check if the single element in the matrix is 
  //set to the new value (99)
  const int *ptr1 = Matrix_at(&mat1, 0, 0);
  ASSERT_EQUAL(*ptr1, 99);

  // Third test
  // Matrix full of zeros
  const int matrix_width2 = 4;
  const int matrix_height2 = 3;

  // Create a Matrix with known dimensions (4x3) filled with zeroes
  Matrix mat2;
  Matrix_init(&mat2, matrix_width2, matrix_height2);

  // Call the Matrix_fill_border function to set the border elements 
  //to a new value (e.g., 99)
  Matrix_fill_border(&mat2, 99);

  // Check if the border elements in the matrix 
  //are set to the new value (99)
  for (int r2 = 0; r2 < Matrix_height(&mat2); r2++)
  {
    for (int c2 = 0; c2 < Matrix_width(&mat2); c2++)
    {
      const int *ptr2 = Matrix_at(&mat2, r2, c2);

      // Check if it's a border element 
      //(first/last row or first/last column)
      if (r2 == 0 || r2 == Matrix_height(&mat2) - 1 || c2 == 0 || 
      c2 == Matrix_width(&mat2) - 1)
      {
        ASSERT_EQUAL(*ptr2, 99);
      }
      else
      {
        // Check if it's not a border element (should remain zero)
        ASSERT_EQUAL(*ptr2, 0);
      }
    }
  }

  // Fourth test
  // Checks max value
  const int max_value3 = 500;
  const int matrix_width3 = 3;
  const int matrix_height3 = 3;

  // Create a Matrix with known dimensions (3x3)
  Matrix mat3;
  Matrix_init(&mat3, matrix_width3, matrix_height3);

  // Call the Matrix_fill_border function to set the border elements 
  //to the maximum value (500)
  Matrix_fill_border(&mat3, max_value3);

  // Check if the border elements in the matrix are set 
  //to the maximum value (500)
  for (int r3 = 0; r3 < Matrix_height(&mat3); r3++)
  {
    for (int c3 = 0; c3 < Matrix_width(&mat3); c3++)
    {
      const int *ptr3 = Matrix_at(&mat3, r3, c3);

      // Check if it's a border element 
      //(first/last row or first/last column)
      if (r3 == 0 || r3 == Matrix_height(&mat3) - 1 || c3 == 0 || 
      c3 == Matrix_width(&mat3) - 1)
      {
        ASSERT_EQUAL(*ptr3, max_value3);
      }
    }
  }
}
TEST(test_matrix_max)
{
  // Create a Matrix with known dimensions (3x3)
  // First test
  Matrix mat;
  Matrix_init(&mat, 3, 3);

  // Fill the Matrix with data (e.g., various positive and negative integers)
  int data[9] = {5, -2, 8, 0, 10, -1, 3, 7, 4};
  for (int i = 0; i < 9; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_max function to find the maximum element value in the matrix
  int max = Matrix_max(&mat);

  // Check if the actual maximum matches the expected maximum (10)
  ASSERT_EQUAL(max, 10);

  // Second test
  const int matrix_width1 = 3;
  const int matrix_height1 = 3;
  const int negative_data1[9] = {-5, -2, -8, -1, -10, -3, -7, -4, -6};

  // Create a Matrix with known dimensions (3x3) and fill it with negative values
  Matrix mat1;
  Matrix_init(&mat1, matrix_width1, matrix_height1);

  for (int i1 = 0; i1 < 9; i1++)
  {
    mat1.data[i1] = negative_data1[i1];
  }

  // Call the Matrix_max function to find the maximum element value in the matrix
  int max1 = Matrix_max(&mat1);

  // Check if the actual maximum matches the expected maximum (-1)
  ASSERT_EQUAL(max1, -1);

  // Third test
  const int matrix_width2 = 3;
  const int matrix_height2 = 3;

  // Create a Matrix with known dimensions (3x3) and fill it with zeros
  Matrix mat2;
  Matrix_init(&mat2, matrix_width2, matrix_height2);

  // Call the Matrix_max function to find the maximum element value in the matrix
  int max2 = Matrix_max(&mat2);

  // Check if the actual maximum matches the expected maximum (should be zero)
  ASSERT_EQUAL(max2, 0);

  // Fourth test
  const int single_element_value3 = 0;

  // Create a Matrix with dimensions 1x1 and set the single element to the value
  Matrix mat3;
  Matrix_init(&mat3, 1, 1);
  mat.data[0] = single_element_value3;

  // Call the Matrix_max function to find the maximum element value in the matrix
  int max3 = Matrix_max(&mat3);

  // Check if the actual maximum matches the expected maximum 
  //(single_element_value)
  ASSERT_EQUAL(max3, single_element_value3);

  // Fifth test
  const int largest_value4 = 500;
  const int matrix_width4 = 3;
  const int matrix_height4 = 3;

  // Create a Matrix with known dimensions (3x3)
  Matrix mat4;
  Matrix_init(&mat4, matrix_width4, matrix_height4);

  // Fill the Matrix with the largest possible value (500)
  for (int r4 = 0; r4 < Matrix_height(&mat4); r4++)
  {
    for (int c4 = 0; c4 < Matrix_width(&mat4); c4++)
    {
      *Matrix_at(&mat4, r4, c4) = largest_value4;
    }
  }

  // Call the Matrix_max function to find the maximum element value in the matrix
  int max4 = Matrix_max(&mat4);

  // Check if the actual maximum matches the expected maximum (500)
  ASSERT_EQUAL(max4, largest_value4);
}
TEST(test_matrix_column_of_min_value_in_row)
{
  // Create a Matrix with known dimensions (4x4)
  // First test
  Matrix mat;
  Matrix_init(&mat, 4, 4);

  // Fill the Matrix with data (positive integers)
  int data[16] = {5, 8, 12, 3, 10, 7, 9, 11, 14, 6, 13, 4, 2, 15, 1, 16};
  for (int i = 0; i < 16; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_column_of_min_value_in_row function to find the column
  // of the minimal value in a specific region (row 2, columns 1 to 4)
  int minColumn = Matrix_column_of_min_value_in_row(&mat, 2, 1, 4);
  //^^ Note: Column indices are 0-based

  // Check if the actual column with the minimal
  // value matches the expected column (which is 3)
  ASSERT_EQUAL(minColumn, 3);

  // Second test
  //  Create a Matrix with known dimensions (1x4)
}
TEST(test_matrix_min_value_in_row)
{
  // Create a Matrix with known dimensions (4x4)
  Matrix mat;
  Matrix_init(&mat, 4, 4);

  // Fill the Matrix with data (positive integers)
  int data[16] = {5, 8, 12, 3, 10, 7, 9, 11, 14, 6, 13, 4, 2, 15, 1, 16};
  for (int i = 0; i < 16; i++)
  {
    mat.data[i] = data[i];
  }

  // Call the Matrix_min_value_in_row function to find the minimal
  // value in a specific region (row 2, columns 1 to 4)
  int minValue = Matrix_min_value_in_row(&mat, 2, 1, 4);
  //^^ Note: Column indices are 0-based

  // Check if the actual minimal value matches the expected
  // minimal value (which is 4)
  ASSERT_EQUAL(minValue, 4);
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
