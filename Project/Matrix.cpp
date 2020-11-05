#include "Matrix.h"


#define rdown(f) (f * f < 0.001f ? 0 : f)

Matrix::Matrix(int dimentions) : _dimentions(dimentions)
{
	For(i, dimentions)
	{
		auto v = std::vector<float>(dimentions);
		For (j, dimentions)
		{
			float scalar = .0f;
			if (i == j) scalar = 1.0f;

			v[j] = scalar;
		}
		_scalars.push_back(v);
	}
}

void Matrix::PrintMatrix()
{
	For(x, _dimentions)
	{
		For(y, _dimentions)
		{
			std::cout << rdown(_scalars[x][y]) << ' ';
		}
		std::cout << '\n';
	}
}

Matrix Matrix::Product(Matrix& m)
{
	Matrix product = Matrix(_dimentions);
	For(i, _dimentions)
	{
		For(j, _dimentions)
		{
			float sum = 0.0f;
			For(k, _dimentions)
			{
				sum += _scalars[i][k] * m._scalars[k][j];
			}
			product._scalars[i][j] = sum;
		}
	}
	return product;
}

void Matrix::MultiplyWith(Matrix& m)
{
	auto p = Product(m);
	_scalars = p._scalars;
}

void Matrix::SetScale(Vector2 scale)
{
	_scalars[0][0] *= scale.x;
	_scalars[1][1] *= scale.y;
}

void Matrix::SetRotation(float degrees)
{
	Matrix m = GetRotationMatrix(degrees);

	MultiplyWith(m);
}

Matrix Matrix::GetRotationMatrix(float degrees)
{
	float radians = degrees / 180.0f * PI;

	Matrix m;

	m._scalars[0][0] = cosf(radians);
	m._scalars[0][1] = sinf(radians);
	m._scalars[1][0] = -sinf(radians);
	m._scalars[1][1] = cosf(radians);

	return m;
}

void Matrix::SetOffset(Vector2 v)
{
	_scalars[2][0] = v.x;
	_scalars[2][1] = v.y;
}

Vector2 Matrix::GetTransformedVector(Vector2 v)
{
		Vector2 product;

		product.x = v.x * _scalars[0][0] + v.y * _scalars[1][0] + _scalars[2][0];
		product.y = v.x * _scalars[0][1] + v.y * _scalars[1][1] + _scalars[2][1];

		return product;
}
