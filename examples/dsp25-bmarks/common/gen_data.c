#include <stdint.h>
#include <stdlib.h>

void gen_u32(uint32_t* ptr, unsigned int size) {
	for (int i = 0; i < size; i++)
		ptr[i] = ((float) rand()) / ((float) rand());
}
void gen_f32(float* ptr, unsigned int size) {
	for (int i = 0; i < size; i++)
		ptr[i] = rand();
}
