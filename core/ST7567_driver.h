#ifndef ST7567_H
#define ST7567_H

#include "build_type.h"

#ifdef HARDWARE_BUILD

#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define SPI_SPEED_HZ 1000000

#define WIDTH 128
#define HEIGHT 64
#define PIN_CS 8
#define PIN_RST 24
#define PIN_DC 23
#define PIN_BACKLIGHT 18

#define ST7567_PAGESIZE 128
#define ST7567_DISPOFF 0xae
#define ST7567_DISPON 0xaf
#define ST7567_SETSTARTLINE 0x40
#define ST7567_STARTLINE_MASK 0x3f
#define ST7567_REG_RATIO 0x20
#define ST7567_SETPAGESTART 0xb0
#define ST7567_PAGESTART_MASK 0x07
#define ST7567_SETCOLL 0x00
#define ST7567_COLL_MASK 0x0f
#define ST7567_SETCOLH 0x10
#define ST7567_COLH_MASK 0x0f
#define ST7567_SEG_DIR_NORMAL 0xa0
#define ST7567_SEG_DIR_REV 0xa1
#define ST7567_DISPNORMAL 0xa6
#define ST7567_DISPINVERSE 0xa7
#define ST7567_DISPRAM 0xa4
#define ST7567_DISPENTIRE 0xa5
#define ST7567_BIAS_1_9 0xa2
#define ST7567_BIAS_1_7 0xa3
#define ST7567_ENTER_RMWMODE 0xe0
#define ST7567_EXIT_RMWMODE 0xee
#define ST7567_EXIT_SOFTRST 0xe2
#define ST7567_SETCOMNORMAL 0xc0
#define ST7567_SETCOMREVERSE 0xc8
#define ST7567_POWERCTRL_VF 0x29
#define ST7567_POWERCTRL_VR 0x2a
#define ST7567_POWERCTRL_VB 0x2c
#define ST7567_POWERCTRL 0x2f
#define ST7567_REG_RES_RR0 0x21
#define ST7567_REG_RES_RR1 0x22
#define ST7567_REG_RES_RR2 0x24
#define ST7567_SETCONTRAST 0x81
#define ST7567_SETBOOSTER 0xf8
#define ST7567_SETBOOSTER4X 0x00
#define ST7567_SETBOOSTER5X 0x01
#define ST7567_NOP 0xe3
#define ST7565_STARTBYTES 0

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
