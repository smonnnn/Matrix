#include "matrix.h"
#include <stdio.h>

int main(){
	float mat1_data[] = {
		1, 2, 3, 
		4, 5, 6, 
		0, 0, 0
	};
	float mat2_data[] = {
		10, 11, 0,
		20, 21, 0, 
		30, 31, 0
	};
	Matrix mat1 = mat_new_from_data(3, 3, mat1_data);
	Matrix mat2 = mat_new_from_data(3, 3, mat2_data);

	Matrix result_mat_mult;
	Matrix result_element_wise_mult;
	Matrix result_mat_add_mat;
	float result_dot;

	mat_mult_matrix(&mat1, &mat2, &result_mat_mult);
	mat_dot(&mat1, &mat2, &result_dot);
	mat_element_wise_mult(&mat1, &mat2, &result_element_wise_mult);
	mat_add_matrix(&mat1, &mat2, &result_mat_add_mat);

	printf("A:\n");
	mat_print(&mat1);
	printf("B:\n");
	mat_print(&mat2);
	printf("A x B:\n");
	mat_print(&result_mat_mult); //should be 140.00 146.00 320.00 335.00
	printf("A dot B: %f\n-------------------------\n", result_dot);
	printf("A element wise product B:\n");
	mat_print(&result_element_wise_mult);
	printf("A + B:\n");
	mat_print(&result_mat_add_mat);
	printf("A + 1:\n");
	mat_add_constant(&mat1, 1.0f);
	mat_print(&mat1);
	printf("B * 2:\n");
	mat_mult_constant(&mat2, 2.0f);
	mat_print(&mat2);

	mat_delete(&mat1);
	mat_delete(&mat2);
	mat_delete(&result_mat_mult);
	mat_delete(&result_element_wise_mult);
	mat_delete(&result_mat_add_mat);

	return 0;
}