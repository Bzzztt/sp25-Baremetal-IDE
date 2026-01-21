//==================================================
// C GOLDEN MODEL
// From Wavelet Transform Engine repo
//==================================================

#include "naive_wavelet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h> 

float SQRT3 = sqrt(3);
float SQRT2 = sqrt(2);

// ===================== Model =====================

static void split(float* vec, int N) {
    int start = 1, end = N - 1;
    while (start < end) {
        for (int i = start; i < end; i += 2) {
            float tmp = vec[i];
            vec[i] = vec[i + 1];
            vec[i + 1] = tmp;
        }
        start++;
        end--;
    }
}

static void merge(float* vec, int N) {
    int half = N >> 1;
    int start = half - 1, end = half;
    while (start > 0) {
        for (int i = start; i < end; i += 2) {
            float tmp = vec[i];
            vec[i] = vec[i + 1];
            vec[i + 1] = tmp;
        }
        start--;
        end++;
    }
}

static void forwardStep(float* S, int N) {
    int half = N / 2;

    // Update 1
    for (int n = 0; n < half; n++) {
        S[n] = S[n] + SQRT3 * S[half + n];
    }

    // Predict
    // S[half] = S[half] - (SQRT3 / 4.0) * S[0] - (((SQRT3 - 2) / 4.0) * S[half - 1]);
    for (int n = 1; n < half; n++) {
        S[half + n] = S[half + n] - (SQRT3 / 4.0) * S[n] - (((SQRT3 - 2) / 4.0) * S[n - 1]);
    }

    // Update 2
    for (int n = 0; n < half - 1; n++) {
        S[n] = S[n] - S[half + n + 1];
    }
    // S[half - 1] = S[half - 1] - S[half];

    // Normalize
    for (int n = 0; n < half; n++) {
        S[n] = ((SQRT3 - 1.0) / SQRT2) * S[n];
        S[n + half] = ((SQRT3 + 1.0) / SQRT2) * S[n + half];
    }
}

static inverseStep(float* S, int N) {
    int half = N / 2;

    // Denormalize
    for (int n = 0; n < half; n++) {
        S[n] = ((SQRT3 + 1.0) / SQRT2) * S[n];
        S[n + half] = ((SQRT3 - 1.0) / SQRT2) * S[n + half];
    }

    // Undo update 2
    for (int n = 0; n < half - 1; n++) {
        S[n] = S[n] + S[half + n + 1];
    }
    // S[half - 1] = S[half - 1] + S[half];

    // Undo predict
    // S[half] = S[half] + (SQRT3 / 4.0) * S[0] + (((SQRT3 - 2) / 4.0) * S[half - 1]);
    for (int n = 1; n < half; n++) {
        S[half + n] = S[half + n] + (SQRT3 / 4.0) * S[n] + (((SQRT3 - 2) / 4.0) * S[n - 1]);
    }

    // Undo update 1
    for (int n = 0; n < half; n++) {
        S[n] = S[n] - SQRT3 * S[half + n];
    }
}

void naive_float_DWT(float* vec, int N) {
    int n = N;
    while (n > 1) {
        split(vec, n);
        forwardStep(vec, n);
        n >>= 1;
    }
}

void naive_float_iDWT(float* vec, int N) {
    int n = 2;
    while (n <= N) {
        inverseStep(vec, n);
        merge(vec, n);
        n <<= 1;
    }
}

