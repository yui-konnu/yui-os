#include <types.h>
#include <stdarg.h>
#include "mini-printf.h"

volatile uint16_t * base_text_buffer = (volatile uint16_t *)0xB8000;

volatile uint16_t * current_text_buffer = (volatile uint16_t *)0xB8000;

static const uint16_t TERM_WIDTH = 80;
static const uint16_t TERM_HEIGHT = 25;

static char internal_buffer[100];

static inline uint16_t terminal_entry(char ch, uint8_t fg, uint8_t bg) {
    return (uint16_t)ch | ((fg | bg << 4) << 8);
}


void io_putc(char ch) {
    uint32_t a;

    if(ch == '\n') {
        a = ((uint32_t)current_text_buffer - (uint32_t)base_text_buffer) / 2;
        current_text_buffer += (TERM_WIDTH - (a % TERM_WIDTH));
    }
    else {
        *current_text_buffer++ = terminal_entry(ch, 7, 0);
    }
}

void io_puts(const char * str) {
    while(*str) {
        io_putc(*str);
        str++;
    }
}

void io_clear() {
    int x, y;
    volatile uint16_t * copy;

    copy = current_text_buffer = base_text_buffer;

    for(y = 0; y < TERM_HEIGHT; y++) {
        for(x = 0; x < TERM_WIDTH; x++) {
            *copy++ = 0;
        }
    }
}

int io_iprintf(const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(internal_buffer, sizeof(internal_buffer), fmt, va);
    va_end(va);

    io_puts(internal_buffer);

    return ret;
}