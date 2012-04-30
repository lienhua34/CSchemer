#include "common.h"
#include <string.h>

/*************************************************************
 *This file implements a scheme objects parser
 *************************************************************/

static boolean is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}
static boolean is_delimiter(char ch)
{
    return is_whitespace(ch) || ch == '(' || ch == ')' || ch == '"' || ch == ';';
}
static boolean is_comment(char ch)
{
    return ch == ';';
}
static boolean is_atmosphere(char ch)
{
    return is_whitespace(ch) || is_comment(ch);
}
static boolean is_letter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
static boolean is_special_initial(char ch)
{
    return ch == '!' || ch == '$' || ch == '%' || ch == '&' || ch == '*' || ch == '/' ||
           ch == ':' || ch == '<' || ch == '=' || ch == '>' || ch == '?' || ch == '^' ||
           ch == '_' || ch == '~';
}
static boolean is_initial(char ch)
{
    return is_letter(ch) || is_special_initial(ch);
}
static boolean is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}
static boolean is_special_subsequent(char ch)
{
    return ch == '+' || ch == '-' || ch == '.' || ch == '@';
}
static boolean is_subsequent(char ch)
{
    return is_initial(ch) || is_digit(ch) || is_special_subsequent(ch);
}

///state constants
static cellpoint STATE_INIT;
static cellpoint STATE_SHARP;
static cellpoint STATE_DOT;
static cellpoint STATE_ADD;
static cellpoint STATE_SUB;
static cellpoint STATE_NUM;
static cellpoint STATE_CHAR;
static cellpoint STATE_STR;
static cellpoint STATE_SYM;
static cellpoint STATE_LIST;
static cellpoint STATE_VEC;
static cellpoint STATE_QUOTE;

///需要在scheme实现中记录这两个栈变量，以便在垃圾回收时将这些栈都给回收了！！！！！！！
t_stack parser_stack;
t_stack state_stack;
cellpoint current_state;
cellpoint state_constants;

void set_state_constants(void)
{
	cellpoint sc = state_constants;
	STATE_INIT = car(sc);
	sc = cdr(sc);
	STATE_SHARP = car(sc);
	sc = cdr(sc);
	STATE_DOT = car(sc);
	sc = cdr(sc);
	STATE_ADD = car(sc);
	sc = cdr(sc);
	STATE_SUB = car(sc);
	sc = cdr(sc);
	STATE_NUM = car(sc);
	sc = cdr(sc);
	STATE_CHAR = car(sc);
	sc = cdr(sc);
	STATE_STR = car(sc);
	sc = cdr(sc);
	STATE_SYM = car(sc);
	sc = cdr(sc);
	STATE_LIST = car(sc);
	sc = cdr(sc);
	STATE_VEC = car(sc);
	sc = cdr(sc);
	STATE_QUOTE = car(sc);
}
void parser_init(void)
{
	//init state constants
	state_constants = cons(make_integer(0), NIL);
	state_constants = cons(make_integer(1), state_constants);
	state_constants = cons(make_integer(2), state_constants);
	state_constants = cons(make_integer(3), state_constants);
	state_constants = cons(make_integer(4), state_constants);
	state_constants = cons(make_integer(5), state_constants);
	state_constants = cons(make_integer(6), state_constants);
	state_constants = cons(make_integer(7), state_constants);
	state_constants = cons(make_integer(8), state_constants);
	state_constants = cons(make_integer(9), state_constants);
	state_constants = cons(make_integer(10), state_constants);
	state_constants = cons(make_integer(11), state_constants);
	//set state constants
	set_state_constants();
	//init current_state
	current_state = STATE_INIT;
}

