#ifndef TABLES_HH
#define TABLES_HH

#include <cstdint>

// Table contains values 0..26 (like OPL1/2/3), but last bit not used in YM2413
// UPDATE: This table isn't used anymore because we found a simple (plausible)
//         hardware implementation.
// TODO: For a software implementation this table might still be useful.
static const uint8_t amTable[210] = {
	 0, 0, 0, 0, 0, 0, 0,  // 7x
	 1, 1, 1, 1,           // 4x
	 2, 2, 2, 2,
	 3, 3, 3, 3,
	 4, 4, 4, 4,
	 5, 5, 5, 5,
	 6, 6, 6, 6,
	 7, 7, 7, 7,
	 8, 8, 8, 8,
	 9, 9, 9, 9,
	10,10,10,10,
	11,11,11,11,
	12,12,12,12,
	13,13,13,13,
	14,14,14,14,
	15,15,15,15,
	16,16,16,16,
	17,17,17,17,
	18,18,18,18,
	19,19,19,19,
	20,20,20,20,
	21,21,21,21,
	22,22,22,22,
	23,23,23,23,
	24,24,24,24,
	25,25,25,25,
	26,26,26,              // 3x
	25,25,25,25,
	24,24,24,24,
	23,23,23,23,
	22,22,22,22,
	21,21,21,21,
	20,20,20,20,
	19,19,19,19,
	18,18,18,18,
	17,17,17,17,
	16,16,16,16,
	15,15,15,15,
	14,14,14,14,
	13,13,13,13,
	12,12,12,12,
	11,11,11,11,
	10,10,10,10,
	 9, 9, 9, 9,
	 8, 8, 8, 8,
	 7, 7, 7, 7,
	 6, 6, 6, 6,
	 5, 5, 5, 5,
	 4, 4, 4, 4,
	 3, 3, 3, 3,
	 2, 2, 2, 2,
	 1, 1, 1, 1,
};

static const uint8_t mlTab[16] = {
	1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30
};

// In real HW very likely not stored in a table, but calculated along these lines:
//  pmTable[x][0]    = 0
//  pmTable[x][2]    = x
//  pmTable[x][1,3]  =  pmTable[x][2] >> 1
//  pmTable[x][4..7] = -pmTable[x][0..3]
static const int8_t pmTable[8][8] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0 }, // FNUM = 000xxxxxx
	{ 0, 0, 1, 0, 0, 0,-1, 0 }, // FNUM = 001xxxxxx
	{ 0, 1, 2, 1, 0,-1,-2,-1 }, // FNUM = 010xxxxxx
	{ 0, 1, 3, 1, 0,-1,-3,-1 }, // FNUM = 011xxxxxx
	{ 0, 2, 4, 2, 0,-2,-4,-2 }, // FNUM = 100xxxxxx
	{ 0, 2, 5, 2, 0,-2,-5,-2 }, // FNUM = 101xxxxxx
	{ 0, 3, 6, 3, 0,-3,-6,-3 }, // FNUM = 110xxxxxx
	{ 0, 3, 7, 3, 0,-3,-7,-3 }, // FNUM = 111xxxxxx
};

