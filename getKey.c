#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <stdio.h>  
#include<time.h>
#include "data.h"
char* getKey(int digit)
{
	char key[4] = { 0 };
	char* keyptr=key;
	int i = 0;
	char table[52] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D'
	,'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	while (1) {
		int r = digit % 52;
		key[i] = table[r];
		i++;
		digit = digit / 52;
		if (digit == 0)
			break;
	}
	return keyptr;
}