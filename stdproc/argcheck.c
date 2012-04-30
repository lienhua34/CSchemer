#include "common.h"
#include "argcheck.h"

void check_arglst_len_eq(char *func, int req_len, cellpoint arglst)
{
    int len;
	args_push(arglst);
	len = get_integer(list_len());
    if (len != req_len){
        printf("Error: procedure \"%s\" expects %d argument%s, but given %d\n", func, req_len, (req_len > 1)?"":"s", len);
		error_handler();
    }
}
void check_arg_type(char *func, char* loc, cellpoint arg, int type)
{
	switch (type){
	case BOOLEAN_T:
		if (is_false(is_boolean(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a boolean, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case CHARACTER_T:
		if (is_false(is_char(arg))){
			printf("Errror: procedure \"%s\" expects the %s argument is a character, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case INTEGER_T:
		if (is_false(is_integer(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a integer, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case NUMBER_T:
		if (is_false(is_number(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a number, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case SYMBOL_T:
		if (is_false(is_symbol(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a symbol, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case STRING_T:
		if (is_false(is_string(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a string, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case VECTOR_T:
		if (is_false(is_vector(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a vector, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case PAIR_T:
		if (is_false(is_pair(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a pair, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case LIST_T:
		if (is_false(is_list(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a list, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	case PROCEDURE_T:
		if (is_false(is_procedure(arg))){
			printf("Error: procedure \"%s\" expects the %s argument is a procedure, but given: ", func, loc);
			write(arg);
			newline();
			error_handler();
		}
		break;
	default:
		printf("Error: unknown check arg type. -- CHECK_ARG_TYPE.\n");
		error_handler();
	}
}
