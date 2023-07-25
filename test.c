#include "matrix.h"
#include <stdio.h>

int main(){
	Matrix mat1 = mat_identity(3, 3);
	Matrix mat2 = mat_identity(3, 3);
	Matrix result_mat_mult;
	float result_dot;

	mat_set(&mat2, 0, 0, 5.0f);
	mat_set(&mat2, 1, 1, 4.0f);
	mat_set(&mat2, 2, 2, 3.0f);

	mat_mult_matrix(&mat1, &mat2, &result_mat_mult);
	mat_dot(&mat1, &mat2, &result_dot);

	printf("Matrix multiplication test:\n");
	printf("A:\n");
	mat_print(&mat1);
	printf("B:\n");
	mat_print(&mat2);
	printf("A x B = C:\n");
	mat_print(&result_mat_mult);
	printf("A dot B: %f\n", result_dot);



	return 0;
}