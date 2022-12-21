#ifndef linreg
#define linreg
#include "matrix.hpp"

class LinReg
{
private:
    Matrix w;
    int n = 0;
public:
    LinReg(Matrix &);

    LinReg(int); 

    void fit(Matrix , Matrix &, double , int);

    Matrix operator()(Matrix);

    Matrix get_weights();
};
#endif