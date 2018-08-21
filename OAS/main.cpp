#include "global_OAS.h"
Node *node;
FILE *fp;
int main(int argc, char *argv[]) // Parameter·Î 
{
	int i;
	fp = fopen("Rule_Extract.txt", "w");
	if (argv[1] == NULL)
	{
		printf("parameter need input node file. (example file name : xor.nff)\n");
		return 0;
	}
	int len = Read_net(argv[1]);
	fprintf(fp, "%d\n",len);
	for (i = 0; i < len; i++)
	{
		fprintf(fp, "Node: %s %d\n", node[i].name,node[i].type);
		if (node[i].type != 1)
			normal_node(i);
	}
	return 0;
}