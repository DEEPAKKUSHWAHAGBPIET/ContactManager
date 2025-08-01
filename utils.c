// utils.c
#include <ctype.h>
#include <string.h>
#include "utils.h"

void toLowerCase(char* str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// Check if phone number has exactly 10 digits
int isValidPhone(const char *phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {2
     
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

// Very basic email validation: checks for '@' and '.'
int isValidEmail(const char *email) {
    if (!email) return 0;

    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    // Basic checks
    if (!at || !dot) return 0;

    // '@' must come before '.'
    if (at > dot) return 0;

    // '@' can't be at the start
    if (at == email) return 0;

    // '.' can't be right after '@' (e.g., demo@.com)
    if (at + 1 == dot) return 0;

    // '.' can't be at the end (e.g., demo@example.)
    if (*(dot + 1) == '\0') return 0;

    // No spaces allowed
    if (strchr(email, ' ')) return 0;

    return 1;
}
