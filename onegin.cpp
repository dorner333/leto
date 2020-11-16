#include <stdio.h>
#include <sys\stat.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include <TXLib.h>

//-----------------------------------------------------------------------------

typedef struct
    {
    char* pointer;
    int   length;
    } STR;

//-----------------------------------------------------------------------------

int open_file(char* *buffer);

int mkline(char* *buffer, STR* *arr_buffer,int size_of_file);

void print_file (STR* *arr_buffer,int linecounter);

void printfstr(STR* *arr_buffer, int line_counter);

int compare(const void * x1, const void * x2);

//-----------------------------------------------------------------------------

int main()
    {
    char* buffer     = NULL;
    STR*  arr_buffer = NULL;


    int sizeoffile  = open_file(&buffer);

    int linecounter = mkline(&buffer, &arr_buffer, sizeoffile);

    qsort (arr_buffer, linecounter, sizeof(STR), compare);

    print_file (&arr_buffer, linecounter);

    return 0;
    }

//-----------------------------------------------------------------------------

int open_file (char* *buffer)
    {
    char name[50] = "";
    printf ("Enter name of file\n");
    scanf  ("%s", name);

    struct stat statistica = {0};
    int stat_error = stat (name, &statistica);
    assert (stat_error == 0);

    //printf ("stat Size of %s is: %ld\n", name, statistica.st_size);     //размера файла stat

    FILE* input_file = fopen (name, "r");

    *buffer = (char*) calloc (statistica.st_size + 1, sizeof(char));

    statistica.st_size = fread (*buffer, sizeof(char), statistica.st_size, input_file);

    //printf ("fread Size of %s is: %ld\n", name, statistica.st_size);    //hfpvth afqkf fread

    fclose (input_file);

    return statistica.st_size;
}


int mkline(char* *buffer, STR* *arr_buffer,int size_of_file)
{
    int linecounter = 0;

    for (int i = 0; i < size_of_file; i++)
        {
        if ( (*buffer)[i] == '\n') linecounter++;
        }

     printf("linecounter = %d\n", linecounter);

    *arr_buffer = (STR*) calloc (linecounter + 1, sizeof (STR));

    ((*arr_buffer)[0].pointer) = &(*buffer)[0];
                                                 //printf("adress of 1 #%p\n", &(*buffer)[0]);
                                                 //printfstr(&(*buffer)[0]);


    int start_counter = 0,
        arr_counter   = 0,
        length_counter  = 0;

    for (int i = 0; i < size_of_file; i++)
        {
        if ( (*buffer)[i] == '\n' )
            {
            (*arr_buffer)[arr_counter].pointer =  &(*buffer)[start_counter];
            (*arr_buffer)[arr_counter].length  =  length_counter;
            start_counter = i+1;
            arr_counter++;
            length_counter = 0;
            }
        else length_counter++;
        }

    for (int i = 0; i < linecounter; i++)
        {
        printfstr(arr_buffer, i);
        }



            //printf("adress of %d #%p\n",counter, &(*buffer)[i+1]);
            //printfstr(&(*buffer)[i+1]);
            // (*arr_buffer)[counter].pointer =  &(*buffer)[i+1];
            //counter++;



return linecounter;
}
//-----------------------------------------------------------------------------

void printfstr(STR* *arr_buffer,int line_counter)
    {
    for (int j = 0; j < (*arr_buffer)[line_counter].length; j++)
        {
        printf("%c", *((*arr_buffer)[line_counter].pointer + j));
        }
    //printf("\n");
    //распечатка длины строки и адреса начала строки

    //printf("length of string #%d = %d; start of the string adress = %p",
    //line_counter + 1, arr_buffer[line_counter].length, arr_buffer[line_counter].pointer);

    printf("\n");
    }


//-----------------------------------------------------------------------------

int compare(const void * x1, const void * x2)
{
    char* string1 = ((STR*) x1) -> pointer;
    char* string2 = ((STR*) x2) -> pointer;
    int   length1 = ((STR*) x1) -> length,
          length2 = ((STR*) x2) -> length;
    int   ssize   = 0,
          counter = 0;

    if (length1 < length2) ssize = length1;
    else                   ssize = length2;

    for(int i = 0, j = 0; (i < ssize) && (j < ssize);)
        {

        if  (*(string1 + i) == *(string2 + j))
            {
            i++;
            j++;
            continue;
            }

        if  (isalpha (*(string1 + i)) == 0)
            {
            i++;
            continue;
            }

        if  (isalpha ( *(string2 + j) ) == 0)
            {
            j++;
            continue;
            }

        if   ( tolower(*(string1 + i)) > tolower(*(string2 + j))) counter = 1 ;
        else                                             counter = -1;
        break;
        }
    //int a = strcmp (string1, string2);
    return counter;
}


//-----------------------------------------------------------------------------

void print_file (STR* *arr_buffer,int linecounter)
{
printf ("Print sort file  \n\n\n");

for (int i = 0; i < linecounter; i++)
    {
    printfstr(arr_buffer,i);
    }

FILE* output_file = fopen ("w_onegin.txt" , "w");
int len = 0;
for (int i = 0; i < linecounter; i++)
    {
    if ( *((*arr_buffer)[i].pointer) == '\n') continue;
    len = (*arr_buffer)[i].length;
    for (int j = 0; j < len; j++)
        {
        fprintf (output_file,"%c",*((*arr_buffer)[i].pointer + j));
        }
    fprintf (output_file,"\n");
    }
fclose (output_file);

}
