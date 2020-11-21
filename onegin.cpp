//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \mainpage
//!
//!  \author     dorner333
//!  \brief      program that take text from file, sort it an write to new file
//!  \version    9.0
//!  \param[in]  name  of file
//!  \param[out] sorted text
//!
//!
//! this program open your file, make qsort with comparision 1 - from the begin of strings,
//!                                                          2 - from the end   of strings.
//! and write text to file - "sorted.txt"
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

#include <stdio.h>
#include <sys\stat.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

//#include <TXLib.h>

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief    STR - struct that contain adress of the begining of the string and the length of string
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

typedef struct
    {
    char* pointer;
    int   length;
    } STR;

//-----------------------------------------------------------------------------

int open_file(char* *buffer);

int mkline(char* *buffer, STR* *arr_buffer,int size_of_file);

void print_to_file (STR* *arr_buffer,int linecounter, const char* mode);

int compare      (const void * x1, const void * x2);

int back_compare (const void * x1, const void * x2);

void print_file (char* buffer, int linecounter);

void SWAP(STR* array, int left, int right);

void fl_qsort (STR* array, int(*comparator)(const void*, const void*), int left, int right);

//-----------------------------------------------------------------------------

int main()
    {
    char* buffer     = NULL;
    STR*  arr_buffer = NULL;


    int sizeoffile  = open_file(&buffer);

    int linecounter = mkline(&buffer, &arr_buffer, sizeoffile);

    qsort (arr_buffer, linecounter, sizeof(STR), compare);
    print_to_file (&arr_buffer, linecounter, "w");

    //fl_qsort (arr_buffer, &compare, 0, linecounter-1);
    //print_to_file (&arr_buffer, linecounter, "a");

    qsort (arr_buffer, linecounter, sizeof(STR), compare);
    print_to_file (&arr_buffer, linecounter, "a");

    print_file (buffer, linecounter);

    return 0;
    }


//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       Function that open your file and copy all text to buffer
//!  \param[in]   name of file
//!  \param[out]  buffer
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
int open_file (char* *buffer)
    {
    char name[50] = "";
    printf ("Enter name of file\n");
    scanf  ("%s", name);
    printf ("\n");

    struct stat statistica = {0};
    int stat_error = stat (name, &statistica);
    assert (stat_error == 0);

    //printf ("stat Size of %s is: %ld\n", name, statistica.st_size);     //נאחלונא פאיכא stat

    FILE* input_file = fopen (name, "r");

    *buffer = (char*) calloc (statistica.st_size + 1, sizeof(char));

    statistica.st_size = fread (*buffer, sizeof(char), statistica.st_size, input_file);

    //printf ("fread Size of %s is: %ld\n", name, statistica.st_size);    //hfpvth afqkf fread

    fclose (input_file);

    return statistica.st_size;
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       Function that make strings from buffer and put them to arr_buffer
//!  \param[in]   buffer
//!  \param[out]  arr_buffer, linecounter - count of strings
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
int mkline(char* *buffer, STR* *arr_buffer,int size_of_file)
{
    int linecounter = 0;

    for (int i = 0; i < size_of_file; i++)
        {
        if ( (*buffer)[i] == '\n') linecounter++;
        }

     //printf("linecounter = %d\n", linecounter);

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
            (*buffer)[i] = '\0';
            (*arr_buffer)[arr_counter].pointer =  &(*buffer)[start_counter];
            (*arr_buffer)[arr_counter].length  =  length_counter;
            start_counter = i+1;
            arr_counter++;
            length_counter = 0;
            }
        else length_counter++;
        }

    //for (int i = 0; i < linecounter; i++) printf ("%s\n",(*arr_buffer)[i].pointer);
    //printf ("\n");




            //printf("adress of %d #%p\n",counter, &(*buffer)[i+1]);
            //printfstr(&(*buffer)[i+1]);
            // (*arr_buffer)[counter].pointer =  &(*buffer)[i+1];
            //counter++;



