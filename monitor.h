// monitor.h -- Defines the interface for monitor.h
// From JamesM's kernel development tutorials.

#include "common.h"

#ifndef MONITOR_H
#define MONITOR_H


// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

#define VIDEO_MEM_ADDR 0xB8000

//Позиция курсора
u16int cursor_x = 0;
u16int cursor_y = 0;

u16int * video_memory = VIDEO_MEM_ADDR;

#endif // MONITOR_H
