#include "../include/linreg.hpp"


LinReg::LinReg(Matrix &w):w(w), n(w.getycord()){}

LinReg::LinReg(int n): n(n+1) 
{
    w = Matrix(n+1, 1, double(1));
}

void LinReg::fit(Matrix X, Matrix &Y, double lr, int num_of_iter)
{
    for(int i = 0; i < num_of_iter; i++)
    {
        Matrix Y_pred = (*this)(X);
        Matrix grad = 2*(X.transpose())*(Y_pred-Y);
        w -= lr*grad;
    }
}

Matrix LinReg::operator()(Matrix X)
{
    X = X.concatenate_zeros();
    Matrix Y_pred = X*w;
    return Y_pred;
}

Matrix LinReg::get_weights()
{
    return w;
}