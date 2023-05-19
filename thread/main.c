#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg) {
	printf("This from child thread!\n");

	int ret = pthread_join(pthread_self(), NULL);

	printf("This from child 2, ret=%d\n", ret);
	return 0;
}

int main() {
	int tid;
	pthread_t thread;

	tid = pthread_create(&thread, NULL, &thread_func, NULL);

	sleep(1);
	printf("This from main thread!\n");
	
	return 0;
}
