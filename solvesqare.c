#include <stdio.h>
#include <TXLib.h>
#include <math.h>

/*Нахождение корней квадратного уравнения*/

int solvesquare (double a, double b, double c, double* x1, double* x2)
    {

    if (a == 0)
        {
        if (b == 0)
            {
            if (c == 0)
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


int main()
    {

    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    printf("Введите коэффиценты квадратного уравнения через пробел\n");
    scanf ("%lg %lg %lg",&a ,&b, &c);
    printf("Решаем уравнение: %.3lgx^2 + %.3lgx + %.3lg = 0\n",a ,b ,c);

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
