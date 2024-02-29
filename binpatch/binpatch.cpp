#include <cstdio>
#include <cassert>

const char* FILE_NAME = "arseasy.com";

int main ()
{
    FILE* file = fopen (FILE_NAME, "rb+");
    if (!file)
    {
        fprintf (stderr, "Error with opening file! \n");
        return 1;
    }

    fseek (file, 1, SEEK_SET);
    fputc (0x79, file);         // change offset in first jump

    fseek (file, 0, SEEK_SET);
    fclose (file);
}
