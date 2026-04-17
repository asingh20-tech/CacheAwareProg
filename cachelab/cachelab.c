//
// cachelab.c - Cache lab template
//
//
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// more libraries if needed for your program
struct cacheline
{
    long long tag;
    int lru;
    int valid;
};

// print result of cache simulation showing hit number, miss number, miss rate, and total running time
void printResult(int hits, int misses, int missRate, int runTime)
{
    printf("[result] hits: %d misses: %d miss rate: %d%% total running time: %d cycle\n", hits, misses, missRate, runTime);
}

// main function should be coded here

int main(int argc, char **argv)
{
    int time = 0;
    long long m;
    int s;
    int e;
    int b;

    int hits = 0;
    int misses = 0;
    char filename[100];
    char replacement[50];
    int opt;

    while ((opt = getopt(argc, argv, "m:s:e:b:i:r:")) != -1)
    {
        switch (opt)
        {
        case 'm':
            m = atoi(optarg);
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'e':
            e = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 'i':
            strcpy(filename, optarg);
            break;
        case 'r':
            strcpy(replacement, optarg);
            break;
        }
    }
    int S = 1 << s;
    int E = 1 << e;
    printf("%lld m , %d s , %d e , %d b , %s i , %s r\n ", m, s, e, b, filename, replacement);

    struct cacheline **cache = malloc(S * sizeof(struct cacheline *));

    for (int i = 0; i < S; i++)
    {
        cache[i] = malloc(E * sizeof(struct cacheline));
        for (int j = 0; j < E; j++)
        {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].lru = 0;
        }
    }
    printf("S = %d , E = %d", S, E);

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        long long address;
        while (fscanf(file, "%llx", &address) == 1)
        {
            printf("%llx\n", address);
            int set_index = (address >> b) & ((1 << s) - 1);
            int tag = address >> (b + s);
            time++;
            int hit = 0;
            for (int j = 0; j < E; j++)
            {
                if (cache[set_index][j].valid == 1 && cache[set_index][j].tag == tag)
                {
                    hit = 1;
                    hits++;

                    cache[set_index][j].lru = time;

                    printf("HIT\n");
                    break;
                }
            }
            if (hit == 0)
            {
                misses++;
                int empty;
                printf("MISS\n");
                for (int j = 0; j < E; j++)
                {
                    if (cache[set_index][j].valid == 0)
                    {
                        cache[set_index][j].valid = 1;
                        cache[set_index][j].tag = tag;
                        cache[set_index][j].lru = 1;
                        empty = 1;
                        break;
                    }
                }
                if (empty == 0)
                {
                    int minlru = cache[set_index][0].lru;
                    int minindex = 0;

                    for (int j = 1; j < E; j++)
                    {
                        if (cache[set_index][j].lru < minlru)
                        {
                            minlru = cache[set_index][j].lru;
                            minindex = j;
                        }
                    }

                    cache[set_index][minindex].tag = tag;
                    cache[set_index][minindex].lru = time;
                }
            }
        }
    }
    else
    {
        printf("-----FILE DOSENT EXIST------");
    }
    return 0;
}

// GOOD LUCK!
