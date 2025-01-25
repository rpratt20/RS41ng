#ifndef __CAP_LOOK_H
#define __CAP_LOOK_H

// Original code was fixed at a value of 0x62.
// Look up crystal_capacitance values for temperature adjustment of DFM-17 frequecy
// Experimental values may need adjusting after flight experience. 
// Setting of 62 decreases above 0 C. 100hz/degree table set to 5 degrees.
// Above -20 C. 22 Jan 25 test UPDATED long table down to -20.
// 
/* 
//       -58 -56 -54 -52 -50           0  1  2  3  4 
//       -48 -46 -44 -42 -40           5  6  7  8  9
//       -38 -36 -34 -32 -30          10 11 12 13 14
//       -28 -26 -24 -22 -20          15 16 17 18 19

//       -18 -16 -14 -12 -10          20 21 22 23 24
//        -8  -6  -4  -2   0          25 26 27 28 29
//         2   4   6   8  10          30 31 32 33 34 
//        12  14  16  18  20          35 36 37 38 39
//        22  24  26  28  30          40 41 42 43 44
//        32  34  36  38  40          45 46 47 48 49
*/


uint8_t c_value[50] = { 0x00,0x00,0x00,0x00,0x00,
                        0x00,0x20,0x20,0x20,0x20,
                        0x30,0x30,0x30,0x32,0x33,
                        0x42,0x46,0x49,0x56,0x58,

                        0x58,0x5D,0x5D,0x61,0x61,
                        0x64,0x65,0x65,0x65,0x65,
                        0x66,0x64,0x64,0x64,0x63,
                        0x63,0x63,0x63,0x62,0x62,
                        0x63,0x60,0x60,0x60,0x5E,
                        0x5E,0x5D,0x5D,0x5D,0x5C
                        
};
#endif