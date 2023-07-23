//Functions only return a new matrix when the size changes.

typedef struct Matrix{
	float* data;
	int size;
	int width;
	int height;
} Matrix;

Matrix* mat_new(int width, int height);

void mat_mult_constant(Matrix* mat, float c);

Matrix* mat_mult_matrix(Matrix* mat1, Matrix* mat2);

void mat_add_constant(Matrix* mat, float c);

Matrix* mat_hadamard_product(Matrix* mat1, Matrix* mat2);

