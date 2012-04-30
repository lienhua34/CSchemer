#include "common.h"
#include "argcheck.h"

/////////////////////////////////////////////////////////////////////
//pair standard procedure
/////////////////////////////////////////////////////////////////////
///pair?
cellpoint pair_pred_proc(cellpoint arglst)
{
	check_arglst_len_eq("pair?", 1, arglst);
	
	cellpoint arg = car(arglst);
	return is_pair(arg);
}
///cons
cellpoint cons_proc(cellpoint arglst)
{
	check_arglst_len_eq("cons", 2, arglst);
	
	cellpoint farg = car(arglst);
	cellpoint sarg = car(cdr(arglst));
	return cons(farg, sarg);
}
///car
cellpoint car_proc(cellpoint arglst)
{
	check_arglst_len_eq("car", 1, arglst);
	check_arg_type("car", "first", car(arglst), PAIR_T);

	return car(car(arglst));
}
///cdr
cellpoint cdr_proc(cellpoint arglst)
{
	check_arglst_len_eq("cdr", 1, arglst);
	check_arg_type("cdr", "first", car(arglst), PAIR_T);

	return cdr(car(arglst));
}
///car-set!
cellpoint car_set_proc(cellpoint arglst)
{
	check_arglst_len_eq("car-set!", 2, arglst);
	check_arg_type("car-set!", "first", car(arglst), PAIR_T);

	car_set(car(arglst), car(cdr(arglst)));
	return make_symbol("ok");
}
///cdr-set!
cellpoint cdr_set_proc(cellpoint arglst)
{
	check_arglst_len_eq("cdr-set!", 2, arglst);
	check_arg_type("cdr-set!", "first", car(arglst), PAIR_T);

	cdr_set(car(arglst), car(cdr(arglst)));
	return make_symbol("ok");
}
