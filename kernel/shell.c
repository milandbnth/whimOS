#include "shell.h"

#define MAX_CMD_LEN 256

extern void serial_write(char c);
extern void serial_print(const char *str);
extern char serial_read(void);

// ── string helpers ────────────────────────────────────────────────
static int str_eq(const char *a, const char *b) {
    while (*a && *b) if (*a++ != *b++) return 0;
    return *a == *b;
}

static int str_starts(const char *str, const char *prefix) {
    while (*prefix) if (*str++ != *prefix++) return 0;
    return 1;
}

// ── commands ──────────────────────────────────────────────────────
static void cmd_help(void) {
    serial_print("Commands:\n");
    serial_print("  help       show this message\n");
    serial_print("  clear      clear the screen\n");
    serial_print("  echo <msg> print a message\n");
    serial_print("  about      about WhimOS\n");
}

static void cmd_clear(void) {
    // ANSI escape: clear screen + move cursor to top
    serial_print("\033[2J\033[H");
}

static void cmd_echo(const char *args) {
    serial_print(args);
    serial_print("\n");
}

static void cmd_about(void) {
    serial_print("WhimOS — a hobby x86 OS\n");
    serial_print("Arch: x86 32-bit\n");
    serial_print("Boot: Multiboot\n");
}

// ── input buffer ─────────────────────────────────────────────────
static char buf[MAX_CMD_LEN];
static int  buf_len = 0;

static void buf_clear(void) {
    for (int i = 0; i < MAX_CMD_LEN; i++) buf[i] = 0;
    buf_len = 0;
}

static void prompt(void) {
    serial_print("\nwhimos> ");
}

static void execute(void) {
    serial_write('\n');

    if (buf_len == 0) {
        prompt();
        return;
    }

    if (str_eq(buf, "help")) {
        cmd_help();
    } else if (str_eq(buf, "clear")) {
        cmd_clear();
    } else if (str_eq(buf, "about")) {
        cmd_about();
    } else if (str_starts(buf, "echo ")) {
        cmd_echo(buf + 5);
    } else {
        serial_print("Unknown command: ");
        serial_print(buf);
        serial_print("\n");
    }

    prompt();
    buf_clear();
}

// ── public API ────────────────────────────────────────────────────
void shell_init(void) {
    serial_print("\n");
    serial_print(" __        __ _      _             ___    ____  \n");
    serial_print(" \\ \\      / /| |__  (_) _ __ ___  / _ \\  / ___| \n");
    serial_print("  \\ \\ /\\ / / | '_ \\ | || '_ ` _ \\| | | | \\___ \\ \n");
    serial_print("   \\ V  V /  | | | || || | | | | | |_| |  ___) |\n");
    serial_print("    \\_/\\_/   |_| |_||_||_| |_| |_|\\___/  |____/ \n");
    serial_print("\n");
    serial_print("Welcome to WhimOS!\n");
    serial_print("\xa9 Copyright (C) 2026 Milan Debnath. All rights reserved.\n");
    serial_print("Type 'help' for available commands.\n");
    prompt();
}

void shell_run(void) {
    char c = serial_read();

    if (c == '\r' || c == '\n') {
        execute();
    } else if ((c == 127 || c == '\b') && buf_len > 0) {
        buf_len--;
        buf[buf_len] = 0;
        serial_write('\b');
        serial_write(' ');
        serial_write('\b');
    } else if (buf_len < MAX_CMD_LEN - 1) {
        buf[buf_len++] = c;
        serial_write(c);
    }
}