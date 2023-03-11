#ifndef ST7567_H
#define ST7567_H

#include "build_type.h"

#ifdef HARDWARE_BUILD

#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

const int SPI_SPEED_HZ = 1000000;

const int WIDTH = 128;
const int HEIGHT = 64;
const int PIN_CS = 8;
const int PIN_RST = 24;
const int PIN_DC = 23;
const int PIN_BACKLIGHT = 18;


const int ST7567_PAGESIZE = 128;
const int ST7567_DISPOFF = 0xae;
const int ST7567_DISPON = 0xaf;
const int ST7567_SETSTARTLINE = 0x40;
const int ST7567_STARTLINE_MASK = 0x3f;
const int ST7567_REG_RATIO = 0x20;
const int ST7567_SETPAGESTART = 0xb0;
const int ST7567_PAGESTART_MASK = 0x07;
const int ST7567_SETCOLL = 0x00;
const int ST7567_COLL_MASK = 0x0f;
const int ST7567_SETCOLH = 0x10;
const int ST7567_COLH_MASK = 0x0f;
const int ST7567_SEG_DIR_NORMAL = 0xa0;
const int ST7567_SEG_DIR_REV = 0xa1;
const int ST7567_DISPNORMAL = 0xa6;
const int ST7567_DISPINVERSE = 0xa7;
const int ST7567_DISPRAM = 0xa4;
const int ST7567_DISPENTIRE = 0xa5;
const int ST7567_BIAS_1_9 = 0xa2;
const int ST7567_BIAS_1_7 = 0xa3;
const int ST7567_ENTER_RMWMODE = 0xe0;
const int ST7567_EXIT_RMWMODE = 0xee;
const int ST7567_EXIT_SOFTRST = 0xe2;
const int ST7567_SETCOMNORMAL = 0xc0;
const int ST7567_SETCOMREVERSE = 0xc8;
const int ST7567_POWERCTRL_VF = 0x29;
const int ST7567_POWERCTRL_VR = 0x2a;
const int ST7567_POWERCTRL_VB = 0x2c;
const int ST7567_POWERCTRL = 0x2f;
const int ST7567_REG_RES_RR0 = 0x21;
const int ST7567_REG_RES_RR1 = 0x22;
const int ST7567_REG_RES_RR2 = 0x24;
const int ST7567_SETCONTRAST = 0x81;
const int ST7567_SETBOOSTER = 0xf8;
const int ST7567_SETBOOSTER4X = 0x00;
const int ST7567_SETBOOSTER5X = 0x01;
const int ST7567_NOP = 0xe3;
const int ST7565_STARTBYTES = 0;

void ST7567_command(unsigned char* command, int command_length);
void ST7567_data(unsigned char* data, int data_length);

void ST7567_init();
void ST7567_begin();
void ST7567_reset();
void ST7567_disable(unsigned char* buffer);

void ST7567_contrast(unsigned char val);
void ST7567_show(unsigned char* buffer);

void ST7567_set_backlight(int val);

#endif

#endif
