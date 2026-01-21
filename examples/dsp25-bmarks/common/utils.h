#ifndef utils-h
#define utils-h

#include <stdbool.h>

typedef struct {
	bool success;
	uint64_t cycles;
	unsigned int time;
} result;

unsigned int time(void (*func) (void));
bool check_bytes(size_t size, size_t number, void* result, void* ref);
result run_test_simple(char* name, void (*setup) (void), bool (*test) (unsigned int), bool (*check) (unsigned int));
result run_test_advanced(char* name, void (*setuo) (void), bool (*test) (unsigned int), bool (*check) (unsigned int), unsigned int num_tests);

#endif
