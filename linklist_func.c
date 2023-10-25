#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include "data.h"
bool keyidentical(char* ptrkey, char* key)
{
	int keylen = 0;
	while (key[keylen] != '\0') keylen++;
	bool identical = true;
	for (int i = 0; i < keylen; i++) {
		if (ptrkey[i] != key[i]) {
			identical = false;
			return identical;
		}
	}
	return identical;
}
node* new_node(int value, char* key)
{
	node* x;
	x = (node*)malloc(sizeof(node));
	if (x == NULL)
		return NULL;
	else {
		for (int i = 0; key[i] != '\0'; i++) {
			x->key[i] = key[i];
		}
		x->value = value;
		x->next = NULL;
		return x;
	}
}
void CREATE(database* d,char* key,int value)
{
	node* t;
	t = new_node(value, key);
	t->next = NULL;
	d->tail->next = t;
	d->tail = t;
}
void READ(database* d, char* key)
{
	node* ptr;
	ptr = d->head->next;
	while (ptr->next != NULL || d->tail == ptr) {
		if (keyidentical(ptr->key, key) == true) {
			/*printf("value: %d\n", ptr->value);*/
			break;
		}
		ptr = ptr->next;
		if (ptr == NULL) {
			printf("There's no %s in database\n", key);
			break;
		}
	}
}


