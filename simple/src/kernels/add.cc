/* A simple kernel
 */
#include <adf.h>
//#include "include.h"
#include "../kernels.h"

void kernel_a(input_stream_int32 * inbdac,
 input_stream_int32 * inadbc,

output_stream_int32 * out) {
  int32 c1, c2;
  long temp;
  for (unsigned i=0; i<NUM_SAMPLES; i++) {
    
        c1 = readincr(inbdac);      
        writeincr(out, c1);
        c1 = readincr(inbdac);
        c2 = readincr(inadbc);
        temp = c1+c2;
        writeincr(out, temp);
        
        
        c1 = readincr(inbdac);
        c2 = readincr(inadbc);
        temp = temp>>16;
        temp = temp + (c1+c2);  
                  
        writeincr(out, temp);
        
        c1 = readincr(inbdac); 
        temp =(temp>>16) + c1;      
        writeincr(out, temp);
        
  }
}

void kernel_bd_ac(
    //input_stream_int32 * inbd,
input_stream_int32 * inbd,
input_stream_int32 * inac,
//input_stream_int32 * inac,
output_stream_int32 * out) {
  int32 c1, c2,c3;

  for (unsigned i=0; i<NUM_SAMPLES; i++) {
    
       
        c1 = readincr(inbd);
        //printf("bdlo=%d",c1);
        writeincr(out, c1);
        c1 = readincr(inbd);
       // printf("bdhi=%d",c1);
        writeincr(out, c1);
        c2 = readincr(inac);
        printf("aclo=%d\n",c2);       
        writeincr(out, c2);
        c2 = readincr(inac);
        printf("achi=%d\n",c2);       
        writeincr(out, c2);
        
  }
}

void kernel_ad_bc(
    //input_stream_int32 * inbd,
input_stream_int32 * inad,
input_stream_int32 * inbc,
//input_stream_int32 * inac,
output_stream_int32 * out) {
  int32 c1, c2,c3;
  long temp;
  for (unsigned i=0; i<NUM_SAMPLES; i++) {
    
       
        c1 = readincr(inad);       
        c2 = readincr(inbc);       
        
        temp = c1+c2;
        //printf("add_lo=%d",c2+c1); 
        writeincr(out, c1+c2);
        
        c1 = readincr(inad);       
        c2 = readincr(inbc); 
        
        temp = temp + ((c1+c2)<<16);
        temp = temp >>16;               
        writeincr(out, temp);
               


  }
}