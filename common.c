#include <stdio.h>

#ifdef WIN32
#else
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "common.h"
