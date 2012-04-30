#include "common.h"

/*************************************************************
 *This file provides two main functions: eval & apply
 *************************************************************/

//////////////////////////////////////////////////////
//self_evaluating
//number, boolean, string, character and vector object is self-evaluating.
//////////////////////////////////////////////////////
static cellpoint is_self_evaluating(cellpoint exp)
{
	if (is_true(is_number(exp)) || is_true(is_boolean(exp)) ||
		is_true(is_null(exp)) || is_true(is_string(exp)) ||
		is_true(is_char(exp)) || is_true(is_vector(exp))){
		reg = a_true;
	}else {
		reg = a_false;
	}
	return reg;
}

////////////////////////////////////////////////////////
//variable
//variables is a symbol object
////////////////////////////////////////////////////////
static cellpoint is_variable(cellpoint exp)
{
	return is_symbol(exp);
}
//two args: exp & label
static cellpoint is_tagged_list(void)
{
	if (is_true(is_pair(args_ref(1)))){
		reg = car(args_ref(1));
		args_push(args_ref(2));
		args_push(reg);
		reg = eq();
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//////////////////////////////////////////////////////
//quotation
//format: (quote <datum>)
//////////////////////////////////////////////////////
static cellpoint is_quoted(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("quote"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint quotation_text(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg))){
		printf("quote: Bad syntax. in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}

//////////////////////////////////////////////////////////
//lambda
//format: (lambda <formal> <body>)
//////////////////////////////////////////////////////////
static cellpoint is_lambda(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("lambda"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint lambda_parameters(void)
{
	reg = args_ref(1);
	reg = cdr(reg);
	if (is_true(is_null(reg))){
		printf("lambda: bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint lambda_body(void)
{
	reg = args_ref(1);
	reg = cdr(cdr(reg));
	if (is_true(is_null(reg))){
		printf("lambda: bad syntax (body can't be empty!) in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	args_pop(1);
	return reg;
}
//two args: formals & body
static cellpoint make_lambda(void)
{
	reg = cons(args_ref(1), args_ref(2));
	stack_push(&vars_stack, reg);
	reg = make_symbol("lambda");
	reg = cons(reg, stack_pop(&vars_stack));
	args_pop(2);
	return reg;
}
//one arg: exp
static cellpoint eval_lambda(void)
{
	args_push(args_ref(1));
	reg = lambda_parameters();
	stack_push(&vars_stack, reg);
	args_push(args_ref(1));
	reg = lambda_body();
	stack_push(&vars_stack, reg);
	//make a compound procedure object
	args_push(current_env);
	args_push(stack_pop(&vars_stack));
	args_push(stack_pop(&vars_stack));
	reg = make_procedure();
	args_pop(1);
	return reg;
}

/////////////////////////////////////////////////////
//assignment
//format: (set! <var> <value>)
/////////////////////////////////////////////////////
static cellpoint is_assignment(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("set!"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint assignment_variable(void)
{
	reg = args_ref(1);
	reg = cdr(reg);
	if (is_true(is_null(reg))){
		printf("set!: bad syntax (no identifier) in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint assignment_value(void)
{
	reg = args_ref(1);
	reg = cdr(cdr(reg));
	if (is_true(is_null(reg))){
		printf("set!: bad syntax (missing expression after identifier) in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint eval_assignment(void)
{
	//calls assignment_variable
	args_push(args_ref(1));
	reg = assignment_variable();
	stack_push(&vars_stack, reg);
	//compute assignment value
	args_push(args_ref(1));
	reg = assignment_value();
	args_push(a_false);
	args_push(reg);
	reg = eval();
	stack_push(&vars_stack, reg);
	//calls set_var_val
	args_push(current_env);
	args_push(stack_pop(&vars_stack));
	args_push(stack_pop(&vars_stack));
	set_var_val();
	
	args_pop(1);
	return make_symbol("ok");
}

///////////////////////////////////////////////////////////////
//definition
//format: (define <var> <value>) or 
//        (define (var <formals>) <body>)
//////////////////////////////////////////////////////////////
static cellpoint is_definition(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("define"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint definition_variable(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg))){
		printf("define: bad syntax in:");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	if (is_false(is_symbol(reg))){
		reg = car(reg);
	}
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint definition_value(void)
{
	if (is_true(is_null(cdr(cdr(args_ref(1)))))){
		printf("define: bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(cdr(args_ref(1)));
	if (is_true(is_symbol(reg))){
		reg = car(cdr(cdr(args_ref(1))));
	}else {
		//get formal arguments list
		reg = cdr(reg);
		stack_push(&vars_stack, reg);
		//get body
		reg = cdr(cdr(args_ref(1)));
		//make a lambda expression
		args_push(reg);
		args_push(stack_pop(&vars_stack));
		reg = make_lambda();
	}
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint eval_definition(void)
{
	//calls definition_variable
	args_push(args_ref(1));
	reg = definition_variable();
	stack_push(&vars_stack, reg);
	//compute definition value
	args_push(args_ref(1));
	reg = definition_value();
	args_push(a_false);
	args_push(reg);
	reg = eval();
	stack_push(&vars_stack, reg);
	//calls define_var
	args_push(current_env);
	args_push(stack_pop(&vars_stack));
	args_push(stack_pop(&vars_stack));
	define_var();

	args_pop(1);
	return make_symbol("ok");
}

////////////////////////////////////////////////////////////////
//if
//format: (if <test> <consequent>) or
//        (if <test> <consequent> <alternative>)
///////////////////////////////////////////////////////////////
static cellpoint is_if(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("if"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint if_predicate(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg))){
		printf("if: bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint if_consequent(void)
{
	reg = cdr(cdr(args_ref(1)));
	if (is_true(is_null(reg))){
		printf("if: bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint if_alternative(void)
{
	
	reg = cdr(cdr(cdr(args_ref(1))));
	if (is_true(is_null(reg))){
		reg = a_false;
	}else {
		reg = car(reg);
	}
	args_pop(1);
	return reg;
}
//three args: pred, consq & alter
static cellpoint make_if(void)
{
	reg = NIL;
	if (is_false(is_null(args_ref(3)))){
		reg = cons(args_ref(3), NIL);
	}
	reg = cons(args_ref(2), reg);
	reg = cons(args_ref(1), reg);
	reg = cons(make_symbol("if"), reg);
	args_pop(3);
	return reg;
}
//two args: exp & tail_context
static cellpoint eval_if(void)
{
	//computes if_predicate
	args_push(args_ref(1));
	reg = if_predicate();
	//tail_context is a_false
	args_push(a_false);
	args_push(reg);
	reg = eval();
	if (is_true(reg)){
		//computes if_consequent
		args_push(args_ref(1));
		reg = if_consequent();
		//transmits the tail_context
		args_push(args_ref(2));
		args_push(reg);
		reg = eval();
	}else {
		//computes if_alternative
		args_push(args_ref(1));
		reg = if_alternative();
		//transmits the tail_context
		args_push(args_ref(2));
		args_push(reg);
		reg = eval();
	}
	args_pop(2);
	return reg;
}

/////////////////////////////////////////////////////////////////
//begin
//format: (begin <exps>)
/////////////////////////////////////////////////////////////////
static cellpoint is_begin(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("begin"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint begin_actions(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: exps
static cellpoint last_exp(void)
{
	reg = is_null(cdr(args_ref(1)));
	args_pop(1);
	return reg;
}
//one arg: exps
static cellpoint first_exp(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: exps
static cellpoint rest_exps(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: exps
static cellpoint make_begin(void)
{
	reg = make_symbol("begin");
	reg = cons(reg, args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: exps
static cellpoint sequence_2_exp(void)
{
	//used in cond_2_if
	reg = args_ref(1);
	if (is_false(is_null(reg))){
		//calls last_exp
		args_push(args_ref(1));
		reg = last_exp();
		if (is_true(reg)){
			args_push(args_ref(1));
			reg = first_exp();
		}else {
			args_push(args_ref(1));
			reg = make_begin();
		}
	}
	args_pop(1);
	return reg;
}
//two args: exps & tail_context
static cellpoint eval_sequence(void)
{
	stack_push(&vars_stack, args_ref(1));
	args_push(stack_top(&vars_stack));
	reg = last_exp();
	while (is_false(reg)){
		args_push(stack_top(&vars_stack));
		reg = first_exp();
		//eval the exp which isn't the last one with tail_context is a_false
		args_push(a_false);
		args_push(reg);
		reg = eval();
		//renew the remain exps
		args_push(stack_pop(&vars_stack));
		reg = rest_exps();
		stack_push(&vars_stack, reg);
		args_push(stack_top(&vars_stack));
		reg = last_exp();
	}
	//get the last expression
	args_push(stack_pop(&vars_stack));
	reg = first_exp();
	//eval the last expression with the second argument (tail_context)
	args_push(args_ref(2));
	args_push(reg);
	reg = eval();

	args_pop(2);
	return reg;
}

///////////////////////////////////////////////////////////////
//cond
//format: (cond <clause> ...)
///////////////////////////////////////////////////////////////
static cellpoint is_cond(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("cond"));
	args_push(reg);
	reg = is_tagged_list();
	return reg;
}
//one arg: exp
static cellpoint cond_clauses(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: clause
static cellpoint cond_predicate(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: clause
static cellpoint cond_actions(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: clause
static cellpoint is_cond_else_clause(void)
{
	//calls cond_predicate
	args_push(args_ref(1));
	reg = cond_predicate();
	stack_push(&vars_stack, reg);
	//calls eq
	args_push(make_symbol("else"));
	args_push(stack_pop(&vars_stack));
	reg = eq();

	args_pop(1);
	return reg;
}
//one arg: clauses
static cellpoint expand_clauses(void)
{
	if (is_true(is_null(args_ref(1)))){
		reg = a_false;
	}else {
		args_push(car(args_ref(1)));
		reg = is_cond_else_clause();
		if (is_true(reg)){
			reg = cdr(args_ref(1));
			if(is_true(is_null(reg))){
				//calls cond_actions
				args_push(car(args_ref(1)));
				reg = cond_actions();
				//calls sequence_2_exp
				args_push(reg);
				reg = sequence_2_exp();
			}else {
				printf("Error: ELSE clause isn't last clause in cond expression.\n");
				error_handler();
			}
		}else {
			//calls cond_predicate
			args_push(car(args_ref(1)));
			reg = cond_predicate();
			stack_push(&vars_stack, reg);
			//calls sequence_2_exp
			args_push(car(args_ref(1)));
			reg = cond_actions();
			args_push(reg);
			reg = sequence_2_exp();
			stack_push(&vars_stack, reg);
			//calls expand_clauses to expand the rest clauses
			args_push(cdr(args_ref(1)));
			reg = expand_clauses();
			//calls make_if
			args_push(reg);
			args_push(stack_pop(&vars_stack));
			args_push(stack_pop(&vars_stack));
			reg = make_if();
		}
	}
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint cond_2_if(void)
{
	args_push(args_ref(1));
	reg = cond_clauses();
	args_push(reg);
	reg = expand_clauses();
	args_pop(1);
	return reg;
}

////////////////////////////////////////////////////////////////
//application
////////////////////////////////////////////////////////////////
static cellpoint is_application(cellpoint exp)
{
	reg = is_pair(exp);
	return reg;
}
//one arg: exp
static cellpoint operator(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint operands(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: ops
static cellpoint no_operands(void)
{
	reg = is_null(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: ops
static cellpoint first_operand(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: ops
static cellpoint rest_operands(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: ops
static cellpoint list_of_values(void)
{
	args_push(args_ref(1));
	reg = no_operands();
	if (is_true(reg)){
		reg = NIL;
	}else {
		//get the first operand
		args_push(args_ref(1));
		reg = first_operand();
		//eval the first operand with tail_context is a_false
		args_push(a_false);
		args_push(reg);
		reg = eval();
		stack_push(&vars_stack, reg);
		//eval the rest operands
		args_push(args_ref(1));
		reg = rest_operands();
		args_push(reg);
		reg = list_of_values();
		
		reg = cons(stack_pop(&vars_stack), reg);
	}
	args_pop(1);
	return reg;
}
//one arg: body
static cellpoint eval_lambda_body(void)
{
	stack_push(&vars_stack, args_ref(1));
	args_push(stack_top(&vars_stack));
	reg = last_exp();
	while (is_false(reg)){
		args_push(stack_top(&vars_stack));
		reg = first_exp();
		//eval the exp which isn't the last one with tail_context is a_false
		args_push(a_false);
		args_push(reg);
		reg = eval();
		//renew the remain exps
		args_push(stack_pop(&vars_stack));
		reg = rest_exps();
		stack_push(&vars_stack, reg);
		args_push(stack_top(&vars_stack));
		reg = last_exp();
	}
	//get the last expression
	args_push(stack_pop(&vars_stack));
	reg = first_exp();
	//eval the last expression with the tail_context is a_true
	args_push(a_true);
	args_push(reg);
	reg = eval();

	args_pop(1);
	return reg;
}

////////////////////////////////////////////////////////////////
//and & or expressions
///////////////////////////////////////////////////////////////
static cellpoint is_and(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("and"));
	args_push(reg);
	return is_tagged_list();
}
static cellpoint is_or(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("or"));
	args_push(reg);
	return is_tagged_list();
}
//two args: exp & tail_context
static cellpoint eval_and(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg))){
		args_pop(2);
		return a_true;
	}
	stack_push(&vars_stack, reg);
	while (is_false(is_null(cdr(reg)))){
		//evals the expressions which aren't the last expression
		args_push(a_false);
		args_push(car(reg));
		reg = eval();
		if (is_false(reg)){
			args_pop(2);
			return a_false;
		}
		//renews the remaining expressions
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		reg = stack_top(&vars_stack);
	}
	//evals the last expression
	args_push(args_ref(2));
	args_push(car(stack_pop(&vars_stack)));
	reg = eval();
	args_pop(2);
	return reg;
}
//two args: exp & tail_context
static cellpoint eval_or(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg))){
		args_pop(2);
		return a_false;
	}
	stack_push(&vars_stack, reg);
	while (is_false(is_null(cdr(reg)))){
		//evals the expressions which aren't the last expression
		args_push(a_false);
		args_push(car(reg));
		reg = eval();
		if (is_true(reg)){
			args_pop(2);
			return reg;
		}
		//renews the remaining expressions
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		reg = stack_top(&vars_stack);
	}
	//evals the last expressions
	args_push(args_ref(2));
	args_push(car(stack_pop(&vars_stack)));
	reg = eval();
	args_pop(2);
	return reg;
}

///////////////////////////////////////////////////////////////////
//let expression
///////////////////////////////////////////////////////////////////
static cellpoint is_let(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("let"));
	args_push(reg);
	return is_tagged_list();
}
static void check_bindings(char *proc, cellpoint binding, cellpoint exp)
{
	if (is_true(is_list(binding))){
		if (is_true(is_symbol(car(binding))) && 
			is_false(is_null(cdr(binding))) &&
			is_true(is_null(cdr(cdr(binding))))){
			return;
		}
	}
	printf("%s: Bad syntax (no an identifier and expression for binding) in: ", proc);
	write(exp);
	newline();
	error_handler();
}
//one arg: exp
static cellpoint let_bindings(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg)) || is_false(is_list(car(reg)))){
		printf("let: Bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint let_vars(void)
{
	args_push(args_ref(1));
	reg = let_bindings();
	stack_push(&vars_stack, NIL);
	while (is_false(is_null(reg))){
		check_bindings("let", car(reg), args_ref(1));
		stack_push(&vars_stack, cons(car(car(reg)), stack_pop(&vars_stack)));
		reg = cdr(reg);
	}
	args_push(stack_pop(&vars_stack));
	reg = reverse();
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint let_vals(void)
{
	args_push(args_ref(1));
	reg = let_bindings();
	stack_push(&vars_stack, NIL);
	while (is_false(is_null(reg))){
		check_bindings("let", car(reg), args_ref(1));
		stack_push(&vars_stack, cons(car(cdr(car(reg))), stack_pop(&vars_stack)));
		reg = cdr(reg);
	}
	args_push(stack_pop(&vars_stack));
	reg = reverse();
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint let_body(void)
{
	reg = cdr(cdr(args_ref(1)));
	if (is_true(is_null(reg))){
		printf("let: Bad syntax (no expression in body) in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	args_pop(1);
	return reg;
}
//two args: bindings & body
static cellpoint make_let(void)
{
	reg = cons(args_ref(1), args_ref(2));
	reg = cons(make_symbol("let"), reg);
	args_pop(2);
	return reg;
}
//one arg: exp
static cellpoint let_2_combination(void)
{
	//get the binding vals of let expression
	args_push(args_ref(1));
	reg = let_vals();
	stack_push(&vars_stack, reg);
	//make a lambda expression
	args_push(args_ref(1));
	reg = let_vars();
	stack_push(&vars_stack, reg);
	args_push(args_ref(1));
	reg = let_body();
	args_push(reg);
	args_push(stack_pop(&vars_stack));
	reg = make_lambda();
	//make a combination
	reg = cons(reg, stack_pop(&vars_stack));
	args_pop(1);
	return reg;
}

///////////////////////////////////////////////////////////////////
//let* expression
///////////////////////////////////////////////////////////////////
static cellpoint is_letstar(cellpoint exp)
{
	reg = exp;
	args_push(make_symbol("let*"));
	args_push(reg);
	return is_tagged_list();
}
//one arg: exp
static cellpoint letstar_bindings(void)
{
	reg = cdr(args_ref(1));
	if (is_true(is_null(reg)) || is_false(is_list(car(reg)))){
		printf("let*: Bad syntax in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	reg = car(reg);
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint letstar_body(void)
{
	reg = cdr(cdr(args_ref(1)));
	if (is_true(is_null(reg))){
		printf("let*: Bad syntax (no expression in body) in: ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	args_pop(1);
	return reg;
}
//one arg: exp
static cellpoint letstar_2_nested_lets(void)
{
	//get the reverse list of bindings list
	args_push(args_ref(1));
	reg = letstar_bindings();
	args_push(reg);
	reg = reverse();
	stack_push(&vars_stack, reg);
	//get body of let* expression
	args_push(args_ref(1));
	reg = letstar_body();
	//create nested lets
	if (is_true(is_null(stack_top(&vars_stack)))){
		args_push(reg);
		args_push(stack_pop(&vars_stack));
		reg = make_let();
	}else {
		while (is_false(is_null(stack_top(&vars_stack)))){
			check_bindings("let*", car(stack_top(&vars_stack)), args_ref(1));
			args_push(reg);
			args_push(cons(car(stack_top(&vars_stack)), NIL));
			reg = make_let();
			reg = cons(reg, NIL);
			//renews bingdings
			stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		}
		stack_pop(&vars_stack);
		reg = car(reg);
	}
	args_pop(1);
	return reg;
}

///////////////////////////////////////////////////////////////////
//eval
//requires two arguments:exp & tail_context
///////////////////////////////////////////////////////////////////
cellpoint eval(void)
{
	if (is_true(is_self_evaluating(args_ref(1)))){
		reg = args_ref(1);
	}else if (is_true(is_variable(args_ref(1)))){
		reg = args_ref(1);
		args_push(current_env);
		args_push(reg);
		reg = lookup_var_val();
	}else if (is_true(is_quoted(args_ref(1)))){
		args_push(args_ref(1));
		reg = quotation_text();
	}else if (is_true(is_assignment(args_ref(1)))){
		args_push(args_ref(1));
		reg = eval_assignment();
	}else if (is_true(is_definition(args_ref(1)))){
		args_push(args_ref(1));
		reg = eval_definition();
	}else if (is_true(is_if(args_ref(1)))){
		//eval if expression with the second argument (tail_context)
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = eval_if();
	}else if (is_true(is_lambda(args_ref(1)))){
		args_push(args_ref(1));
		reg = eval_lambda();
	}else if (is_true(is_begin(args_ref(1)))){
		args_push(args_ref(1));
		reg = begin_actions();
		//eval the actions of begin exp with the second argument (tail_context)
		args_push(args_ref(2));
		args_push(reg);
		reg = eval_sequence();
	}else if (is_true(is_cond(args_ref(1)))){
		args_push(args_ref(1));
		reg = cond_2_if();
		//eval the exp with the second argument (tail_context)
		args_push(args_ref(2));
		args_push(reg);
		reg = eval();
	}else if (is_true(is_and(args_ref(1)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = eval_and();
	}else if (is_true(is_or(args_ref(1)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = eval_or();
	}else if (is_true(is_let(args_ref(1)))){
		//convert let to combination
		args_push(args_ref(1));
		reg = let_2_combination();
		//evals the combination
		args_push(args_ref(2));
		args_push(reg);
		reg = eval();
	}else if (is_true(is_letstar(args_ref(1)))){
		//convert let* to nested lets
		args_push(args_ref(1));
		reg = letstar_2_nested_lets();
		//evals the nested lets
		args_push(args_ref(2));
		args_push(reg);
		reg = eval();
	}else if (is_true(is_application(args_ref(1)))){
		//computes operator
		args_push(args_ref(1));
		reg = operator();
		args_push(a_false);
		args_push(reg);
		reg = eval();
		stack_push(&vars_stack, reg);
		//computes operands
		args_push(args_ref(1));
		reg = operands();
		args_push(reg);
		reg = list_of_values();
		//calls apply with the second argument (tail_context)
		args_push(args_ref(2));
		args_push(reg);
		args_push(stack_pop(&vars_stack));
		reg = apply();
	}else {
		printf("Unknown expression type -- EVAL\n");
		error_handler();
	}
	args_pop(2);
	return reg;
}
/////////////////////////////////////////////////////////////
//apply
//requires three arguments:proc , args & tail_context
////////////////////////////////////////////////////////////
cellpoint apply(void)
{
	if (is_true(is_prim_proc(args_ref(1)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = apply_prim_proc();
	}else if (is_true(is_compound_proc(args_ref(1)))){
		//if this application isn't in a tail context,
		//then store the current_env
		if (is_false(args_ref(3))){
			stack_push(&env_stack, current_env);
		}
		/*for test
		  test the tail recursion
		 */
//		printf("call ");
//		write(args_ref(1));
//		newline();
//		args_push(env_stack);
//		printf("the length of env_stack: %d\n", get_integer(list_len()));
		//calls procedure_parameters
		args_push(args_ref(1));
		reg = procedure_parameters();
		stack_push(&vars_stack, reg);
		//calls procedure_env
		args_push(args_ref(1));
		reg = procedure_env();
		//calls extend_env
		stack_push(&vars_stack, args_ref(2));
		args_push(reg);
		args_push(stack_pop(&vars_stack));
		args_push(stack_pop(&vars_stack));
		current_env = extend_env();
		//calls procedure_body
		args_push(args_ref(1));
		reg = procedure_body();
		//calls eval_lambda_body
		args_push(reg);
		reg = eval_lambda_body();
		//if this application isn't in tail context,
		//then restore the stored current_env
		if (is_false(args_ref(3))){
			current_env = stack_pop(&env_stack);
		}
	}else {
		printf("Unknown procedure : ");
		write(args_ref(1));
		newline();
		error_handler();
	}
	args_pop(3);
	return reg;
}
