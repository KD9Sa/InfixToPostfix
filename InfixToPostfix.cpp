#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
	char data;
	Node* next;
}Node;

typedef struct Deque {
	Node* head;
	Node* tos;
}Deque;

typedef struct Stack {
	Deque* d;
}Stack;

Stack* init() {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	Deque* d = (Deque*)malloc(sizeof(Deque));
	s->d = d;
	s->d->head = NULL;
	s->d->tos = NULL;
	return s;
}

void Push(Stack* s, char x) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = x;
	new_node->next = NULL;
	if (s->d->head == NULL) {
		s->d->head = new_node;
		s->d->tos = new_node;
	} else {
		s->d->tos->next = new_node;
		s->d->tos = new_node;
	}
}

char Pop(Stack* s) {
	if (s->d->head == NULL) {
		printf("Cannot pop from an empty stack.\n");
		return NULL;
	}

	if (s->d->head->next == NULL) {
		char x = s->d->tos->data;
		s->d->head = NULL;
		s->d->tos = NULL;
		return x;
	}

	char x = s->d->tos->data;
	Node* p = s->d->head;
	while (p->next != s->d->tos) {
		p = p->next;
	}
	p->next = NULL;
	free(s->d->tos);
	s->d->tos = p;
	return x;
}

typedef struct fNode {
	float data;
	fNode* next;
}fNode;

typedef struct fDeque {
	fNode* head;
	fNode* tos;
}fDeque;

typedef struct fStack {
	fDeque* d;
}fStack;

fStack* finit() {
	fStack* s = (fStack*)malloc(sizeof(fStack));
	fDeque* d = (fDeque*)malloc(sizeof(fDeque));
	s->d = d;
	s->d->head = NULL;
	s->d->tos = NULL;
	return s;
}

void fPush(fStack* s, float x) {
	fNode* new_node = (fNode*)malloc(sizeof(fNode));
	new_node->data = x;
	new_node->next = NULL;
	if (s->d->head == NULL) {
		s->d->head = new_node;
		s->d->tos = new_node;
	}
	else {
		s->d->tos->next = new_node;
		s->d->tos = new_node;
	}
}

float fPop(fStack* s) {
	if (s->d->head == NULL) {
		printf("Cannot pop from an empty stack.\n");
		return NULL;
	}

	if (s->d->head->next == NULL) {
		float x = s->d->tos->data;
		s->d->head = NULL;
		s->d->tos = NULL;
		return x;
	}

	float x = s->d->tos->data;
	fNode* p = s->d->head;
	while (p->next != s->d->tos) {
		p = p->next;
	}
	p->next = NULL;
	free(s->d->tos);
	s->d->tos = p;
	return x;
}

int count_values(Stack* s) {
	int count = 0;
	Node* p = s->d->head;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

void print_stack(Stack* s) {
	printf("[");
	Node* p = s->d->head;
	while (p != NULL) {
		if (p->next == NULL) {
			printf("%c", p->data);
			p = p->next;
			continue;
		}
		printf("%c, ", p->data);
		p = p->next;
	}
	printf("]\n");
}

float evaluate_postfix(Stack* s) {
	Stack* reverse = init();
	int postfix_size = count_values(s);
	for (int i = 0; i < postfix_size; i++) {
		Push(reverse, Pop(s));
	}
	fStack* evaluate = finit();
	for (int i = 0; i < postfix_size; i++) {
		char c = Pop(reverse);
		if (isdigit(c)) {
			fPush(evaluate, (float)(c - '0'));
		}
		if (c == '+') {
			float first = fPop(evaluate);
			float second = fPop(evaluate);
			float sum = second + first;
			fPush(evaluate, sum);
		}
		if (c == '-') {
			float first = fPop(evaluate);
			float second = fPop(evaluate);
			float sub = second - first;
			fPush(evaluate, sub);
		}
		if (c == '*') {
			float first = fPop(evaluate);
			float second = fPop(evaluate);
			float mul = second * first;
			fPush(evaluate, mul);
		}
		if (c == '/') {
			float first = fPop(evaluate);
			float second = fPop(evaluate);
			float div = second / first;
			fPush(evaluate, div);
		}
	}

	return fPop(evaluate);
}

int main() {
	Stack* operators = init();
	Stack* postfix = init();
	char expression[100];
	char previous = ' ';

	printf("Enter an expression to evaluate: ");
	scanf("%[^\n]%*c", &expression);

	for (int i = 0; i < strlen(expression); i++) {
		if (expression[i] == ' ') {
			continue;
		}
		else if (isdigit(expression[i])) {
			Push(postfix, expression[i]);
		}
		else if (expression[i] == '(') {
			Push(operators, expression[i]);
			previous = expression[i];
		}
		else if (expression[i] == ')') {
			char c = Pop(operators);
			while (c != '(') {
				Push(postfix, c);
				c = Pop(operators);
			}
			previous = Pop(operators);
			Push(operators, previous);
		}
		else if (expression[i] == '*' || expression[i] == '/') {
			if (previous == '*' || previous == '/') {
				char popped = Pop(operators);
				Push(postfix, popped);
			}
			Push(operators, expression[i]);
			previous = expression[i];
		}
		else if (expression[i] == '+' || expression[i] == '-') {
			if (previous == '*' || previous == '/' || previous == '+' || previous == '-') {
				char popped = Pop(operators);
				Push(postfix, popped);
			}
			Push(operators, expression[i]);
			previous = expression[i];
		}
		else {
			printf("Invalid input.");
		}
	}

	int operators_size = count_values(operators);
	for (int i = 0; i < operators_size; i++) {
		char popped = Pop(operators);
		Push(postfix, popped);
	}

	print_stack(postfix);

	float result = evaluate_postfix(postfix);
	printf("Postfix expression result is: %.2f\n", result);
}