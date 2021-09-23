#include "constans.h"
#include "read_data.h"
#include "division_numbers.h"
#include "print_number.h"
#include "center.h"

int first_prepare(void)
{
    FILE *f = fopen(INPUT_FILE, "r");
    int mantisa[MANT_SIZE * 2] = { 0 };
    int power = 0;
    int decimal[MANT_SIZE] = { 0 };
    int cuorent[MANT_SIZE] = { 0 };
    int neg_flag = 1;
	int rc = read_file(f, mantisa, decimal, &power, &neg_flag);
    fclose(f);
	if (rc != OK)
		return rc;

    rc = division(mantisa, decimal, cuorent, &power);
    if (rc != OK)
        return rc;

    rc = normalize(cuorent, &power);
    if (rc != OK)
        return rc;

    print_file(cuorent, power, neg_flag);
    return OK;
}

void central(void)
{
    int rc = first_prepare();
    if (rc != OK)
    {
        FILE *g = fopen(OUTPUT_FILE, "w");
        switch (rc)
        {
        case END_READ:
            fprintf(g, "Input all fields");
            fclose(g);
            break;
        case NOT_DIGIT:
            fprintf(g, "Incorrect number entry");
            fclose(g);
            break;
        case TOO_LONG_NUMBER:
            fprintf(g, "Too long number");
            fclose(g);
            break;
        case UNLIMITED_POWER:
            fprintf(g, "Power is too big");
            fclose(g);
            break;
        case DIVISION_BY_ZERO:
            fprintf(g, "Division by zero");
            fclose(g);
            break;
        case ENTRY_POWER_UNLIM:
            fprintf(g, "Entry power is too big");
            fclose(g);
            break;
        default:
            fclose(g);
        }
    }
}