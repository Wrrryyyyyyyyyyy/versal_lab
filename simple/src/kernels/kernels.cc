#include <adf.h>
//#include "include.h"
#include "../kernels.h"

void simple(input_stream_int32 * inx, input_stream_int32 * iny,output_stream_int32 * out) {
  int32 c1, c2;
  long temp;
  long temp_lo;
  for (unsigned i=0; i<NUM_SAMPLES; i++) {
    c1 = readincr(inx);
    c2 = readincr(iny);
    temp = c1*c2;
    temp_lo = temp & 0x000000000000ffff;
   // printf("num[%d],temp = %ld\n",i,temp_lo);
    writeincr(out, temp_lo);
    temp = temp>>16;
   // temp_lo = temp & 0x000000000000ffff;
  // printf("temp = %ld\n",temp_lo);
    writeincr(out, temp);
    
  }
}
