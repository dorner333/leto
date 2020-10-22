#include <stdio.h>
#include <sys\stat.h>
#include <assert.h>
#include <stdlib.h>
#include <TXLib.h>
//-----------------------------------------------------------------------------
void test_file();


//-----------------------------------------------------------------------------

int main()
    {
    test_file();
    test_file();
    return 0;
    }

//-----------------------------------------------------------------------------

void test_file()
    {
    char name[50] = "";
    printf ("Enter name of file\n");
    scanf  ("%s", name);

    struct stat statistica = {0};
    int stat_error = stat (name, &statistica);
    assert (stat_error == 0);

    printf ("Size of %s is: %ld\n", name, statistica.st_size);

    FILE* input_file = fopen (name, "rb");

    char* buffer = (char*) calloc (statistica.st_size + 1, sizeof(char));

    for (int i = 0; i < statistica.st_size + 1; i++)
        {
        int symbol = fgetc (input_file);
        printf ("symbol - (%c)   code - (%d)\n", symbol, symbol);

        if (symbol == EOF) break;

        buffer[i] = symbol;

        }

    fclose (input_file);

//    char[collichestvo_strock

    printf ("(!(!(%s)!)!)\n", buffer);

    free (buffer);

    }

