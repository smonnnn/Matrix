#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix mat_new(int width, int height){
	Matrix mat;
	mat.width = width;
	mat.height = height;
	mat.size = width * height;
	mat.data = calloc(mat.size, sizeof(float));
	return mat;
}

Matrix mat_new_from_data(int width, int height, float* data){
	Matrix mat;
	mat.width = width;
	mat.height = height;
	mat.size = width * height;
	mat.data = data;
	return mat;
}

Matrix mat_identity(int width, int height){
	if(width < height){
		printf("Matrix width cannot be smaller than height!\nCannot create an identity matrix for this size. Exiting...");
		exit(EXIT_FAILURE);
	}

	Matrix mat = mat_new(width, height);
	for(int i = 0; i < width; i++){
		mat.data[i + (i * width)] = 1.0f;
	}
	return mat;
}

void mat_print(Matrix* mat){
	for(int i = 0; i < mat->height; i++){
		for(int j = 0; j < mat->width; j++){
			printf("%7.2f ", mat->data[j + (i * mat->width)]);
		}
		printf("\n");
	}
	printf("-------------------------\n");
}

void mat_delete(Matrix* mat){
	free(mat->data);
	//free(mat);
}

void mat_set(Matrix* mat, int x, int y, float value){
	if((x >= mat->width) || (y >= mat->height)){
		printf("Index out of bounds, cannot set value!\n Exiting...\n");
		exit(EXIT_FAILURE);
	}
	mat->data[x + (y * mat->width)] = value;
}

void mat_mult_constant(Matrix* mat, float c){
	for(int i = 0; i < mat->size; i++){
		mat->data[i] *= c;
	}
}

void mat_mult_matrix(Matrix* mat1, Matrix* mat2, Matrix* output){
	if(mat1->width != mat2->height){
		printf("The first matrix's width does not match the second matrix's height!\nCannot compute the product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat2->width, mat1->height);
	for(int i = 0; i < output->width; i++){
		for(int j = 0; j < output->height; j++){
			for(int k = 0; k < mat1->width; k++){
				output->data[i + (j * output->width)] += (mat1->data[k + (j * mat1->width)] * mat2->data[i + (k * mat2->width)]);
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
	if((mat1->height != mat2->height) || (mat1->width != mat2->width)){
		printf("The sizes of the matrices do not match!\nCannot compute the sum of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat1->width, mat1->height);
	for(int i = 0; i < mat1->size; i++){
		output->data[i] = mat1->data[i] + mat2->data[i];
	}
}

void mat_subtract_matrix(Matrix* mat1, Matrix* mat2, Matrix* output){
	if((mat1->height != mat2->height) || (mat1->width != mat2->width)){
		printf("The sizes of the matrices do not match!\nCannot compute the sum of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat1->width, mat1->height);
	for(int i = 0; i < mat1->size; i++){
		output->data[i] = mat1->data[i] - mat2->data[i];
	}
}

void mat_element_wise_mult(Matrix* mat1, Matrix* mat2, Matrix* output){
	if((mat1->height != mat2->height) || (mat1->width != mat2->width)){
		printf("The sizes of the matrices do not match!\nCannot compute the hadamard product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	*output = mat_new(mat1->width, mat1->height);
	for(int i = 0; i < mat1->size; i++){
		output->data[i] = mat1->data[i] * mat2->data[i];
	}
}

void mat_apply_function(Matrix* mat, Matrix* output, float (*function)(float)){
	for(int i = 0; i < mat->size; i++){
		output->data[i] = (*function)(mat->data[i]);
	}
}

void mat_dot(Matrix* mat1, Matrix* mat2, float* output){
	Matrix mat3;
	*output = 0.0f;
	mat_mult_matrix(mat1, mat2, &mat3);
	for(int i = 0; i < mat3.size; i++){
		*output += mat3.data[i];
	}
	mat_delete(&mat3);
}