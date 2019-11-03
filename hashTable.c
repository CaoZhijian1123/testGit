#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

int n, m;
int NOTFOUND = -1;
int DEL = -1;
int EMPTY = -2;

typedef struct SCORE{
	char name[20];
	int score;

} score;

typedef struct NODE {
	score s;
	struct NODE * next;
} Node;

unsigned int hash(char* str);
void pro();
int h(char *s, int i);
int delete(Node * nodes, char name[]);
int  getValue(Node * nodes, char name[]);
void insert(Node * nodes, score s);
Node * init(int m);
//chaining
int main() {
	pro();



	//system("pause");
	return 0;
}

void pro() {


	scanf("%d", &n);
	m = n / 5;


	Node * scores=init( m);

	char op;
	score s;
	

	for (int i = 0; i < n; i++)
	{
		
		scanf(" %c", &op);
		scanf("%s", s.name);
		
		
		
		if (op=='i')
		{
			scanf(" %d", &s.score);		
			insert(scores, s);
			printf("%c %s %d\n", op, s.name, s.score);

		}
		else if (op == 's') {
			s.score=getValue(scores, s.name);
			printf("%c %s %d\n", op, s.name, s.score);
		
		}
		else if (op=='d') {
			s.score = delete(scores, s.name);
			printf("%c %s %d\n", op, s.name, s.score);
		}
	}




}

Node * init( int m) {
	Node *nodes;
	nodes = (Node*)malloc(sizeof(Node)*m);
	for (int i = 0; i < m; i++)
	{
		nodes[i].next = NULL;
		nodes[i].s.score = EMPTY;
	}
	return nodes;
}

void insert(Node * nodes, score s) {
	int pos = h(s.name, 0);
	Node * tar=nodes+pos;
	if (tar->s.score==EMPTY)
	{
		tar->s = s;
		return;
	}

	Node *temp;
	temp = (Node*)malloc(sizeof(Node));
	temp->s = s;
	temp->next = tar->next;
	//(*tar).next = &temp;
	tar->next = temp;

}


int  getValue(Node * nodes,char name[]) {
	int pos = h(name, 0);
	Node * tar = nodes + pos;
	while (tar!=NULL)
	{
		if (strcmp(tar->s.name,name)==0 && tar->s.score!=EMPTY)
		{
			return tar->s.score;
		}
		tar = tar->next;

	}


	return NOTFOUND;

}

int delete(Node * nodes, char name[]) {
	int pos = h(name, 0);
	Node * tar = nodes + pos;
	if (strcmp(tar->s.name,name)==0 && tar->s.score>=0)
	{
		int score = tar->s.score;
		if (tar->next!=NULL)
		{
			*tar = *tar->next;
		}
		else
		{
			tar->s.score = EMPTY;

		}

		return score;
	}
	

	while (tar->next!=NULL)
	{
		if (strcmp(tar->next->s.name, name)==0)
		{
			int score = tar->next->s.score;
			tar->next = tar->next->next;
			return score;
		}
		tar = tar->next;
	}



	return NOTFOUND;

}


int h(char *s, int i) {
	int h1 = hash(s)% m;
	int result = (h1 + i * i) % m;
	return result;

}

/*
	get hashCode from a str
*/
unsigned int hash(char* str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash&0x7fffffff);
}


