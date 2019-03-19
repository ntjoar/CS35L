#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iError()
{
  if(ferror(stdin))
    {
      fprintf(stderr, "Input error");
      exit(1);
    }
}

int main(int argc, char** argv){
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

    char currentCh = getchar();
    iError();
    int alreadyDone; // 0, 1, depending on whether putchar has been used.

    while(currentCh != EOF) // Transliterate                                                                        
    {
        int i;
        alreadyDone = 0;
        for(i = 0; i < strlen(from); i++)
        {
            if(currentCh == from[i])
            {
                putchar(to[i]);
                alreadyDone = 1;
                break;
            }
        }
        if(alreadyDone == 0)
        {
            putchar(currentCh);
        }
        currentCh = getchar();
        iError();
    }
}
