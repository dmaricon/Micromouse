#include <stdio.h>
#include "stack.h"

main()
{
	int x;
	int c=0;
	Stack s;
	s_init(&s);

	printf("~Menu~\n(1) Push\n(2) Pop\n(3) Exit\n");
	while(c!=1 && c!=2 && c!=3){
		scanf("%d",&c);
		if(c!=1 && c!=2 && c!=3)printf("Invalid entry!\n");
	}

	while(c!=3){
		if(c==1){
			printf("Push integer:");
			scanf("%d",&x);
			push(&s,x);
			display(&s);
		}
		if(c==2){
			x=pop(&s);
			printf("Popped integer:%d\n",x);
			display(&s);
		}
		c=0;
		printf("~Menu~\n(1) Push\n(2) Pop\n(3) Exit\n");
		while(c!=1 && c!=2 && c!=3){
			scanf("%d",&c);
			if(c!=1 && c!=2 && c!=3)printf("Invalid entry!\n");
		}
	}
}
