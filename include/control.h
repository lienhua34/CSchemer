#ifndef ARGS_H_INCLUDED
#define ARGS_H_INCLUDED

extern cellpoint reg;
extern cellpoint allocons;
extern t_stack vars_stack;
extern t_stack args_stack;
extern t_stack env_stack;
extern cellpoint the_global_env;
extern void initial(void);
extern void vars_init(void);
extern cellpoint args_ref(int);
extern void args_push(cellpoint);
extern void args_pop(int);

//error handler
extern jmp_buf jump_buffer;
extern void error_handler(void);

#endif //ARGS_H_INCLUDED
