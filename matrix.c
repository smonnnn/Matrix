#include "matrix.h"

Matrix* mat_new(int width, int height){
	Matrix mat;
	mat.width = width;
	mat.height = height;
	met.size = width * height;
	mat.data = calloc(mat.size * sizeof(float));
	return &mat;
}

void mat_mult_constant(Matrix* mat, float c){
	for(int i = 0; i < mat->size; i++){
		mat->data[i] *= c;
	}
}

Matrix* mat_mult_matrix(Matrix* mat1, Matrix* mat2){
	if(mat1->width == mat2->heigth){
		printf("The first matrix's width does not match the second matrix's height!\nCannot compute the product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	Matrix output = mat_new(mat2->width, mat1->height);
	for(int i = 0; i < output.width; i++){
		for(int j = 0; j < output.height; j++){
			for(int k = 0; k < mat1->width; k++){
				output.data[i + (j * i)] += (mat1->data[k + (j * k)] * mat2->data[k + (i * k)]);
			}
		}
	}
	return &output;
}
