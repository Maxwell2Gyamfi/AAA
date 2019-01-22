/*******************************************************************************************
* Program Description:
*    -This program will allow a client to manage precious items disposed in a warehouse.
*     At the start of the program the user will be presented with the Main Menu which
*     will allow them either to create a new account or login with their credentials.
*
* Main functionalities are:
*    -Login with Email and Password:if successfully logged in, will be presented with the
*     main warehouse systems menu(Admin/User mode).
*
*    -Admin Mode Functionalities consists of :
*	   -Switch to User Mode
*	   -Display all users accounts
*	   -Search a user account
*	   -Suspend a user account
*	   -Remove account from suspended list
*      -Change Password
*
*     -User Mode Functionalities consists of:
*      -Add an Item to warehouse
*	   -View all warehouse items
*	   -Search an Item in warehouse
*	   -Delete an Item from warehouse
*	   -Change personal password
*	   -Delete personal account
*
*	   -Create new account: which allows user to create a new account if not present
*       in the system.
*
* User-interface variables:-
*	   *OUT (Return values):
*			- int : Success indicator (0 failure, 1 success)
*	   *IN (Value Parameters):
*			- Uses Value Parameters
*	   *IN and OUT (Reference Parameters):
*			- Uses Reference Parameters
*
* History [Date (Author): Description)]:-
*   2019-17-01 (Maxwell Gyamfi): Warehouse Login Systems
*******************************************************************************************/

//disables visual studio default functions
#pragma warning(disable:4996)

// Standard C library header files (#include ....):
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Validators.h"
#include "Linked List.h"
#include "User.h"

//definitions
#define EMAIL_LENGHT 20
#define PASSWORD_LENGHT 15
#define MAX_LENGHT_DESCRIPTION 40
#define MAX_ACCOUNTS 9999
#define POUND_SIGN 156

//Record data-types declarations
typedef struct Items
{
	int item_number;
	char item_description[MAX_LENGHT_DESCRIPTION];
	float item_price;

}items;

//Record data-types declarations
typedef struct User
{
	int user_id;
	char user_email[EMAIL_LENGHT];
	char user_password[PASSWORD_LENGHT];
	int is_admin;
	int login_attempts;
	int is_suspended;
	int total_items;

}userdetails;

//Record data-types declarations
typedef struct Items_linked_list
{
	items item;
	struct Items_linked_list *next;

}linked_list_items;
