#ifndef __CAP_LOOK_H
#define __CAP_LOOK_H

// Original code was fixed at a value of 0x62.
// Look up crystal_capacitance values for temperature adjustment of DFM-17 frequecy
// Experimental values may need adjusting after flight experience. 
// Setting of 62 decreases above 0 C. 100hz/degree table set to 5 degrees.
// Above -20 C. 22 Jan 25 test UPDATED long table down to -20.
// 4Feb +40 to -10C adjust, 11 Feb Double new units-minor adjust.
// 13 Feb adjust blk 20 after test to -23C with 2 units/2freq.
// 25 May First flight test adjustments added to -30C.
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


uint8_t c_value[50] = { 0x03,0x03,0x1C,0x1F,0x22,
                        0x27,0x2C,0x2F,0x33,0x37,
                        0x3C,0x3F,0x43,0x48,0x4C,
                        0x4F,0x51,0x55,0x58,0x59,
                        0x5A,0x5E,0x5F,

                                       0x61,0x62,
                        0x64,0x67,0x67,0x67,0x69,
                        0x68,0x68,0x68,0x68,0x68,
                        0x68,0x66,0x66,0x65,0x64,
                        0x64,0x63,0x62,0x61,0x60,
                        0x5F,0x5C,0x5B,0x59,0x59
                        
};
#endif