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


/* 
 * Kernel weighted_sum
 *
 * Compute the weighted sum of the last 8 values.
 */

#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "../include.h"

using namespace adf;

void weighted_sum_with_margin(input_buffer<int32,extents<NUM_SAM>,margin<MARGIN>> & in, output_buffer<int32,extents<NUM_SAM>> & out)
{
	auto inIter=aie::begin_random_circular(in);
	auto outIter=aie::begin_random_circular(out);

	inIter+=8;	// reads and updates the access pointer

	for (unsigned i = 0; i < NUM_SAM; i++)
	{
		int32 val;
		int32 wsum = 0; // accumulator

		inIter-=7;
		
		for (unsigned j = 1; j <= 8; j++)
		{
			//fills-in the variable 'val' from the buffer and increments the access pointer just after that area
			// here val is an int32, so the pointer is incremented by 4
			// if it was a vector of 8 int32 (v8int32) it would have been incremented by 8*4 = 32
			val=*inIter++;
			wsum = wsum + (j * val);
		}

		*outIter++=wsum;// Writes and updates the pointer for the next iteration
	}
}


