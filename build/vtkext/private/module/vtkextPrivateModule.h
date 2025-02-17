
#ifndef VTKEXTPRIVATE_EXPORT_H
#define VTKEXTPRIVATE_EXPORT_H

#ifdef VTKEXTPRIVATE_STATIC_DEFINE
#  define VTKEXTPRIVATE_EXPORT
#  define VTKEXTPRIVATE_NO_EXPORT
#else
#  ifndef VTKEXTPRIVATE_EXPORT
#    ifdef vtkextPrivate_EXPORTS
        /* We are building this library */
#      define VTKEXTPRIVATE_EXPORT 
#    else
        /* We are using this library */
#      define VTKEXTPRIVATE_EXPORT 
#    endif
#  endif

#  ifndef VTKEXTPRIVATE_NO_EXPORT
#    define VTKEXTPRIVATE_NO_EXPORT 
#  endif
#endif

#ifndef VTKEXTPRIVATE_DEPRECATED
#  define VTKEXTPRIVATE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKEXTPRIVATE_DEPRECATED_EXPORT
#  define VTKEXTPRIVATE_DEPRECATED_EXPORT VTKEXTPRIVATE_EXPORT VTKEXTPRIVATE_DEPRECATED
#endif

#ifndef VTKEXTPRIVATE_DEPRECATED_NO_EXPORT
#  define VTKEXTPRIVATE_DEPRECATED_NO_EXPORT VTKEXTPRIVATE_NO_EXPORT VTKEXTPRIVATE_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKEXTPRIVATE_NO_DEPRECATED
#    define VTKEXTPRIVATE_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkextPrivateModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"

#endif /* VTKEXTPRIVATE_EXPORT_H */
