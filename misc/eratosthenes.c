#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Seive {
    bool* nums;
    int   length;
} Seive;

Seive* init_sieve(int length)
{
    Seive* seive = malloc(sizeof(Seive));

    seive->nums = malloc(length * sizeof(bool));
    memset(seive->nums, true, length * sizeof(bool));
    seive->length = length;

    return seive;
}

void free_seive(Seive* seive)
{
    free(seive->nums);
    free(seive);
}

int next_prime(int prime, Seive* seive)
{
    prime++;
    while (prime < seive->length && !seive->nums[prime])
        prime++;

    return prime;
}

void run_seive(Seive* seive)
{
    seive->nums[0] = false;
    seive->nums[1] = false;
    for (int prime = 2; prime < seive->length; prime = next_prime(prime, seive))
        for (int i = prime * 2; i <= seive->length; i += prime)
            seive->nums[i] = false;
}

void print_primes(Seive* seive)
{
    printf("[");
    for (int i = 0; i < seive->length; i++)
        if (seive->nums[i])
            printf("%d, ", i);
    printf("\b\b]\n");
}

int main()
{
    Seive* seive = init_sieve(1000);

    run_seive(seive);
    print_primes(seive);
    
    free_seive(seive);

    return 0;
}