// KSL Table   values are in range [0, 112]
//  UPDATE: This table is no longer used. But it might still be useful for
//          an efficient software implementation.  See 'ksl.cc' for a simple
//          algorithm to calculate this table.
static const uint8_t kslTable[4][8][16] = {
        {{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }},
        {{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  2,  2,  3,  3,  4 },
         { 0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  5,  6,  6,  7,  7,  8 },
         { 0,  0,  0,  2,  4,  5,  6,  7,  8,  9,  9, 10, 10, 11, 11, 12 },
         { 0,  0,  4,  6,  8,  9, 10, 11, 12, 13, 13, 14, 14, 15, 15, 16 },
         { 0,  4,  8, 10, 12, 13, 14, 15, 16, 17, 17, 18, 18, 19, 19, 20 },
         { 0,  8, 12, 14, 16, 17, 18, 19, 20, 21, 21, 22, 22, 23, 23, 24 },
         { 0, 12, 16, 18, 20, 21, 22, 23, 24, 25, 25, 26, 26, 27, 27, 28 }},
        {{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  3,  4,  5,  6,  7,  8 },
         { 0,  0,  0,  0,  0,  3,  5,  7,  8, 10, 11, 12, 13, 14, 15, 16 },
         { 0,  0,  0,  5,  8, 11, 13, 15, 16, 18, 19, 20, 21, 22, 23, 24 },
         { 0,  0,  8, 13, 16, 19, 21, 23, 24, 26, 27, 28, 29, 30, 31, 32 },
         { 0,  8, 16, 21, 24, 27, 29, 31, 32, 34, 35, 36, 37, 38, 39, 40 },
         { 0, 16, 24, 29, 32, 35, 37, 39, 40, 42, 43, 44, 45, 46, 47, 48 },
         { 0, 24, 32, 37, 40, 43, 45, 47, 48, 50, 51, 52, 53, 54, 55, 56 }},
        {{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  6,  8, 10, 12, 14, 16 },
         { 0,  0,  0,  0,  0,  6, 10, 14, 16, 20, 22, 24, 26, 28, 30, 32 },
         { 0,  0,  0, 10, 16, 22, 26, 30, 32, 36, 38, 40, 42, 44, 46, 48 },
         { 0,  0, 16, 26, 32, 38, 42, 46, 48, 52, 54, 56, 58, 60, 62, 64 },
         { 0, 16, 32, 42, 48, 54, 58, 62, 64, 68, 70, 72, 74, 76, 78, 80 },
         { 0, 32, 48, 58, 64, 70, 74, 78, 80, 84, 86, 88, 90, 92, 94, 96 },
         { 0, 48, 64, 74, 80, 86, 90, 94, 96,100,102,104,106,108,110,112 }},
};

// Table used for envelope-advance calculations. In real hardware there
// likely is no such table. Instead there could be logic along these lines:
//   egStep[x][1,3,5,7] = 1
//   egStep[x][0      ] = 0
//   egStep[x][2,6    ] = x & 2
//   egStep[x][4      ] = x & 1
static const uint8_t egStep[4][8] = {
	{ 0, 1, 0, 1, 0, 1, 0, 1 }, //  4 out of 8
	{ 0, 1, 0, 1, 1, 1, 0, 1 }, //  5 out of 8
	{ 0, 1, 1, 1, 0, 1, 1, 1 }, //  6 out of 8
	{ 0, 1, 1, 1, 1, 1, 1, 1 }, //  7 out of 8
};

