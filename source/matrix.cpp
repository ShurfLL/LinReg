#include "../include/matrix.hpp"
#include <random>
#include<cmath>

static double random_w(){
    static std::random_device rnd_device;
    static std::mt19937 mersenne_engine {rnd_device()};
    static std::uniform_real_distribution<double> dist (0, 1);
    return dist(mersenne_engine);
}

Matrix::Matrix(int xcord, int ycord) : xcord_(xcord), ycord_(ycord)
{
    allocSpace();
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] = 0;
        }
    }
}

Matrix::Matrix(int xcord, int ycord, double a) : xcord_(xcord), ycord_(ycord)
{
    allocSpace();
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] = a;
        }
    }
}

Matrix::Matrix(int xcord, int ycord, double **a) : xcord_(xcord), ycord_(ycord)
{
    allocSpace();
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix(int xcord, int ycord, bool rand) : xcord_(xcord), ycord_(ycord)
{
    allocSpace();
    if (rand) 
    {
        for (int i = 0; i < xcord_; ++i)
        {
            for (int j = 0; j < ycord_; ++j)
            {
                p[i][j] = random_w();
            }
        }
    }
    else
    {
        for (int i = 0; i < xcord_; ++i)
        {
            for (int j = 0; j < ycord_; ++j)
            {
                p[i][j] = 0;
            }
        }
    }
};

Matrix::Matrix(const Matrix &a) : xcord_(a.xcord_), ycord_(a.ycord_)
{
    allocSpace();
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] = (a.p)[i][j];
        }
    }
}

Matrix::Matrix(Matrix &&a) : xcord_(a.xcord_), ycord_(a.ycord_)
{
    p = a.p;
    a.p = nullptr;
}

Matrix::~Matrix(){
    xcord_ = 0;
    ycord_ = 0;
    for (int i = 0; i < xcord_; i++) {
        delete []p[i];
    }
    delete []p;
}

double &Matrix::operator()(int x, int y) 
{
    return p[x][y];
}

Matrix &Matrix::operator=(const Matrix &m)
{
    Matrix temp(m);
    std::swap(temp.p, this->p);
    this->xcord_ = temp.xcord_;
    this->ycord_ = temp.ycord_;
    return *this;
}

Matrix &Matrix::operator=(Matrix &&m)
{
    Matrix temp(m);
    std::swap(temp.p, this->p);
    this->xcord_ = temp.xcord_;
    this->ycord_ = temp.ycord_;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(double num)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] += num;
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(double num)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] -= num;
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
    Matrix temp(xcord_, m.ycord_);
    for (int i = 0; i < temp.xcord_; ++i)
    {
        for (int j = 0; j < temp.ycord_; ++j)
        {
            for (int k = 0; k < ycord_; ++k)
            {
                temp.p[i][j] += (p[i][k] * m.p[k][j]);
            }
        }
    }
    *this = temp;
    return *this;
}

Matrix &Matrix::operator*=(double num)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] *= num;
        }
    }
    return *this;
}

Matrix &Matrix::operator/=(double num)
{
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            p[i][j] /= num;
        }
    }
    return *this;
}

int Matrix::getycord()
{
    return this->ycord_;
}

int Matrix::getxcord()
{
    return this->xcord_;
}

Matrix Matrix::transpose()
{
    Matrix ret(ycord_, xcord_);
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}

double Matrix::dotProduct(Matrix a, Matrix b)
{
    double sum = 0;
    for (int i = 0; i < a.xcord_; ++i)
    {
        sum += (a(i, 0) * b(i, 0));
    }
    return sum;
}

void Matrix::allocSpace()
{
    p = new double *[xcord_];
    for (int i = 0; i < xcord_; ++i)
    {
        p[i] = new double[ycord_];
    }
}

Matrix Matrix::activate()
{
    Matrix A(xcord_, ycord_);
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            double value = 1 / (1 + exp(-p[i][j]));
            A(i, j) = value;
        }
    }

    return A;
}

Matrix Matrix::multiply(Matrix A)
{
    Matrix B = Matrix(xcord_, ycord_);
    for (int i = 0; i < xcord_; ++i)
    {
        for (int j = 0; j < ycord_; ++j)
        {
            B(i, j) = A(i, j) * p[i][j];
        }
    }

    return B;
}

void Matrix::print_size()
{
    std::cout << xcord_ << ' ' << ycord_;
}

Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

Matrix operator+(double num, const Matrix &m2)
{
    Matrix temp(m2);
    return (temp += num);
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator-(double num, const Matrix &m2)
{
    Matrix temp(m2);
    return (temp -= num);
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

Matrix operator*(const Matrix &m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix &m)
{
    return (m * num);
}

Matrix operator/(const Matrix &m, double num)
{
    Matrix temp(m);
    return (temp /= num);
}

std::ostream &operator<<(std::ostream &os, const Matrix &a)
{
    for (int i = 0; i < a.xcord_; ++i)
    {
        for (int j = 0; j < a.ycord_; ++j)
        {
            os << " " << a.p[i][j];
        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, const Matrix &a)
{
    for (int i = 0; i < a.xcord_; ++i)
    {
        for (int j = 0; j < a.ycord_; ++j)
        {
            is >> a.p[i][j];
        }
    }
    return is;
}

Matrix Matrix::concatenate_zeros(){
    Matrix a(xcord_, ycord_+1);
    for(int x = 0; x < xcord_; x++) 
    {
        a.p[x][0] = 1;
        for (int y = 1; y <= ycord_; y++)
        {
            a.p[x][y] = p[x][y-1];
        }
    }
    return a;
}
