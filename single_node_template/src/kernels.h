#include <adf.h>

#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H
#define NUM_SAMPLES 8
void vitis_single_node_templates(input_window_int32* win, output_window_int32* wout, input_stream_int32* sin, output_stream_int32* sout, const int (&)[NUM_SAMPLES], int, int (&)[NUM_SAMPLES], int&);

extern int32 LUT[NUM_SAMPLES];

#endif
