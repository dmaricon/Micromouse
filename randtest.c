#include <stdio.h>
#include <stdlib.h>

main()
{
	int n;

	while(1){
		while(getchar()!='\n');

		n=rand()%100;
		printf("%d\n",n);
	}
}
