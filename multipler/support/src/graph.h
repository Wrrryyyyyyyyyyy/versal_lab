//<copyright-disclaimer-start>
//  **************************************************************************************************************
//  * © 2023 Advanced Micro Devices, Inc. All rights reserved.                                                   *
//  * DISCLAIMER                                                                                                 *
//  * The information contained herein is for informational purposes only, and is subject to change              *
//  * without notice. While every precaution has been taken in the preparation of this document, it              *
//  * may contain technical inaccuracies, omissions and typographical errors, and AMD is under no                *
//  * obligation to update or otherwise correct this information.  Advanced Micro Devices, Inc. makes            *
//  * no representations or warranties with respect to the accuracy or completeness of the contents of           *
//  * this document, and assumes no liability of any kind, including the implied warranties of noninfringement,  *
//  * merchantability or fitness for particular purposes, with respect to the operation or use of AMD            *
//  * hardware, software or other products described herein.  No license, including implied or                   *
//  * arising by estoppel, to any intellectual property rights is granted by this document.  Terms and           *
//  * limitations applicable to the purchase or use of AMD’s products are as set forth in a signed agreement     *
//  * between the parties or in AMD's Standard Terms and Conditions of Sale. GD-18                               *
//  *                                                                                                            *
//  **************************************************************************************************************
//<copyright-disclaimer-end>


#pragma once

#include <adf.h>
#include "aie_kernels.h"
#include "include.h"

using namespace adf;

/*
 * Adaptive Data Flow graph to compute weighted moving sum of
 * the last 8 samples in a stream of numbers
 */

class FirstGraph : public adf::graph
{
private:
  adf::kernel k;

public:
  adf::input_plio pl_in;
  adf::output_plio pl_out;

  FirstGraph()
  {
	// Create the PLIO ports
	pl_in = input_plio::create("PLIO_In", plio_32_bits, INPUT_FILE, 250.0);
	pl_out = output_plio::create("PLIO_Out", plio_32_bits, OUTPUT_FILE, 250.0);

	// create kernels
    k = adf::kernel::create(weighted_sum_with_margin);

    // create nets to connect kernels and IO ports
    adf::connect<> net0 (pl_in.out[0], k.in[0]);
    adf::connect<> net1 (k.out[0], pl_out.in[0]);

    // specify kernel sources
    adf::source(k) = "aie_kernels/weighted_sum.cc";

    // specify kernel run times
    adf::runtime<ratio>(k) = 0.9;

  }
};