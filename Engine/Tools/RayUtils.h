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
#define DEBUG_MESSAGE(type, message, ...) \
	do { \
		switch (type) \
		{ \
		case RAY_ERROR: \
			fprintf(stdout, "[!!RayEngine ERROR!!]: file:%s, line: "## message ## "\n", __FILE__, ##__VA_ARGS__); \
			break;\
		case RAY_EXCEPTION: \
			fprintf(stdout, "[**RayEngine EXCEPTION**]: file:%s, line:"## message ## "\n", __FILE__, ##__VA_ARGS__); \
			break;\
		case RAY_MESSAGE: \
			fprintf(stdout, "[RayEngine]: "## message ## "\n", ##__VA_ARGS__); \
			break;\
		} \
	} while (0)
#else
#define DEBUG_MESSAGE(type, message, ...)
#endif