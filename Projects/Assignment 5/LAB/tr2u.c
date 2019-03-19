#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){ // Change all getchar and putchar to read and write

    if(argc != 3) // Call is also an argument
    {
        fprintf(stderr, "Error, invalid number of arguments");
        exit(1);
    }

    char* from = argv[1];
    char* to = argv[2];

    if(strlen(from) != strlen(to)) // Same length
    {
        fprintf(stderr, "Error, argument is not the same length");
        exit(1);
    }

    int s, t;
    for(s = 0; s < strlen(from); s++) // Are there duplicates?
    {
        for(t = 0; t < strlen(to); t++)
        {
            if(from[s] == to[t])
            {
                fprintf(stderr, "Duplicates detected");
                exit(1);
            }
        }
    }

    int alreadyDone; // 0, 1, depending on whether putchar has been used.
    char currentCh[1];
    ssize_t status = read(0, currentCh, 1);

    while(status > 0) // Transliterate                                                                        
    {
        size_t i;
        for(i = 0; i < strlen(from); i++)
        {
            if(currentCh[0] == from[i])
            {
                currentCh[0] = to[i];
                break;
            }
        }
        
        write(1, currentCh, 1);
        status = read(0, currentCh, 1);
    }
    return 0;
}