#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

// typedef struct {
//     uint64_t number;
//     unsigned step_count;
// } cache_entry;

// cache_entry cache[100000];
// unsigned cache_size = 0;

// unsigned is_in_cache(uint64_t number) {
//     for(int ix = 0; ix < cache_size; ++ix) {         // Checks cache for number as a key and returns the amount of steps
//         if (cache[ix].number == number) {
//             return cache[ix].step_count;
//         }
//     }
//     return -1;
// }

// void insert_to_cache(uint64_t number, unsigned count) {
//     if (cache_size < 100000) {                       // Updates the cache with the new key-value pair
//         cache[cache_size].number = number;
//         cache[cache_size].step_count = count;
//         cache_size++;
//     }
// }

typedef struct cache_entry {
    uint64_t number;
    unsigned step_count;
    struct cache_entry *prev;
    struct cache_entry *next;
} cache_entry;

typedef struct {
    cache_entry *head;
    cache_entry *tail;
    unsigned current_size;
    unsigned max_size;
} lru_cache;

lru_cache* generate_cache(unsigned cache_size) {    // Creates the cache and returns it
    lru_cache *cache = malloc(sizeof(lru_cache));   // Allocates memory for a lru_cache structure
    cache->head = NULL;
    cache->tail = NULL;
    cache->current_size = 0;
    cache->max_size = cache_size;
    return cache;
}

void recent_to_front(lru_cache *cache, cache_entry *entry) {  
    if (cache->head == entry) {             // Already at head, do nothing
        return;
    }
    // ***********
    // Figuring out logic
    // ***********
    if (!cache->tail) {                     // First entry in cache
        cache->tail = entry;
    }
}

void insert_to_cache (lru_cache *cache, uint64_t number, unsigned count) {
    // ***********
    // Figuring out insert function
    // ***********
}

unsigned collatz(uint64_t number) {
    if (number == 1) {                  // Checks case where no calculation is needed
        return 0;
    }
    // *** edit ***
    // unsigned count_from_cache = is_in_cache(number);
    // if (count_from_cache != -1) {
    //     return count_from_cache;
    // }

    unsigned long long new_number;      // Variable created to store number after each step
    if (number % 2 == 0) {              // Calculates each collatz step
        new_number = number / 2;
    } else {
        new_number = 3 * number + 1;
    }
    if (new_number == 1) {              // Checks new number to prevent unnecessary recursing
        return 1;
    }
    unsigned count = 1 + collatz(new_number);
    // *** edit ***
    // insert_to_cache(number, count);
    return count;
}

int main(int argc, char *argv[]) {
    
    unsigned N = atoi(argv[1]);                 // Amount of numbers to be tested
    unsigned MIN = atoi(argv[2]);               // Minimum number able to be tested
    unsigned long long MAX = atoi(argv[3]);     // Maximum number able to be tested
    unsigned steps_count;                       // Stores the amount of steps taken to finish one number
    uint64_t RN;                                // Stores the random number

    srand(time(NULL));                          // Ensures different random numbers each time program is ran

    FILE *collatz_file = fopen("collatz.csv", "w");
    fprintf(collatz_file, "Random Number, Steps\n");

    while (N > 0) {                             // Simulates Collatz Conjecture for all values
        uint64_t random_number = rand();
        RN = (random_number << 32) | rand();
        RN = MIN + (RN % (MAX - MIN + 1));

        steps_count = collatz(RN);
        fprintf(collatz_file, "%" PRIu64 ", %u\n", RN, steps_count);
        N -= 1;
    }
    fclose(collatz_file);
    return 0;
}