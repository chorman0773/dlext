#ifndef DLEXT_H_2020_07_16_09_05_56
#define DLEXT_H_2020_07_16_09_05_56

#include <dlfcn.h>

#ifdef __cplusplus
extern"C"{
#endif

/**
 * @page fdlopen
 * @brief Opens the so file read by fd.
 *
 * @section synopis SYNOPSIS
 * #include <dlext.h>
 *
 * void* fdlopen(int fd,int mode);
 *
 * @section description DESCRIPTION
 *
 * The fdlopen function opens a handle to a dso which is read from fd, as though by a call to dlopen(3).
 *
 * If fd is open to a file which was passed (by name) to a call to dlopen(3), the behaviour is undefined.
 *
 * If fd is not at the beginning, the shared object is read from the current point in the file,
 *  if additional processing of the shared object is required, it is recommended to lseek(2) to the beginning of the shared object.
 *
 * If fd is closed before calling dlclose(3) on the return value (if not-null), the behaviour is undefined
 *  (Note that exiting the program before calling dlclose(3) does *not* cause undefined behaviour).
 *
 * fd shall not be a tty (as determined by isatty(2)).
 *
 * @param fd The file descriptor number which has the file open.
 * @param mode The mode to use in opening the dso. All modes have the same meaning as in dlopen(3).
 * @return A handle to the dso, suitable for use with dlsym, and for being closed with dlclose.
 * @see dlopen(3)
 * @see dlclose(3)
 * @see dlsym(3)
 * @section error ERRORS
 * If an error occurs, the function returns null and sets errno to the appropriate constant.
 *
 * Like standard library functions, if fdlopen returns a valid value,
 *  the value of errno is unspecified (but this function will not set errno to 0).
 *
 * - ENOSYS - If it is not possible to resolve the request.
 * - EBADF - If fd is an invalid file descriptor.
 * - EBADFD - If fd is a tty, or otherwise not valid for this call (though is otherwise a valid file descriptor).
 * - EACCES - If fd is not opened for read-access, or a permission issue causes the file to be unreachable.
 * - EISDIR - If fd is a directory.
 * - Any other error which can be returned by a call to dlopen.
 *
 * @section note Implementation Note
 * The implementation of fdlopen provided by this library makes use of the `/proc` filesystem.
 *  ENOSYS is returned if `/proc` cannot be accessed with F_OK.
 */
void* fdlopen(int fd,int mode);

#ifdef __cplusplus
};
#endif

#endif