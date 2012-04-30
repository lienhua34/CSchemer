#include "common.h"

//reg: uses to store temporary object
cellpoint reg;
//allocons: uses to store the arguments of cons or make_string or make_vector when
//          calls garbage collection
cellpoint allocons;
//vars_stack: uses to store temporary object
t_stack vars_stack;
//args_stack: uses to control argument transmission
t_stack args_stack;
//env_stack: uses to control function call
t_stack env_stack;
//the_global_env:the global environment
cellpoint the_global_env;
//current_env: current environment
cellpoint current_env;

void vars_init(void)
{
	allocons = cons(NIL, NIL);
	reg = NIL;
	stack_init(&env_stack);
	stack_init(&vars_stack);
	stack_init(&args_stack);
	stack_init(&parser_stack);
	stack_init(&state_stack);
	current_env = the_global_env;
}
//initial
void initial(void)
{
	//initial the memory
	memory_init();
	//create two boolean objects #t & #f
	bool_init();
	//initial the parser's environment
	parser_init();
	//initial obarray for symbol
	init_obarray();
	//create the global environment
	the_global_env = setup_environment();
	//initial the variables
	vars_init();
	//initial the garbage collection systom
	gc_init();
}

/////////////////////////////////////////////////////
//arguments transmission
////////////////////////////////////////////////////
cellpoint args_ref(int n)
{
	cellpoint args = args_stack;
	while (n > 1){
		args = cdr(args);
		--n;
	}
 	return car(args);
}
void args_push(cellpoint arg)
{
	stack_push(&args_stack, arg);
}
void args_pop(int n)
{
	while (n > 0){
		stack_pop(&args_stack);
		--n;
	}
}

///////////////////////////////////////////////////////
//error handler
///////////////////////////////////////////////////////
jmp_buf jump_buffer;

void error_handler(void)
{
	longjmp(jump_buffer, 1);
}
