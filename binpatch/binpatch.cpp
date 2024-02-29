#include <cstdio>
#include <cassert>

enum ProgramStatus
{
    NO_ERROR = 0,
    ERROR    = 1
};

const int CMD_ARGS = 2;

#define CHECK_STATUS(status)  \
    if (status == ERROR)      \
        return ERROR

static FILE* OpenFile  (ProgramStatus* status, const char* file_name, const char* open_mode);
static void  MakePatch (FILE* file);

int main (int argc, const char** argv)
{
    if (argc != CMD_ARGS)
    {
        fprintf (stderr, "Incorrest cmd line arguments input! \n");
        return 1;
    }

    ProgramStatus status = NO_ERROR;

    FILE* file = OpenFile (&status, argv[1], "rb+");
    CHECK_STATUS (status);

    MakePatch (file);
    fclose (file);

    return NO_ERROR;
}

static FILE* OpenFile (ProgramStatus* status, const char* file_name, const char* open_mode)
{
    assert (status);
    assert (file_name);
    assert (open_mode);

    FILE* file = fopen (file_name, "rb+");
    if (!file)
    {
        fprintf (stderr, "Error with opening file! \n");
        *status = ERROR;
    }

    return file;
}

static void MakePatch (FILE* file)
{
    assert (file);

    fseek (file, 1, SEEK_SET);
    fputc (0x79, file);         // change offset in first jump

    fseek (file, 0, SEEK_SET);
}
