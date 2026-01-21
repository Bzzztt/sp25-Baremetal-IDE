add_library(dsp25-bmarks STATIC float16.c utils.c gen_data.c naive_wavelet.c)

target_include_directories(dsp25-bmarks PUBLIC .)

target_link_libraries(dsp25-bmarks PUBLIC chip-config)
