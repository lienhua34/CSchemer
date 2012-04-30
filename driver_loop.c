#include "common.h"

//////////////////////////////////////////////////////////////
//read_sexp is for read_eval_print loop
//////////////////////////////////////////////////////////////

static char ibuffer[1024];
static char *scan = NULL;
static cellpoint read_sexp(void)
{
    return read_parse(ibuffer, &scan);
}

//////////////////////////////////////////////////////////////
//read_eval_print loop
//////////////////////////////////////////////////////////////
static char *input_prompt = ";;;CSchemer input: ";
static char *output_prompt = ";;;CSchemer output: ";

void driver_loop(void)
{
	initial();
	printf("initialed.\n");
	while (1){
		if (setjmp(jump_buffer) == 0){
			printf("\n%s\n", input_prompt);
			reg = read_sexp();
			//eval the expression with tail_context is a_false
			args_push(a_false);
			args_push(reg);
			reg = eval();
			printf("\n%s\n", output_prompt);
			write(reg);
			newline();
		}else {
			//error handler, initial some variables
			vars_init();
		}
	}
}
