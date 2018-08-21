#include "global_OAS.h"
#define TH_hold 0
Rule *startrule;
Rule *endrule;
int in_num;
int node_num;
double tot_worst;
double tot_best;
int compare(const void *A, const void * B)
{
	struct in_node *a, *b;
	a = (struct in_node*)A;
	b = (struct in_node*)B;
	if (a->para > b->para) return -1;
	else if (a->para < b->para) return 1;
	return 0;
}
void normal_node(int x) {
	int i, j;
	Queue *queue = NULL;
	queue = (Queue*)malloc(sizeof(Queue));
	queue->rule = (Rule*)malloc(sizeof(Rule));
	queue->rule->arr = (int*)malloc(sizeof(int)*(in_num+1));
	queue->rule->arr2 = (bool*)malloc(sizeof(bool)*(in_num + 1));
	queue->rule->num = 0;
	queue->rule->arr[0] = -1;
	queue->tot = 0;
	queue->next = NULL;
	in_num = node[x].in_num;
	tot_worst = 0;
	tot_best = 0;
	node_num = x;
	startrule = NULL;
	endrule = NULL;
	for (i = 0; i < in_num; i++)
	{
		if (node[x].in[i].positive < 0)
			tot_worst += node[x].in[i].para*node[x].in[i].positive;
		else
			tot_best += node[x].in[i].para*node[x].in[i].positive;
	}
	queue->tot_worst= tot_worst;
	queue->tot_best = tot_best;
	qsort(node[x].in, in_num, sizeof(node[x].in[0]), compare);
	//for (i = 0; i < in_num; i++)
		//printf("%d %lf %d\n", node[x].in[i].node,node[x].in[i].para,node[x].in[i].positive);
	for (j = 0; j < in_num; j++)
	{
		queue = solve(queue, j);
		if (queue == NULL)
			break;
		/*
		Queue *f = queue;
		while (f != NULL)
		{
			printf("tot: %lf %lf %lf\n", f->tot, f->tot_worst, f->tot_best);
			printf("list : ");
			for (i = 0; i < f->rule->num; i++)
				printf("%d ", f->rule->arr[i]);
			printf("\n");
			printf("true : ");
			for (i = 0; i < f->rule->num; i++)
			{
				if (f->rule->arr2[i] == true)
					printf("T ");
				else
					printf("F ");
			}
			printf("\n");
			if (f->next == NULL)
				break;
			f = f->next;
		}
		printf("\n\n");
		*/
	}
	Queue *aaa = queue;
	while (aaa != NULL)
	{
		if (Rule_Clear(aaa->rule)==0)
		{
			if (aaa->tot + node[x].bias >= TH_hold)
				aaa->rule->Positive = true;
			else
				aaa->rule->Positive = false;
			endrule->next_rule = aaa->rule;
			endrule = endrule->next_rule;
		}
		aaa = aaa->next;
	}
	Rule *g = startrule;
	while (g != NULL)
	{
		fprintf(fp,"true : ");
		if (g->Positive == true)
			fprintf(fp, "Positive");
		else
			fprintf(fp, "Negative");
		fprintf(fp, "\n");
		fprintf(fp, "list : ");
		if (g->num == 0)
		{
			fprintf(fp, "ALWAYS\n");
			break;
		}
		if (g->arr2[0] == false)
			fprintf(fp, "~");
		fprintf(fp, "%s", node[node[x].in[g->arr[0]].node].name);
		for (i = 1; i < g->num; i++)
		{
			fprintf(fp, "&");
			if (g->arr2[i] == false)
				fprintf(fp, "~");
			fprintf(fp, "%s", node[node[x].in[g->arr[i]].node].name);
		}
		fprintf(fp, "\n");
		if (g->next_rule == NULL)
			break;
		g = g->next_rule;
	}
	fprintf(fp, "END : RULE");
	fprintf(fp, "\n\n");
	all_Rule(startrule);
}
void all_Rule(struct Rule *root) {

	struct Rule *dummy;

	while (root) {
		dummy = root;

		root = (root)->next_rule;

		free(dummy);

	}
}
void all_Queue(struct Queue *root) {

	struct Queue *dummy;

	while (root) {

		dummy = root;

		root = (root)->next;

		free(dummy);

	}
}

