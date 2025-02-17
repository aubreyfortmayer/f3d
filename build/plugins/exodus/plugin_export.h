
#ifndef F3D_PLUGIN_EXPORT_H
#define F3D_PLUGIN_EXPORT_H

#ifdef F3D_PLUGIN_EXODUS_STATIC_DEFINE
#  define F3D_PLUGIN_EXPORT
#  define F3D_PLUGIN_EXODUS_NO_EXPORT
#else
#  ifndef F3D_PLUGIN_EXPORT
#    ifdef f3d_plugin_exodus_EXPORTS
        /* We are building this library */
#      define F3D_PLUGIN_EXPORT 
#    else
        /* We are using this library */
#      define F3D_PLUGIN_EXPORT 
#    endif
#  endif

#  ifndef F3D_PLUGIN_EXODUS_NO_EXPORT
#    define F3D_PLUGIN_EXODUS_NO_EXPORT 
#  endif
#endif

#ifndef F3D_PLUGIN_EXODUS_DEPRECATED
#  define F3D_PLUGIN_EXODUS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef F3D_PLUGIN_EXODUS_DEPRECATED_EXPORT
#  define F3D_PLUGIN_EXODUS_DEPRECATED_EXPORT F3D_PLUGIN_EXPORT F3D_PLUGIN_EXODUS_DEPRECATED
#endif

#ifndef F3D_PLUGIN_EXODUS_DEPRECATED_NO_EXPORT
#  define F3D_PLUGIN_EXODUS_DEPRECATED_NO_EXPORT F3D_PLUGIN_EXODUS_NO_EXPORT F3D_PLUGIN_EXODUS_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef F3D_PLUGIN_EXODUS_NO_DEPRECATED
#    define F3D_PLUGIN_EXODUS_NO_DEPRECATED
#  endif
#endif

#endif /* F3D_PLUGIN_EXPORT_H */
