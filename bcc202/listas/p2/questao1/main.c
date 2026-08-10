#include <stdio.h>
#include "list.h"

int main() {
	List *list = createList();

	for (int i = 0; i < 5; i++)
		insertList(list, i + 1);

	printList(list);
	tradePositions(list, 0);

	printList(list);

	return 0;
}
