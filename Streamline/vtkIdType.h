#ifndef __vtkIdType_h
#define __vtkIdType_h

#ifndef __VTK_SYSTEM_INCLUDES__INSIDE
Do_not_include_vtkIdType_directly__vtkSystemIncludes_includes_it;
#endif

// Choose an implementation for vtkIdType.
#define VTK_HAS_ID_TYPE
#ifdef VTK_USE_64BIT_IDS
# define VTK_ID_TYPE_IS_NOT_BASIC_TYPE
# define VTK_SIZEOF_ID_TYPE 8
# ifdef _WIN32
typedef __int64 vtkIdType;
#  define VTK_NEED_ID_TYPE_STREAM_OPERATORS
# else // _WIN32
typedef long long vtkIdType;
#  define VTK_NEED_ID_TYPE_STREAM_OPERATORS
# endif // _WIN32
#else // VTK_USE_64BIT_IDS
# define VTK_SIZEOF_ID_TYPE VTK_SIZEOF_INT
typedef int vtkIdType;
#endif // VTK_USE_64BIT_IDS

// Define a wrapper class so that we can define streaming operators
// for vtkIdType without conflicting with other libraries'
// implementations.
class VTK_COMMON_EXPORT vtkIdTypeHolder
{
public:
	vtkIdTypeHolder(vtkIdType& v) : Value(v) {}
	vtkIdType& Value;
private:
	vtkIdTypeHolder& operator=(const vtkIdTypeHolder&); // Not Implemented.
};
VTK_COMMON_EXPORT ostream& operator << (ostream& os, vtkIdTypeHolder idh);
VTK_COMMON_EXPORT istream& operator >> (istream& is, vtkIdTypeHolder idh);

#endif