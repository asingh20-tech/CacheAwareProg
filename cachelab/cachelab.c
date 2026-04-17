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

    return 0;
}

// GOOD LUCK!
