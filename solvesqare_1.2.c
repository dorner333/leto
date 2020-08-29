#include <stdio.h>
#include <TXLib.h>
#include <math.h>

/*square equation solution*/


//-----------------------------------------------------------------------------

int solvesquare (double a, double b, double c, double* x1, double* x2);

int isZero (double value);

void test_isZero();
void test_solvesquare();

const double bias = 1e-5;

//-----------------------------------------------------------------------------

int main()
    {


//-----------------------------------------------------------------------------

test_isZero();
test_solvesquare();

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

    if (nofroots == 2)
        printf ("x1=%.3lg x2=%.3lg\n",x1 ,x2);
    else
        {
        if (nofroots == 1)
        printf ("x1=%.3lg\n",x1);
        else
            {
            if (nofroots == 0)
                printf ("корней нет\n");
            else
                printf ("бесконечность корней\n");
            }
        }
    return 0;
    }


//-----------------------------------------------------------------------------


int solvesquare (double a, double b, double c, double* x1, double* x2)
    {

    if (isZero(a) == 1)
        {
        if (isZero(b) == 1)
            {
            if (isZero(c) == 1)
                return -1;
            else
                return  0;
            }
        else
            *x1 = -c/b;
        return 1;
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
    int exp= -1;

    test;

           a = 1,
           b = 0,
           c = -4;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp= 2;

    test;

           a = 1,
           b = 1,
           c = 100;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp= 0;

    test;

           a = 0,
           b = 0,
           c = 1;

           x1 = 0,
           x2 = 0;

           res = solvesquare (a, b, c, &x1, &x2);
           exp= 0;



    #undef test
    }


//-----------------------------------------------------------------------------


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


    double value = 0 ;
    int    res   = isZero(value);
    int    exp   = 1;

    test;

           value = 1 ;
           res   = isZero(value);
           exp   = 0;

    test;

           value = 1e-5 ;
           res   = isZero(value);
           exp   = 1;

    test;

    #undef test

    }


