#ifndef __vtkWIN32Header_h
#define __vtkWIN32Header_h

#ifndef __VTK_SYSTEM_INCLUDES__INSIDE
Do_not_include_vtkWin32Header_directly__vtkSystemIncludes_includes_it;
#endif

#include "vtkConfigure.h"

//
// Windows specific stuff------------------------------------------
#if defined(_WIN32) || defined(WIN32)

// define strict header for windows
#ifndef STRICT
#define STRICT
#endif

#ifdef VTK_USE_ANSI_STDLIB
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <windows.h>

#ifdef _MSC_VER
// Handle MSVC compiler warning messages, etc.
#ifndef VTK_DISPLAY_WIN32_WARNINGS
#pragma warning ( disable : 4127 )
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4251 )
#pragma warning ( disable : 4305 )
#pragma warning ( disable : 4309 )
#pragma warning ( disable : 4710 )
#pragma warning ( disable : 4706 )
#pragma warning ( disable : 4786 )
#pragma warning ( disable : 4097 )
#endif //VTK_DISPLAY_WIN32_WARNINGS
#endif

#endif

#if defined(WIN32) && !defined(VTKSTATIC)
#define VTK_EXPORT __declspec( dllexport )

#if defined(vtkCommon_EXPORTS)
#define VTK_COMMON_EXPORT __declspec( dllexport ) 
#else
#define VTK_COMMON_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkFiltering_EXPORTS)
#define VTK_FILTERING_EXPORT __declspec( dllexport ) 
#else
#define VTK_FILTERING_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkImaging_EXPORTS)
#define VTK_IMAGING_EXPORT __declspec( dllexport ) 
#else
#define VTK_IMAGING_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkGraphics_EXPORTS)
#define VTK_GRAPHICS_EXPORT __declspec( dllexport ) 
#else
#define VTK_GRAPHICS_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkIO_EXPORTS)
#define VTK_IO_EXPORT __declspec( dllexport ) 
#else
#define VTK_IO_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkRendering_EXPORTS)
#define VTK_RENDERING_EXPORT __declspec( dllexport ) 
#else
#define VTK_RENDERING_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkHybrid_EXPORTS)
#define VTK_HYBRID_EXPORT __declspec( dllexport ) 
#else
#define VTK_HYBRID_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkParallel_EXPORTS)
#define VTK_PARALLEL_EXPORT __declspec( dllexport ) 
#else
#define VTK_PARALLEL_EXPORT __declspec( dllimport ) 
#endif

#if defined(vtkPatented_EXPORTS)
#define VTK_PATENTED_EXPORT __declspec( dllexport ) 
#else
#define VTK_PATENTED_EXPORT __declspec( dllimport ) 
#endif
#else
#define VTK_COMMON_EXPORT
#define VTK_FILTERING_EXPORT
#define VTK_GRAPHICS_EXPORT
#define VTK_IMAGING_EXPORT
#define VTK_IO_EXPORT
#define VTK_RENDERING_EXPORT
#define VTK_HYBRID_EXPORT
#define VTK_PARALLEL_EXPORT
#define VTK_PATENTED_EXPORT
#define VTK_EXPORT
#endif

// this is exclusively for the tcl Init functions
#if defined(WIN32)
#define VTK_TK_EXPORT __declspec( dllexport )
#else
#define VTK_TK_EXPORT
#endif

#endif