#pragma once
#ifndef _TRACE_H_
#define _TRACE_H_

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void Trace(const LPWSTR format, ...);

#endif

