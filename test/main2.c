#include <stdio.h>
#include <string.h>


int main(void)
{
	int arr[2], num;
	char s[] = "Home ", *ptr, *pt;

	ptr = strtok(s, " ");
	pt = strtok(NULL, " ");
	num = atoi(pt);


	printf("%s\n%s\n", ptr, pt);
	return (0);
}
