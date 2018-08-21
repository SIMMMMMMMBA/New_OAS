#include "global_Rewrite.h"
map<string, Node> Nodes;
map<string, Node> output;
map<string, int> Rules;
void Read_Rule()
{
	char dumb[10], name[10];
	int type;
	int i, j;
	int len;
	FILE *fp = fopen(Read_file, "r");
	fscanf(fp, "%d", &len);
	for (i = 0; i < len; i++)
	{
		fscanf(fp, "%s %s %d", dumb, name, &type);
		Nodes[name].type = type;
		if (type ==2 || type==4)
		{
			Nodes[name].start = NULL;
			Rule *last = NULL;
			while (1)
			{
				Rule *newrule = (Rule*)malloc(sizeof(Rule));
				char tr[10], a[100], b[10];
				bool trues;
				fscanf(fp, "%s : %s", dumb, tr);
				if (strcmp(tr, "RULE") == 0)
					break;
				if (strcmp(tr, "Negative") == 0)
				{
					trues = false;
				}
				else
					trues = true;
				fscanf(fp, "%s%s%s", dumb, b, a);
				int len1 = strlen(a);
				int count = 0;
				string find = "";
				for (j = 0; j<len1; j++)
				{
					if (a[j] == '&')
						count++;
				}
				newrule->arr = new string[count + 2];
				newrule->arr2 = (bool*)malloc(sizeof(bool)*(count + 2));
				newrule->Positive = trues;
				newrule->next_rule = NULL;
				newrule->num = count + 1;
				count = 0;
				trues = true;
				for (j = 0; j < len1; j++)
				{
					if (a[j] == '~')
						trues = false;
					else if (a[j] == '&')
					{
						newrule->arr[count] = find;
						newrule->arr2[count] = trues;
						trues = true;
						count++;
						find = "";
					}
					else
						find += a[j];
				}
				newrule->arr[count] = find;
				newrule->arr2[count] = trues;
				if (Nodes[name].start == NULL)
				{
					Nodes[name].start = newrule;
					last = Nodes[name].start;
				}
				else
				{
					last->next_rule = newrule;
					last = last->next_rule;
				}
			}
		}
		else if (type == 3)
		{
			Nodes[name].start = NULL;
			Rule *last = NULL;
			while (1)
			{
				Rule *newrule = (Rule*)malloc(sizeof(Rule));
				char tr[10], a[100], b[10];
				bool trues;
				fscanf(fp, "%s : %s", dumb, tr);
				if (strcmp(tr, "RULE") == 0)
					break;
				if (strcmp(tr, "Negative") == 0)
				{
					trues = false;
				}
				else
					trues = true;
				fscanf(fp, "%s%s%s", dumb, b, a);
				int len1 = strlen(a);
				int count = 0;
				string find = "";
				for(j=0;j<len1;j++)
				{
					if (a[j] == '&')
						count++;
				}
				newrule->arr = new string[count+2];
				newrule->arr2 = (bool*)malloc(sizeof(bool)*(count + 2));
				newrule->Positive = trues;
				newrule->next_rule = NULL;
				newrule->num = count + 1;
				count = 0;
				trues = true;
				for (j = 0; j < len1; j++)
				{
					if (a[j] == '~')
						trues = false;
					else if (a[j] == '&')
					{
						newrule->arr[count] = find;
						newrule->arr2[count] = trues;
						trues = true;
						count++;
						find = "";
					}
					else
						find += a[j];
				}
				newrule->arr[count] = find;
				newrule->arr2[count] = trues;
				if (Nodes[name].start == NULL)
				{
					Nodes[name].start = newrule;
					last = Nodes[name].start;
				}
				else
				{
					last->next_rule = newrule;
					last = last->next_rule;
				}
			}
		}
	}
	fclose(fp);
	output_tree("y");
	//Rewrite(Nodes["y"].start);
}
void output_tree(string y)
{
	set<string> s;
	set<string>::iterator iter;
	int i;
	Rule *start = Nodes[y].start;
	while (start != NULL)
	{
		for (i = 0; i < start->num; i++)
		{
			if (Nodes[start->arr[i]].type != 1)
				s.insert(start->arr[i]);
		}
		start = start->next_rule;
	}
	if (s.size() == 0)
		return;
	for (iter = s.begin(); iter != s.end(); ++iter)
	{
		change_plus(y, *iter);
		Rewrite(Nodes[y].start);
	}

	Rule *starts = Nodes[y].start;
	while (starts != NULL)
	{
		int i;
		printf("Positive : %d \n", starts->Positive);
		for (i = 0; i < starts->num - 1; i++)
		{
			if (starts->arr2[i] == false)
				printf("~");
			printf("%s&", starts->arr[i].c_str());
		}
		if (starts->arr2[starts->num - 1] == false)
			printf("~");
		printf("%s\n", starts->arr[starts->num - 1].c_str());
		starts = starts->next_rule;
	}
}
void change_plus(string y, string x)
{
	Rule *firstrule = (Rule*)malloc(sizeof(Rule));
	Rule *newrule = firstrule;
	Rule *next = Nodes[y].start;
	Rule *before;
	int i, j;
	firstrule->next_rule = NULL;
	while (next != NULL)
	{
		for (i = 0; i < next->num; i++)
		{
			if (next->arr[i].compare(x)==0)
				break;
		}
		if (next->num != i)
		{
			Rule *k = Nodes[x].start;
			while (k != NULL)
			{
				if (k->Positive == next->arr2[i])
				{
					Rule *add = (Rule*)malloc(sizeof(Rule));
					int count1 = 0;
					add->arr = new string [(k->num+next->num)];
					add->arr2 = (bool*)malloc(sizeof(bool)*(k->num + next->num));
					add->Positive = next->Positive;
					add->next_rule = NULL;
					//printf("A : %d %d %s\n", k->Positive, next->arr2[i], next->arr[i].c_str());
					for (j = 0; j < next->num; j++)
					{
						if (i != j)
						{
							add->arr[count1] = next->arr[j];
							add->arr2[count1] = next->arr2[j];
							count1++;
						}
					}
					for (j = 0; j < k->num; j++)
					{
						add->arr[count1] = k->arr[j];
						add->arr2[count1] = k->arr2[j];
						//printf("%s ", k->arr[j].c_str());
						count1++;
					}
					//printf("\n");
					add->num = count1;
					newrule->next_rule = add;
					newrule = newrule->next_rule;
				}
				k = k->next_rule;
			}
			before = next;
			next = next->next_rule;
			free(before);
		}
		else
		{
			newrule->next_rule = next;
			newrule = newrule->next_rule;
			next = next->next_rule;
			newrule->next_rule = NULL;
		}
	}
	Nodes[y].start = firstrule->next_rule;
	free(firstrule);
}
void Rewrite(Rule *start)
{
	Rule *before = start;
	Rule *next = start;
	int i;
	while (next != NULL)
	{
		set<pair<string, bool>> s;
		int size;
		int check = 0;
		set<pair<string, bool>>::iterator iter1;
		string A;
		for (i = 0; i < next->num; i++)
		{
			pair<string, bool> pair1(next->arr[i], next->arr2[i]);
			pair<string, bool> pair2(next->arr[i], not next->arr2[i]);
			iter1 = s.find(pair2);
			if (iter1 != s.end())
			{
				check = 1;
				// error rule
				break;
			}
			s.insert(pair1);
		}
		if (check == 1)
		{
			before->next_rule = next->next_rule;
			before = next;
			next = next->next_rule;
			free(before);
		}
		else
		{
			int plus = 0;
			size = s.size();
			next->arr = new string[size + 1];
			next->arr2 = (bool*)malloc(sizeof(bool)*(size + 1));
			for (iter1 = s.begin(); iter1 != s.end(); ++iter1)
			{
				next->arr[plus]=iter1->first;
				next->arr2[plus] = iter1->second;
				++plus;
			}
			next->num = plus;
			before = next;
			next = next->next_rule;
		}
	}
}