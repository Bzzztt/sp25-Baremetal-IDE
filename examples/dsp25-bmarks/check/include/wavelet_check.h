#ifndef WAVELET_CHECK_H
#define WAVELET_CHECK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "utils.h"
#include "gen_data.h"
#include "wavelet_check.h"
#include "libbmark.h"
#include "naive_wavelet.h"
#include "hal_wavelet.h"

result wavelet_check(unsigned int test_size);
int main(void);

#endif
