#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 1000
#define RECORD_COUNT 500
#define PHONE_LENGTH 12

typedef struct {
	char phone[PHONE_LENGTH];
	char *name;
	char *address;
} Record;

typedef struct HashNode {
	Record *record;
	struct HashNode *next;
} HashNode;

typedef struct {
	HashNode *table;
} HashTable;

HashTable *initHashTable() {
	HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
	hashTable->table = (HashNode *)malloc(TABLE_SIZE * sizeof(HashNode));
	
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable->table[i].record = NULL;
		hashTable->table[i].next = NULL;
	}
	
	return hashTable;
}

unsigned int hash(char *key) {
	unsigned int hash = 0;
	while (*key) {
		hash = (hash * 31) + *key;
		key++;
	}
	return hash % TABLE_SIZE;
}

void insertLinearProbing(HashTable *hashTable, char *phone, char *name, char *address) {
	Record *record = (Record *)malloc(sizeof(Record));
	strncpy(record->phone, phone, PHONE_LENGTH);
	record->name = strdup(name);
	record->address = strdup(address);
	
	unsigned int index = hash(phone);
	
	while (hashTable->table[index].record != NULL) {
		index = (index + 1) % TABLE_SIZE;
	}
	
	hashTable->table[index].record = record;
}

void insertQuadraticProbing(HashTable *hashTable, char *phone, char *name, char *address) {
	Record *record = (Record *)malloc(sizeof(Record));
	strncpy(record->phone, phone, PHONE_LENGTH);
	record->name = strdup(name);
	record->address = strdup(address);
	
	unsigned int index = hash(phone);
	unsigned int originalIndex = index;
	int i = 1;
	
	while (hashTable->table[index].record != NULL) {
		index = (originalIndex + i * i) % TABLE_SIZE;
		i++;
	}
	
	hashTable->table[index].record = record;
}

void insertChaining(HashTable *hashTable, char *phone, char *name, char *address) {
	Record *record = (Record *)malloc(sizeof(Record));
	strncpy(record->phone, phone, PHONE_LENGTH);
	record->name = strdup(name);
	record->address = strdup(address);
	
	unsigned int index = hash(phone);
	
	if (hashTable->table[index].record == NULL) {
		hashTable->table[index].record = record;
	} else {
		HashNode *current = &hashTable->table[index];
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = (HashNode *)malloc(sizeof(HashNode));
		current->next->record = record;
		current->next->next = NULL;
	}
}

Record *searchLinearProbing(HashTable *hashTable, char *phone) {
	unsigned int index = hash(phone);
	
	while (hashTable->table[index].record != NULL && strcmp(hashTable->table[index].record->phone, phone) != 0) {
		index = (index + 1) % TABLE_SIZE;
	}
	
	if (hashTable->table[index].record != NULL && strcmp(hashTable->table[index].record->phone, phone) == 0) {
		return hashTable->table[index].record;
	} else {
		return NULL;
	}
}

Record *searchQuadraticProbing(HashTable *hashTable, char *phone) {
	unsigned int index = hash(phone);
	unsigned int originalIndex = index;
	int i = 1;
	
	while (hashTable->table[index].record != NULL && strcmp(hashTable->table[index].record->phone, phone) != 0) {
		index = (originalIndex + i * i) % TABLE_SIZE;
		i++;
	}
	
	if (hashTable->table[index].record != NULL && strcmp(hashTable->table[index].record->phone, phone) == 0) {
		return hashTable->table[index].record;
	} else {
		return NULL;
	}
}

Record *searchChaining(HashTable *hashTable, char *phone) {
	unsigned int index = hash(phone);
	
	HashNode *current = &hashTable->table[index];
	while (current != NULL) {
		if (current->record != NULL && strcmp(current->record->phone, phone) == 0) {
			return current->record;
		}
		current = current->next;
	}
	
	return NULL;
}

