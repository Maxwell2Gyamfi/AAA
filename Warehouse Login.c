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
*          -Change Password
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
*           in the system.
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
#include "Prototypes.h"
#include "Validators.h"
#include "Linked_list.h"
#include "User.h"

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

