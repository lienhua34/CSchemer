#include "common.h"

/*************************************************************
 *This file provides procedures operating character objects
 *************************************************************/

//two args: ch1 & ch2
cellpoint char_eq(void)
{
	if (get_char(args_ref(1)) == get_char(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_eq_ci(void)
{
	//compute the upcase of ch1 & ch2
	args_push(args_ref(1));
	reg = char_upcase();
	stack_push(&vars_stack, reg);
	args_push(args_ref(2));
	reg = char_upcase();
	//calls char_eq
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = char_eq();
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_less(void)
{
	if (get_char(args_ref(1)) < get_char(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_less_ci(void)
{
	//compute the upcase of ch1 & ch2
	args_push(args_ref(1));
	reg = char_upcase();
	stack_push(&vars_stack, reg);
	args_push(args_ref(2));
	reg = char_upcase();
	//calls char_less
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = char_less();
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_greater(void)
{
	if (get_char(args_ref(1)) > get_char(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_greater_ci(void)
{
	//compute the upcase of ch1 & ch2
	args_push(args_ref(1));
	reg = char_upcase();
	stack_push(&vars_stack, reg);
	args_push(args_ref(2));
	reg = char_upcase();
	//calls char_greater
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = char_greater();
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_less_eq(void)
{
	if (get_char(args_ref(1)) <= get_char(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_less_eq_ci(void)
{
	//computes the upcase of ch1 & ch2
	args_push(args_ref(1));
	reg = char_upcase();
	stack_push(&vars_stack, reg);
	args_push(args_ref(2));
	reg = char_upcase();
	//calls char_less_eq
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = char_less_eq();
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_greater_eq(void)
{
	if (get_char(args_ref(1)) >= get_char(args_ref(2))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: ch1 & ch2
cellpoint char_greater_eq_ci(void)
{
	//computes the upcase of ch1 & ch2
	args_push(args_ref(1));
	reg = char_upcase();
	stack_push(&vars_stack, reg);
	args_push(args_ref(2));
	reg = char_upcase();
	//calls char_greater_eq
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = char_greater_eq();
	args_pop(2);
	return reg;
}
//one arg: ch
cellpoint char_is_upcase(void)
{
	char ch = get_char(args_ref(1));
	if (ch >= 'A' && ch <= 'Z'){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_is_lowercase(void)
{
	char ch = get_char(args_ref(1));
	if (ch >= 'a' && ch <= 'z'){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_is_alphabetic(void)
{
	char c = get_char(args_ref(1));
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_is_numeric(void)
{
	char c = get_char(args_ref(1));
	if (c >= '0' && c <= '9'){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_is_whitespace(void)
{
	char c = get_char(args_ref(1));
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_2_integer(void)
{
	reg = args_ref(1);
	reg = make_integer((int)get_char(reg));
	args_pop(1);
	return reg;
}
//one arg: n
cellpoint integer_2_char(void)
{
	reg = args_ref(1);
	reg = make_char((char)get_integer(reg));
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_upcase(void)
{
	args_push(args_ref(1));
	reg = char_is_lowercase();
	if (is_true(reg)){
		char c = get_char(args_ref(1));
		c = c - 'a' + 'A';
		reg = make_char(c);
	}else {
		reg = args_ref(1);
	}
	args_pop(1);
	return reg;
}
//one arg: ch
cellpoint char_downcase(void)
{
	args_push(args_ref(1));
	reg = char_is_upcase();
	if (is_true(reg)){
		char c = get_char(args_ref(1));
		c = c - 'A' + 'a';
		reg = make_char(c);
	}else {
		reg = args_ref(1);
	}
	args_pop(1);
	return reg;
}
