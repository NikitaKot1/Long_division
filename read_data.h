#ifndef READ_DATA_H
#define READ_DATA_H

//функции
void shift_str(char*);
int read_field(char*, FILE*);
void make_decimal(char*, int*);
bool true_digit(char*);
void delete_all_zero(char*);
void str_to_int(char*, int*);
int read_file(FILE*, int mantisa[], int decimal[], int*, int*);

#endif
