#include <stdio.h>
#include <stdlib.h>

float pow(float base, float exp)
{
	int i;
	float power = 1;

	if (exp < 0)
	{
		exp = -exp;
		base = 1 / base;
	}

	for (i = 0; i < exp; i++)
		power *= base;

	return power;
}

int main()
{
	float base, exp, power;

	printf("Please enter a base and exp:\n");
	scanf("%f %f", &base, &exp);

	power = pow(base, exp);

	printf("%.0f power %.0f is: %.2f\n",base,exp,power);

	printf("\n");
	return 0;
}
