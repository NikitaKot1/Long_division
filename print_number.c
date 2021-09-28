#include "constans.h"
#include "print_number.h"
#include "division_numbers.h"

void shift_num(int *arr)
{
    while (*arr != END_OF_MASS_INT)
    {
        *arr = *(arr + 1);
        arr++;
    }
}

int delete_zero_num(int *arr)
{
    int n = 0;
    while (*arr == 0)
    {
        int *new_arr = arr;
        shift_num(new_arr);
        n++;
    }
    return n;
}

int find_point(int *arr, int k)
{
    int n = 0;
    while (*arr != k && *arr != END_OF_MASS_INT)
    {
        arr++;
        n++;
    }
    return n;
}

void swap_int(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}

void insert_point(int *arr, int n)
{
    int size = find_mass_end(arr, MANT_SIZE);
    arr[size + 1] = END_OF_MASS_INT;
    for (int i = size; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = n;
}

int normalize(int cuorent[], int *power)
{
    if (cuorent[0] == 0)
    {
        delete_zero_num(cuorent);
    }
    if (cuorent[0] == PHANTOM_POINT)
    {
        int *zer = cuorent + 1;
        int n = delete_zero_num(zer);
        *power -= n;
    }
    if (*power > 99999 || *power < -99999)
        return UNLIMITED_POWER;
    int cuo_end = find_mass_end(cuorent, MANT_SIZE);
    if (cuo_end > 32)
    {
        cuo_end = 32;
        while (cuorent[cuo_end + 1] != END_OF_MASS_INT)
        {
            int *sh = &(cuorent[cuo_end + 1]);
            shift_num(sh);
        }
        cuo_end = 31;
    }
    
    if (cuorent[cuo_end] > 4)
    {
        (*power)++;
        bool flag = true;
        cuorent[cuo_end - 1] = END_OF_MASS_INT;
        int i = cuo_end - 2;
        while (flag && i >= 0)
        {
            flag = false;
            cuorent[i] += 1;
            if (cuorent[i] > 9)
                {
                    flag = true;
                    cuorent[i] -= 10;
                    i--;
                    (*power)++;
                }
        }
    }
    int pos_point = find_point(cuorent, PHANTOM_POINT);
    if (cuorent[pos_point] == PHANTOM_POINT)
    {
        while (pos_point > 0)
        {
            swap_int (&cuorent[pos_point], &cuorent[pos_point - 1]);
            pos_point--;
            (*power)++;
        }
    }
    else 
    {
        insert_point(cuorent, PHANTOM_POINT);
    }
    if (*power > 99999 || *power < -99999)
        return UNLIMITED_POWER;
    insert_point(cuorent, 0);
    int end = find_point(cuorent, END_OF_MASS_INT) - 1;
    while (cuorent[end] == 0)
    {
        int *k = &cuorent[end];
        shift_num(k);
        end--;
    }
    return OK;

}

void print_file(int *cuorent, int power, int neg_flag)
{
    FILE *f = fopen(OUTPUT_FILE, "w");
    if (neg_flag == -1)
        fprintf(f, "-");
    while (*cuorent != END_OF_MASS_INT)
    {
        if (*cuorent != PHANTOM_POINT)
            fprintf(f, "%d", *cuorent);
        else
            fprintf(f, ".");
        cuorent++;
    }
    fprintf(f, "E");
    fprintf(f, "%d", power);
    fclose(f);
}