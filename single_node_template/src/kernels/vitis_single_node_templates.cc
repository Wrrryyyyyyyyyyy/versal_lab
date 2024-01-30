#include "../kernels.h"

int32 LUT[NUM_SAMPLES] = {1,2,3,4,5,6,7,8};

void vitis_single_node_templates(
    input_window_int32* win, output_window_int32* wout, 
input_stream_int32* sin, output_stream_int32* sout, 
const int (&vectorIn)[NUM_SAMPLES], int factorIn, 
int (&vectorOut)[NUM_SAMPLES], int& factorOut ){
  int32 wc1, sc1;
  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    
    window_readincr(win, wc1);
    wc1 = wc1 + 5 + LUT[i]; 
    window_writeincr(wout, wc1);
    
    sc1 = readincr(sin);
    sc1 = sc1 * sc1;
    writeincr(sout, sc1);

    vectorOut[i] = vectorIn[i] + 5;
    factorOut = factorIn + 5;
	
  }
}
