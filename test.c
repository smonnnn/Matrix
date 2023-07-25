#include "matrix.h"
#include <stdio.h>

int main(){
	Matrix mat1 = mat_identity(3, 3);
	Matrix mat2 = mat_identity(3, 3);
	Matrix result;

	mat_set(&mat2, 0, 0, 5.0f);
	mat_set(&mat2, 1, 1, 4.0f);
	mat_set(&mat2, 2, 2, 3.0f);

	mat_mult_matrix(&mat1, &mat2, &result);

	mat_print(&mat1);
	mat_print(&mat2);
	mat_print(&result);

	return 0;
}