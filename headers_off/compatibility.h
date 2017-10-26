#ifndef COMPATIILITY_H
#define COMPATIILITY_H

#if defined (__amd64__) || defined (_M_X64) || defined (_WIN64)

typedef short bool;
typedef unsigned int 
typedef unsigned short
typedef short
typedef short
typedef long 
typedef long
typedef unsigned long
typedef unsigned long
typedef 
typedef 
typedef 

#elif defined (__i386__) || defined (_M_IX86) || defined (_WIN32)

typedef int
typedef unsigned int
typedef unsigned short
typedef short
typedef short
typedef long 
typedef long
typedef unsigned long
typedef unsigned long
typedef unsigned long long
typedef 
typedef 
typedef 

#else
#   error "wrong platform"
#endif