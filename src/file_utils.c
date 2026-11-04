#include <stdio.h>
#include <stdlib.h>

#include "file_utils.h"

char *read_file(char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *source_code = malloc(sizeof(char) * file_size);
    if (source_code == NULL)
    {
        return NULL;
    }

    fread(source_code, 1, file_size + 1, file);

    fclose(file);

    source_code[file_size] = '\0';

    return source_code;
}