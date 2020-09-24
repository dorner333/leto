//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \mainpage
//!
//!  \author     dorner333
//!  \brief      Function that solves a square equation
//!  \version    1.5
//!  \param[in]  a,b,c  square equation coefficients
//!  \param[out] x1,x2 roots of square equation
//!
//!This program gets the value of the coefficients (a b c),
//!processes them and gives the number of roots and the roots themselves
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

#include <stdio.h>
#include <math.h>

/*square equation solution*/


//-----------------------------------------------------------------------------

int solvesquare (double a, double b, double c, double* x1, double* x2);

int solvelinear(double a, double b, double* x);

int isZero (double value);

void printroots (int nofroots, double x1, double x2);

void test_isZero();
void test_solvesquare();
void test_solvelinear();

//-----------------------------------------------------------------------------

const double bias = 1e-5;
const int    infinity_roots_value = 666;

//-----------------------------------------------------------------------------

int main()
    {


//-----------------------------------------------------------------------------

test_solvesquare();
void test_solvelinear();
test_isZero();

//-----------------------------------------------------------------------------


    double a = 0,
           b = 0,
           c = 0;

    double x1 = 0,
           x2 = 0;

    printf("Enter equation coefficents\n");
    scanf ("%lg %lg %lg",&a ,&b, &c);
    printf("Solving equation: %.3lgx^2 + %.3lgx + %.3lg = 0\n",a ,b ,c);

    int nofroots = solvesquare (a, b, c, &x1, &x2);

    printroots(nofroots, x1, x2);

    return 0;
    }


//-----------------------------------------------------------------------------

//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       Function that calculates the roots
//!  \param[in]   a,b,c  square equation coefficients
//!  \param[out]  x1,x2 roots of square equation
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

int solvesquare (double a, double b, double c, double* x1, double* x2)
    {

    if (isZero(a) == 1)
        {
        return solvelinear(b, c, x1);
        }
    else
        {
        double discr = b*b - 4*a*c;

        if (discr < 0)
            return 0;
        else
            {
            if (discr > 0)
                {
                *x1 = (-b - sqrt(discr)) / (2 * a);
                *x2 = (-b + sqrt(discr)) / (2 * a);
                return 2;
                }
            else
                {
                *x1 = (-b) / (2 * a);
                return 1;
                }
            }
        }
    }

//-----------------------------------------------------------------------------

void test_solvesquare()
    {

    #define test      if (res == exp) printf("Test on %d OK\n",__LINE__);\
                      else            printf("Test on %d BAD: res - %d, expected - %d\n",__LINE__ , res, exp)

    double a = 0,
           b = 0,
           c = 0;

    double x1 = 0,
           x2 = 0;

    int res = solvesquare (a, b, c, &x1, &x2);
    int exp = infinity_roots_value;

    test;

           a = 1,
           b = 0,
           c = -4;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp = 2;

    test;

           a = 1,
           b = 1,
           c = 100;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp = 0;

    test;

           a = 0,
           b = 0,
           c = 1;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp = 0;

    test;

    #undef test
    }


//-----------------------------------------------------------------------------

//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       Function that calculates the roots, if a = 0
//!  \param[in]   b,c  linear equation coefficients
//!  \param[out]  x1  root of square equation
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

int solvelinear(double a, double b, double* x)
    {
    if (isZero(a) == 1)
            {
            if (isZero(b) == 1)
                return infinity_roots_value;
            else
                return  0;
            }
        else
            *x = -b/a;
        return 1;
    }

//-----------------------------------------------------------------------------

void test_solvelinear()
    {

    #define test      if (res == exp) printf("Test on %d OK\n",__LINE__);\
                      else            printf("Test on %d BAD: res - %d, expected - %d\n",__LINE__ , res, exp)

    double a = 0,
           b = 0;

    double x1 = 0;

    int res = solvelinear (a, b, &x1);
    int exp = infinity_roots_value;

    test;

           a = 1;
           b = 0;

           x1 = 0;

           res = solvelinear (a, b, &x1);
           exp = 0;

    test;

           a = 1;
           b = 1;

           x1 = 0;

           res = solvelinear (a, b, &x1);
           exp = 1;

    test;

    #undef test
    }




//-----------------------------------------------------------------------------

//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief      A function that compares a number to zero
//!  \param[in]  nofroots, x1, x2 roots of square equation
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

void printroots (int nofroots, double x1, double x2)
{
    switch (nofroots)
    {
     case  infinity_roots_value: printf ("infinity roots\n");           break;
     case  0                   : printf ("no roots\n");                 break;
     case  1                   : printf ("x1=%.3lg\n",x1);              break;
     case  2                   : printf ("x1=%.3lg x2=%.3lg\n",x1 ,x2); break;
    }
}

//-----------------------------------------------------------------------------

//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief A function that compares a number to zero
//!  \param[in] value
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

/*comparson with zero*/

int isZero (double value)
    {
    if (fabs (value) <= bias) return 1;
    if (fabs (value) >  bias) return 0;
    }

//-----------------------------------------------------------------------------

void test_isZero()
    {

    #define test      if (res == exp) printf("Test on %d OK\n",__LINE__);\
                      else            printf("Test on %d BAD: res - %d, expected - %d\n",__LINE__ , res, exp)


    double value = 0;
    int    res   = isZero(value);
    int    exp   = 1;

    test;

           value = 1;
           res   = isZero(value);
           exp   = 0;

    test;

           value = 1e-5 ;
           res   = isZero(value);
           exp   = 1;

    test;

    #undef test

    }
