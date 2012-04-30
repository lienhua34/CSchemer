#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


typedef unsigned int cellpoint;
typedef unsigned int uint;

struct cons_cell {
    uint car;
    uint cdr;
};

#define NIL 0

#define boolean int
#define true 1
#define false 0

#define INTEGER_BIT 0x0001
#define RATIONAL_BIT 0x0002
#define REAL_BIT 0x0004
#define COMPLEX_BIT 0x0008
#define BOOLEAN_BIT 0x0010
#define CHARACTER_BIT 0x0020
#define SYMBOL_BIT 0x0040
#define STRING_BIT 0x0080
#define VECTOR_BIT 0x0100
#define PRIM_PROC_BIT 0x0200
#define COMP_PROC_BIT 0x04000
#define ATOM_BIT (1 << (sizeof(uint)*8-1))

//primitive procedure objects type
typedef cellpoint (*prim_proc_t)(cellpoint);

//variables
extern boolean eval_error;

#include "stack.h"
#include "memory.h"
#include "atom.h"
#include "control.h"
#include "number.h"
#include "character.h"
#include "boolean.h"
#include "symbol.h"
#include "mstring.h"
#include "vector.h"
#include "output.h"
#include "list.h"
#include "input.h"
#include "equal_predicate.h"
#include "read_parse.h"
#include "procedure.h"
#include "environment.h"
#include "eval.h"
#include "driver_loop.h"
#include "garbage_collection.h"

#endif // COMMON_H_INCLUDED
