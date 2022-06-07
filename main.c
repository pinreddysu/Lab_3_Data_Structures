#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 30

typedef struct node {   // node is the struct name
  char data[size];// data holds an integer value for the linked list node
  int rep;
  struct node *next;    // self-referential pointer declaration (MUST USE struct node
                        // rather than node_t since node_t has not been encountered
                        // yet in the type definition)
} node_t;

void print_list (node_t *head);
node_t * create_node (char word[], int freq, node_t *ptr);
void insert (node_t **head, char word[], int num);
int search(node_t *ptr, char word[],node_t **prev, node_t **cur);
void selectionSort(node_t* head);
void file_func(node_t *head);
void concordance_wo_stop(node_t *head);
void deleteNode(node_t **head, char word[]);
/*
 AUTHOR: Suchith Pinreddy,Yash Nikumb
 FILENAME: problem1.c
 SPECIFICATION: The problem basically creates a file containing the number of unique words, the number of unique words, and the number of times each unique word appears in the text file
 FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    FILE *infile;
    char s[30];
    infile = fopen("C:/Users/pinre/Downloads/CS_2413/text.txt","r");
    node_t *head2 = NULL;
    while(fscanf(infile,"%s",s)==1){
        for(int i =0;i<=strlen(s);i++){
            if(s[i]>=65&&s[i]<=90)
                s[i]=s[i]+32;
                }
            if(!(s[strlen(s)-1]>='a'&&s[strlen(s)-1]<='z')){
                s[strlen(s)-1]='\0';
            }
        insert(&head2,s,0);
    }
    selectionSort(head2);
    //print_list(head2);
    file_func(head2);
    concordance_wo_stop(head2);
    /*printf("\nThe List with memory addresses:\n");
    node_t *cur1;
    cur1 =head2;
    node_t *cur;
    cur = head2;
    printf("The list head address:  %p\n",head2);
    int i = 0;
    while (cur1 != NULL){
        i++;
        cur1 = cur1->next;
    }
    printf("There are %d distinct words in text file\n",i);
    while (cur != NULL) {
        printf("address:  %p   data:  %s  data2: %d next: %p\n",cur,cur->data,cur->rep,cur->next);
        cur = cur->next; // cur = (*cur).next;
  }*/
}
/* NAME: file_func(node_t *head)
 PARAMETERS: node_t *head
 PURPOSE: It print outs the concordance file
 PRECONDITION: Should be an address and a pointer
 POSTCONDITION: prints the concordance file address and single pointer.
*/
void file_func(node_t *head){
    node_t *cur1;
    cur1 =head;
    node_t *cur;
    cur = head;
    FILE *fp;
    int i = 0;
    while (cur1 != NULL){
        i++;
        cur1 = cur1->next;
    }
    fp = fopen("concordance.txt","w");
    fprintf(fp,"There are %d distinct words in the text file:\n",i);
    fclose(fp);
    FILE *outfile2;
    outfile2 = fopen("concordance.txt", "a");
    while (cur != NULL) {
        fprintf(outfile2,"%s  %d \n",cur->data,cur->rep);
        cur = cur->next; // cur = (*cur).next;
  }
  fclose(outfile2);

}
/* NAME: file_func_wo_stopwords(node_t *head)
 PARAMETERS: node_t *head
 PURPOSE: Prints the wordstop
 PRECONDITION: Should be an address pointer
 POSTCONDITION:The file should print the stopwords
*/
void file_func_wo_stopwords(node_t *head){
    node_t *cur1;
    cur1 =head;
    node_t *cur;
    cur = head;
    FILE *fp;
    int i = 0;
    while (cur1 != NULL){
        i++;
        cur1 = cur1->next;
    }
    fp = fopen("concordance_wo_stop_words.txt","w");
    fprintf(fp,"There are %d distinct words in the text file:\n",i);
    fclose(fp);
    FILE *outfile2;
    outfile2 = fopen("concordance_wo_stop_words.txt", "a");
    while (cur != NULL) {
        fprintf(outfile2,"%s  %d \n",cur->data,cur->rep);
        cur = cur->next; // cur = (*cur).next;
  }
  fclose(outfile2);

}
/* NAME: print_list
 PARAMETERS: node_t *head
 PURPOSE: The purpose of the function is to print the list
 PRECONDITION: What should be true regarding the parameters and when the function can be called
 POSTCONDITION: What should be true after the function returns, such as variables changed or values returned
*/
void print_list (node_t *head) {
  printf("\nThe List is:\n");
  node_t *cur;
  cur = head;
  if (cur == NULL)
    printf("  Empty\n");//head in search to access to list // pointer to use to increment think it like array //swap data and rec calls// node swapping i->
  else {
    while (cur != NULL) {
      printf("  %s\n",cur->data); //address of head store structure of a which makes pointing to data and next
      cur = cur->next; // cur = (*cur).next;
    }
  }
}

