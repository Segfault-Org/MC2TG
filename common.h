#ifndef COMMON_H
#define COMMON_H

#include <libintl.h>
#define _(X) gettext(X)

#define strstart(str, that) strncmp(that, str, strlen(that)) == 0

// From sysexits.h
#define EX_IOERR 74
#define EX_OK 0
#define EX_USAGE 64

// Custom exit codes
#define EX_AUTH 10
#endif
