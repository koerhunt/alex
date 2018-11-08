#ifndef SINTAXIS_H
#define SINTAXIS_H
#endif // SINTAXIS_H

#include <stack>

int MATRIZ_PREDICTIVA[][51] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,4,4,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,-1,-1,-1,-1,-1,5,5,5,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,-1},
    {7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1},
    {14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,21,21,21,21,21,21,21,-1,21,21,-1,-1},
    {22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,22,23,23,22,23,22,23,-1,22,22,-1,-1},
    {24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,24,27,27,24,27,24,27,-1,24,24,-1,-1},
    {26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,26,27,27,26,27,26,27,-1,26,26,-1,-1},
    {28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,28,29,29,28,29,28,29,-1,28,28,-1,-1},
    {30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-1,-1,32,-1,33,-1,-1,34,35,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,39,40,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,42,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1},
    {44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,47,-1,-1},
    {48,48,48,48,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,53,53,53,53,53,-1,53,52,53,-1,-1,53,53,-1,53,53,53,53,53,53,53,53,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {55,55,55,55,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {58,58,58,58,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,58,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,58},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,60,-1,60,-1,-1,-1,59,-1,-1,-1,-1,-1,-1,-1,-1,60,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {61,61,61,61,-1,-1,-1,-1,-1,61,-1,-1,-1,-1,-1,-1,-1,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,63,-1,63,-1,-1,62,63,-1,-1,-1,-1,-1,-1,-1,-1,63,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {64,64,64,64,-1,-1,-1,-1,-1,64,-1,-1,-1,-1,-1,-1,-1,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,64,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64},
    {66,66,66,66,-1,-1,-1,-1,-1,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,68,-1,68,-1,-1,68,68,-1,67,-1,67,67,67,67,67,68,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {69,69,69,69,-1,-1,-1,-1,-1,69,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,69,69,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,69},
    {-1,-1,-1,-1,70,70,-1,-1,-1,-1,71,-1,71,-1,-1,71,71,-1,71,-1,-1,71,71,71,71,71,71,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,72,73,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {74,74,74,74,-1,-1,-1,-1,-1,74,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74,74,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74},
    {-1,-1,-1,-1,76,76,75,75,75,-1,76,-1,76,-1,-1,76,76,-1,76,-1,76,76,76,76,76,76,76,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,77,78,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,81,-1,80,84,85,82,83,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {86,87,88,89,-1,-1,-1,-1,-1,92,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,90,91,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,94}
};

//restar 1
int MATRIZ_DE_PRODUCCIONES[][61] = {
    {1032,1009,1000,1010,1013,   2,  12,1014,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1027,   3,1027,   0,   0,   0,   0,   0,   0,   0,   0},
    {   7,   5,2019,1026,   4,   0,   0,   0,   0,   0,   0},
    {   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {   8,   6,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1025,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2017,1033,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2017,1034,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2017,1035,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2017,1036,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2018,1000,   9,   0,   0,   0,   0,   0,   0,   0,   0},
    {  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1011,1001,1012,  11,   0,   0,   0,   0,   0,   0,   0},
    {  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1037,  13,1038,   0,   0,   0,   0,   0,   0,   0,   0},
    {  15,  14,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  13,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  16,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  19,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  18,1026,  17,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  16,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  20,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  21,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  23,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  24,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  25,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  28,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1013,  13,1014,   0,   0,   0,   0,   0,   0,   0,   0},
    {  31,1019,  36,2022,   0,   0,   0,   0,   0,   0,   0},
    {1039,1009,  36,1010,2028,  13,  22,2030,1040,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2029,1041,  13,   0,   0,   0,   0,   0,   0,   0,   0},
    {2023,1042,1009,  36,2024,1010,  13,2025,1043,   0,   0},
    {2026,1044,  13,1045,1009,  36,1010,2027,1046,   0,   0},
    {1047,1009,  26,1010,   0,   0,   0,   0,   0,   0,   0},
    {2020,1000,  27,   0,   0,   0,   0,   0,   0,   0,   0},
    {1025,  26,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1048,1009,  29,1010,   0,   0,   0,   0,   0,   0,   0},
    {  36,2021,  30,   0,   0,   0,   0,   0,   0,   0,   0},
    {1025,  29,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2001,1000,  32,   0,   0,   0,   0,   0,   0,   0,   0},
    {  33,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1011,  34,1012,   0,   0,   0,   0,   0,   0,   0,   0},
    {  36,  35,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {1025,  34,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  38,  37,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2002,1016,  36,2016,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  40,  39,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2003,1015,  38,2015,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  41,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2004,1017,  41,2014,   0,   0,   0,   0,   0,   0,   0},
    {  43,  42,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  49,  43,2013,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  46,2011,  44,   0,   0,   0,   0,   0,   0,   0,   0},
    {  45,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2005,1004,  43,   0,   0,   0,   0,   0,   0,   0,   0},
    {2005,1005,  43,   0,   0,   0,   0,   0,   0,   0,   0},
    {  50,2010,  47,   0,   0,   0,   0,   0,   0,   0,   0},
    {  48,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2006,1006,  46,   0,   0,   0,   0,   0,   0,   0,   0},
    {2006,1007,  46,   0,   0,   0,   0,   0,   0,   0,   0},
    {2006,1008,  46,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1020,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1018,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1023,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1024,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1021,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2012,1022,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  31,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1001,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1002,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1003,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1030,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1031,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2008,1009,  36,2009,1010,   0,   0,   0,   0,   0,   0},
    {2017,1049,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    {2007,1050,   0,   0,   0,   0,   0,   0,   0,   0,   0}
};

std::stack<int> ExecucionStack;
std::stack<int> TmpStack;

int sccol;

void imprimirStack(){

    while(ExecucionStack.size()>0){
        TmpStack.push(ExecucionStack.top());
        ExecucionStack.pop();
    }

    while(TmpStack.size()>0){
        int el = TmpStack.top();
        cout<<"--"<<el;
        ExecucionStack.push(el);
        TmpStack.pop();
    }
    cout<<endl;

}