/* create_node dyanmically allocates a list node, initializes it,
 *   and returns the new node's memory address
 */
node_t * create_node (char word[], int freq, node_t *ptr) { //end of list comes first
  node_t *newp = malloc(sizeof(node_t)); // newp is intialized to structure
  //newp -> data = malloc(strlen(word)+1);  //char pointer will require separate memory allocation
  strncpy(newp -> data,word, size);
  newp->data[strlen(word)] = '\0';
  //newp->data = word;
  newp->rep = 1;
  newp->next = ptr;
  //printf("node date %s", newp->data);
  return (newp); //returns address   pointers think of memory and
}

/* insert inserts the value in integer parameter num at the end of the list
 *
 * Note:  head is a node_t ** which means
 *          head contains the memory address of the list head
 *          *head contains the memory address of the first node in the list
 *          **head is the first node in the list
 */
 /* NAME: insert
 PARAMETERS: node_t **head, char word[], int num
 PURPOSE: The function inserts the nodes in the linked list
 PRECONDITION: should pass a pointer address string of words and a integer value
 POSTCONDITION: Creates the link list
*/
void insert (node_t **head, char word[], int num) { //pointer to pointer since address is being inputted.
  // dynamically allocate the list node and initialize it to num and NULL

  node_t *cur;
  node_t *prev;
  //search(*head,word,&prev,&cur);
  if (search(*head,word,&prev,&cur)){
    cur->rep++;
  }
  else{
    node_t *newp = create_node(word,1,NULL);
    if(prev==NULL){
        *head = newp;
    }
    else{
        newp->next=cur;
        prev->next=newp;
    }
  }
/*
  //printf("\n%p\n",*head);
  //printf("\n%p\n",newp);            //stores previous add of head
  if (*head == NULL) {            // check for an empty list
    *head = newp;                 // set head to newp
  }
  else {
    cur = *head;
    //printf("\n%p\n",cur);
    while (cur->next != NULL)     // traverse to the last node in the list
        cur = cur->next;
    cur->next = newp;             // set the last node's next pointer to newp
  }
  */
}
/* NAME: computeAvg
 PARAMETERS: L, list of numbers
 PURPOSE: The function computes the average of the list of numbers given as input
 PRECONDITION: What should be true regarding the parameters and when the function can be called
 POSTCONDITION: What should be true after the function returns, such as variables changed or values returned
*/
int search (node_t *head, char word[], node_t **prev, node_t **cur) {
  int found = 0;
  *prev = NULL;
  *cur = head;
  while (*cur != NULL && strncmp((*cur)->data,word,strlen(word)) != 0) {
    *prev = *cur;
    *cur = (*cur)->next;
  }
  if (*cur != NULL)
    found = 1;
  return (found);
}
/* NAME: SlectionSort
 PARAMETERS: node_t *head
 PURPOSE: The function sorts the words
 PRECONDITION: The precondition shoul be an address pointer as an actual parameter
 POSTCONDITION:The words will be sorted in alphabetical order
*/
void selectionSort(node_t * head)
{
    char x[size];
	node_t* temp = head;

	// Traverse the List
	while (temp) {
		node_t* min = temp;
		node_t* r = temp->next;

		// Traverse the unsorted sublist
		while (r) {
			if (strncmp(min->data, r->data,size)>0)
				min = r;

			r = r->next;
		}

		// Swap Data
		strncpy(x,temp->data,size);
		x[strlen(x)]='\0';
		int y = temp->rep;
		strncpy(temp->data, min->data,size);
		temp->data[strlen(temp->data)]='\0';
		temp->rep=min->rep;
		strncpy(min->data, x,size);
		min->data[strlen(min->data)]='\0';
		min->rep = y;
		temp = temp->next;
	}
}
/* NAME: concordance_wo_stop
 PARAMETERS: node_t *head
 PURPOSE: The function computes the average of the list of numbers given as input
 PRECONDITION: What should be true regarding the parameters and when the function can be called
 POSTCONDITION: What should be true after the function returns, such as variables changed or values returned
*/
void concordance_wo_stop(node_t *head){
    FILE *infile;
    char s[30];
    infile = fopen("C:/Users/pinre/Downloads/CS 2413/stopwords.txt","r");
    while(fscanf(infile,"%s",s)==1){
        deleteNode(&head, s);
    file_func_wo_stopwords(head);
    }

    node_t *cur1;
    cur1 = head;
    while (cur1 != NULL) {
        printf("address:  %p   data:  %s  data2: %d next: %p\n",cur1,cur1->data,cur1->rep,cur1->next);
        cur1 = cur1->next; // cur = (*cur).next;
}
}
/* NAME: deleteNode
 PARAMETERS: node_t **head, char word[
 PURPOSE: Deletion of the node
 PRECONDITION: The parameter should be a Char string and an address pointer
 POSTCONDITION: Delete the node for a specific word
*/
void deleteNode(node_t **head, char word[])
{
    // Store head node
    node_t *temp = *head, *prev;

    // If head node itself holds the key to be deleted

    if (temp != NULL && strncmp(temp ->data,word,size)==0) {
        *head = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && strncmp(temp ->data, word,size)!=0) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}
