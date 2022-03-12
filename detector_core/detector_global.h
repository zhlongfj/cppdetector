#pragma once

// DARWIN
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#ifndef BUILD_STATIC
# if defined(DETECTOR_LIB)
#  define DETECTOR_EXPORT __attribute__((visibility("default")))
# else
#  define DETECTOR_EXPORT __attribute__((visibility("default")))
# endif
#else
# define DETECTOR_EXPORT
#endif
// ANDROID
#elif defined(__ANDROID__) || defined(ANDROID)
#ifndef BUILD_STATIC
#include <QtCore/qcompilerdetection.h>
# if defined(DETECTOR_LIB)
#  define DETECTOR_EXPORT Q_DECL_EXPORT
# else
#  define DETECTOR_EXPORT Q_DECL_IMPORT
# endif
#else
# define DETECTOR_EXPORT
#endif

// Windows
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <stdint.h>
#ifndef BUILD_STATIC
# if defined(DETECTOR_LIB)
#  define DETECTOR_EXPORT  __declspec(dllexport)
# else
#  define DETECTOR_EXPORT __declspec(dllimport)
#endif
#else
# define DETECTOR_EXPORT
#endif
// LINUX
#elif defined(__linux__) || defined(__linux)
#include <stdint.h>
# if defined(DETECTOR_LIB)
#  define DETECTOR_EXPORT __attribute__((visibility("default")))
# else
#  define DETECTOR_EXPORT __attribute__((visibility("default")))
#endif
#else
#  define DETECTOR_EXPORT
#endif



