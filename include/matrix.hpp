#ifndef matrix
#define matrix
#include<iostream>
#include <cmath>
#include<random>

class Matrix
{
public:
    Matrix(int, int);
    Matrix(int, int, double);
    Matrix(int, int, double **);
    Matrix(int, int, bool);
    Matrix();
    ~Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    Matrix &operator=(const Matrix &);
    Matrix &operator=(Matrix &&);

    double &operator()(int x, int y);

    Matrix &operator+=(const Matrix &);
    Matrix &operator+=(double);
    Matrix &operator-=(const Matrix &);
    Matrix &operator-=(double);
    Matrix &operator*=(const Matrix &);
    Matrix &operator*=(double);
    Matrix &operator/=(double);

    int getxcord();
    int getycord();

    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, const Matrix &);

    Matrix transpose();

    double dotProduct(Matrix, Matrix);

    Matrix activate();
    Matrix multiply(Matrix);

    void print_size();

    Matrix concatenate_zeros();

private:
    int xcord_, ycord_;
    double **p;
    void allocSpace();
};

Matrix operator+(const Matrix &, const Matrix &);
Matrix operator+(double, const Matrix &);
Matrix operator-(const Matrix &, const Matrix &);
Matrix operator-(double, const Matrix &);
Matrix operator*(const Matrix &, const Matrix &);
Matrix operator*(const Matrix &, double);
Matrix operator*(double, const Matrix &);
Matrix operator/(const Matrix &, double);
#endif