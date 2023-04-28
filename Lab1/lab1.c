//
//	lab 1
//	spring 2023
//	name: 
//


//  includes
#include	<stdio.h>


// defines


// global variables


// functions
int	main (void);


// main
int
main (void)
{
	int option;


	while (1)
	{
		printf ("enter option\n");
		if (scanf ("%d", &option) != 1)
		{
			printf ("error\n");
			return 0;
		}

		switch (option)
		{
			case 1:
				printf ("case 1\n");
				break;

			case 2:
				printf ("case 2\n");
				break;

			case 0:
				printf ("exit\n");
				return 0;

			default:
				printf ("wrong option\n");
		}

	}	

}
