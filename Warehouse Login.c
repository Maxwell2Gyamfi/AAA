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

int main()
{
	//local variables
	int choice = 0;
	int count = 0;

	//allocate memory for user accounts
	userdetails *users = (userdetails*)calloc(MAX_ACCOUNTS, sizeof(userdetails));
	count = read_users_file(users, "all_users.txt");


	do
	{
		system("cls");//clear screen
		main_display_menu();
		//action selection menu
		choice = get_valid_integer(1, 3);
		switch (choice)
		{
		case 1:
			count == 0 ? printf("\nThere are no accounts in the system"), Pause() :
				(count = login(users, count));
			break;
		case 2:
			create_account(&count, users);
			save_users_files(users, count, "all_users.txt");
			Pause();
			break;
		default:
			printf("\nQuitting!!!");
			Pause();
			break;
		}
	} while (choice != 3);
	//free dynaically allocated memory
	free(users);
	return 0;
}
/**************************************************************************
* Function Name: main_display_menu()
*
* Funtion Description:
*   -This function displays the main menu of the program prompting the user
*    to select an option between, login with email and password and create
*    a new user account.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays main menu
****************************************************************************/
void main_display_menu()
{
	printf("\n\n");
	printf("               WAREHOUSE SYSTEMS MAIN MENU\n");
	printf("               ---------------------------\n");
	printf("  1 ---> Login with email and password\n");
	printf("  2 ---> Create a new account\n");
	printf("  3 ---> Exit program\n\n");
	printf("---> Select an option(1-3): ");
}
/******************************************************************************************
* Function Name: Pause()
*
* Funtion Description:
*   This function pauses the screen prompting the user to press any key to proceed
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): pauses screen
******************************************************************************************/
void Pause()
{

	printf("\n\nPress any key to continue...");
	getch();

}
