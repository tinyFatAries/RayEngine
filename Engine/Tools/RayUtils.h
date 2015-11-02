//===========================================================================
// Singleton: Template class for creating single-instance global classes.
//===========================================================================

#pragma once
#include <stdio.h>

#define DEBUG_MODE

#define RAY_ERROR 0
#define RAY_EXCEPTION 1
#define RAY_MESSAGE 2

#ifdef DEBUG_MODE
#define DEBUG_MESSAGE(message, type) \
	do { \
		switch (type) \
		{ \
		case RAY_ERROR: \
			fprintf(stderr, "[!!RayEngine ERROR!!]: file:%s, line: ", __FILE__); \
			fprintf(stdout, message); \
			fprintf(stderr, "\n"); \
			break;\
		case RAY_EXCEPTION: \
			fprintf(stderr, "[**RayEngine EXCEPTION**]: file:%s, line:", __FILE__); \
			fprintf(stdout, message); \
			fprintf(stderr, "\n"); \
			break;\
		case RAY_MESSAGE: \
			fprintf(stderr, "[RayEngine]: "); \
			fprintf(stdout, message); \
			fprintf(stderr, "\n"); \
			break;\
		} \
	} while (0)
#else
#define DEBUG_MESSAGE(message, type)
#endif