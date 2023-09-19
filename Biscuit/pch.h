#ifndef PCH_H
#define PCH_H

#ifndef WIN32
#define _GNU_SOURCE 1
#endif
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#ifdef WIN32
#include <conio.h>
#else
#include "CRT.h"
#endif
#include <string.h>
#include <assert.h>
#include <time.h>
#include <signal.h>

#define bool char
#define false 0
#define true 1

#define xstr(s) str(s)
#define str(s) #s

#define BISCUIT_VERSION_API 1
#define BISCUIT_VERSION_REV 0
#define BISCUIT_VERSION_HORFIX d
#define BISCUIT_VERSION_FULL xstr(BISCUIT_VERSION_API) "." xstr(BISCUIT_VERSION_REV) xstr(BISCUIT_VERSION_HORFIX)

#if defined(WIN32)
#define BISCUIT_PLATFORM "Windows"
#elif defined(__linux__)
#define BISCUIT_PLATFORM "Linux"
#elif defined(__apple__)
#define BISCUIT_PLATFORM "Apple"
#else
#define BISCUIT_PLATFORM "Unknown"
#endif

#endif