// It's very possible this table still contains errors. The real YM2413 likely
// has a 'simple' formula that produces these values. But so far I've been
// unable to figure that out.
static const uint8_t attackTable[128] = {
// column A: output (input value 0..127) gets mapped to this value
// column B: input
// column C: range of possible outputs, assuming function is monotone
// column D: output range, assuming certain 'smoothness' properties
// column E: contains 'OK' if this value is actually measured
//       A      B      C      D    E
//     -----||------|-------|-----|----
	 0, //   0 ->  x
	 0, //   1 ->  0
	 1, //   2 ->  1-0    1-0
	 1, //   3 ->  1-0    1-0
	 1, //   4 ->  1-0    1-0
	 1, //   5 ->  1            OK
	 2, //   6 ->  2            OK
	 3, //   7 ->  5-2
	 4, //   8 ->  5-2
	 5, //   9 ->  5            OK
	 6, //  10 ->  6            OK
	 7, //  11 ->  9-6
	 8, //  12 ->  9-6
	 9, //  13 ->  9            OK
	10, //  14 -> 10            OK
	11, //  15 -> 13-10  11-10
	12, //  16 -> 13-10  12-10
	13, //  17 -> 13-10  13-10
	13, //  18 -> 13-10  13-11
	13, //  19 -> 13-10  13-12
	13, //  20 -> 13            OK
	14, //  21 -> 14            OK
	14, //  22 -> 14            OK
	15, //  23 -> 20-14
	16, //  24 -> 20-14
	17, //  25 -> 20-14
	18, //  26 -> 20-14
	19, //  27 -> 20-14
	20, //  28 -> 20            OK
	21, //  29 -> 21            OK
	22, //  30 -> 22            OK
	23, //  31 -> 28-22  23-22
	24, //  32 -> 28-22  24-22
	25, //  33 -> 28-22  25-22
	26, //  34 -> 28-22  26-23
	27, //  35 -> 28-22  27-24
	28, //  36 -> 28-22  28-25
	28, //  37 -> 28-22  28-26
	28, //  38 -> 28-22  28-27
	28, //  39 -> 28            OK
	29, //  40 -> 29-28
	29, //  41 -> 29            OK
	30, //  42 -> 30            OK
	31, //  43 -> 39-30  31-30
	32, //  44 -> 39-30  32-30
	33, //  45 -> 39-30  33-31
	34, //  46 -> 39-30  34-32
	35, //  47 -> 39-30  35-33
	36, //  48 -> 39-30  36-34
	37, //  49 -> 39-30  37-35
	38, //  50 -> 39-30  38-36
	39, //  51 -> 39-30  39-37
	39, //  52 -> 39-30  39-38
	39, //  53 -> 39            OK
	40, //  54 -> 41-39
	41, //  55 -> 41            OK
	42, //  56 -> 42-41
	42, //  57 -> 42            OK
	43, //  58 -> 53-42  43-42
	44, //  59 -> 53-42  44-42
	45, //  60 -> 53-42  45-42
	46, //  61 -> 53-42  46-43
	47, //  62 -> 53-42  47-44
	48, //  63 -> 53-42  48-45
	49, //  64 -> 53-42  49-46
	50, //  65 -> 53-42  50-47
	51, //  66 -> 53-42  51-48
	52, //  67 -> 53-42  52-49
	53, //  68 -> 53-42  53-50
	53, //  69 -> 53-42  53-51
	53, //  70 -> 53-42  53-52
	53, //  71 -> 53            OK
	54, //  72 -> 55-53
	55, //  73 -> 55            OK
	56, //  74 -> 71-55  56-55
	57, //  75 -> 71-55  57-55
	58, //  76 -> 71-55  58-55
	59, //  77 -> 71-55  59-55
	60, //  78 -> 71-55  60-55
	61, //  79 -> 71-55  61-56
	62, //  80 -> 71-55  62-57
	63, //  81 -> 71-55  63-58
	64, //  82 -> 71-55  64-59
	65, //  83 -> 71-55  65-60
	66, //  84 -> 71-55  66-61
	67, //  85 -> 71-55  67-62
	68, //  86 -> 71-55  68-63
	69, //  87 -> 71-55  69-64
	70, //  88 -> 71-55  70-65
	71, //  89 -> 71-55  71-66
	71, //  90 -> 71-55  71-67
	71, //  91 -> 71-55  71-68
	71, //  92 -> 71-55  71-69
	71, //  93 -> 71-55  71-70
	71, //  94 -> 71            OK
	72, //  95 -> 73-71  72-71
	73, //  96 -> 73-71  73-72
	73, //  97 -> 73            OK
	74, //  98 -> 94-73  74-73
	75, //  99 -> 94-73  75-73
	76, // 100 -> 94-73  76-73
	77, // 101 -> 94-73  77-73
	78, // 102 -> 94-73  78-73
	79, // 103 -> 94-73  79-73
	80, // 104 -> 94-73  80-74
	81, // 105 -> 94-73  81-75
	82, // 106 -> 94-73  82-76
	83, // 107 -> 94-73  83-77
	84, // 108 -> 94-73  84-78
	85, // 109 -> 94-73  85-79
	86, // 110 -> 94-73  86-80
	87, // 111 -> 94-73  87-81
	88, // 112 -> 94-73  88-82
	89, // 113 -> 94-73  89-83
	90, // 114 -> 94-73  90-84
	91, // 115 -> 94-73  91-85
	92, // 116 -> 94-73  92-86
	93, // 117 -> 94-73  93-87
	94, // 118 -> 94-73  94-88
	94, // 119 -> 94-73  94-89
	94, // 120 -> 94-73  94-90
	94, // 121 -> 94-73  94-91
	94, // 122 -> 94-73  94-92
	94, // 123 -> 94-73  94-93
	94, // 124 -> 94           OK
	95, // 125 -> 97-94
	96, // 126 -> 97-94
	97, // 127 -> 97           OK
};

#endif