return linecounter;
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       comparator from the beginning of the string
//!  \param[in]   2 strings
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
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

        if   ( tolower(*(string1 + i)) > tolower(*(string2 + j)))   return  1;
        else                                                        return -1;
        break;
        }
    return length1 - length2;
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       comparator from the end of the string
//!  \param[in]   2 strings
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
int back_compare(const void * x1, const void * x2)
{
    char* string1 = ((STR*) x1) -> pointer;
    char* string2 = ((STR*) x2) -> pointer;
    int   length1 = ((STR*) x1) -> length,
          length2 = ((STR*) x2) -> length;

    for(int i = 1, j = 1; (i <= length1) && (j <= length2);)
        {

        if  (*(string1 + length1 - i) == *(string2 + length2 - j))
            {
            i++;
            j++;
            continue;
            }

        if  (isalpha (*(string1 + length1 - i)) == 0)
            {
            i++;
            continue;
            }

        if  (isalpha ( *(string2 + length2 - j) ) == 0)
            {
            j++;
            continue;
            }

        if   ( tolower(*(string1 + length1 - i)) > tolower(*(string2 + length2 - j)))   return  1;
        else                                                        return -1;
        break;
        }
    return length1 - length2;
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       it is my qsort, but it don't work now :(  If you see the problem, tel me pls!!!!
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
void fl_qsort (STR* array, int(*comparator)(const void*, const void*), int left, int right)
{
if (right >= left) return;
int begin = left;
int end   = right;
int pivot = (left + right)/2;
STR* base_element = array + pivot;                      //*

while (left <= right)
{
    while (comparator(array + left , base_element) > 0) left++ ;
    while (comparator(array + right, base_element) < 0) right--;

    if (left < right) SWAP(array, left, right);
}
fl_qsort (array,comparator,begin , right - 1);
fl_qsort (array,comparator, left + 1, end  );
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       swap 2 strings
//!  \param[in]   2 srrings
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
void SWAP(STR* array, int left, int right)
{
STR swapper = array[left];
              array[left] = array[right];
                            array[right] = swapper;
}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       function that write sorted text to file
//!  \param[in]   arr_buffer
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
void print_file (char* buffer, int linecounter)
{

printf ("Print unsorted file:\n\n");

int sum  = 0;
int pluss = 0;
for (int i = 0; i < linecounter; i++)
    {
    sum += printf("%s\n", buffer + sum);
    }


FILE* output_file = fopen ("sorted.txt" , "a");

fprintf (output_file, "Unsorted text:\n\n");
    sum  = 0;
    pluss = 0;
for (int i = 0; i < linecounter; i++)
    {
    sum += fprintf (output_file, "%s\n", buffer + sum);
    }

fclose (output_file);

}

//-----------------------------------------------------------------------------
//{[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
//!
//!  \brief       function that write unsorted text to file
//!  \param[in]   buffer
//!
//}[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]
void print_to_file (STR* *arr_buffer,int linecounter,  const char* mode)
{
printf ("Print sort file:  \n\n");

for (int i = 0; i < linecounter; i++)
    {
 if ( *((*arr_buffer)[i].pointer) == '\0') continue;
 printf ("%s\n",(*arr_buffer)[i].pointer);
    }
printf("\n");

printf ("[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n"
        "[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n");

FILE* output_file = fopen ("sorted.txt" , mode);
int len = 0;

fprintf (output_file,"Print sorted file:\n\n");
for (int i = 0; i < linecounter; i++)
    {
    if ( *((*arr_buffer)[i].pointer) == '\0') continue;
    fprintf (output_file,"%s",(*arr_buffer)[i].pointer);
    fprintf (output_file,"\n");
    }
fprintf (output_file,"\n\n");
fprintf (output_file,"[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n"
                     "[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n");

fclose (output_file);

}
