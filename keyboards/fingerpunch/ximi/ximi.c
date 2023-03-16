#include "ximi.h"

#ifdef RGB_MATRIX_ENABLE

// Layout
//
//┌────────────────────────┐                 ┌────────────────────────┐
//│ 18  17  12  11  06  05 │                 │ 26  27  32  33  38  39 │
//│────────────────────────┤                 ├────────────────────────│
//│ 19  16  13  10  07  04 │                 │ 25  28  31  34  37  40 │
//├────────────────────────┤                 ├────────────────────────┤
//│ 20  15  14  09  08  03 │                 │ 24  29  30  35  36  41 │
//└───────────────────┬────┴───────┐ ┌───────┴────┬───────────────────┘
//                    │ 02  01  00 │ │ 21  22  23 │
//                    └────────────┘ └────────────┘
//
//

// use this matrix if you use the 6 column layout ----------------------------------------------

led_config_t g_led_config = { {
//COL   00     01      02       03      04      05      06        ROW 
    {  18,     17,     12,      11,      6,      5,      0    },//00
    {  19,     16,     13,      10,      7,      4,      1    },//01
    {  20,     15,     14,       9,      8,      3,      2    },//02
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED  },//03
    {  39,     38,     33,      32,     27,     26,     21    },//00
    {  40,     37,     34,      31,     28,     25,     22    },//01
    {  41,     36,     35,      30,     29,     24,     23    },//02
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED  },//03
}, {
   //LEFT
   //thumb1 ▼      thumb2 ▼      thumb3 ▼      C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
   {  89,  54 }, {  74,  49 },  {  58,  48 }, {  75,  34 }, {  75,  21 }, {  75,   8 }, {  60,   6 },
   //C1 R2 ▼       C1 R3 ▼       C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    {  60,  19 }, {  60,  32 }, {  46,  25 }, {  46,  12 }, {  46,   0 }, {  29,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R1 ▼       C5 R2 ▼       C5 R3 ▼
    {  30,  20 }, {  31,  33 }, {  17,  42 }, {  15,  30 }, {  13,  17 }, {   0,  15 }, {   0,  28 }, {   0,  41 }, 
    //RIGHT
   //thumb1 ▼     thumb2 ▼      thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
    { 135,  54 }, { 150,  49 }, { 166,  48 }, { 149,  34 }, { 149,  21 }, { 149,   8 }, { 163,   6 },
   //C1 R2 ▼       C1 R3 ▼       C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼       C3 R2 ▼
    { 163,  19 }, { 163,  32 }, { 178,  25 }, { 178,  12 }, { 178,   0 }, { 195,   7 }, { 194,  20 }, 
   //C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R1 ▼       C5 R2 ▼       C5 R3 ▼
    { 193,  33 }, { 206,  42 }, { 209,  30 }, { 211,  17 }, {   221,  12 }, { 221,  28 }, { 221,  41 }
}, {       
    //LEFT               
    1, 1,  1, // 1, 9,  1, // change to this if you want the thumb home key to be highlighted as a home row key color
    4, 4,  4,
    4, 12, 4,
    4, 12, 4,
    4, 12, 4,
    4, 12, 4,
    1, 1,  1,
    //RIGHT
    1, 1,  1, // 1, 9,  1, // change to this if you want the thumb home key to be highlighted as a home row key color
    4, 4,  4,
    4, 12, 4,
    4, 12, 4,
    4, 12, 4,
    4, 12, 4,
    1, 1,  1
} };

// -----------------------------------------------------------------------------------------------


// use this matrix if you use the 5 column layout ──────────────────────────────────────────┐
/*
led_config_t g_led_config = { {
//COL   00     01   02   03   04   05              ROW 
    { NO_LED,  17,  12,  11,   5,   4          },//00
    { NO_LED,  16,  13,  10,   6,   3          },//01
    { NO_LED,  15,  14,   9,   7,   2          },//02
    { NO_LED,   8,   1,   0, NO_LED, NO_LED    },//03
    { NO_LED,  35,  30,  29,  23,  22          },//00
    { NO_LED,  34,  31,  28,  24,  21          },//01
    { NO_LED,  33,  32,  27,  25,  20          },//02
    { NO_LED,  26,  19,  18, NO_LED,  NO_LED   } //03
}, {
   //LEFT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
                  {  89,  54 }, {  74,  49 }, {  75,  34 }, {  75,  21 }, {  75,   8 }, {  60,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    {  60,  19 }, {  60,  32 }, {  58,  48 }, {  46,  25 }, {  46,  12 }, {  46,   0 }, {  29,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    {  30,  20 }, {  31,  33 }, {  17,  42 }, {  15,  30 }, {  13,  17 },
    //RIGHT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
                  { 135,  54 }, { 150,  49 }, { 149,  34 }, { 149,  21 }, { 149,   8 }, { 163,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    { 163,  19 }, { 163,  32 }, { 166,  48 }, { 178,  25 }, { 178,  12 }, { 178,   0 }, { 195,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    { 194,  20 }, { 193,  33 }, { 206,  42 }, { 209,  30 }, { 211,  17 }
}, { 
    //LEFT
    1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    //RIGHT
    1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4
} };
*/
// ────────────────────────────────────────────────────────────────────────────────────────────────────┘
#endif
