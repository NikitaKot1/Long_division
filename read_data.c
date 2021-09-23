#include "constans.h"
#include "read_data.h"

void slash_n(char *str)
{
    while (*str != '\n' && *str != '\0')
        str++;
    *str = '\0';
}

void shift_str(char *str)
{
    while (*str != '\0')
    {
        *str = *(str + 1);
        str++;
    }
}

int read_field(char *str, FILE *f)
{
    if (fgets(str, sizeof(str) + 10, f) == NULL)
    {
        return END_READ;
    }
    return OK;
}

void make_decimal(char *str, int *mant_pow)
{
    *mant_pow = 0;
    char *start = str, *point = str;
    while (*start != '.' && *start !='\0')
    {
        start++;
        point++;
    }
    if (*start == '.')
        start++;
    while (*start != '\0')
    {
        start++;
        (*mant_pow)++;
    }
    if (*point == '.')
    {
        shift_str(point);
    }
}

bool true_digit(char *str)
{
    if (!(str[0] == '-' || isdigit(str[0])))
    {
        return false;
    }
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void delete_all_zero(char *str)
{
	while (*str == '0' && *str != '\0')
	{
		shift_str(str);
	}
}

void str_to_int(char *str, int *n)
{
    while (*str != '\0')
	{
		*n = *str - '0';
		n++;
		str++;
	}
	*n = END_OF_MASS_INT;
}

int prof_mant(char *str)
{
    if (str[0] == '-')
        if (strlen(str) > 32)
            return TOO_LONG_NUMBER;
    if (strlen(str) > 31)
        return TOO_LONG_NUMBER;
    return OK;
}

int read_file(FILE *f, int mantisa[], int decimal[], int *power, int *neg_flag)
{
    char mantisa_s[MANT_SIZE];
    char power_s[POW_SIZE];
    char decimal_s[MANT_SIZE];
/*    if (read_field(mantisa_s, f) != OK || read_field(power_s, f) != OK || read_field(decimal_s, f) != OK)
    {
        return END_READ;
    }*/
    if (fgets(mantisa_s, sizeof(mantisa_s), f) == NULL)
        return END_READ;
    if (fgets(power_s, sizeof(power_s), f) == NULL)
        return END_READ;
    if (fgets(decimal_s, sizeof(decimal_s), f) == NULL)
        return END_READ;
    
    slash_n(mantisa_s);
    slash_n(power_s);
    slash_n(decimal_s);

    if (mantisa_s[0] == '-' && strlen(mantisa_s) > 32)
        return TOO_LONG_NUMBER;
    if (mantisa_s[0] != '-' && strlen(mantisa_s) > 31)
        return TOO_LONG_NUMBER;
    if (decimal_s[0] == '-' && strlen(decimal_s) > 31)
        return TOO_LONG_NUMBER;
    if (decimal_s[0] != '-' && strlen(decimal_s) > 30)
        return TOO_LONG_NUMBER;
    if (power_s[0] == '-' && strlen(power_s) > 6)
        return ENTRY_POWER_UNLIM;
    if (power_s[0] != '-' && strlen(power_s) > 5)
        return ENTRY_POWER_UNLIM;
    if (mantisa_s[0] == '-')
    {
        (*neg_flag) *= -1;
        shift_str(mantisa_s);
    }
	if (decimal_s[0] == '-')
    {
        (*neg_flag) *= -1;
        shift_str(decimal_s);
    }
    int mant_pow = 0;
    make_decimal(mantisa_s, &mant_pow);
    if (!true_digit(mantisa_s) || !true_digit(power_s) || !true_digit(decimal_s))
    {
        return NOT_DIGIT;
    }
	char *endptr;
	*power = strtol(power_s, &endptr, 10) - mant_pow;
	if (*power > 99999 || *power < -99999)
		return UNLIMITED_POWER;
	delete_all_zero(mantisa_s);
	delete_all_zero(decimal_s);
    if (decimal_s[0] == '\0')
    {
        return DIVISION_BY_ZERO;
    }
	str_to_int(mantisa_s, mantisa);
	str_to_int(decimal_s, decimal);
	return OK;
}