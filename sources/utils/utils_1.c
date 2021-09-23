//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "utils.h"

/* external functions that we may use :
 * - ssize_t write(int fd, const void *buf, size_t count) : writes until 'count' bytes in the file descriptor from the
 * buffer pointed by 'buf'.
 */

/* int ms_strlen(const char *str) */

int ms_strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1;
    const unsigned char *p2;
    unsigned char       c1;
    unsigned char       c2;

    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    c1 = *p1;
    c2 = *p2;
    while (c1 == c2)
    {
        c1 = (unsigned char)*p1++;
        c2 = (unsigned char)*p2++;
        if (c1 == '\0')
            return (c1 - c2);
    }
    return (c1 - c2);
}