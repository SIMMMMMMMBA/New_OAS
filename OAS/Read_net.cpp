#include"global_OAS.h"
int Read_net(char *in_file)
{
	int in_n, dis_n, out_n, con_n;
	int i, j, count=0;
	char node_n[50];
	char type[50];
	char name[50];
	FILE *fp = fopen(in_file, "r");
	fscanf(fp, "%d %d %d %d", &in_n,&dis_n,&out_n,&con_n);
	node = (Node*)malloc(sizeof(Node)*(in_n + dis_n + out_n + con_n));
	for (i = 0; i < in_n; i++)
	{
		fscanf(fp, "%s %s %s", node_n, type, name);
		node[count].type = 1;
		node[count].name = (char*)malloc(sizeof(char)*(strlen(name)+1));
		strcpy(node[count].name, name);
		fscanf(fp, "%d", &node[count].out_num);
		node[count].out_node = (int*)malloc(sizeof(int)*node[count].out_num);
		for (j = 0; j < node[count].out_num; j++)
			fscanf(fp, "%d", &node[count].out_node[j]);
		count++;
	}
	for (i = 0; i < dis_n; i++)
	{
		fscanf(fp, "%s %s %s %lf", node_n, type, name, &node[count].bias);
		node[count].type = 2;
		node[count].name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
		strcpy(node[count].name, name);
		fscanf(fp, "%d", &node[count].in_num);
		node[count].in = (in_node*)malloc(sizeof(in_node)*node[count].in_num);

		for (j = 0; j < node[count].in_num; j++)
		{
			fscanf(fp, "%d %lf", &node[count].in[j].node, &node[count].in[j].para);
			node[count].in[j].positive = 1;
			if (node[count].in[j].para < 0)
			{
				node[count].in[j].para *= -1;
				node[count].in[j].positive = -1;
			}
		}
		fscanf(fp, "%d", &node[count].out_num);
		node[count].out_node = (int*)malloc(sizeof(int)*node[count].out_num);

		for (j = 0; j < node[count].out_num; j++)
			fscanf(fp, "%d", &node[count].out_node[j]);
		count++;
	}
	for (i = 0; i < out_n; i++)
	{
		fscanf(fp, "%s %s %s %lf", node_n, type, name, &node[count].bias);
		node[count].type = 3;
		node[count].name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
		strcpy(node[count].name, name);
		fscanf(fp, "%d", &node[count].in_num);
		node[count].in = (in_node*)malloc(sizeof(in_node)*node[count].in_num);

		for (j = 0; j < node[count].in_num; j++)
		{
			fscanf(fp, "%d %lf", &node[count].in[j].node, &node[count].in[j].para);
			node[count].in[j].positive = 1;
			if (node[count].in[j].para < 0)
			{
				node[count].in[j].para *= -1;
				node[count].in[j].positive = -1;
			}
		}

		count++;
	}
	for (i = 0; i < con_n; i++)
	{
		fscanf(fp, "%s %s %s %lf", node_n, type, name, &node[count].bias);
		node[count].type = 4;
		node[count].name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
		strcpy(node[count].name, name);
		fscanf(fp, "%d", &node[count].in_num);
		node[count].in = (in_node*)malloc(sizeof(in_node)*(node[count].in_num));
		for (j = 0; j < node[count].in_num; j++)
		{
			fscanf(fp, "%d %lf", &node[count].in[j].node, &node[count].in[j].para);
			node[count].in[j].positive = 1;
			if (node[count].in[j].para < 0)
			{
				node[count].in[j].para *= -1;
				node[count].in[j].positive = -1;
			}
		}

		fscanf(fp, "%d", &node[count].out_num);
		node[count].out_node = (int*)malloc(sizeof(int)*node[count].out_num);
		for (j = 0; j < node[count].out_num; j++)
			fscanf(fp, "%d", &node[count].out_node[j]);
		count++;
	}
	fclose(fp);
	return count;
}