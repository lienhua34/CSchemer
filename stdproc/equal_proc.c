#include "common.h"
#include "argcheck.h"

///////////////////////////////////////////////////////////////////////
//equivalence predicate procedure
///////////////////////////////////////////////////////////////////////

///eq?
cellpoint eq_proc(cellpoint arglst)
{
	check_arglst_len_eq("eq?", 2, arglst);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return eq();
}
///eqv?
cellpoint eqv_proc(cellpoint arglst)
{
	check_arglst_len_eq("eqv?", 2, arglst);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return eqv();
}
///equal?
cellpoint equal_proc(cellpoint arglst)
{
	check_arglst_len_eq("equal?", 2, arglst);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return equal();
}
