#include "ST7567_driver.h"

#ifdef HARDWARE_BUILD

void ST7567_command(unsigned char* command, int command_length) {
    digitalWrite(PIN_DC, 0);
    wiringPiSPIDataRW(0, command, command_length);
}

void ST7567_data(unsigned char* data, int data_length) {
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
    unsigned char command[10] = {
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

void ST7567_contrast(unsigned char val) {
    ST7567_command((unsigned char[]) { ST7567_SETCONTRAST, val }, 2);
}

void ST7567_show(unsigned char* buffer) {
    ST7567_command((unsigned char[]) { ST7567_ENTER_RMWMODE }, 1);
    for (int page = 0; page < 8; page++) {
	int offset = page * ST7567_PAGESIZE;
	ST7567_command((unsigned char[]){
                   ST7567_SETPAGESTART | page,
                   ST7567_SETCOLL,
                   ST7567_SETCOLH },
                   3);
	ST7567_data(buffer + offset, ST7567_PAGESIZE);
    }
    ST7567_command((unsigned char[]) { ST7567_EXIT_RMWMODE }, 1);
}

void ST7567_set_backlight(int val) {
    digitalWrite(18, !val);
}

void ST7567_disable(unsigned char* buffer) {
    for (int i = 0; i < (WIDTH * HEIGHT) / 8; i++) buffer[i] = 0;
    ST7567_show(buffer);
    ST7567_reset();
    digitalWrite(PIN_BACKLIGHT, HIGH);
}

#endif

void null_func_3(void) {}
