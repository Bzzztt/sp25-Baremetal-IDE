#include "wavelet_check.h"
#include "utils.h"
#include "hal_wavelet.h"
#include "naive_wavelet.h"
#include <stdint.h>
#include <stdbool.h>

uint32_t* dwti_data;
unsigned int dwti_data_size;
uint32_t* dwti_real_out;
unsigned int dwti_out_size;
void dwt_int_setup() {
	dwti_data = malloc(sizeof(uint32_t) * dwti_data_size);
	gen_u32(dwt_int_data, dwti_data_size);
	dwti_out_size = num_outputs(dwti_data_size, false);
	dwti_real_out = malloc(dwti_out_size * sizeof(uint32_t));
}
bool dwt_int_test(unsigned int index) {
	dwt_int(dwt_int_data, dwti_real_out, dwti_data_size, WAVELET_DB_4);
	return true;
}
bool dwt_int_check(unsigned int index) {
	bool success = true;
	uint32_t dwt_ref_out[dwti_out_size];

	for (unsigned int i = 0; i < dwti_out_size; i++) {
		printf("GOT: %d\n", dwti_real_out[i]);
	}

	free(dwti_real_out);
	free(dwti_data);
	return success;
}

uint32_t* idwti_data;
unsigned int idwti_data_size;
uint32_t* idwti_real_out;
unsigned int idwti_out_size;
void idwt_int_setup() {
	idwti_data = malloc(sizeof(uint32_t) * idwti_data_size);
	gen_u32(idwti_data, idwti_data_size);
	idwti_out_size = num_outputs(idwti_data_size, false);
	idwti_real_out = malloc(idwti_out_size * sizeof(uint32_t));
}
bool idwt_int_test(unsigned int index) {
	idwt_int(idwti_data, idwti_real_out, idwti_data_size, WAVELET_DB_4);
	return true;
}
bool idwt_int_check(unsigned int index) {
	bool success = true;
	uint32_t idwt_ref_out[idwti_out_size];

	for (unsigned int i = 0; i < idwti_out_size; i++) {
		printf("GOT: %d\n", idwti_real_out[i]);
	}

	free(idwti_real_out);
	free(idwti_data);
	return success;
}

float* dwtf_data;
unsigned int dwtf_data_size;
float* dwtf_real_out;
unsigned int dwtf_out_size;
void dwt_float_setup(unsigned int index) {
	dwtf_data = malloc(sizeof(uint32_t) * dwtf_data_size);
	gen_f32(dwtf_data, dwtf_data_size);
	dwtf_out_size = num_outputs(dwtf_data_size, false);
	dwtf_real_out = malloc(dwtf_out_size * sizeof(float));
}
bool dwt_float_test(unsigned int index) {
	dwt_float(dwtf_real_data, dwtf_real_out, dwtf_data_size, WAVELET_DB_4);
	return true;
}
bool dwt_float_check(unsigned int index) {
	bool success = true;
	uint32_t dwtf_ref_out[dwtf_out_size];
	naive_float_DWT(dwtf_data, dwtf_out_size);

	for (unsigned int i = 0; i < dwtf_out_size; i++) {
		if (dwtf_real_out[i] != dwtf_data[i]) {
			printf("WRONG RESULT for element %d- GOT: %f, SHOULD BE: %f\n", i, dwtf_real_out[i], dwtf_data[i]);
			success = false;
		}
		printf("GOT: %d\n", dwtf_real_out[i]);
	}

	free(dwtf_real_out);
	free(dwtf_data);
	return success;
}

float* idwtf_data;
unsigned int idwtf_data_size;
float* idwtf_real_out;
unsigned int idwtf_out_size;
void idwt_float_setup() {
	idwti_data = malloc(sizeof(uint32_t) * idwtf_data_size);
	gen_f32(idwtf_data, idwtf_data_size);
	idwtf_out_size = num_outputs(idwtf_data_size, false);
	idwtf_real_out = malloc(idwtf_out_size * sizeof(float));
}
bool idwt_float_test(unsigned int index) {
	idwt_float(idwtf_real_data, idwtf_real_out, idwtf_data_size, WAVELET_DB_4);
	return true;
}
bool idwt_float_check(unsigned int index) {
	bool success = true;
	uint32_t idwtf_ref_out[idwtf_out_size];
	naive_float_iDWT(idwtf_data, idwtf_out_size);

	for (unsigned int i = 0; i < idwtf_out_size; i++) {
		if (idwtf_real_out[i] != idwtf_data[i]) {
			printf("WRONG RESULT for element %d- GOT: %f, SHOULD BE: %f\n", i, idwtf_real_out[i], idwtf_data[i]);
			success = false;
		}
		printf("GOT: %d\n", idwtf_real_out[i]);
	}

	free(idwtf_real_out);
	free(idwtf_data);
	return success;
}

void wavelet_test(unsigned int test_size) {
	dwti_data_size = idwti_data_size = dwtf_data_size = idwtf_data_size = test_size;
	
	printf("\n\n%d-COUNT WAVELET TESTS\n", test_size);
	run-test-simple("Int DWT", dwt_int_setup, dwt_int_test, dwt_int_check);
	run-test-simple("Int iDWT", idwt_int_setup, idwt_int_test, idwt_int_check);
	run-test-simple("Float DWT", dwt_float_setup, dwt_float_test, dwt_float_check);
	run-test-simple("Float iDWT", idwt_float_setup, idwt_float_test, idwt_float_check);
	printf("\n");
}