static char *reload_ibuffer(char *buf)
{
    gets(buf);
    return buf;
}
static void eat_atmosphere(char **sc)
{
    if (is_whitespace(**sc)){
        //eat whitespaces
        while(is_whitespace(**sc)){
            ++*sc;
        }
    }else{
        //eat comment
        while(**sc != '\n' && **sc != '\0'){
            ++*sc;
        }
    }
}
static void do_input_error(char **pscan)
{
	**pscan = '\0';
	error_handler();
}
static void parse_list(char*, char **);
static void parse_vector(char *, char **);
static void do_state_init(char *ibuf, char **pscan)
{
    if (**pscan == '#'){
        stack_push(&state_stack, current_state);
        current_state = STATE_SHARP;
        ++*pscan;
    } else if (**pscan == '\''){
		stack_push(&state_stack, current_state);
		current_state = STATE_QUOTE;
		++*pscan;
		do_state_init(ibuf, pscan);
	}else if (**pscan == '.'){
        stack_push(&state_stack, current_state);
        current_state = STATE_DOT;
        ++*pscan;
    } else if (**pscan == '+'){
        stack_push(&state_stack, current_state);
        current_state = STATE_ADD;
        ++*pscan;
    } else if (**pscan == '-'){
        stack_push(&state_stack, current_state);
        current_state = STATE_SUB;
        ++*pscan;
    } else if (is_digit(**pscan)){
        stack_push(&state_stack, current_state);
        current_state = STATE_NUM;
    } else if (is_initial(**pscan)){
        stack_push(&state_stack, current_state);
        current_state = STATE_SYM;
    } else if (**pscan == '"'){
        stack_push(&state_stack, current_state);
        current_state = STATE_STR;
        ++*pscan;
    } else if (**pscan == '('){
        parse_list(ibuf, pscan);
    } else if (**pscan == ')'){
        if (current_state == STATE_LIST){
            parse_list(ibuf, pscan);
        }else if (current_state == STATE_VEC){
            parse_vector(ibuf, pscan);
        }else {
            printf("Error: unexpected ')' -- READ\n");
			do_input_error(pscan);
        }
    } else if(is_atmosphere(**pscan)){
        eat_atmosphere(pscan);
    } else{
        perror("Error: Bad input. -- READ\n");
		do_input_error(pscan);
    }
}
static void do_state_sharp(char *ibuf, char **pscan)
{
    if (**pscan == 'd'){
        //only deal with decimal
        current_state = STATE_NUM;
        ++*pscan;
    } else if (**pscan == '\\'){
        current_state = STATE_CHAR;
        ++*pscan;
    } else if (**pscan == '('){
        parse_vector(ibuf, pscan);
    } else if (**pscan == 't' || **pscan == 'f'){
        boolean b = (**pscan == 't') ? true : false;
        ++*pscan;
        if (is_delimiter(**pscan) || **pscan == '\0'){
            stack_push(&parser_stack, make_boolean(b));
            current_state = stack_pop(&state_stack);
        }else {
            printf("Error: illegally uses '#' -- READ\n");
			do_input_error(pscan);
        }
    } else{
        printf("Error: illegally uses '#' -- READ\n");
        do_input_error(pscan);
    }
}
static void do_state_dot(char **pscan)
{
    if (is_digit(**pscan)){
        //deal with real, this for extend
        ;
    } else if (**pscan == '.'){
        ++*pscan;
        if (**pscan != '.'){
            printf("Error: illegally uses '.' -- READ\n");
            do_input_error(pscan);
        } else{
            ++*pscan;
            if (is_delimiter(**pscan) || **pscan == '\0'){
                reg = make_symbol("...");
                current_state = stack_pop(&state_stack);
				if (current_state == STATE_QUOTE){
					reg = cons(reg, NIL);
					reg = cons(make_symbol("quote"), reg);
					current_state = stack_pop(&state_stack);
				}
				stack_push(&parser_stack, reg);
            } else{
                printf("Error: illegally uses '.' -- READ\n");
                do_input_error(pscan);
            }
        }
    } else if (is_delimiter(**pscan) && stack_top(&state_stack) == STATE_LIST){
        stack_push(&parser_stack, make_symbol("."));
        current_state = stack_pop(&state_stack);
    } else{
        printf("Error: illegally uses '.' -- READ\n");
        do_input_error(pscan);
    }
}
static void do_state_add(char **pscan)
{
    if (is_delimiter(**pscan) || **pscan == '\0'){
		reg = make_symbol("+");
        current_state = stack_pop(&state_stack);
		if (current_state == STATE_QUOTE){
			reg = cons(reg, NIL);
			reg = cons(make_symbol("quote"), reg);
			current_state = stack_pop(&state_stack);
		}
		stack_push(&parser_stack, reg);
    }else {
        printf("Error: illegally uses '+' -- READ\n");
        do_input_error(pscan);
    }
}
static void do_state_sub(char **pscan)
{
    if (is_delimiter(**pscan) || **pscan == '\0'){
		reg =  make_symbol("-");
        current_state = stack_pop(&state_stack);
		if (current_state == STATE_QUOTE){
			reg = cons(reg, NIL);
			reg = cons(make_symbol("quote"), reg);
			current_state = stack_pop(&state_stack);
		}
		stack_push(&parser_stack, reg);
    }else {
        printf("Error: illegally uses '-' -- READ\n");
        do_input_error(pscan);
    }
}
static void parse_num(char **pscan)
{
    char rbuf[50];
    char *rbufp = rbuf;

    *rbufp++ = **pscan;
    ++*pscan;
    while (!is_delimiter(**pscan) && **pscan != '\0'){
        *rbufp++ = **pscan;
        if (!is_digit(**pscan)){
			printf("Error: Bad number constant %s -- READ\n", rbuf);
            do_input_error(pscan);
        }
        ++*pscan;
    }
    *rbufp = '\0';
	reg =  make_integer(atoi(rbuf));
	current_state = stack_pop(&state_stack);
	if (current_state == STATE_QUOTE){
		reg = cons(reg, NIL);
		reg = cons(make_symbol("quote"), reg);
		current_state = stack_pop(&state_stack);
	}
	stack_push(&parser_stack, reg);
}
static void parse_char(char **pscan)
{
    char rbuf[50];
    char *rbufp = NULL;

    if (**pscan == '\0'){
		reg =  make_char('\n');
        current_state = stack_pop(&state_stack);
		if (current_state == STATE_QUOTE){
			reg = cons(reg, NIL);
			reg = cons(make_symbol("quote"), reg);
			current_state = stack_pop(&state_stack);
		}
		stack_push(&parser_stack, reg);
        return;
    }

    rbufp = rbuf;
    *rbufp++ = **pscan;
    ++*pscan;
    if (is_delimiter(**pscan) || **pscan == '\0'){
		reg = make_char(*rbuf);
        current_state = stack_pop(&state_stack);
		if (current_state == STATE_QUOTE){
			reg = cons(reg, NIL);
			reg = cons(make_symbol("quote"), reg);
			current_state = stack_pop(&state_stack);
		}
		stack_push(&parser_stack, reg);
    }else {
        while (!is_delimiter(**pscan) && **pscan != '\0'){
            *rbufp++ = **pscan;
            ++*pscan;
        }
        *rbufp = '\0';
        if (strcmp(rbuf, "space") == 0){
			reg = make_char(' ');
            current_state = stack_pop(&state_stack);
			if (current_state == STATE_QUOTE){
				reg = cons(reg, NIL);
				reg = cons(make_symbol("quote"), reg);
				current_state = stack_pop(&state_stack);
			}
			stack_push(&parser_stack, reg);
        }else if (strcmp(rbuf, "newline") == 0){
			reg = make_char('\n');
            current_state = stack_pop(&state_stack);
			if (current_state == STATE_QUOTE){
				reg = cons(reg, NIL);
				reg = cons(make_symbol("quote"), reg);
				current_state = stack_pop(&state_stack);
			}
			stack_push(&parser_stack, reg);
        }else {
            printf("Error: Bad character constant #\\%s -- READ", rbuf);
            do_input_error(pscan);
        }
    }
}
static void parse_string(char *ibuf, char **pscan)
{
    char rbuf[100];
    char *rbufp = rbuf;

    while (**pscan != '"'){
        if (**pscan == '\\'){
            ++*pscan;
            if (**pscan == '\\' || **pscan == '"'){
                *rbufp++ = **pscan;
                ++*pscan;
            }else {
                printf("Error: unknown escape sequence \\%c in string. -- READ\n",**pscan);
                do_input_error(pscan);
                return;
            }
        }else if (**pscan == '\0'){
            *rbufp++ = '\n';
            *pscan = reload_ibuffer(ibuf);
        }else {
            *rbufp++ = **pscan;
            ++*pscan;
        }
    }
    *rbufp = '\0';
	reg = chars_2_string(rbuf);
    current_state = stack_pop(&state_stack);
	if (current_state == STATE_QUOTE){
		reg = cons(reg, NIL);
		reg = cons(make_symbol("quote"), reg);
		current_state = stack_pop(&state_stack);
	}
	stack_push(&parser_stack, reg);
    ++*pscan;
}
static void parse_sym(char **pscan)
{
    char rbuf[50];
    char *rbufp = rbuf;

    *rbufp++ = **pscan;
    ++*pscan;
    while (!is_delimiter(**pscan) && **pscan != '\0'){
        *rbufp++ = **pscan;
        if (!is_subsequent(**pscan)){
			printf("Error: %s is a illegal symbol. -- READ\n", rbuf);
            do_input_error(pscan);
        }
        ++*pscan;
    }
    *rbufp = '\0';
	reg = make_symbol(rbuf);
	current_state = stack_pop(&state_stack);
	if (current_state == STATE_QUOTE){
		reg = cons(reg, NIL);
		reg = cons(make_symbol("quote"), reg);
		current_state = stack_pop(&state_stack);
	}
	stack_push(&parser_stack, reg);
}
static void parse_list(char *ibuf, char **pscan)
{
    if (**pscan == '\0'){
        *pscan = reload_ibuffer(ibuf);
    }else if (**pscan == '('){
        stack_push(&state_stack, current_state);
        current_state = STATE_LIST;
        stack_push(&parser_stack, make_symbol("("));
        ++*pscan;
    }else if (**pscan == ')'){
		args_push(make_symbol("("));
		args_push(stack_top(&parser_stack));
		reg = eq();
        if (is_true(reg)){
			reg = NIL;
            current_state = stack_pop(&state_stack);
			if (current_state == STATE_QUOTE){
				reg = cons(reg, NIL);
				reg = cons(make_symbol("quote"), reg);
				current_state = stack_pop(&state_stack);
			}
			stack_pop(&parser_stack);
			stack_push(&parser_stack, reg);
            ++*pscan;
        }else {
			//checks whether the top of parser_stack is a dot
			args_push(make_symbol("."));
			args_push(stack_top(&parser_stack));
			reg = eq();
			if (is_true(reg)){
				perror("Error: illegally uses '.' -- READ\n");
				do_input_error(pscan);
			}else {
				stack_push(&vars_stack, stack_pop(&parser_stack));
				args_push(make_symbol("."));
				args_push(stack_top(&parser_stack));
				reg = eq();
				if (is_true(reg)){
					reg = stack_pop(&vars_stack);
					stack_pop(&parser_stack);
				}else {
					reg = cons(stack_pop(&vars_stack), NIL);
				}
				stack_push(&vars_stack, reg);
				//create a list object
				args_push(make_symbol("("));
				args_push(stack_top(&parser_stack));
				while (is_false(eq())){
					args_push(make_symbol("."));
					args_push(stack_top(&parser_stack));
					reg = eq();
					if (is_true(reg)){
						perror("Error: illegally uses '.' -- READ\n");
						do_input_error(pscan);
						return;
					}
					reg = stack_pop(&vars_stack);
					reg = cons(stack_pop(&parser_stack), reg);
					stack_push(&vars_stack, reg);
					//checks the next element
					args_push(make_symbol("("));
					args_push(stack_top(&parser_stack));
				}
				stack_pop(&parser_stack);
				current_state = stack_pop(&state_stack);
				reg = stack_pop(&vars_stack);
				if (current_state == STATE_QUOTE){
					reg = cons(reg, NIL);
					reg = cons(make_symbol("quote"), reg);
					current_state = stack_pop(&state_stack);
				}
				stack_push(&parser_stack, reg);
				++*pscan;
			}
		}
    }else {
        do_state_init(ibuf, pscan);
    }
}
static void parse_vector(char *ibuf, char **pscan)
{
    if (**pscan == '\0'){
        *pscan = reload_ibuffer(ibuf);
    }else if (**pscan == '('){
        if (current_state == STATE_SHARP){
            current_state = STATE_VEC;
            stack_push(&parser_stack, make_symbol("#("));
            ++*pscan;
        }else {
            parse_list(ibuf, pscan);
        }
        do_state_init(ibuf, pscan);
    }else if (**pscan == ')'){
		stack_push(&vars_stack, NIL);
		//create a vector object
		args_push(make_symbol("#("));
		args_push(stack_top(&parser_stack));
        while (is_false(eq())){
			reg = stack_pop(&vars_stack);
			reg = cons(stack_pop(&parser_stack), reg);
			stack_push(&vars_stack, reg);
			//check the next element
			args_push(make_symbol("#("));
			args_push(stack_top(&parser_stack));
        }
		stack_pop(&parser_stack);
		reg = stack_pop(&vars_stack);
		args_push(reg);
		reg = vector();
        current_state = stack_pop(&state_stack);
		if (current_state == STATE_QUOTE){
			reg = cons(reg, NIL);
			reg = cons(make_symbol("quote"), reg);
			current_state = stack_pop(&state_stack);
		}
		stack_push(&parser_stack, reg);
        ++*pscan;
    }else {
        do_state_init(ibuf, pscan);
    }
}
//parser
cellpoint read_parse(char *ibuf, char **pscan)
{
	current_state = STATE_INIT;
    stack_init(&parser_stack);
    stack_init(&state_stack);

    while (*pscan == NULL || **pscan == '\0'){
        *pscan = reload_ibuffer(ibuf);
    }

    while (1){
        if (current_state == STATE_INIT && !stack_is_empty(&parser_stack)){
            //parses a object
            return stack_pop(&parser_stack);
        }

		if (current_state == STATE_INIT){
            do_state_init(ibuf, pscan);
		}else if (current_state == STATE_SHARP){
            do_state_sharp(ibuf, pscan);
		}else if (current_state == STATE_DOT){
            do_state_dot(pscan);
		}else if (current_state == STATE_ADD){
            do_state_add(pscan);
		}else if (current_state == STATE_SUB){
            do_state_sub(pscan);
		}else if (current_state == STATE_NUM){
			//parses number object
            parse_num(pscan);
		}else if (current_state == STATE_CHAR){
            //parses character object
            parse_char(pscan);
		}else if (current_state == STATE_STR){
            //parses string object
            parse_string(ibuf, pscan);
		}else if (current_state == STATE_SYM){
			//parses symbol object
            parse_sym(pscan);
		}else if (current_state == STATE_LIST){
			//parses list object
            parse_list(ibuf, pscan);
		}else if (current_state == STATE_VEC){
			//parses vector object
            parse_vector(ibuf, pscan);
		}else {
            perror("Error: Bad state. -- READ\n");
			error_handler();
            return NIL;
        }
    }
}
