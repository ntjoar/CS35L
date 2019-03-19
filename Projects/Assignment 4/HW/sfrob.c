#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frobcmp(char const* a, char const* b)
{
    for(; *a != ' ' && *b != ' '; a++, b++) 
    {
        if ((*a ^ 42) < (*b ^ 42) || *a == ' ') 
        {
            return -1;
        }
        if ((*a ^ 42) > (*b ^ 42) || *b == ' ') 
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

void iError()
{
    if(ferror(stdin))
    {
        fprintf(stderr, "Input error");
        exit(1);
    }
}

int main(void) {
    char* charArray;
    char** wordArray;

    charArray = (char*)malloc(sizeof(char));
    wordArray = (char**)malloc(sizeof(char*));

    if(charArray == NULL || wordArray == NULL)
    {
        fprintf(stderr, "Error, no arguments detected");
        exit(1);
    }

    int cNum = 0; //Character array position
    int wNum = 0; //Word array position

    char currentCh = getchar();
    iError();
    char nextCh = getchar();
    iError();

    while(currentCh != EOF) //Organize and decode?
    {
        charArray[cNum] = currentCh;
        char* tempChar = realloc(charArray, sizeof(char*) * (cNum + 2));

        if(tempChar == NULL)
        {
            free(charArray);
            fprintf(stderr, "Char Array has leaking memory");
            exit(1);
        }
        charArray = tempChar;

        if(currentCh == ' ' && nextCh != ' ') //Add a word
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

        if(currentCh == ' ' && nextCh == ' ') //Error testing on the spaces, because they can get annoying
        {
            while(&free)
            {
                if(currentCh != ' ')
                {
                    currentCh = getchar();
                    iError();
                }
                else
                {
                    break;
                }
            }
            nextCh = getchar();
            iError();
            cNum++;
            continue;
        }
        else if(currentCh == ' ' && nextCh == EOF)
        {
            break;
        }
        else if(nextCh == EOF)
        {
            currentCh = ' ';
            cNum++;
            continue;
        }
        cNum++;
        currentCh = nextCh;
        nextCh = getchar();
        iError();
    }

    qsort(wordArray, wNum, sizeof(char*), comp);

    int words;
    int letters;
    for(words = 0; words < wNum; words++)
    {
        for(letters = 0;; letters++)
        {
            putchar(wordArray[words][letters]);
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
