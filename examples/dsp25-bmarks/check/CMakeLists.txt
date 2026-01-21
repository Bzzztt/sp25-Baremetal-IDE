add_executable(dsp25-check
  src/wavelet_check.c
  src/main.c
)

target_include_directories(dsp25-check PUBLIC include)

target_link_libraries(dsp25-check PRIVATE 
  -L${CMAKE_BINARY_DIR}/glossy -Wl,--whole-archive glossy -Wl,--no-whole-archive
)

target_link_libraries(dsp25-check PRIVATE libbmark)
target_link_libraries(dsp25-check PRIVATE dsp25-bmarks)
