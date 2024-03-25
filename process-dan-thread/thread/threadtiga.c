#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t tid[2];

static int num_accts = 1024; // number of bank accounts
static int num_trans = 10000; // number of transactions
static int think_time = 50; // amount of "thinking time"
struct acct_t
{
	int bal;
};

/*
 * Pointer to accounts
 */
struct acct_t *accts;
/*
 * Method to perform a number of transactions.
 * Parameter "dummy" is not used.
 */
void *transact(void *dummy)
{
	for (int i = 0; i < num_trans/2; i++)
	{
		// pick two random accounts
		int acct_id_from = rand() % num_accts;
		int acct_id_to = rand() % num_accts;
		// pick a random amount
		int amt = rand() % 100;
		// try to transfer the money
		if (accts[acct_id_from].bal > amt)
		{
			accts[acct_id_from].bal -= amt;
			accts[acct_id_to].bal += amt;
			// "thinking time"... don't modify this code!!
			amt *= think_time;
			while (amt--);
		}
	}
}

int main(int argc, char **argv)
{
	// make sure the number of arguments is odd (including the program name)
	if (!(argc == 1 || argc == 3 || argc == 5 || argc == 7))
	{
		fprintf(stderr, "usage: %s [-a <accts>>] [-i <transactions>] [-t <think-time>]\n", argv[0]);
		exit(-1);
	}
	// look at each runtime argument & see which value it's attempting to set
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-a"))
		{
			num_accts = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-i"))
		{
			num_trans = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-t"))
		{
			think_time = atoi(argv[i + 1]);
			i++;
		}
		else
		{
			fprintf(stderr, "usage: %s [-a <accts>] [-i <stransactions>] [-t <thinktime>]\n", argv[0]);
			exit(-1);
		}
	}
	// display the parameters that will be used for this test run
	fprintf(stderr, "%s: -a %d -i %d -t %d\n", argv[0], num_accts, num_trans, think_time);
	// initialize the random number generator
	srand(1);
	// create the bank accounts
	accts = (struct acct_t *)malloc(num_accts * sizeof(struct acct_t));
	// initialize the bank accounts' values and keep track of the total sum
	// in all accounts
	int original_sum = 0;

	for (int i = 0; i < num_accts; i++)
	{
		accts[i].bal = rand() % 1000;
		original_sum += accts[i].bal;
	}

	// call the transact function to do the transfers
        for (int i = 0; i < 2; i++)
        {
                int err = pthread_create(&(tid[i]), NULL, &transact, NULL);
                if (err != 0)
                        printf("\ncan't create thread :[%s]", strerror(err));
                else 
                        printf("\n Thread created successfully\n");
        }

	pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

	// find the total sum of all accounts after the transfers are done
	int sum = 0;

	for (int i = 0; i < num_accts; i++)
	{
		sum += accts[i].bal;
	}
	// if the sum is not equal to the original sum, then we had a race
	// condition!!
	if (sum != original_sum)
	{
		fprintf(stderr, "ERROR! original_sum = %d, sum = %d\n", original_sum, sum);
	}
	else
	{
		fprintf(stderr, "Values are still consistent\n");
	}
	return 0;
}

