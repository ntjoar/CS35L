#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <getopt.h>

int frobcmp(char const* a, char const* b)
{
    for(; *a != ' ' && *b != ' '; a++, b++) 
    {
        if ((*a ^ 42) < (*b ^ 42) || *a == ' ') 
        {
            return -1;
        }
        if ((*a ^42) > (*b ^ 42) || *b == ' ') 
        {
            return 1;
        }
    }
    return 0;
}

int frobcmpOpt(char const* a, char const* b) //Option given
{
    for(; *a != ' ' && *b != ' '; a++, b++) 
    {
        char aUp = *a ^ 42;
        char bUp = *b ^ 42;
        if (toupper(aUp) < toupper(bUp)) 
        {
            return -1;
        }
        if (toupper(aUp) > toupper(bUp)) 
        {
            return 1;
        }
        if(*a == ' ' && *b != ' ')
        {
            return -1;
        }
        if(*a == ' ' && *b == ' ')
        {
            return 1;
        }
    }
    return 0;
}

int comp(const void* a, const void* b)
{
  const char* inp1 = *(const char **) a;
  const char* inp2 = *(const char **) b;
  return frobcmp(inp1, inp2);
}

int compOpt(const void* a, const void* b)
{
  const char* inp1 = *(const char **) a;
  const char* inp2 = *(const char **) b;
  return frobcmpOpt(inp1, inp2);
}

void iError()
{
    if(ferror(stdin))
    {
        fprintf(stderr, "Input error");
        exit(1);
    }
}

int main(int argc, char** argv) {
    struct stat fileS;

    if(fstat(0,&fileS) < 0)
    {
        fprintf(stderr, "Unable to read info");
        exit(1);
    }

    char* charArray;
    char** wordArray;
    char getCh;
    int fGiven;
    fGiven = 0;

    charArray = (char*)malloc(sizeof(char));
    wordArray = (char**)malloc(sizeof(char*));

    if(charArray == NULL || wordArray == NULL)
    {
        fprintf(stderr, "Error, no arguments detected");
        exit(1);
    }

    if(argc <= 0 || argc > 2)
    {
        fprintf(stderr, "Error, too many options given");
        exit(1);
    }

    if(argc == 2 && strcmp(argv[1], "-f") != 0)
    {
        fprintf(stderr, "Error, option given is invalid");
        exit(1);
    }

    if(argc == 2 && strcmp(argv[1], "-f") == 0)
    {
        fGiven = 1;
    }

    int cNum = 0; //Character array position
    int wNum = 0; //Word array position

    char currentCh[1];
    char nextCh[1];
    ssize_t cStatus = read(0, currentCh, 1);
    ssize_t status = read(0, nextCh, 1);
    if(cStatus < 0 || status < 0)
    {
        fprintf(stderr, "Error, fail to read");
    }
    int i = 0; // Is end of file

    while(status >= 0) //Organize and decode?
    {
        charArray[cNum] = currentCh[0];
        char* tempChar = realloc(charArray, sizeof(char*) * (cNum + 2));

        if(tempChar == NULL)
        {
            free(charArray);
            fprintf(stderr, "Char Array has leaking memory");
            exit(1);
        }
        charArray = tempChar;

        if(currentCh[0] == ' ' && nextCh[0] == ' ' && status != 0)
        {
            currentCh[0] = nextCh[0];
            status = read(0, nextCh, 1);
            iError();
            cNum++;
            continue;
        }

        if(status == 0 && i == 0 && currentCh[0] != ' ')
        {
            i = 1;
            currentCh[0] = ' ';
            charArray[cNum + 1] = currentCh[0];
            char* tempChar = realloc(charArray, sizeof(char*) * (cNum + 2));
            if(tempChar == NULL)
            {
                free(charArray);
                fprintf(stderr, "Char Array has leaking memory");
                exit(1);
            }
            charArray = tempChar;
        }

        if(currentCh[0] == ' ') //Add a word
        {
            wordArray[wNum] = charArray;
            char** tempWord = realloc(wordArray, sizeof(char*) * (wNum + 2));
            if(tempWord == NULL)
            {
                free(wordArray);
                fprintf(stderr, "Word Array has leaking memory");
                exit(1);
            }
            wordArray = tempWord;
            charArray = NULL;
            charArray = (char*)malloc(sizeof(char));
            wNum++;
            cNum = -1;
        }

        if(i == 1)
        {
            break;
        }
        else if(currentCh[0] == ' ' && status == 0)
        {
            break;
        }

        currentCh[0] = nextCh[0];
        status = read(0, nextCh, 1);
        iError();
        cNum++;
    }

    if(fGiven == 1)
    {
        qsort(wordArray, wNum, sizeof(char*), compOpt);
    }
    else
    {
        qsort(wordArray, wNum, sizeof(char*), comp);
    }
    
    int words;
    int letters;
    for(words = 0; words < wNum - 0; words++)
    {
        for(letters = 0;; letters++)
        {
            write(1, &wordArray[words][letters], 1);
            iError();
            if (wordArray[words][letters] == ' ')
            {   
                break;
            }
        }
    }

    int dest;
    for (dest = 0; dest < wNum; dest++) //Free allocated memory
    {
        free(wordArray[dest]);
    }
    free(wordArray);
    return 0;
}
