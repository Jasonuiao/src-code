#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/ioctl.h>
//#include <sys/socket.h>
#include <sys/time.h>
#include <pthread.h>


static int dyn_arr(void)
{
	double * ptd;
	int max, number;
	int i = 0;
	puts("What is the mac number of type entry?");
	if (scanf("%d", &max) !=1){
		puts("error!");
		exit(EXIT_FAILURE);
	}
	ptd = (double*)malloc(max * sizeof(double));
	if (ptd == NULL)
	{
		puts("error!");
		exit(EXIT_FAILURE);
	}
	
	puts("Enter your values:");
	while (i < max && scanf("%lf", &ptd[i]) == 1 ) {
		++i;
	}
	
	number = i;
	printf("your number %d\n", i);

	for (int i = 0; i < number; i++) {
		printf("%7.2f ", ptd[i]);
		//if (i % 7 == 6)
		//	putchar('\n');
	}
	//if (i % 7 != 0)
	//	putchar('\n');
	free(ptd);

	return 0;
}
