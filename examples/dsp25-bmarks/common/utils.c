#include "utils.h"
#include <stdbool>
#include "chip_config.h"

static unsigned int read_cycles() {
	unsigned int cycles;
	asm volatile("rdcycle %0" : "=r" (cycles));
	return cycles;
}

// DEFAULT CHECK
bool check_bytes(size_t size, size_t number, void* result, void* ref) {
	bool success = true;
	for (unsigned int i = 0; i < size*number; i++) {
		if (result[i] != ref[i]) {
			success = false;
			printf("Byte %d is incorrect: got %c instead of %c\n", i, result[i], ref[i]);
		}
		success = success && (result[i] == ref[i]);
	}
	return success;
}

/* Time a function */
unsigned int time(void (*func) (void)) {
	unsigned int time = read_cycles();
	func();
	return read_cycles-time;
}

/* Run a test */
result run_test_simple(char* name, void (*setup) (unsigned int), bool (*test) (unsigned int), bool (*check) (unsigned int)) {
	printf("\nTesting test %s...\n", name);
	setup(0);
	unsigned int total_cycles = read_cycles();
	bool success = test(0);
	total_cycles = read_cycles() - total_cycles;
	unsigned int total_time = total_cycles / SYS_CLK_FREQ;

	if (check != NULL) {
		printf("Checking results...\n");
		success = success && check(0);
	}

	printf("- Total cycles: %d\n", total_cycles);
	printf("- Total time: %d\n", total_time);
	char* res_str = "FAILURE";
	if (success)
		res_str = "SUCCESS";
	printf("Test %s: %s!\n", name, res_str);
	printf("\n");

	result res;
	res.success = success;
	res.cycles = total_cycles;
	res.time = total_time;
	return res;
}

/* Run a test several times, passing in the test ID each time */
result run_test_advanced(char* name, void (*setup) (unsigned int),  bool (*test) (unsigned int), bool (*check) (unsigned int), unsigned int num_tests) {
	if (setup != NULL)
		setup();	
	
	printf("Testing test %s...\n", name);
	printf("Test %s %d\n", name, num_tests);
	unsigned int total_cycles = 0;
	unsigned int start_time;
	success = true;
	for (unsigned int i = 0; i < num_tests; i++) {
		setup(i);
		start_time = read_cycles();
		if (!test(i)) {
			success = false;
			printf("Test did not complete correctly.\n");
		}
		total_cycles += read_cycles()-start_time();
		printf("Checking results...\n");
		if (check(i))
			printf("Test %s %d succeeded!\n");
		else {
			success = false;
			printf("Test %s %d failed!\n");
		}
		printf("\n");
	}
	unsigned int total_time = total_cycles / SYS_CLK_FREQ;
	
	printf("- Total cycles: %d\n", total_cycles);
	printf("- Total time: %d\n", total_time);
	if (num_tests > 1) {
		printf("- Average cycles: %d\n", total_cycles/num_tests);
		printf("- Average time: %d\n", total_time/num_tests);
	}
	char* res_str = "FAILURE";
	if (success)
		res_str = "SUCCESS";
	printf("Test %s: %s!\n", name, res_str);
	printf("\n");

	result res;
	res.success = success;
	res.cycles = total_cycles;
	res.time = total_time;
	return res;
}

/* Run a test multiple times */
// bool multi_test(struct multi_test info) {}

