#pragma once
#include "Validators.h"
#include "User.h"
/******************************************************************************
* Function Name: check_item_number_duplicate(linked_list_items *head,
				 int item_number)
*
* Funtion Description:
*   -This function checks if an item id exists already in the system before a
*    user can decide to utilize as an item number
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- linked_list_items *head,int item_number
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for item number duplicate
*********************************************************************************/
int check_item_number_duplicate(linked_list_items *head, int item_number)
{

	linked_list_items *current = head;//pointer to head

	while (current != NULL)
	{
		if (current->item.item_number == item_number)//compare item number
		{
			printf("\nAn item with number '%d' is already in the system,try again: ", item_number);
			return 1;
		}
		current = current->next;
	}

	return 0;
}
/***************************************************************************
* Function Name: load_default_file(linked_list_items** head)
*
* Funtion Description:
*   -This function reads data from a file named default.txt which contains
*    sample example of warehouse items. Display error message and quits if
*    default file fails to open, otherwise read string line by line, split
*    string based on specified delimeter and read into linked list head
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- linked_list_items **head
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): loads default file into program
*****************************************************************************/
int load_default_file(linked_list_items** head)
{
	//local variables
	FILE *file;
	char *token;
	char *rest;
	char buffer[60];
	struct Items new_item;
	int i = 0;

	memset(buffer, 0, sizeof(buffer));//set array elements to 0
	file = fopen("default.txt", "rb");//read data from file

	if (file == NULL)//display error message and quit if file not found
	{
		printf("Error default file was not found!!");
		Pause();
		exit(0);
	}
	while (fgets(buffer, sizeof(buffer), file))//reads line from file stream and store in buffer array
	{
		rest = buffer;//pointer to buffer array
		while ((token = strtok_s(rest, ",", &rest)))//splits string based on delimeter and stores in token
		{
			i++;
			//converts token to appropriate data-type,store into variable and into linked list head
			if (i == 1)sscanf(token, "%d", &new_item.item_number);
			else if (i == 2)snprintf(new_item.item_description, sizeof(new_item.item_description), "%s", token);
			else sscanf(token, "%f", &new_item.item_price), i = 0, insert(new_item, head);

		}

	}
}
/********************************************************************
* Function Name: free_linked_list_items(linked_list_items **head)
*
* Funtion Description:
*   -This function frees linked list memory allocated for each
*    structure item. This is done to avoid memory leakage
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- linked_list_items **head
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): free block of memory allocated
***********************************************************************/
void free_linked_list_items(linked_list_items **head)
{
	linked_list_items *temp;//pointer to hold current head
	linked_list_items *current = *head;//pointer to deferenced head
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);//release block of memory
	}
}
/******************************************************************************************
* Function Name: save_items_to_file(linked_list_items *item,char *account_email)
*
* Funtion Description:
*   This function saves linked list node items into a text file
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items *item,char *account_email
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): save items to file
******************************************************************************************/
void save_items_to_file(linked_list_items *item, char *account_email)
{
	FILE *file;
	items user_item;
	linked_list_items *head = item;
	file = fopen(account_email, "wb");//open file 
	if (file == NULL)
	{
		printf("Error writing to file");
		exit(0);
	}
	while (head != NULL)
	{
		user_item = head->item;//save item local variable
		fwrite(&user_item, sizeof(items), 1, file);//write data to file
		head = head->next;
	}
	fclose(file);

}
/******************************************************************************************
* Function Name: read_items_from_file(linked_list_items **item, char *account_email)
*
* Funtion Description:
*   This function reads data from file and inserts them into linked list node
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- count
*	*IN (Value Parameters):
*			- char *account_email
*	*IN and OUT (Reference Parameters):
*			- linked_list_items **item
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): save items to file
******************************************************************************************/
int read_items_from_file(linked_list_items **item, char *account_email)
{
	//local varaibles
	FILE *file;
	char *s;
	int count = 0;
	items user_item;

	file = fopen(account_email, "rb");//open file

	if (file == NULL)
	{
		return 0;
	}

	//while end of file character not reached, read data and insert to linked list
	while (s = fgetc(file))
	{
		if (s == EOF)
		{
			break;
		}
		else
		{
			fseek(file, -1, SEEK_CUR);//avoid reading past eof character
			fread(&user_item, sizeof(items), 1, file);
			insert(user_item, item);//insert item at end of linked list
			count++;
		}
	}
	fclose(file);
	return(count > 0 ? 1 : 0);
}
/******************************************************************************************
* Function Name: insert(items user_items, linked_list_items **item)
*
* Funtion Description:
*   This function inserts read data from text file back into linked list nodes.
*   if there are no nodes in linked then the item is the first node itself otherwise,
*   traverse linked list until NULL reached and append item.
*
*
* User-interface variables:-
*	*OUT (Return values):
*			-NONE
*	*IN (Value Parameters):
*			- items user_items
*	*IN and OUT (Reference Parameters):
*			- linked_list_items **item
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): insert read items to linked list
******************************************************************************************/
void insert(items user_items, linked_list_items **item)
{

	linked_list_items * new_linked_list = malloc(sizeof(linked_list_items));//allocate memory
	linked_list_items *last = *item;

	if (new_linked_list == NULL)
	{
		printf("Error allocating memory");
		exit(0);
	}

	new_linked_list->item = user_items;//add item to new linked list
	new_linked_list->next = NULL;

	if (*item == NULL)
	{
		*item = new_linked_list;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_linked_list;
}
/*************************************************************************************
* Function Name: linked_list_items * sortedmerge(linked_list_items* a,
				 linked_list_items* b)
*
* Funtion Description:
*   -This function takes two lists sorted in increasing order, and splices
*    their nodes together to make one big sorted list which
*    is returned.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items* a, linked_list_items* b
*	*IN and OUT (Reference Parameters):
*			- result
*
* History [Date (Author): Description)]:-
* 2019-17-01 (geeksforgeeks.org): merges the two list halves
************************************************************************************/
linked_list_items * sortedmerge(linked_list_items* a, linked_list_items* b)
{
	linked_list_items* result = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (a->item.item_number <= b->item.item_number)
	{
		result = a;
		result->next = sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next);
	}
	return result;
}
/*************************************************************************************
* Function Name: frontbacksplit(linked_list_items* head, linked_list_items** aref,
*                linked_list_items** bref)
*
* Funtion Description:
*   -This function splits the nodes of the given list into front and back halves,
	 and return the two lists using the reference parameters.
	-If the length is odd, the extra node should go in the front list.
	 Uses the fast/slow pointer strategy.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items* head
*	*IN and OUT (Reference Parameters):
*			- linked_list_items** aref, linked_list_items** bref
*
* History [Date (Author): Description)]:-
* 2019-17-01 (geeksforgeeks.org): splits the node into front and back halves
************************************************************************************/
void frontbacksplit(linked_list_items* head, linked_list_items** aref, linked_list_items** bref)
{
	linked_list_items* slow;
	linked_list_items* fast;
	if (head == NULL || head->next == NULL)
	{
		*aref = head;
		*bref = NULL;
	}
	else
	{

		slow = head;
		fast = head->next;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		/* 'slow' is before the midpoint in the list, so split it in two
		   at that point. */
		*aref = head;
		*bref = slow->next;
		slow->next = NULL;
	}
}
/*************************************************************************************
* Function Name: mergesort(linked_list_items** headref)
*
* Funtion Description:
*   -This function sorts linked list by changing next pointers(not data)
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- linked_list_items** headref
*
* History [Date (Author): Description)]:-
* 2019-17-01 (geeksforgeeks.org): sorts linked list
************************************************************************************/
void mergesort(linked_list_items** headref)
{
	linked_list_items* head = *headref;
	linked_list_items* a;
	linked_list_items* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
		return;
	/* Split head into 'a' and 'b' sublists */
	frontbacksplit(head, &a, &b);

	/* Recursively sort the sublists */
	mergesort(&a);
	mergesort(&b);
	//answer = merge the two sorted lists together
	*headref = sortedmerge(a, b);
}
/*************************************************************************************
* Function Name: search_item(linked_list_items* head)
*
* Funtion Description:
*   -This function allows a user to search for an item accross the warehouse.
*   -Displays 'item not found' if item non-existent otherwise displays item-number,
*    description and price
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items* head
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): searchs item accross warehouse
************************************************************************************/
void search_item(linked_list_items* head)
{
	int item_number = 0;
	linked_list_items * current = head;//pointer to linked list head
	system("cls");
	printf("\n\n      SEARCH AN ITEM MENU\n");
	printf("       -------------------\n");

	printf("---> Input item to be searched(1-30000): ");
	item_number = get_valid_integer(1, 30000);//request item number

	while (current != NULL)
	{
		if (current->item.item_number == item_number)//compares item number
		{
			printf("\nItem Number              Item Description                         Item Price\n");
			printf("-----------              ----------------                         ----------\n");
			printf("%-25d%-41s%c %5.1f\n",
				current->item.item_number, current->item.item_description, POUND_SIGN, current->item.item_price);
			return;
		}
		current = current->next;//change current head
	}
	printf("\nItem not found!!!");
	return;


}
/*************************************************************************************
* Function Name: delete_item(linked_list_items** head)
*
* Funtion Description:
*   -This function allows a user to select items and delete from warehouse.
*   -It will first clear the output console and display all items prompting
*    user to select an item.
*   -It checks if head node itself holds the item number of item to be deleted.
*    In case it does it changes head and free old head.
*   -If item was not found it displays 'item not found message and returns,otherwise
*    it will keep looking for item until found.
*   -Finally it will display all items proving item was successfully deleted.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int position
*	*IN and OUT (Reference Parameters):
*			- linked_list_items** head
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): deletes item from warehouse
************************************************************************************/
void delete_item(linked_list_items** head)
{
	//local variables
	int itemnumber = 0;
	char *choice = '\0';
	linked_list_items *previous = NULL;
	linked_list_items *current = *head;//dereference and store head node

	system("cls");//clear screen
	printf("\n\n");
	printf("  DELETE AN ITEM MENU\n");
	printf("  -------------------");

	display_items(current);
	printf("\nSelect item to be removed: ");
	itemnumber = get_valid_integer(1, 30000);//sanitize user input

	//checks if head node itself holds the item number of item to be deleted
	if (current != NULL && current->item.item_number == itemnumber)
	{
		printf("Confirm removing selected item?(Y/N): ");
		choice = get_valid_yes_or_no();////ensure user choice of deleting
		if (choice == 'Y')
		{
			*head = current->next;//change head
			free(current);//free old head
			display_items(*head);
			printf("\nSelected item successfully removed!!!");
			return;
		}
		else
		{
			printf("\nSelected item was not removed!!!");
			return;
		}
	}

	// Search for the item to be deleted, keep track of the 
	// previous node as we need to change 'prev->next'
	while (current != NULL && current->item.item_number != itemnumber)
	{
		previous = current;
		current = current->next;
	}

	//display message and return if item not found
	if (current == NULL)
	{
		printf("Item was not found");
		return;
	}

	printf("\nConfirm removing selected item?(Y/N): ");
	choice = get_valid_yes_or_no();//ensure user choice of deleting
	if (choice == 'Y')
	{
		//unlink node from linked list
		previous->next = current->next;
		free(current);//free memory
		display_items(*head);
		printf("\nSelected item successfully removed!!!");
		return;
	}
	else
	{
		printf("\nSelected item was not removed!!!");
		return;
	}

}
/******************************************************************************************
* Function Name: user_menu(struct User *user,int count,int position)
*
* Funtion Description:
*   This function allows a user add a new item to the warehouse.
*   It requests an item number checking for duplicates, item description and price.
*   It then appends the new item to the linked list head
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- linked_list_items **linked
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): adds new item to warehouse
******************************************************************************************/
void append(linked_list_items **linked)
{
	linked_list_items * new_linked_list = malloc(sizeof(linked_list_items));
	linked_list_items *last = *linked;
	linked_list_items *start = *linked;
	linked_list_items *temp = *linked;
	items item;

	if (new_linked_list == NULL)
	{
		printf("Error allocating memory");
		exit(0);
	}

	system("cls");
	printf("\n\n");
	printf("        ADD NEW ITEM MENU\n");
	printf("        -----------------\n");

	//request item details
	printf("\nInput item number(1-30000): ");
	item.item_number = get_valid_integer(1, 30000);
	while (check_item_number_duplicate(temp, item.item_number))//check for item number duplicate
	{
		item.item_number = get_valid_integer(1, 30000);
		check_item_number_duplicate(temp, item.item_number);
	}

	printf("Input item description(max char:40): ");
	get_valid_string(item.item_description);

	printf("Input item price(1-9999999): ");
	item.item_price = get_valid_integer(1, 9999999);

	new_linked_list->item = item;//ads item to linked list

	new_linked_list->next = NULL;//set mext to NULL as appending to end
	if (*linked == NULL)//if there are no nodes then add item
	{
		*linked = new_linked_list;
		display_items(start);
		printf("\nItem added successfully!!!");
		Pause();
		return;
	}

	while (last->next != NULL)//while last node not reached,move to next
	{
		last = last->next;
	}
	last->next = new_linked_list;
	display_items(start);
	printf("\nItem added successfully!!!");


}
/******************************************************************************************
* Function Name: update_total_elements(linked_list_items *head,struct User
		   *user,int position)
*
* Funtion Description:
*   This function the calculates total amount of elements in a warehouse
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items *head,int position
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): calculates number of elements in linked list
******************************************************************************************/
void update_total_elements(linked_list_items *head, struct User *user, int position)
{
	int total_elements = 0;

	while (head != NULL)
	{
		head = head->next;
		total_elements++;
	}
	//change value of total elements at position in array
	user[position].total_items = total_elements;
}
/******************************************************************************************
* Function Name: display_items(linked_list_items * start)
*
* Funtion Description:
*   This function displays the items in the warehouse
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- linked_list_items * start
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays items in the warehouse
******************************************************************************************/
void display_items(linked_list_items * start)
{

	system("cls");//clear screen
	printf("\n\n");
	printf("                  DISPLAY ALL ITEMS\n");
	printf("                  -----------------\n");
	if (start == NULL)
	{
		printf("\nThere are no items to be displayed");
		return;
	}
	else
	{
		printf("\nItem Number              Item Description                         Item Price\n");
		printf("-----------              ----------------                         ----------\n");
		//display item details
		while (start != NULL)
		{
			printf("%-25d%-41s%c %5.1f\n",
				start->item.item_number, start->item.item_description, POUND_SIGN, start->item.item_price);
			start = start->next;
		}
	}

}
/***************************************************************************************
* Function Name: remove_account(struct User *users, int count,int position,
*                linked_list_items**head)
*
* Funtion Description:
*   This function allows the user of the system to permanently remove a account from
*   the system.
*   It denies permission if the admin of the system tries to delete their own account
*   otherwise it will request confirmation of the user deleting their account and if
*   they decide to carry on, it will free all heads of linked list items,removed user
*   text file from system, push the user in the array to the edge and reduce the number
*   of system users by 1.
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- count
*	*IN (Value Parameters):
*			- int position,int count
*	*IN and OUT (Reference Parameters):
*			- struct User *users,linked_list_items**head
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): removes user account from system
******************************************************************************************/
int remove_account(struct User *users, int count, int position, linked_list_items**head)
{
	//local variables
	int status = 0;
	int i = 0;
	char choice = '\0';
	int old_position = position;
	userdetails temp;
	userdetails *ptr = &users[0];

	if (position == 0)
	{
		printf("\nAdmin account cannot be removed,\nPlease contact developer('Maxwell2.Gyamfi@live.uwe.ac.uk')");
		return count;
	}

	printf("\nConfirm removing your account?(Y/N): ");
	choice = get_valid_yes_or_no();
	if (choice == 'Y')
	{
		free_linked_list_items(head);//free block of memory allocated
		status = remove(users[position].user_email);//remove user file
		//push user account to edge of array
		while (position < count)
		{
			temp = ptr[position];
			ptr[position] = ptr[position + 1];
			ptr[position + 1] = temp;
			position++;
		}
		count -= 1;
		save_users_files(users, count, "all_users.txt");//save updated users back to file
		printf("\nAccount removed successfully!!!!");
	}
	else
	{
		printf("\nAccount not removed");
	}
	return count;
}

