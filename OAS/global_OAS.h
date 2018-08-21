#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<string>
#include<algorithm>
using namespace std; 
struct in_node
{
	double para;
	int node;
	int positive;
};
struct Rule
{
	int num; // °¹¼ö
	bool Positive;
	bool *arr2;
	int *arr;
	Rule *next_rule;
};
struct Node
{
	int type; // input 1 , dis 2, output 3, conjunction
	char *name;
	double bias;
	int in_num;
	in_node *in;
	int out_num;
	int *out_node;
	Rule *start;
};
struct Queue
{
	double tot;
	double tot_worst;
	double tot_best;
	Rule *rule;
	Queue *next;
};
extern Node *node;
int Read_net(char *);
void normal_node(int);
Queue *solve(Queue *, int );
void all_Rule(struct Rule *);
void all_Queue(struct Queue *);
int Rule_Clear(Rule *);
extern FILE *fp;
void Read_Rule();