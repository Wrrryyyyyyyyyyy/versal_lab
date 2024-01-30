#include <adf.h>

#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H

#define NUM_SAMPLES 8

  void simple(input_stream_int32* inx, input_stream_int32 * iny,output_stream_int32 * out);
  void kernel_a(input_stream_int32 * inbdac,input_stream_int32 * inadbc,output_stream_int32 * out);
  void kernel_bd_ac(input_stream_int32 * inbd,input_stream_int32 * inac,output_stream_int32 * out);
  void kernel_ad_bc(input_stream_int32 * inad,input_stream_int32 * inbc,output_stream_int32 * out);

#endif

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#endif

