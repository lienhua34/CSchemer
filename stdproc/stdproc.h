#ifndef STDPROC_H_INCLUDED
#define STDPROC_H_INCLUDED

//pair standard procedure
extern cellpoint pair_pred_proc(cellpoint);
extern cellpoint cons_proc(cellpoint);
extern cellpoint car_proc(cellpoint);
extern cellpoint cdr_proc(cellpoint);
extern cellpoint car_set_proc(cellpoint);
extern cellpoint cdr_set_proc(cellpoint);

//equivalence predicate procedure
extern cellpoint eq_proc(cellpoint);
extern cellpoint eqv_proc(cellpoint);
extern cellpoint equal_proc(cellpoint);

//list standard procedure
extern cellpoint null_proc(cellpoint);
extern cellpoint list_pred_proc(cellpoint);
extern cellpoint list_proc(cellpoint);
extern cellpoint length_proc(cellpoint);
extern cellpoint append_proc(cellpoint);
extern cellpoint reverse_proc(cellpoint);
extern cellpoint list_tail_proc(cellpoint);
extern cellpoint list_ref_proc(cellpoint);
extern cellpoint memq_proc(cellpoint);
extern cellpoint memv_proc(cellpoint);
extern cellpoint member_proc(cellpoint);
extern cellpoint assq_proc(cellpoint);
extern cellpoint assv_proc(cellpoint);
extern cellpoint assoc_proc(cellpoint);

//boolean standard procedure
extern cellpoint boolean_pred_proc(cellpoint);
extern cellpoint boolean_not_proc(cellpoint);

//character standard procedure
extern cellpoint char_pred_proc(cellpoint);
extern cellpoint char_eq_proc(cellpoint);
extern cellpoint char_less_proc(cellpoint);
extern cellpoint char_greater_proc(cellpoint);
extern cellpoint char_less_eq_proc(cellpoint);
extern cellpoint char_greater_eq_proc(cellpoint);
extern cellpoint char_eq_ci_proc(cellpoint);
extern cellpoint char_less_ci_proc(cellpoint);
extern cellpoint char_greater_ci_proc(cellpoint);
extern cellpoint char_less_eq_ci_proc(cellpoint);
extern cellpoint char_greater_eq_ci_proc(cellpoint);
extern cellpoint char_upper_case_proc(cellpoint);
extern cellpoint char_lower_case_proc(cellpoint);
extern cellpoint char_alphabetic_proc(cellpoint);
extern cellpoint char_numeric_proc(cellpoint);
extern cellpoint char_whitespace_proc(cellpoint);
extern cellpoint char_2_integer_proc(cellpoint);
extern cellpoint integer_2_char_proc(cellpoint);
extern cellpoint char_upcase_proc(cellpoint);
extern cellpoint char_downcase_proc(cellpoint);

//symbol standard procedure
extern cellpoint symbol_pred_proc(cellpoint);
extern cellpoint symbol_2_string_proc(cellpoint);
extern cellpoint string_2_symbol_proc(cellpoint);

//string standard procedure
extern cellpoint string_pred_proc(cellpoint);
extern cellpoint make_string_proc(cellpoint);
extern cellpoint string_proc(cellpoint);
extern cellpoint string_length_proc(cellpoint);
extern cellpoint string_ref_proc(cellpoint);
extern cellpoint string_set_proc(cellpoint);
extern cellpoint string_eq_proc(cellpoint);
extern cellpoint string_eq_ci_proc(cellpoint);
extern cellpoint string_less_proc(cellpoint);
extern cellpoint string_greater_proc(cellpoint);
extern cellpoint string_less_eq_proc(cellpoint);
extern cellpoint string_greater_eq_proc(cellpoint);
extern cellpoint string_less_ci_proc(cellpoint);
extern cellpoint string_greater_ci_proc(cellpoint);
extern cellpoint string_less_eq_ci_proc(cellpoint);
extern cellpoint string_greater_eq_ci_proc(cellpoint);
extern cellpoint substring_proc(cellpoint);
extern cellpoint string_append_proc(cellpoint);
extern cellpoint string_2_list_proc(cellpoint);
extern cellpoint list_2_string_proc(cellpoint);
extern cellpoint string_copy_proc(cellpoint);
extern cellpoint string_fill_proc(cellpoint);

//number standard procedure
extern cellpoint integer_pred_proc(cellpoint);
extern cellpoint rational_pred_proc(cellpoint);
extern cellpoint real_pred_proc(cellpoint);
extern cellpoint complex_pred_proc(cellpoint);
extern cellpoint number_pred_proc(cellpoint);
extern cellpoint number_eq_proc(cellpoint);
extern cellpoint number_less_proc(cellpoint);
extern cellpoint number_greater_proc(cellpoint);
extern cellpoint number_less_eq_proc(cellpoint);
extern cellpoint number_greater_eq_proc(cellpoint);
extern cellpoint add_proc(cellpoint);
extern cellpoint sub_proc(cellpoint);
extern cellpoint mul_proc(cellpoint);
extern cellpoint div_proc(cellpoint);
extern cellpoint remainder_proc(cellpoint);

//vector standard procedure
extern cellpoint vector_pred_proc(cellpoint);
extern cellpoint make_vector_proc(cellpoint);
extern cellpoint vector_proc(cellpoint);
extern cellpoint vector_length_proc(cellpoint);
extern cellpoint vector_ref_proc(cellpoint);
extern cellpoint vector_set_proc(cellpoint);
extern cellpoint vector_2_list_proc(cellpoint);
extern cellpoint list_2_vector_proc(cellpoint);
extern cellpoint vector_fill_proc(cellpoint);

//output procedures
extern cellpoint write_proc(cellpoint);
extern cellpoint display_proc(cellpoint);
extern cellpoint newline_proc(cellpoint);
extern cellpoint write_char_proc(cellpoint);

//control procedures
extern cellpoint proc_pred_proc(cellpoint);
extern cellpoint apply_proc(cellpoint);

#endif //STDPROC_H_INCLUDED
