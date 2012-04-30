#include "common.h"

/*************************************************************
 *This file provides two main output procedures:
 *   display & write
 *************************************************************/

//output procedure: display
static void display_boolean(cellpoint cp)
{
    if (is_true(cp)){
        printf("#t");
    }else{
        printf("#f");
    }
}
static void display_character(cellpoint cp)
{
    printf("%c", get_char(cp));
}
static void display_number(cellpoint cp)
{
    printf("%d", get_integer(cp));
}
static void display_symbol(cellpoint cp)
{
    printf("%s", get_symbol(cp));
}
static void display_pair(cellpoint cp)
{
	printf("(");
	display(car(cp));
	cp = cdr(cp);
	while (is_true(is_pair(cp))){
		printf(" ");
		display(car(cp));
		cp = cdr(cp);
	}
	if (is_false(is_null(cp))){
		printf(" . ");
		display(cp);
	}
	printf(")");
}
static void display_string(cellpoint cp)
{
    int i, len = string_len(cp);
    for (i=0; i < len; i++){
        printf("%c", get_char(string_ref(cp,i)));
    }
}
static void display_vector(cellpoint cp)
{
    int i;
    int vlen = vector_len(cp);
    printf("#(");
    for (i=0; i < vlen; i++){
        display(vector_ref(cp, i));
        printf(" ");
    }
    printf(")");
}
static void display_procedure(cellpoint proc)
{
	printf("#<procedure:");
	args_push(proc);
	reg = procedure_name();
	if (is_false(is_null(reg))){
		display(reg);
	}
	printf(">");
}
void display(cellpoint cp)
{
    if (is_true(is_null(cp))){
        printf("()");
    } else if (is_true(is_boolean(cp))){
        display_boolean(cp);
    } else if (is_true(is_number(cp))){
        display_number(cp);
    } else if (is_true(is_char(cp))){
        display_character(cp);
    } else if (is_true(is_symbol(cp))){
        display_symbol(cp);
    } else if (is_true(is_string(cp))){
        display_string(cp);
    } else if (is_true(is_vector(cp))){
        display_vector(cp);
    } else if (is_true(is_procedure(cp))){
		display_procedure(cp);
	}else if (is_true(is_pair(cp))){
        display_pair(cp);
    } else {
        printf("display error.\n");
		error_handler();
    }
}

///output procedure: write
static void write_boolean(cellpoint cp)
{
    if (is_true(cp)){
        printf("#t");
    }else{
        printf("#f");
    }
}
static void write_character(cellpoint cp)
{
    char ch = get_char(cp);
    if (ch == ' '){
        printf("#\\space");
    }else if (ch == '\n'){
        printf("#\\newline");
    }else {
        printf("#\\%c", ch);
    }
}
static void write_number(cellpoint cp)
{
    printf("%d", get_integer(cp));
}
static void write_symbol(cellpoint cp)
{
    printf("%s", get_symbol(cp));
}
static void write_pair(cellpoint cp)
{
    printf("(");
    write(car(cp));
	cp = cdr(cp);
	while (is_true(is_pair(cp))){
		printf(" ");
		write(car(cp));
		cp = cdr(cp);
	}
	if (is_false(is_null(cp))){
		printf(" . ");
		write(cp);
	}
	printf(")");
}
static void write_string(cellpoint cp)
{
    int i, len = string_len(cp);
    printf("\"");
    for (i=0; i < len; i++){
        char ch = get_char(string_ref(cp,i));
        if (ch == '\\' || ch == '"'){
            printf("\\%c", ch);
        } else if (ch == '\n'){
            printf("\\n");
        }else {
            printf("%c", ch);
        }
    }
    printf("\"");
}
static void write_vector(cellpoint cp)
{
    int i;
    int vlen = vector_len(cp);
    printf("#(");
    for (i=0; i < vlen; i++){
        write(vector_ref(cp, i));
        printf(" ");
    }
    printf(")");
}
static void write_procedure(cellpoint proc)
{
	printf("#<procedure:");
	args_push(proc);
	reg = procedure_name();
	if (is_false(is_null(reg))){
		write(reg);
	}
	printf(">");
}
void write(cellpoint cp)
{
    if (is_true(is_null(cp))){
        printf("()");
    } else if (is_true(is_boolean(cp))){
        write_boolean(cp);
    } else if (is_true(is_number(cp))){
        write_number(cp);
    } else if (is_true(is_char(cp))){
        write_character(cp);
    } else if (is_true(is_symbol(cp))){
        write_symbol(cp);
    } else if (is_true(is_string(cp))){
        write_string(cp);
    } else if (is_true(is_vector(cp))){
        write_vector(cp);
    } else if (is_true(is_procedure(cp))){
		write_procedure(cp);
	}else if (is_true(is_pair(cp))){
        write_pair(cp);
    } else {
        printf("write error.\n");
		error_handler();
    }
}

///output procedure: newline
void newline(void)
{
    printf("\n");
}
