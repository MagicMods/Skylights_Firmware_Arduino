#include "FastLED.h"
#include <Palettes.h>
#include <main.h>
#define FASTLED_INTERNAL

// DEFINE_GRADIENT_PALETTE(red_gp){
//     255,255,255};

// Gradient palette "red_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds9/tn/red.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(red_gp){
    0,255,0,0,
    255,255,0,0};

DEFINE_GRADIENT_PALETTE(blue_gp){
    0, 0, 0, 255,
    255, 0, 0, 255};

DEFINE_GRADIENT_PALETTE(white_gp){
    0, 255, 255, 255,
    255, 255, 255, 255};

DEFINE_GRADIENT_PALETTE(whiteBED_gp){
    0, 255, 255, 255,
    255, 255, 255, 255};

DEFINE_GRADIENT_PALETTE(whiteDESK_gp){
    0, 255, 255, 255,
    255, 255, 255, 255};

DEFINE_GRADIENT_PALETTE(whiteCEILLING_gp){
    0, 255, 255, 255,
    100, 0, 0, 0,
    150, 255, 255, 255,
    200, 0, 0, 0,
    255, 255, 255, 255};

DEFINE_GRADIENT_PALETTE(whiteWIN_gp){
    0, 255, 255, 255,
    255, 255, 255, 255};

// DEFINE_GRADIENT_PALETTE(white_gp){
//     0, 255, 255, 255,
    // 255, 255, 255, 255};

DEFINE_GRADIENT_PALETTE(bhw4_018_gp){
    0, 32, 1, 26,
    45, 49, 1, 11,
    76, 121, 2, 8,
    104, 194, 7, 3,
    127, 222, 36, 1,
    160, 227, 107, 1,
    255, 92, 16, 2};

DEFINE_GRADIENT_PALETTE(bhw4_057_gp){
    0, 6, 0, 1,
    22, 17, 0, 1,
    58, 20, 1, 2,
    91, 75, 0, 12,
    127, 199, 1, 41,
    204, 17, 0, 1,
    255, 6, 0, 1};

DEFINE_GRADIENT_PALETTE(bhw4_024_gp){
    0, 177, 164, 216,
    35, 61, 65, 221,
    66, 21, 34, 112,
    178, 199, 25, 1,
    214, 249, 0, 1,
    255, 18, 1, 0};

DEFINE_GRADIENT_PALETTE(bhw4_048_gp){
    0, 1, 12, 36,
    51, 10, 100, 158,
    94, 128, 225, 210,
    127, 252, 250, 237,
    153, 128, 227, 199,
    255, 5, 25, 52};

DEFINE_GRADIENT_PALETTE(bhw1_purplered_gp){
    0, 255, 0, 0,
    255, 107, 1, 205};

DEFINE_GRADIENT_PALETTE(bhw1_01_gp){
    0, 227, 101, 3,
    117, 194, 18, 19,
    255, 92, 8, 192};

DEFINE_GRADIENT_PALETTE(bhw1_04_gp){
    0, 229, 227, 1,
    15, 227, 101, 3,
    142, 40, 1, 80,
    198, 17, 1, 79,
    255, 0, 0, 45};

DEFINE_GRADIENT_PALETTE(bhw1_w00t_gp){
    0, 3, 13, 43,
    104, 78, 141, 240,
    188, 255, 0, 0,
    255, 28, 1, 1};

DEFINE_GRADIENT_PALETTE(bhw2_57_gp){
    0, 0, 0, 0,
    43, 14, 2, 5,
    81, 40, 1, 7,
    130, 182, 1, 1,
    173, 40, 1, 7,
    214, 14, 2, 5,
    255, 0, 0, 0};

DEFINE_GRADIENT_PALETTE(bhw2_51_gp){
    0, 14, 2, 5,
    63, 40, 1, 7,
    130, 182, 1, 1,
    188, 40, 1, 7,
    255, 14, 2, 5};

DEFINE_GRADIENT_PALETTE(bhw2_n_gp){
    0, 16, 1, 35,
    63, 39, 6, 75,
    119, 117, 24, 197,
    173, 120, 8, 60,
    255, 121, 0, 0};

DEFINE_GRADIENT_PALETTE(bhw3_52_gp){
    0, 31, 1, 27,
    45, 34, 1, 16,
    99, 137, 5, 9,
    132, 213, 128, 10,
    175, 199, 22, 1,
    201, 199, 9, 6,
    255, 1, 0, 1};

DEFINE_GRADIENT_PALETTE(bhw3_23_gp){
    0, 232, 203, 199,
    38, 208, 66, 133,
    73, 173, 13, 55,
    117, 197, 47, 14,
    163, 201, 45, 43,
    201, 123, 5, 2,
    255, 27, 1, 1};

DEFINE_GRADIENT_PALETTE(GMT_ocean_gp){
    0, 0, 0, 0,
    31, 0, 1, 1,
    63, 0, 1, 4,
    95, 0, 19, 42,
    127, 0, 79, 138,
    159, 15, 144, 112,
    191, 91, 233, 89,
    223, 155, 244, 158,
    255, 242, 255, 255};

DEFINE_GRADIENT_PALETTE(bhw1_sunconure_gp){
    0, 20, 223, 13,
    160, 232, 65, 1,
    252, 232, 5, 1,
    255, 232, 5, 1};

DEFINE_GRADIENT_PALETTE(bhw2_22_gp){
    0, 0, 0, 0,
    99, 227, 1, 1,
    130, 249, 199, 95,
    155, 227, 1, 1,
    255, 0, 0, 0};

DEFINE_GRADIENT_PALETTE(bhw2_grrrrr_gp){
    0, 184, 15, 155,
    35, 78, 46, 168,
    84, 65, 169, 230,
    130, 9, 127, 186,
    163, 77, 182, 109,
    191, 242, 246, 55,
    216, 142, 128, 103,
    255, 72, 50, 168};

DEFINE_GRADIENT_PALETTE(bhw2_turq_gp){
    0, 1, 33, 95,
    38, 1, 107, 37,
    76, 42, 255, 45,
    127, 255, 255, 45,
    178, 42, 255, 45,
    216, 1, 107, 37,
    255, 1, 33, 95};

DEFINE_GRADIENT_PALETTE(bhw3_61_gp){
    0, 14, 1, 27,
    48, 17, 1, 88,
    104, 1, 88, 156,
    160, 1, 54, 42,
    219, 9, 235, 52,
    255, 139, 235, 233};

DEFINE_GRADIENT_PALETTE(bhw3_62_gp){
    0, 255, 255, 45,
    43, 208, 93, 1,
    137, 224, 1, 242,
    181, 159, 1, 29,
    255, 63, 4, 68};

DEFINE_GRADIENT_PALETTE(bhw3_56_gp){
    0, 8, 6, 16,
    40, 42, 13, 18,
    76, 17, 4, 10,
    107, 39, 29, 37,
    145, 144, 1, 1,
    170, 249, 5, 1,
    196, 234, 28, 18,
    226, 255, 85, 10,
    255, 255, 138, 29};

DEFINE_GRADIENT_PALETTE(purplefly_gp){
    0, 0, 0, 0,
    63, 239, 0, 122,
    191, 252, 255, 78,
    255, 0, 0, 0};