/*
Student name: 1.) Suchith Pinreddy - Sorting and searching the words in the txt files and debugging the program.
                -Designed, implemented the following functions;
                int search(node_t *ptr, char word[],node_t **prev, node_t **cur);
                void selectionSort(node_t* head);
                void file_func(node_t *head);
                -Modified the following functions:
                void print_list (node_t *head);
                node_t * create_node (char word[], int freq, node_t *ptr);
                void insert (node_t **head, char word[], int num);
                2.) Yash Nikumb - Implemented the struct data type and the insertion, deletion and nulling the function. Running the test cases.
                -Designed, implemented the following:
                void print_list (node_t *head);
                node_t * create_node (char word[], int freq, node_t *ptr);
                void insert (node_t **head, char word[], int num);
                -Modified the following functions:
                int search(node_t *ptr, char word[],node_t **prev, node_t **cur);
                void selectionSort(node_t* head);
                void file_func(node_t *head);
text.txt and stopwords.txt – passed because the both files had the example outputs. file name text and stopwords.
2. text.txt with one word and empty stopwords.txt – passed because the concordance.txt file had this output
"There are 1 distinct words in the text file:
a  1 " file name text2 and stopwords2.
3. text.txt with one stop word and stopwords.txt with that stop word – passed because concordance_w_o_stop_words had this output in the file
"There are 0 distinct words in the text file:" file name text3 and stopwords3
4. empty text.txt and nonempty stopwords.txt – passed because both files had this output in the file
"There are 0 distinct words in the text file:" file name text4 and stopwords4.
5. text.txt with > 500 total words and stopwords.txt with > 10 total words – passed because both files are saved with the distinct words
concordance = "There are 205 distinct words in the text file:"
concordance_wo_stop_words = "There are 201 distinct words in the text file:" with all the elements. file name text5 and stopwords5.
2.) iii) 2) Worst case scenario: The worst case scenario for the program above will be O(n).
            1) Example; the last word in the text file will be the worst case scenario.
            3) The space complexity will be the addition of all the words in the text file.

Sources:
i) https://nam04.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.geeksforgeeks.org%2Flinked-list-set-3-deleting-node%2F&data=04%7C01%7Cspinredd%40ttu.edu%7C82fa4c5b9b9e45aa143508d9e84f3fc1%7C178a51bf8b2049ffb65556245d5c173c%7C0%7C0%7C637796249331280714%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwiLCJXVCI6Mn0%3D%7C3000&sdata=iTeT21m3LPdXeBWONHNKfMDWBa8yo4oECPSDaBuvGPw%3D&reserved=0
ii) https://www.geeksforgeeks.org/iterative-selection-sort-for-linked-list/
*/



