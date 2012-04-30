#include "common.h"

/*************************************************************
 *This file provides procedures operating procedure objects.
 *************************************************************/

///////////////////////////////////////////////////////////////
//procedure common functions
///////////////////////////////////////////////////////////////
cellpoint is_procedure(cellpoint obj)
{
	if (is_true(is_prim_proc(obj)) || is_true(is_compound_proc(obj))){
		return a_true;
	}else {
		return a_false;
	}
}
//one arg: proc
cellpoint procedure_name(void)
{
	reg = car(cdr(args_ref(1)));
	args_pop(1);
	return reg;
}
//two args: proc & name
void procedure_name_set(void)
{
	car_set(cdr(args_ref(1)), args_ref(2));
	args_pop(2);
}

/////////////////////////////////////////////////////////////////
//primitive procedure
/////////////////////////////////////////////////////////////////

//two args: proc & args
cellpoint apply_prim_proc(void)
{
	reg = (cellpoint)prim_proc_obj(args_ref(1));
	reg = (*(prim_proc_t)reg)(args_ref(2));
	args_pop(2);
	return reg;
}

//////////////////////////////////////////////////////////////////
//compound procedure
//////////////////////////////////////////////////////////////////

//one arg: pp
cellpoint procedure_parameters(void)
{
	reg = car(cdr(cdr(args_ref(1))));
	args_pop(1);
	return reg;
}
//one arg: pp
cellpoint procedure_body(void)
{
	reg = car(cdr(cdr(cdr(args_ref(1)))));
	args_pop(1);
	return reg;
}
//one arg: pp
cellpoint procedure_env(void)
{
	reg = car(cdr(cdr(cdr(cdr(args_ref(1))))));
	args_pop(1);
	return reg;
}



