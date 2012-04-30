#include "common.h"

/*************************************************************
 *This file provides procedures operating number objects.
 *statement: 
 *    This system only supports integer objects.
 *************************************************************/

//two args: num1 & num2
cellpoint number_eq(void)
{
	if (get_integer(args_ref(1)) == get_integer(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint number_less(void)
{
	if (get_integer(args_ref(1)) < get_integer(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint number_greater(void)
{
	if (get_integer(args_ref(1)) > get_integer(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint number_less_eq(void)
{
	if (get_integer(args_ref(1)) <= get_integer(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint number_greater_eq(void)
{
	if (get_integer(args_ref(1)) >= get_integer(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint add(void)
{
	reg = make_integer(get_integer(args_ref(1)) + get_integer(args_ref(2)));
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint sub(void)
{
	reg = make_integer(get_integer(args_ref(1)) - get_integer(args_ref(2)));
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint mul(void)
{
	reg = make_integer(get_integer(args_ref(1)) * get_integer(args_ref(2)));
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint mdiv(void)
{
	reg = make_integer(get_integer(args_ref(1)) / get_integer(args_ref(2)));
	args_pop(2);
	return reg;
}
//two args: num1 & num2
cellpoint mremainder(void)
{
	reg = make_integer(get_integer(args_ref(1)) % get_integer(args_ref(2)));
	args_pop(2);
	return reg;
}


