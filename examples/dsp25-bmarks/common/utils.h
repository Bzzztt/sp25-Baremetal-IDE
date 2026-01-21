#ifndef utils_h
#define utils_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
	bool success;
	uint64_t cycles;
	unsigned int time;
} result;

unsigned int time_func(void (*func) (void));
bool check_bytes(size_t size, size_t number, void* result, void* ref);
result run_test_simple(char* name, void (*setup) (unsigned int), bool (*test) (unsigned int), bool (*check) (unsigned int));
result run_test_advanced(char* name, void (*setup) (unsigned int), bool (*test) (unsigned int), bool (*check) (unsigned int), unsigned int num_tests);

#endif
