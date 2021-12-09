#pragma once

#ifdef __GNUC__
#define farcall(x) x
#define far __attribute__(( long_call ))
#pragma GCC diagnostic ignored "-Wattributes" // Workaround for a bug that produces errant warnings in gcc
#define near __attribute(( near ))
#else
#define farcall(x) (*(&(x)))
#define far
#define near
#endif
