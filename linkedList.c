#include "linkedList.h"

List* newList() {
	List* list = (List*)malloc(sizeof(List));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void append(List* list, void* data) {
	ListNode* n = (ListNode*)malloc(sizeof(ListNode));
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	if (list->size == 0) {
		list->head = n;
		list->tail = list->head;
	}
	else {
		list->tail->next = n;
		n->prev = list->tail;
		list->tail = n;
	}
	
	list->size += 1;
}

void removeItem(List* list, int index) {
	if (index < list->size) {
		ListNode* n = list->head;
		if (index == 0) {
			// delete head.
			if (list->size > 1) {
				ListNode* tmp = list->head->next;
				free(list->head);
				list->head = tmp;
			}
			else {
				free(list->head);
			}
		}
		else {
			for (int i = 0; i < index; ++i) {
				n = n->next;
			}
			ListNode* next = n->next;
			ListNode* prev = n->prev;

			prev->next = next;
			next->prev = prev;
			free(n);
		}
	}
}

void* getItem(List* list, int index) {
	if (index > list->size - 1) {
		return NULL;
	}

	ListNode* n = list->head;
	if (index == 0) {
		void* data = n->data;
		return data;
	}

	else {
		for (int i = 0; i < index; ++i) {
			n = n->next;
		}
		void* data = n->data;
		return data;
	}
}