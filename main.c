/*
 * main.c - demo for the SDRAM controller
 */

#include <stdint.h>
#include "uart.h"
#include "clock.h"
#include "debug.h"
#include "term.h"
#include "sdram.h"
#include "dump.h"

int console;

#ifndef NULL
#define NULL    (void *)(0)
#endif

int
main(void) {
    int i;
    uint8_t *addr;

    clock_init(1000);
    console = uart_init(PD5, PD6, 115200);
    debug_console = console;
    sdram_init();

    uart_puts(console, "Ok lets see if we can dump out the memory contents\n");
    (void) dump_page(console, (uint8_t *)(0xd0000000), NULL);
    addr = (uint8_t *)(0xd03fff00);
    for (i = 0; i < 235; i++) {
        *(addr + i) = i;
    }
    addr = dump_page(console, (uint8_t *)(0xd03fff00), NULL);
    addr = dump_page(console, addr, NULL);
    addr = SDRAM_BASE_ADDRESS;
    for (i = 0; i < 235; i++) {
        *(addr + i) = i;
    }
    dump_page(console, addr, NULL);
    while (1) {
        msleep(100);
        uart_puts(console, asctime(mtime()));
        uart_puts(console, "\r");
        if ('r' == uart_getc(console, 0)) {
            dump_page(console, addr, NULL);
        }
    }
}
