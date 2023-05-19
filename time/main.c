#include <stdio.h>
#include <time.h>

int main() {
	char *now;

	now = ctime(NULL);
	printf("Time: %s\n", now);
	return 0;
}
