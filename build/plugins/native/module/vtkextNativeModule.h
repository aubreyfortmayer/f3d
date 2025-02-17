
#ifndef VTKEXTNATIVE_EXPORT_H
#define VTKEXTNATIVE_EXPORT_H

#ifdef VTKEXTNATIVE_STATIC_DEFINE
#  define VTKEXTNATIVE_EXPORT
#  define VTKEXTNATIVE_NO_EXPORT
#else
#  ifndef VTKEXTNATIVE_EXPORT
#    ifdef vtkextNative_EXPORTS
        /* We are building this library */
#      define VTKEXTNATIVE_EXPORT 
#    else
        /* We are using this library */
#      define VTKEXTNATIVE_EXPORT 
#    endif
#  endif

#  ifndef VTKEXTNATIVE_NO_EXPORT
#    define VTKEXTNATIVE_NO_EXPORT 
#  endif
#endif

#ifndef VTKEXTNATIVE_DEPRECATED
#  define VTKEXTNATIVE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKEXTNATIVE_DEPRECATED_EXPORT
#  define VTKEXTNATIVE_DEPRECATED_EXPORT VTKEXTNATIVE_EXPORT VTKEXTNATIVE_DEPRECATED
#endif

#ifndef VTKEXTNATIVE_DEPRECATED_NO_EXPORT
#  define VTKEXTNATIVE_DEPRECATED_NO_EXPORT VTKEXTNATIVE_NO_EXPORT VTKEXTNATIVE_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKEXTNATIVE_NO_DEPRECATED
#    define VTKEXTNATIVE_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkextNativeModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"

#endif /* VTKEXTNATIVE_EXPORT_H */
