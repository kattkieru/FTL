/*
 *  Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.
 */

#pragma once

#if defined( __linux__ )

# define FTL_OS_LINUX 1
# define FTL_PLATFORM_POSIX 1

#elif defined( __APPLE__ )

# define FTL_OS_DARWIN 1
# define FTL_PLATFORM_POSIX 1

#elif defined( _MSC_VER )

# define FTL_OS_WINDOWS 1
# define FTL_PLATFORM_WINDOWS 1

# if !defined( FTL_INCLUDE_WINDOWS_UI )
#  define WIN32_LEAN_AND_MEAN   // Avoid unnecessary cruft
# endif

# if !defined( WIN32 ) //Note: WIN32 is defined for 64 bits too however WIN64 is only defined in 64 bits.
#  define WIN32 1
# endif

// For some reason, this warning cannot be disabled
// from the command line.
// 'Unsupported zero-sized arrays in structs blah...'
#pragma warning( disable: 4200 )


// Some missing POSIX-y functions
#include <math.h>
inline double round( double x ) { return floor(x+0.5); }
inline float roundf( float x ) { return floorf(x+0.5f); }
#if _MSC_VER < 1900
# define snprintf _snprintf
#endif

#else
# error Unknown platform.
#endif

// Build architecture
#if defined(FTL_PLATFORM_POSIX)
# if defined(__x86_64)
#  define FTL_ARCH_64BIT 1
# else
#  define FTL_ARCH_32BIT 1
# endif
#elif defined(FTL_PLATFORM_WINDOWS)
# if defined(_WIN64)
#  define FTL_ARCH_64BIT 1
# else
#  define FTL_ARCH_32BIT 1
# endif
#else
# error "Unsupported platform"
#endif

// Build settings
#if defined(NDEBUG)
# define FTL_BUILD_RELEASE 1
#else
# define FTL_BUILD_DEBUG 1
#endif

#ifndef _MSC_VER
# define FTL_NOEXCEPT noexcept
#else
# define FTL_NOEXCEPT
#endif

#ifndef __has_feature
# define __has_feature(x) 0
#endif

// From LLVM 3.3 source
#if (__has_feature(cxx_rvalue_references)   \
     || defined(__GXX_EXPERIMENTAL_CXX0X__) \
     || (defined(_MSC_VER) && _MSC_VER >= 1600))
# define FTL_HAS_RVALUE_REFERENCES 1
#else
# define FTL_HAS_RVALUE_REFERENCES 0
#endif

// From LLVM 3.3 source
#if (__has_feature(cxx_deleted_functions) \
     || defined(__GXX_EXPERIMENTAL_CXX0X__))
     // No version of MSVC currently supports this.
# define FTL_DELETED_FUNCTION = delete
#else
# define FTL_DELETED_FUNCTION
#endif

// From LLVM 3.3 source
#if (__has_feature(cxx_override_control) \
     || (defined(_MSC_VER) && _MSC_VER >= 1700))
# define FTL_OVERRIDE override
#else
# define FTL_OVERRIDE
#endif

// From LLVM 3.5 source
#ifndef __FTL_GNUC_PREREQ
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define __FTL_GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
# else
#  define __FTL_GNUC_PREREQ(maj, min) 0
# endif
#endif

// From LLVM 3.5 source
#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

// From LLVM 3.5 source
#if __has_attribute(warn_unused_result) || __FTL_GNUC_PREREQ(3, 4)
#define FTL_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
#define FTL_WARN_UNUSED_RESULT
#endif

#if !defined(FTL_NAMESPACE)
# define FTL_NAMESPACE FTL
#endif

#define FTL_NAMESPACE_BEGIN namespace FTL_NAMESPACE {
#define FTL_NAMESPACE_END   }
