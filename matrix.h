typedef struct Matrix{
	float* data;
	int size;
	int width;
	int height;
} Matrix;

Matrix mat_new(int width, int height);

Matrix mat_new_from_data(int width, int height, float* data);

Matrix mat_identity(int width, int height);

void mat_print(Matrix* mat);

void mat_delete(Matrix* mat);

void mat_set(Matrix* mat, int x, int y, float value);

void mat_mult_constant(Matrix* mat, float c);

void mat_mult_matrix(Matrix* mat1, Matrix* mat2, Matrix* output);

void mat_add_constant(Matrix* mat, float c);

void mat_add_matrix(Matrix* mat1, Matrix* mat2, Matrix* output);

void mat_element_wise_mult(Matrix* mat1, Matrix* mat2, Matrix* output);

void mat_apply_function(Matrix* mat, Matrix* output, float (*function)(float));

void mat_dot(Matrix* mat1, Matrix* mat2, float* output);