#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>
/*
	Output matrices do not get allocated, please do this yourself using mat_new, mat_identity or mat_new_from_data. 
	Memory management is the responsibility of the function caller.
*/

float rand_01(){
    return rand() / ((double) RAND_MAX);
}

Matrix mat_new(int width, int height){
	Matrix mat;
	mat.width = width;
	mat.height = height;
	mat.size = width * height;
	mat.data = calloc(mat.size, sizeof(float));
	return mat;
}

Matrix mat_new_random_10(int width, int height){
	Matrix mat = mat_new(width, height);
	for(int i = 0; i < mat.size; i++){
		mat.data[i] = rand_01();
	}
	return mat;
}

void mat_resize_unsafe(Matrix* mat, int width, int height){
	mat->width = width;
	mat->height = height;
	mat->size = width * height;
}

void mat_resize_safe(Matrix* mat, int width, int height){
	mat_resize_unsafe(mat, width, height);
	mat->data = realloc(mat->data, mat->size * sizeof(float));
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

void mat_set(Matrix* mat, int width, int height, float value){
	if((width >= mat->width) || (height >= mat->height)){
		printf("Index out of bounds, cannot set value!\n Exiting...\n");
		exit(EXIT_FAILURE);
	}
	mat->data[width + (height * mat->width)] = value;
}

void mat_transpose(Matrix* mat){
	if(mat->width == 1 || mat->height == 1){
		int temp = mat->width;
		mat->width = mat->height;
		mat->height = temp;
	} 
	else{
		float* t = malloc(mat->size * sizeof(float));
		for(int i = 0; i < mat->width; i++){
			for(int j = 0; j < mat->height; j++){
				t[j + (i * mat->height)] = mat->data[i + (j * mat->width)]; //This memory access pattern sucks.
			}
		}
		int temp = mat->width;
		mat->width = mat->height;
		mat->height = temp;
		mat->data = t;
	}
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

	memset(output->data, 0, output->size * sizeof(float));

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
	if(mat1->size != mat2->size){
		printf("The sizes of the matrices do not match!\nCannot compute the sum of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < mat1->size; i++){
		output->data[i] = mat1->data[i] + mat2->data[i];
	}
}

void mat_subtract_matrix(Matrix* mat1, Matrix* mat2, Matrix* output){
	if(mat1->size != mat2->size){
		printf("The sizes of the matrices do not match!\nCannot compute the sum of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < mat1->size; i++){
		output->data[i] = mat1->data[i] - mat2->data[i];
	}
}

void mat_element_wise_mult(Matrix* mat1, Matrix* mat2, Matrix* output){
	if(mat1->size != mat2->size){
		printf("The sizes of the matrices do not match!\nCannot compute the element wise product of the two matrices, exiting...\n");
		exit(EXIT_FAILURE);
	}
	
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
	Matrix mat3 = mat_new(mat1->width, mat2->height);
	*output = 0.0f;
	mat_mult_matrix(mat1, mat2, &mat3);
	for(int i = 0; i < mat3.size; i++){
		*output += mat3.data[i];
	}
	mat_delete(&mat3);
}

//This function should only be used by the library itself (for now).
void submat_of(Matrix* mat, int index, Matrix* output){
	mat_resize_unsafe(output, mat->width - 1, mat->height - 1);

	int mat_index = mat->width;
	int output_index = 0;
	for(int j = 0; j < output->height; j++){
		for(int i = 0; i < mat->width; i++){
			if(i == index) {
				mat_index++;
				continue;
			}
			output->data[output_index] = mat->data[mat_index];
			mat_index++;
			output_index++;
		}
	}
	mat_print(output);
}

float mat_determinant(Matrix* mat){
	if(mat->width != mat->height){
		printf("Matrix is not square!\nCannot compute determinant. Exiting...");
		exit(EXIT_FAILURE);
	}

	if(mat->size == 4){
		return (mat->data[0] * mat->data[3]) - (mat->data[1] * mat->data[2]);
	} else {
		float output = 0.0f;
		Matrix buffer = mat_new(mat->width - 1, mat->height - 1);
		int sign = 1; 
		for(int i = 0; i < mat->width; i++){
			submat_of(mat, i, &buffer); 							//stupid memory copying heheheheee
    		output += sign * mat->data[i] * mat_determinant(&buffer);
    		sign *= -1;
		}
		mat_delete(&buffer);
		return output;
	}
	return 0.0f;
}