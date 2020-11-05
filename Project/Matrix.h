#pragma once
#include <vector>
#include <iostream>
#include "Vector2.h"

#define PI 3.1415926f
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)

class Matrix
{
	const int _dimentions;
	std::vector<std::vector<float>> _scalars;
public:
	Matrix(int dimentions = 3);
	void PrintMatrix();
	void MultiplyWith(Matrix& m);
	void SetScale(Vector2 scale);
	void SetRotation(float degrees);
	Matrix Product(Matrix& m);
	static Matrix GetRotationMatrix(float degrees);
	void SetOffset(Vector2 v);
	void SetRotation();
	//void SetOffset(Vector2& v);

	Vector2 GetTransformedVector(Vector2 v);
};

