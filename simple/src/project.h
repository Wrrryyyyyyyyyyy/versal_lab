
#include <adf.h>
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
  kernel first;
  kernel second;
  kernel third;
  kernel fouth;
  kernel five;
  kernel six;
  kernel seven;
  //adf:: pktmerge<2> mg;
public:
  input_plio  ina;
  input_plio  inb;
  input_plio  inc;
  input_plio  ind;
  output_plio out;

 
  simpleGraph(){
    
    ina  = input_plio::create(plio_32_bits, "data/input_ahi.txt");
    inb  = input_plio::create(plio_32_bits, "data/input_alo.txt");
    inc  = input_plio::create(plio_32_bits, "data/input_bhi.txt");
    ind  = input_plio::create(plio_32_bits, "data/input_blo.txt");
    out = output_plio::create(plio_32_bits, "data/output.txt");
    
    //mg = adf::pktmerge<2>::create();

    first = kernel::create(simple);
    second = kernel::create(simple);
    third = kernel::create(simple);
    fouth = kernel::create(simple);
    five = kernel::create(kernel_a);
    six = kernel::create(kernel_bd_ac);
    seven = kernel::create(kernel_ad_bc);

    connect< stream > net0 (ina.out[0], second.in[0]);
    connect< stream > net1 (ina.out[0], fouth.in[0]);

    connect< stream > net2 (inb.out[0], first.in[0]);
    connect< stream > net3 (inb.out[0], third.in[0]);

    connect< stream > net4 (inc.out[0], third.in[1]);
    connect< stream > net5 (inc.out[0], fouth.in[1]);

    connect< stream > net6 (ind.out[0], first.in[1]);
    connect< stream > net7 (ind.out[0], second.in[1]);



    connect< stream > net8 (first.out[0], six.in[0]);
    connect< stream > net9 (second.out[0], seven.in[0]);
    connect< stream > net10 (third.out[0], seven.in[1]);
    connect< stream > net11 (fouth.out[0], six.in[1]);


    connect< stream > net12 (six.out[0], five.in[0]);
    connect< stream > net13 (seven.out[0], five.in[1]);

    connect< stream > net14 (five.out[0], out.in[0]);
    fifo_depth(net0) = 8 ;  
    //fifo_depth(net1) = 8 ; 
    //fifo_depth(net2) = 16 ;   
    //connect< window<128> > net1 (first.out[0], second.in[0]);
    //connect< window<128> > net2 (second.out[0], out.in[0]);

    source(first) = "kernels/kernels.cc";
    source(second) = "kernels/kernels.cc";
    source(third) = "kernels/kernels.cc";
    source(fouth) = "kernels/kernels.cc";
    source(five) = "kernels/add.cc";
    source(six) = "kernels/add.cc";
    source(seven) = "kernels/add.cc";

    runtime<ratio>(first) = 0.1;
    runtime<ratio>(second) = 0.1;
    runtime<ratio>(third) = 0.1;
    runtime<ratio>(fouth) = 0.1;
    runtime<ratio>(five) = 0.1;
    runtime<ratio>(six) = 0.1;
    runtime<ratio>(seven) = 0.1;

  }
};