int Rule_Clear(Rule *Que)
{
	Rule *next = startrule;
	while (next)
	{
		int i, j = 0;
		int k = 0;
		for (i = 0; i < next->num; i++)
		{
			if (j >= Que->num)
			{
				k = 1;
				break;
			}
			if (Que->arr[j] == next->arr[i])
			{
				if(Que->arr2[j] == next->arr2[i])
					j++;
				else
				{
					k = 1;
					break;
				}
			}
			else if (Que->arr[j] != next->arr[i])
			{
				j++;
				i--;
			}
		}
		if (k == 0)
		{
			/*
			printf("NEXT : ");
			for (i = 0; i < next->num; i++)
			{
				print_bool(next->arr2[i]);
				printf("%d ", next->arr[i]);
			}
			printf("\nQue : ");
			for (i = 0; i < Que->num; i++)
			{
				print_bool(Que->arr2[i]);
				printf("%d ", Que->arr[i]);
			}
			printf("\n");
			scanf("%d", &j);*/
			return 1;
		}
		next = next->next_rule;
	}
	return 0;
}
Queue *solve(Queue *que,int level)
{
	Queue *que2;
	Queue *next;
	Queue *top = que;
	int i,j;
	que2 = (Queue*)malloc(sizeof(Queue));
	que2->next = NULL;
	next = que2;
	//printf("level : %d\n", level);
	while (que!=NULL)
	{
		//printf("tot1: %lf %lf %lf\n", que->tot, que->tot_worst, que->tot_best);
		if (Rule_Clear(que->rule))
			que = que->next;
		else if (que->tot + que->tot_worst + node[node_num].bias >= TH_hold)
		{
			que->rule->Positive = true;
			if (startrule == NULL)
			{
				startrule = que->rule;
				startrule->next_rule = NULL;
				endrule = startrule;
			}
			else
			{
				endrule->next_rule = que->rule;
				endrule = endrule->next_rule;
			}
			//printf("XXXXXXX\n");
			/*
			printf("rule : ");
			for (i = 0; i < que->rule->num; i++)
			{
				if (que->rule->arr2[i] == false)
					printf("~");
				printf("%d ", que->rule->arr[i]);
			}
			printf("\n");*/
		}
		else if (que->tot + que->tot_best + node[node_num].bias < TH_hold)
		{
			que->rule->Positive = false;
			if (startrule == NULL)
			{
				startrule = que->rule;
				startrule->next_rule = NULL;
				endrule = startrule;
			}
			else
			{
				endrule->next_rule = que->rule;
				endrule = endrule->next_rule;
			}
			//printf("YYYYYYYYY\n");
			/*
			printf("rule : ");
			for (i = 0; i < que->rule->num; i++)
			{
				if (que->rule->arr2[i] == false)
					printf("~");
				printf("%d ", que->rule->arr[i]);
			}
			printf("\n");*/
		}
		else
		{
			int k = 0;
			if (level - 1 < 0)
				k = 1;
			else
				k = level;
			//printf("ZZZZZZZZZZZZZ\n");
			//printf("%d\n", que->rule->arr[k - 1] + 1);
			for (i = que->rule->arr[k-1]+1; i < in_num; i++)
			{
				Queue *newque,*newque1;
				newque = (Queue*)malloc(sizeof(Queue));
				newque->rule = (Rule*)malloc(sizeof(Rule));
				newque->rule->arr = (int*)malloc(sizeof(int)*(in_num + 1));
				newque->rule->arr2 = (bool*)malloc(sizeof(bool)*(in_num + 1));
				newque->rule->next_rule = NULL;
				newque1 = (Queue*)malloc(sizeof(Queue));
				newque1->rule = (Rule*)malloc(sizeof(Rule));
				newque1->rule->arr = (int*)malloc(sizeof(int)*(in_num + 1));
				newque1->rule->arr2 = (bool*)malloc(sizeof(bool)*(in_num + 1));
				newque1->rule->next_rule = NULL;
				newque->tot_best = que->tot_best;
				newque->tot_worst = que->tot_worst;
				newque->tot = que->tot+node[node_num].in[i].para*node[node_num].in[i].positive;
				newque1->tot = que->tot;
				newque1->tot_best = que->tot_best;
				newque1->tot_worst = que->tot_worst;
				newque1->next = NULL;
				if (node[node_num].in[i].positive >= 0)
				{
					newque->tot_best -= node[node_num].in[i].para*node[node_num].in[i].positive;
					newque1->tot_best -= node[node_num].in[i].para*node[node_num].in[i].positive;
				}
				else
				{
					newque->tot_worst -= node[node_num].in[i].para*node[node_num].in[i].positive;
					newque1->tot_worst -= node[node_num].in[i].para*node[node_num].in[i].positive;
				}
				//printf("j º¯È­ : ");
				for (j = 0; j < level; j++)
				{
					//printf("%d ", j);
					newque->rule->arr[j]=que->rule->arr[j];
					newque->rule->arr2[j] = que->rule->arr2[j];
					newque1->rule->arr[j] = que->rule->arr[j];
					newque1->rule->arr2[j] = que->rule->arr2[j];
				}
				//printf("\n");
				newque->rule->arr[level] = i;
				newque->rule->arr2[j] = true;
				newque1->rule->arr[level] = i;
				newque1->rule->arr2[j] = false;
				newque->rule->num = level + 1;
				newque1->rule->num = level + 1;
				next->next = newque;
				next->next->next = newque1;
				next = next->next->next;
			}
		}
		if (que->next == NULL)
			break;
		que = que->next;
	}
	all_Queue(top);
	return que2->next;
	// pruneing
}