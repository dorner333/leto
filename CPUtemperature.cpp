#include <TXlib.h>
#include <stdio.h>


//-----------------------------------------------------------------------------

void print_data(int data[], int size);

void read_data(int data[], int size);

//-----------------------------------------------------------------------------

int main()
    {
    printf ("CPU temperature on August:\n\n\n");

    const int size = 31;

    int CPUtemperature[size] = {/*96, 55, 57, 57, 37, 57, 57, 57, 37, 28, 37, 57, 68, 58, 68, 59, 75, 75, 58, 59, 58, 59, 56, 65, 75, 85, 85, 85, 85, 75, 63*/};

    read_data  (CPUtemperature, size);

    //swap_data  (int data[], int size);

    print_data (CPUtemperature, size);

    return 0;
    }


//-----------------------------------------------------------------------------

void read_data (int data[], int size)
    {
       for (int i = 0; i < size; i++)
        {
        printf ("CPU temperature on August %2d - ", i+1);
        scanf  ("%d\n",data + i);
        }
    }

//-----------------------------------------------------------------------------

//void swap_data(int data[], int size)

//-----------------------------------------------------------------------------

void print_data(int data[], int size)
    {
    for (int i = 0; i < size; i++)
        {
        printf ("CPU temperature on August %2d - %d\n", i+1, data[i]);
        }
    }

//-----------------------------------------------------------------------------













