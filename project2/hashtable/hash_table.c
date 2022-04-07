/*
 Student Name: Gracen Wallace
 Date: 03/29/19

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf

/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
	//allocate space for new entry
	HashTableEntry* newNode=(HashTableEntry*)malloc(sizeof(HashTableEntry));
	if(!newNode) return NULL;

	//assign values to entry's struct variables
	newNode->value=value;
	newNode->key=key;
	newNode->next=NULL;

	//return pointer to new entry
	return newNode;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
	//hash(key) returns index of bucket to be used, while this_node->key returns associated key of that node in the bucket
	int index=hashTable->hash(key);
	HashTableEntry* thisNode=(hashTable->buckets[index]);
	while((thisNode != NULL) && (thisNode->key != key)) {
		thisNode=(thisNode->next);
	}
	return thisNode;
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specifiedi in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
/**
 * createHashTable
 *
 * Creates a hash table by allocating memory for it on the heap. Initialize num_buckets
 * and hash based on function arguments. Allocate memory for buckets as an array of
 * pointers to HashTableEntry objects based on the number of buckets available.
 * Each bucket contains a singly linked list, whose nodes are HashTableEntry objects.
 *
 * @param myHashFunc The pointer to the custom hash function.
 * @param numBuckets The number of buckets available in the hash table.
 * @return a pointer to the new hash table
 *
 * The createHashTable is provided for you as a starting point.
 */
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
	// The hash table has to contain at least one bucket. Exit gracefully if this condition is not met.
	if (numBuckets==0) {
		printf("Hash table has to contain at least 1 bucket...\n");
		exit(1);
	}

  	// Allocate memory for the new HashTable struct on heap.
  	HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  	// Initialize the components of the new HashTable struct.
  	newTable->hash = hashFunction;
  	newTable->num_buckets = numBuckets;
  	newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  	// As the new buckets contain indeterminant values, init each bucket as NULL.
  	unsigned int i;
  	for (i=0; i<numBuckets; ++i) {
    		newTable->buckets[i] = NULL;
  	}

  	// Return the new HashTable struct.
  	return newTable;
}

/**
 * destroyHashTable
 *
 * Destroy the hash table. The nodes (HashTableEntry objects) of singly linked
 * list, the values stored on the linked list, the buckets, and the hashtable
 * itself are freed from the heap. In other words, free all the allocated memory
 * on heap that is associated with heap, including the values that users store in
 * the hash table.
 *
 * @param myHashTable The pointer to the hash table.
 */
void destroyHashTable(HashTable* hashTable) {
  //iterate through buckets using an index
	int maxBuckets=hashTable->num_buckets;

	for(int index=0;index<maxBuckets;index++) {
		//declare pointer to head of bucket
		HashTableEntry* thisNode=hashTable->buckets[index];
		if(!thisNode) continue;
		//pointer to next so loop can still iterate after deleting this_node
		HashTableEntry* nextNode=thisNode->next;
		//iterate through each node in the bucket
		while(thisNode != NULL) {
			//free value separately since its type is unknown
			free(thisNode->value);
			//free node
			free(thisNode);
			//increment nodes
      if(nextNode != NULL) {
        thisNode=nextNode;
  			nextNode=nextNode->next;
      }
      else  break;
		}
	}

	free(hashTable);
	return;
}

/**
 * insertItem
 *
 * Insert the value into the hash table based on the key.
 * In other words, create a new hash table entry and add it to a specific bucket.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the value.
 * @param value The value to be stored in the hash table.
 * @return old value if it is overwritten, or NULL if not replaced
 */
void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
  HashTableEntry* thisNode=findItem(hashTable,key);
  HashTableEntry** buckets=hashTable->buckets;
  HashFunction hash=hashTable->hash;
  //EDGE CASE: overwrite
  if(thisNode) {
    void* prevValue=thisNode->value;
    thisNode->value=value;
    return prevValue;
  }
  //EDGE CASE: new node in previous bucket, place at head
  HashTableEntry* newNode=createHashTableEntry(key,value);
  if(!newNode) return NULL;
  newNode->next=buckets[hash(key)];
  buckets[hash(key)]=newNode;
  return NULL;
}

/**
 * getItem
 *
 * Get the value that corresponds to the key in the hash table.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 * @return the value corresponding to the key, or NULL if the key is not present
 */
void* getItem(HashTable* hashTable, unsigned int key) {
	//EDGE CASE: key exists in hashtable, return value
	HashTableEntry* thisNode=findItem(hashTable,key);
	if(thisNode) {
    return thisNode->value;
  }
	else {
    return NULL;
  }
	//EDGE CASE: key is not present, return NULL
}

/**
 * removeItem
 *
 * Remove the item in hash table based on the key and return the value stored in it.
 * In other words, return the value and free the hash table entry from heap.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 * @return the pointer of the value corresponding to the key, or NULL if the key is not present
 */
void* removeItem(HashTable* hashTable, unsigned int key) {
  //EDGE CASE: node does not exist in hashTable
	if(!findItem(hashTable,key)) return NULL;
	//EDGE CASE: node exists in hashTable
	HashTableEntry* thisNode=hashTable->buckets[hashTable->hash(key)];
	void* remvdValue;
	//EDGE CASE: delete head
	if(thisNode->key == key) {
		remvdValue=thisNode->value;
		hashTable->buckets[hashTable->hash(key)]=thisNode->next;
    //free node and return value
    free(thisNode);
    return remvdValue;
	}
	//EDGE CASE: delete value not at head
	while(thisNode->next) {
		if(thisNode->next->key==key) {
      //spliced out node while still saving pointer to deleted node
			HashTableEntry* temp=thisNode->next;
			remvdValue=temp->value;
			thisNode->next=thisNode->next->next;
      //free node and return value
    	free(temp);
    	return remvdValue;
		}
		//increment to next node in bucket
		thisNode=thisNode->next;
	}
  return NULL;
}

/**
 * deleteItem
 *
 * Delete the item in the hash table based on the key. In other words, free the
 * value stored in the hash table entry and the hash table entry itself from
 * the heap.
 *
 * @param myHashTable The pointer to the hash table.
 * @param key The key that corresponds to the item.
 *
 */
void deleteItem(HashTable* hashTable, unsigned int key) {
  //EDGE CASE: node does not exist in hashTable
  if(!findItem(hashTable,key)) return;
  //EDGE CASE: node exists in hashTable
  HashTableEntry* thisNode=hashTable->buckets[hashTable->hash(key)];
  //EDGE CASE: delete head
  if(thisNode->key == key) {
    hashTable->buckets[hashTable->hash(key)]=thisNode->next;
    //free node and value
    free(thisNode->value);
    free(thisNode);
    return;
  }
  //EDGE CASE: delete value not at head
  while(thisNode->next) {
    if(thisNode->next->key==key) {
      //spliced out node while still saving pointer to deleted node
      HashTableEntry* temp=thisNode->next;
      thisNode->next=thisNode->next->next;
      //free node and value
      free(temp->value);
      free(temp);
      return;
    }
    //increment to next node in bucket
    thisNode=thisNode->next;
  }
  return;
}
