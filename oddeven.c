#include <stdio.h>

/**
 * main - check the code
 *
 * Return: always 0 (success)
 */
int main(void)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d is even\n", i);
        }
        else
        {
            printf("%d is odd\n", i);
        }
    }

    return (0);
}