float calculateCollisionRate(HashTable *hashTable) {
	int collisionCount = 0;
	
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable->table[i].record != NULL) {
			int currentIndex = i;
			int nextIndex = (currentIndex + 1) % TABLE_SIZE;
			
			while (hashTable->table[nextIndex].record != NULL && nextIndex != i) {
				collisionCount++;
				nextIndex = (nextIndex + 1) % TABLE_SIZE;
			}
		}
	}
	
	return (float)collisionCount / TABLE_SIZE;
}

float calculateAverageSearchLength(HashTable *hashTable, char **keys, int keyCount, Record *(*searchFunction)(HashTable *, char *)) {
	float totalSearchLength = 0;
	
	for (int i = 0; i < keyCount; i++) {
		char *key = keys[i];
		Record *result = searchFunction(hashTable, key);
		if (result != NULL) {
			unsigned int index = hash(key);
			unsigned int originalIndex = index;
			
			while (hashTable->table[index].record != NULL && strcmp(hashTable->table[index].record->phone, key) != 0) {
				index = (index + 1) % TABLE_SIZE;
			}
			
			totalSearchLength += (index - originalIndex + TABLE_SIZE) % TABLE_SIZE + 1;
		}
	}
	
	return totalSearchLength / keyCount;
}

void freeHashTable(HashTable *hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		HashNode *currentNode = hashTable->table[i].next;
		
		while (currentNode != NULL) {
			HashNode *nextNode = currentNode->next;
			free(currentNode);
			currentNode = nextNode;
		}
	}
	
	free(hashTable->table);
	free(hashTable);
}

int main() {
	HashTable *hashTableLinearProbing = initHashTable();
	HashTable *hashTableQuadraticProbing = initHashTable();
	HashTable *hashTableChaining = initHashTable();
	
	char *names[] = {"John", "Jane", "Bob", "Alice", "Charlie", "David", "Eva", "Frank", "Grace", "Henry"};
	char *addresses[] = {"123 Main St", "456 Oak St", "789 Elm St", "101 Pine St", "202 Maple St", "303 Cedar St", "404 Birch St", "505 Walnut St", "606 Spruce St", "707 Pine St"};
	
	char *keys[RECORD_COUNT];
	for (int i = 0; i < RECORD_COUNT; i++) {
		char phone[PHONE_LENGTH];
		sprintf(phone, "555-%04d", i);
		keys[i] = strdup(phone);
		
		insertLinearProbing(hashTableLinearProbing, phone, names[i % 10], addresses[i % 10]);
		insertQuadraticProbing(hashTableQuadraticProbing, phone, names[i % 10], addresses[i % 10]);
		insertChaining(hashTableChaining, phone, names[i % 10], addresses[i % 10]);
	}
	
	float collisionRateLinearProbing = calculateCollisionRate(hashTableLinearProbing);
	float collisionRateQuadraticProbing = calculateCollisionRate(hashTableQuadraticProbing);
	float collisionRateChaining = calculateCollisionRate(hashTableChaining);
	
	float averageSearchLengthLinearProbing = calculateAverageSearchLength(hashTableLinearProbing, keys, RECORD_COUNT, searchLinearProbing);
	float averageSearchLengthQuadraticProbing = calculateAverageSearchLength(hashTableQuadraticProbing, keys, RECORD_COUNT, searchQuadraticProbing);
	float averageSearchLengthChaining = calculateAverageSearchLength(hashTableChaining, keys, RECORD_COUNT, searchChaining);
	
	printf("Linear Probing:\n");
	printf("Collision Rate: %f\n", collisionRateLinearProbing);
	printf("Average Search Length: %f\n", averageSearchLengthLinearProbing);
	
	printf("\nQuadratic Probing:\n");
	printf("Collision Rate: %f\n", collisionRateQuadraticProbing);
	printf("Average Search Length: %f\n", averageSearchLengthQuadraticProbing);
	
	printf("\nChaining:\n");
	printf("Collision Rate: %f\n", collisionRateChaining);
	printf("Average Search Length: %f\n", averageSearchLengthChaining);
	
	freeHashTable(hashTableLinearProbing);
	freeHashTable(hashTableQuadraticProbing);
	freeHashTable(hashTableChaining);
	
	return 0;
}

