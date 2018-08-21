#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<string>
#include<algorithm>
#define Read_file "Rule_Extract.txt"
#include<set>
using namespace std;
struct Rule
{
	int num; // °¹¼ö
	bool Positive;
	bool *arr2;
	string *arr;
	Rule *next_rule;
};
struct Node
{
	int type; // input 1 , dis 2, output 3, conjunction
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
void Read_Rule();
void Rewrite(Rule *);
void output_tree(string);
void change_plus(string, string);