#ifndef DIS_TYPES_H
#define DIS_TYPES_H

#include <stdint.h>

typedef uint8_t byte;
typedef int32_t word;
typedef int64_t big;
typedef double real;
typedef void *pointer;
typedef uintptr_t uptr;

typedef struct Alt {
    int nsend;
    int nrecv;
    struct {
        Channel *c;
        void *val;
    } entry[];
} Alt;

typedef struct Frame Frame;

/// A table in data scape that lists the functions imported by the current
/// module from the module to be loaded.
typedef struct LinkageDescriptor {
    /// The number of items in the `entry` array - can be 0.
    int nentries;
    /// Each entry is aligned on a word boundary; there can therefor be padding
    /// before each structure.
    struct {
        /// MD5 hash of the function's type signature.
        int sig;
        /// UTF-8 encoded name, 0-terminated
        byte name[];
    } entry[];
} LinkageDescriptor;

typedef struct Module Module;

#endif //DIS_TYPES_H
