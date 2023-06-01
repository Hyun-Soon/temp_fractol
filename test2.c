#include <stdio.h>

int main()
{
	int color = 0x000000FF;
	printf("%d vs %d\n", color, 0x000000FF);
	color <<= 8;
	printf("%d vs %d\n", color, 0x0000FF00);
	return 0;
}
