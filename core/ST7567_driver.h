#ifndef ST7567_H
#define ST7567_H

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

struct ST7567 {
    char buffer[(128 * 64) / 8];
};

void ST7567_command(char* command, int command_length) {
    digitalWrite(PIN_DC, 0);
    wiringPiSPIDataRW(0, command, command_length);
}

void ST7567_data(char* data, int data_length) {
    digitalWrite(PIN_DC, 1);
    wiringPiSPIDataRW(0, data, data_length);
}

void ST7567_init() {
    wiringPiSetupGpio();
    wiringPiSPISetup(0, SPI_SPEED_HZ);
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_DC, OUTPUT);
    pinMode(PIN_BACKLIGHT, OUTPUT);
}

void ST7567_begin() {
    char command[10] = {
	ST7567_BIAS_1_7,
    	ST7567_SEG_DIR_NORMAL,
    	ST7567_SETCOMREVERSE,
    	ST7567_DISPNORMAL,
    	ST7567_SETSTARTLINE | 0,
    	ST7567_POWERCTRL,
    	ST7567_REG_RATIO | 3,
    	ST7567_DISPON,
    	ST7567_SETCONTRAST,
	64
    };
    ST7567_command(command, 10);
}

void ST7567_reset() {
    digitalWrite(PIN_RST, LOW);
    delay(1);
    digitalWrite(PIN_RST, HIGH);
    delay(1);
}

void ST7567_contrast(char val) {
    ST7567_command((char[]) { ST7567_SETCONTRAST, val }, 2);
}

void ST7567_show(char* buffer) {
    ST7567_command((char[]) { ST7567_ENTER_RMWMODE }, 1);
    for (int page = 0; page < 8; page++) {
	int offset = page * ST7567_PAGESIZE;
	ST7567_command((char[]){
                   ST7567_SETPAGESTART | page,
                   ST7567_SETCOLL,
                   ST7567_SETCOLH },
                   3);
	ST7567_data(buffer + offset, ST7567_PAGESIZE);
    }
    ST7567_command((char[]) { ST7567_EXIT_RMWMODE }, 1);
}

void ST7567_set_backlight(int val) {
    digitalWrite(18, !val);
}

void ST7567_disable(char* buffer) {
    for (int i = 0; i < (WIDTH * HEIGHT) / 8; i++) buffer[i] = 0;
    ST7567_show(buffer);
    ST7567_reset();
    digitalWrite(PIN_BACKLIGHT, HIGH);
}

void ST7567_set_pixel_in_buffer(char* buffer, int x, int y, int value) {
    int offset = ((y / 8) * WIDTH) + x;
    int bit    = y % 8;
    buffer[offset] &= ~(1 << bit);
    buffer[offset] |= (value & 1) << bit;
}

#endif
