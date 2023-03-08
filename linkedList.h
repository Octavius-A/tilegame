#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	void* data;
	struct ListNode* next;
	struct ListNode* prev;
} ListNode;

typedef struct List {
	int size;
	ListNode* head;
	ListNode* tail;
} List;

List* newList();
void append(List* list, void* data);
void removeItem(List* list, int index);
void* getItem(List* list, int index);