#include "matrix.h"

Matrix mat_new(int width, int height){
	Matrix mat;
	mat.width = width;
	mat.height = height;
	met.size = width * height;
	mat.data = calloc(mat.size * sizeof(float));
	return mat;
}

void mat_mult_constant(Matrix* mat, float c){
	for(int i = 0; i < mat->size; i++){
		mat->data[i] *= c;
	}
}

void mat_mult_matrix(Matrix* mat1, Matrix* mat2, Matrix* output){
	if(mat1->width != mat2->heigth){
		printf("The first matrix's width does not match the second matrix's height!\nCannot compute the product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat2->width, mat1->height);
	for(int i = 0; i < output.width; i++){
		for(int j = 0; j < output.height; j++){
			for(int k = 0; k < mat1->width; k++){
				output.data[i + (j * i)] += (mat1->data[k + (j * k)] * mat2->data[k + (i * k)]);
			}
		}
	}
}

void mat_add_constant(Matrix* mat, float c){
	for(int i = 0; i < mat->size; i++){
		mat->data[i] += c;
	}
}

void mat_add_matrix(Matrix* mat1, Matrix* mat2, Matrix* output){
	if((mat1->height != mat2->heigth) || (mat1->width != mat2->width)){
		printf("The sizes of the matrices do not match!\nCannot compute the sum of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat1->width, mat1->height);
	for(int i = 0; i < mat1->size; i++){
		output[i] = mat1->data[i] + mat2->data[i];
	}
}

void mat_hadamard_product(Matrix* mat1, Matrix* mat2, Matrix* output){
	if((mat1->height != mat2->heigth) || (mat1->width != mat2->width)){
		printf("The sizes of the matrices do not match!\nCannot compute the hadamard product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat1->width, mat1->height);
	for(int i = 0; i < mat1->size; i++){
		output[i] = mat1->data[i] * mat2->data[i];
	}
}