#ifndef SIGNAL_HANDLERS_H
#define SIGNAL_HANDLERS_H

#include <stdio.h>
#include <signal.h>
#include <assert.h>

static volatile bool g_bInterupted = false;

// clang-format off

#define DEFINE_SIGNAL_HANDLER(signalNum) void Sig##signalNum(int sig) { assert(sig == signalNum && "Incorrect Signal Handler!");
#define REGISTER_SIGNAL_HANDLER(signalNum) if(signal(signalNum, Sig##signalNum) == SIG_ERR) perror("Can't register " #signalNum " Signal")

DEFINE_SIGNAL_HANDLER(SIGINT)
    g_bInterupted = true;
    puts("\nInterupted by user");

    REGISTER_SIGNAL_HANDLER(SIGINT);
}

DEFINE_SIGNAL_HANDLER(SIGABRT)
    puts("\nApplication aborted");
    exit(3);
}

// clang-format on

void SetSignals()
{
	REGISTER_SIGNAL_HANDLER(SIGINT);
	REGISTER_SIGNAL_HANDLER(SIGABRT);
}

#endif
