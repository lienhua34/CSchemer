#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

//global variable
extern cellpoint current_env;

//global functions
extern cellpoint lookup_var_val(void);
extern cellpoint extend_env(void);
extern void define_var(void);
extern void set_var_val(void);

extern cellpoint setup_environment(void);

#endif //ENVIRONMENT_H_INCLUDED
