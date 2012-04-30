#include "common.h"
#include <string.h>

/*************************************************************
 *This file provides procedures operating string objects
 *************************************************************/

//one arg: chs
cellpoint string(void)
{
	int len,i;

	args_push(args_ref(1));
	len = get_integer(list_len());
	//push chs
	stack_push(&vars_stack, args_ref(1));
	reg = make_string(len, NIL);
	stack_push(&vars_stack, reg);
	for (i=0; i < len; ++i){
		reg = stack_pop(&vars_stack);
		string_set(reg, i, car(stack_top(&vars_stack)));
		//renew chs
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		stack_push(&vars_stack, reg);
	}
	reg = stack_pop(&vars_stack);
	//pop chs
	stack_pop(&vars_stack);
	args_pop(1);
	return reg;
}
//two args: str1 & str2
cellpoint string_eq(void)
{
    int len1 = string_len(args_ref(1));
    int len2 = string_len(args_ref(2));

    if (args_ref(1) == args_ref(2)){
        args_pop(2);
		return a_true;
    }

    if (len1 != len2){
		args_pop(2);
        return a_false;
    }else {
        int i;
        for (i=0; i < len1; i++){
			//calls char_eq
			reg = string_ref(args_ref(1), i);
			args_push(string_ref(args_ref(2), i));
			args_push(reg);
			reg = char_eq();
            if (is_false(reg)){
                args_pop(2);
				return a_false;
            }
        }
		args_pop(2);
        return a_true;
    }
}
//two args: str1 & str2
cellpoint string_eq_ci(void)
{
	if (args_ref(1) == args_ref(2)){
		args_pop(2);
		return a_true;
	}
	
	int len1 = string_len(args_ref(1));
	int len2 = string_len(args_ref(2));
	int i;
	
	if (len1 != len2){
		args_pop(2);
		return a_false;
	}
	for (i=0; i < len1; ++i){
		//calls char_eq_ci
		reg = string_ref(args_ref(1), i);
		args_push(string_ref(args_ref(2), i));
		args_push(reg);
		reg = char_eq_ci();
		if (is_false(reg)){
			args_pop(2);
			return a_false;
		}
	}
	args_pop(2);
	return a_true;
}
//two args: str1 & str2
cellpoint string_less(void)
{
	int len1 = string_len(args_ref(1));
	int len2 = string_len(args_ref(2));
	int i, len = len1;

	if (len1 >= len2){
		len = len2;
	}
	for (i=0; i < len; ++i){
		//calls char_less
		reg = string_ref(args_ref(1), i);
		args_push(string_ref(args_ref(2), i));
		args_push(reg);
		reg = char_less();
		if (is_true(reg)){
			args_pop(2);
			return a_true;
		}else {
			//calls char_greater
			reg = string_ref(args_ref(1), i);
			args_push(string_ref(args_ref(2), i));
			args_push(reg);
			reg = char_greater();
			if (is_true(reg)){
				args_pop(2);
				return a_false;
			}
		}
	}
	if (len1 < len2){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_less_ci(void)
{
	int len1 = string_len(args_ref(1));
	int len2 = string_len(args_ref(2));
	int i, len = len1;
	
	if (len1 > len2){
		len = len2;
	}
	for (i=0; i < len; ++i){
		//calls char_less_ci
		reg = string_ref(args_ref(1), i);
		args_push(string_ref(args_ref(2), i));
		args_push(reg);
		reg = char_less_ci();
		if (is_true(reg)){
			args_pop(2);
			return a_true;
		}else {
			//calls char_greater_ci
			reg = string_ref(args_ref(1), i);
			args_push(string_ref(args_ref(2), i));
			args_push(reg);
			reg = char_greater_ci();
			if (is_true(reg)){
				args_pop(2);
				return a_false;
			}
		}
	}
	if (len1 < len2){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_greater(void)
{
	int len1 = string_len(args_ref(1));
	int len2 = string_len(args_ref(2));
	int i, len = len1;
	
	if (len1 > len2){
		len = len2;
	}
	for (i=0; i < len; ++i){
		//calls char_greater
		reg = string_ref(args_ref(1), i);
		args_push(string_ref(args_ref(2), i));
		args_push(reg);
		reg = char_greater();
		if (is_true(reg)){
			args_pop(2);
			return a_true;
		}else {
			//calls char_less
			reg = string_ref(args_ref(1), i);
			args_push(string_ref(args_ref(2), i));
			args_push(reg);
			reg = char_less();
			if (is_true(reg)){
				args_pop(2);
				return a_false;
			}
		}
	}
	if (len1 > len2){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_greater_ci(void)
{
	int len1 = string_len(args_ref(1));
	int len2 = string_len(args_ref(2));
	int i, len = len1;
	
	if (len1 > len2){
		len = len2;
	}
	for (i=0; i < len; ++i){
		//calls char_greater_ci
		reg = string_ref(args_ref(1), i);
		args_push(string_ref(args_ref(2), i));
		args_push(reg);
		reg = char_greater_ci();
		if (is_true(reg)){
			args_pop(2);
			return a_true;
		}else {
			//calls char_less_ci
			reg = string_ref(args_ref(1), i);
			args_push(string_ref(args_ref(2), i));
			args_push(reg);
			reg = char_less_ci();
			if (is_true(reg)){
				args_pop(2);
				return a_false;
			}
		}
	}
	if (len1 > len2){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_less_eq(void)
{
	reg = args_ref(1);
	args_push(args_ref(2));
	args_push(reg);
	reg = string_greater();
	if (is_true(reg)){
		reg = a_false;
	}else {
		reg = a_true;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_less_eq_ci(void)
{
	reg = args_ref(1);
	args_push(args_ref(2));
	args_push(reg);
	reg = string_greater_ci();
	if (is_true(reg)){
		reg = a_false;
	}else {
		reg = a_true;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_greater_eq(void)
{
	reg = args_ref(1);
	args_push(args_ref(2));
	args_push(reg);
	reg = string_less();
	if (is_true(reg)){
		reg = a_false;
	}else {
		reg = a_true;
	}
	args_pop(2);
	return reg;
}
//two args: str1 & str2
cellpoint string_greater_eq_ci(void)
{
	reg = args_ref(1);
	args_push(args_ref(2));
	args_push(reg);
	reg = string_less_ci();
	if (is_true(reg)){
		reg = a_false;
	}else {
		reg = a_true;
	}
	args_pop(2);
	return reg;
}
//two args: str, start & end
cellpoint substring(void)
{
	int len = string_len(args_ref(1));
	int start = get_integer(args_ref(2));
	int end = get_integer(args_ref(3));
	int i;
	if ( start < 0 || end < start || end > len){
		printf("Error: the arguments must satisfy 0 <= start <= end <= (string-length string), but the string-length(%d), start(%d), end(%d) don't satisfied.\n", len ,start, end);
		error_handler();
	}
	reg = make_string(end-start, NIL);
	stack_push(&vars_stack, reg);
	for (i=start; i < end; ++i){
		reg = stack_top(&vars_stack);
		string_set(reg, i-start, string_ref(args_ref(1), i));
	}
	reg = stack_pop(&vars_stack);
	args_pop(3);
	return reg;
}
//one arg: strlst
cellpoint string_append(void)
{
	stack_push(&vars_stack, NIL);
	stack_push(&vars_stack, args_ref(1));
	while (is_false(is_null(stack_top(&vars_stack)))){
		int len, i;

		reg = stack_pop(&vars_stack);
		len = string_len(car(reg));
		for (i=0; i < len; ++i){
			stack_push(&vars_stack,cons(string_ref(car(reg), i), stack_pop(&vars_stack)));
		}
		reg = cdr(reg);
		stack_push(&vars_stack, reg);
	}
	stack_pop(&vars_stack);
	reg = stack_pop(&vars_stack);
	//reverse
	args_push(reg);
	reg = reverse();
	//string
	args_push(reg);
	reg = string();
	args_pop(1);
	return reg;
}
//one arg: str
cellpoint string_2_list(void)
{
	int len = string_len(args_ref(1));
	int i;
	
	reg = NIL;
	for (i=len-1; i >= 0; --i){
		reg = cons(string_ref(args_ref(1),i), reg);
	}
	args_pop(1);
	return reg;
}
//one arg: lst
cellpoint list_2_string(void)
{
	args_push(args_ref(1));
	reg = string();
	args_pop(1);
	return reg;
}
//one arg: str
cellpoint string_copy(void)
{
	int len = string_len(args_ref(1));
	int i;
	reg = make_string(len, NIL);
	for (i=0; i < len; ++i){
		string_set(reg, i, string_ref(args_ref(1), i));
	}
	args_pop(1);
	return reg;
}
//two args: str & fill
void string_fill(void)
{
	int len = string_len(args_ref(1));
	int i;
	
	reg = args_ref(2);
	for (i=0; i < len; ++i){
		string_set(args_ref(1), i, reg);
	}
	args_pop(1);
}
