#include "constans.h"
#include "division_numbers.h"

int find_mass_end(int x[], int n)
{
	for (int i = 0; i < n; i++)
		if (x[i] == END_OF_MASS_INT)
			return i;
    return -1;
}

int comare_masses(int a[], int b[], int n, int b_size)
{
	for (int i = 0; i < b_size; i++)
	{
		if (a[n + i] > b[i])
			return FIRST_GREATER;
		if (a[n + i] < b[i])
			return SECOND_GREATER;
	}
	return FIRST_GREATER;
}

void difference(int a[], int b[], int b_size, int *n, int space)
{
    int mine = 0;
	while (comare_masses(a, b, space, b_size) == FIRST_GREATER)
	{
		for (int j = b_size - 1; j >= 0; j--)
        {
			a[space + j] = a[space + j] - b[j] + mine;
            mine = 0;
            if (a[space + j] < 0)
            {
                a[space + j] += 10;
                mine = -1;
            }
        }
		(*n)++;
	}
}

int division(int mantisa[], int decimal[], int cuotient[], int *power)
{
	int space = 0, cuotient_counter = 0;
	int decimal_size = find_mass_end(decimal, MANT_SIZE);
	int mantisa_size = find_mass_end(mantisa, MANT_SIZE * 2);
	if (mantisa_size < decimal_size)
	{
		for (int i = mantisa_size; i < decimal_size; i++)
		{
			mantisa[i] = 0;
		}
		mantisa[decimal_size] = END_OF_MASS_INT;
		*power -= (decimal_size - mantisa_size);
		mantisa_size = decimal_size;
	}
	while (space + decimal_size < MANT_SIZE * 2 && cuotient_counter < MANT_SIZE - 1)
	{
		int diff_col = 0;
		difference(mantisa, decimal, decimal_size, &diff_col, space);
		cuotient[cuotient_counter] = diff_col;
        if (comare_masses(mantisa, decimal, space, decimal_size) == SECOND_GREATER)
        {
            if (mantisa[space + decimal_size] == END_OF_MASS_INT)
            {
                mantisa[space + decimal_size] = 0;
                mantisa[space + decimal_size + 1] = END_OF_MASS_INT;
            }
            mantisa[space + 1] += mantisa[space] * 10;
            mantisa[space] = 0;
        }
		space++;
		cuotient_counter++;
		if (mantisa_size - decimal_size == cuotient_counter - 1)// больше не в целых
		{
			cuotient[cuotient_counter] = PHANTOM_POINT;
			cuotient_counter++;
            for (int i = 0; i < MANT_SIZE * 2; i++)
                if (mantisa[i] == END_OF_MASS_INT)
                    mantisa[i] = 0;
		}
	}
    cuotient[cuotient_counter] = END_OF_MASS_INT;
    return OK;
}