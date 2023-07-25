#include "matrix.h"
#include <stdio.h>

int main(){
	Matrix mat1 = mat_new(3, 3);
	Matrix mat2 = mat_new(3, 3);
	Matrix result_mat_mult;
	Matrix result_element_wise_mult;
	float result_dot;

	mat_set(&mat1, 0, 0, 1.0f);
	mat_set(&mat1, 1, 0, 2.0f);
	mat_set(&mat1, 2, 0, 3.0f);
	mat_set(&mat1, 0, 1, 4.0f);
	mat_set(&mat1, 1, 1, 5.0f);
	mat_set(&mat1, 2, 1, 6.0f);

	mat_set(&mat2, 0, 0, 10.0f);
	mat_set(&mat2, 1, 0, 11.0f);
	mat_set(&mat2, 0, 1, 20.0f);
	mat_set(&mat2, 1, 1, 21.0f);
	mat_set(&mat2, 0, 2, 30.0f);
	mat_set(&mat2, 1, 2, 31.0f);

	mat_mult_matrix(&mat1, &mat2, &result_mat_mult);
	mat_dot(&mat1, &mat2, &result_dot);
	mat_element_wise_mult(&mat1, &mat2, &result_element_wise_mult);

	printf("Matrix multiplication test:\n");
	printf("A:\n");
	mat_print(&mat1);
	printf("B:\n");
	mat_print(&mat2);
	printf("A x B = C:\n");
	mat_print(&result_mat_mult); //should be 140.00 146.00 320.00 335.00
	printf("A dot B: %f\n-------------------------\n", result_dot);
	printf("A element wise product B:\n");
	mat_print(&result_element_wise_mult);

	return 0;
}