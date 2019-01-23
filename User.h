#pragma once
#include "Linked_list.h"
#include "Prototypes.h"
#include "Validators.h"

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
/***************************************************************************************
* Function Name: create_account(int *count,struct User *new_user)
*
* Funtion Description:
*   -This function allows a client to create a new account if not present in the system
*   -It requests user eamil, password and sets the first account as admin.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- int *count,struct User *new_user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): creates a new user account
***************************************************************************************/
int create_account(int *count, struct User *new_user)
{
	//local variables
	char ptr[20];
	char password[20];
	int flag = 0;
	int id = 0;

	system("cls");
	printf("\n\n");
	printf("            CREATE A NEW ACCOUNT MENU\n");
	printf("            -------------------------\n");
	printf(" ---> Input email: ");
	get_valid_email(*count, new_user, 0, ptr);

	//request correct password input
	while (flag == 0)
	{
		printf(" ---> Input password: ");
		get_valid_password(ptr);
		printf("\n ---> Re-input password: ");
		get_valid_password(password);
		if (strcmp(ptr, password) == 0)flag = 1;
		else printf("\nInputted password didn't match!!\n");
	}
	//encrypt password
	cipher_password(ptr, new_user[*count].user_email, password, 0);
	strcpy(new_user[*count].user_password, password);

	//sets first account as admin
	if (*count == 0)
	{
		new_user[*count].is_admin = 1;
		new_user[*count].login_attempts = 3;
		printf("\nFirst account in system as a result, admin account");
		printf("\nPlease contact developer('Maxwell2.Gyamfi@live.uwe.ac.uk')if wish to change");
	}
	else
	{
		new_user[*count].is_admin = 0;
		new_user[*count].login_attempts = 3;
	}
	//assign unique id and increment count
	new_user[*count].user_id = *count + 100;
	new_user[*count].is_suspended = 0;
	new_user[*count].total_items = 0;
	*count = *count + 1;


	printf("\nAccount created successfully!!!");
}
/***************************************************************************************
* Function Name:  read_users_file(struct User *users,char *name)
*
* Funtion Description:
*   -This function reads a text file containing data into record data type Struct User.
*   -It then returns the number of items read.
*
* User-interface variables:-
*	*OUT (Return values):
*			- i(amount of data read)
*	*IN (Value Parameters):
*			- struct User *users,char *name
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): reads data from txt file
******************************************************************************************/
int read_users_file(struct User *users, char *name)
{
	//local variables
	FILE *file;
	int i = 0;
	char s = 0;
	file = fopen(name, "rb");
	if (file == NULL)
	{
		return 0;
	}
	while (s = fgetc(file))
	{
		if (s == EOF)//breaks if end of file character read
		{
			break;
		}
		else
		{
			fseek(file, -1, SEEK_CUR);//sets the file position of the stream to the given offset
			fread(&users[i], sizeof(userdetails), 1, file);//reads text file data to struct User
			i++;
		}
	}
	fclose(file);
	return i;
}
/***************************************************************************************
* Function Name:  save_users_files(struct User *users, int count,char*name)
*
* Funtion Description:
*   -This function saves users deatils to a text file
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- struct User *users, int count,char*name
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): saves data to txt file
******************************************************************************************/
void save_users_files(struct User *users, int count, char*name)
{
	//local variables
	int i = 0;
	FILE *file;
	file = fopen(name, "wb");
	if (file == NULL)
	{
		printf("Error saving to file");
		exit(0);
	}
	//loop and save users to file
	for (i = 0; i < count; i++)
	{
		fwrite(&users[i], sizeof(struct User), 1, file);
	}
	fclose(file);
}
/***************************************************************************************
* Function Name:  login(struct User *user, int count)
*
* Funtion Description:
*   -This function allows a user to login into the system by requesting an email address
*    and a unique user password. If user present in the system and password correct, the
*    user will be either presented with Admin/User Menu.
*  - If user present and incorrect password, the user will be provided with a list of
*    choices to make in order to proceed.
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- count(number of users)
*	*IN (Value Parameters):
*			- struct User *user, int count
*	*IN and OUT (Reference Parameters):
*			- struct User *user, int count
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): login system with password and email
******************************************************************************************/
int login(struct User *user, int count)
{
	//local variables
	int option = 0;
	int position = 0;
	int success = 0;
	char pswd[20];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	userdetails *ptr = &user[0];

	//set array values to 0
	memset(email, 0, sizeof(email));
	memset(password, 0, sizeof(password));
	memset(pswd, 0, sizeof(pswd));

	do
	{
		system("cls");//clear screen
		printf("\n\n");
		printf("          LOGIN MENU\n");
		printf("          ----------\n");
		printf("\n ---> Input email: ");
		get_valid_email(count, user, 1, email);//request and sanitize email address

		position = valid_login_email(user, count, email);//get user position in array
		if (position >= 0 && user[position].login_attempts > 0 && user[position].is_suspended == 0)
		{
			do
			{
				printf(" ---> Input password(attempts remaining:%d): ", user[position].login_attempts);
				get_valid_password(password);//request and sanitize password
				cipher_password(password, user[position].user_email, pswd, 0);//encrypt password
				if (strcmp(user[position].user_password, pswd) == 0)
				{
					if (user[position].is_admin == 1)
					{
						count = admin_account(user, count);//login as admin
					}
					else
					{
						count = user_menu(user, count, position);//login as user

					}
					ptr[position].login_attempts = 3;//resets login attempts
					success = 1;
					break;
				}
				else
				{
					//decrement login attempts
					ptr[position].login_attempts -= 1;
					save_users_files(user, count, "all_users.txt");//save updated list of users to file
					if (ptr[position].login_attempts == 0)
					{
						ptr[position].is_suspended = 1;//suspend user if attempts = 0

						if (position > 0)
						{
							printf("\nThis account is banned, please contact an admin(%s)", user[0].user_email);
						}
						else if (position ==0)
						{
							printf("\nAdmin account is banned, please contact developer('Maxwell2.Gyamfi@live.uwe.ac.uk')");
						}
						Pause();
						break;
					}
					system("cls");
					printf("\n\n");
					printf("      PASSWORD INPUT\n");
					printf("      --------------\n");
					printf("\nEmail : %s", user[position].user_email);
					printf("\nIncorrect password(attempts remaining:%d)\n", user[position].login_attempts);
					printf("\n  ---> 1. Try again");
					printf("\n  ---> 2. Send password to email");
					printf("\n  ---> 3. Return to Login Menu");
					printf("\n\n Select an option(1-3): ");
					option = get_valid_integer(1, 3);//sanitize user selection
					if (option == 2)
					{
						send_email(user, position);//send email
						break;
					}

				}
				success = 1;
			} while (user[position].login_attempts > 0 && option != 3);
		}
		else
		{
			//checks if user suspended and display account banned message
			if (position == 0 && user[0].is_suspended == 1)
			{
				printf("\nAdmin account banned,please contact developer'Maxwell2.Gyamfi@live.uwe.ac.uk");
			}
			else if (user[position].login_attempts == 0 && user[position].is_suspended == 1)
			{
				printf("\nThis account is banned, please contact an admin(%s)", user[0].user_email);
				Pause();
				success = 1;
			}
			else
			{
				printf("\nInputted email is not in the system");
				Pause();
				return count;
			}
		}

	} while (success == 0);
	save_users_files(user, count, "all_users.txt");//save updated list of users to file
	return count;
}
/***************************************************************************************
* Function Name:  valid_login_email(struct User *user, int count,char *email)
*
* Funtion Description:
*   -This function returns the position of the email address if present in the system,
*    otherwise returns -1 as email not found as position 0 is occupied by admin
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- email address position
*	*IN (Value Parameters):
*			- struct User *user, int count,char *email
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): returns position of email address in the system
******************************************************************************************/
int valid_login_email(struct User *user, int count, char *email)
{

	int i = 0;

	//checks the presence of email in the system
	for (i = 0; i < count; i++)
	{
		if (strcmp(user[i].user_email, email) == 0)
		{
			return i;
		}
	}
	return -1;
}
/***************************************************************************************
* Function Name:  admin_account_menu()
*
* Funtion Description:
*   -This function displays the menu of admin account
*
* User-interface variables:-
*	*OUT (Return values):
*			- email address position
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays admin account menu
******************************************************************************************/
void admin_account_menu()
{
	system("cls");
	printf("\n\n");
	printf("             ADMIN MENU\n");
	printf("             ----------\n");
	printf("  1 ---> Switch to user Mode\n");
	printf("  2 ---> Display all users accounts\n");
	printf("  3 ---> Search a user account\n");
	printf("  4 ---> Suspend a user account\n");
	printf("  5 ---> Remove account from suspended list\n");
	printf("  6 ---> Change Password\n");
	printf("  7 ---> Return to main menu\n");
	printf("\nSelect an option(1-7): ");

}
/***************************************************************************************
* Function Name:  admin_account_menu()
*
* Funtion Description:
*   -This function displays the menu of admin account
*
* User-interface variables:-
*	*OUT (Return values):
*			- count
*	*IN (Value Parameters):
*			- struct User *users, int count
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays admin account menu
******************************************************************************************/
int admin_account(struct User *users, int count)
{
	//local variable
	int choice = 0;

	do
	{
		admin_account_menu();
		choice = get_valid_integer(1, 7);//request user choice
		switch (choice)
		{
		case 1:
			count = user_menu(users, count, 0);	//displays user menu	
			break;
		case 2:
			merge_sort(users, 0, count - 1);//merge sorts users based on id
			display_all_accounts(users, count);
			Pause();
			break;
		case 3:
			//sort and sort user by id
			merge_sort(users, 0, count - 1);
			binary_search_account(users, count - 1);
			Pause();
			break;
		case 4:
			suspend_user(users, count);
			Pause();
			break;
		case 5:
			unsuspend_user(users, count);
			Pause();
			break;
		case 6:
			change_password(users, 0);//changes password
			Pause();
			break;
		default:
			break;
		}
	} while (choice != 7);
	return count;
}
/***************************************************************************************
* Function Name:  display_all_accounts(struct User *users,int count)
*
* Funtion Description:
*   -This function displays all the users accounts present in the system
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- struct User *users,int count
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays all accounts in the system
******************************************************************************************/
void display_all_accounts(struct User *users, int count)
{
	//local variables
	char buffer[20];
	memset(buffer, 0, 20);
	int i = 0;
	char admin = 0;
	char password[20];

	system("cls");
	printf("\n\n");
	printf("                   DISPLAY ALL ACCOUNTS\n");
	printf("                   --------------------\n");
	if (count == 0)
	{
		printf("\nThere are no accounts to display");
		return;
	}

	printf("ID   Email                Password         Admin      Suspended       Total Items\n");
	printf("--   -----                --------         -----      ---------       -----------\n");

	for (i = 0; i < count; i++)
	{
		if (users[i].is_suspended == 1)
			strcpy(buffer, "True");
		else
			strcpy(buffer, "False");
		if (users[i].is_admin == 1)
			admin = 'Y';
		else
			admin = 'N';

		cipher_password(users[i].user_password, users[i].user_email, password, 1);//decrypts password
		printf("%-4d %-20s %-16s %-10c %-16s%-4d\n",
			users[i].user_id,
			users[i].user_email,
			password,
			admin, buffer, users[i].total_items);
	}
}
/***************************************************************************************
* Function Name: binary_search_account(struct User *user, int count)
*
* Funtion Description:
*   -This function Search a sorted array by repeatedly dividing the search interval in half.
	-It begins with an interval covering the whole array.
	-If the value of the id is less than the item in the middle of the interval,
	  narrow the interval to the lower half. Otherwise narrow it to the upper half.
	- Repeatedly check until the value is found or the interval is empty.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- struct User *users,int count
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): binary search user account
******************************************************************************************/
void binary_search_account(struct User *user, int count)
{
	//local variables
	int value = 0;
	int start = 0;
	int half = 0;
	int end = count;
	int success = 0;
	char buffer[20];
	char admin;
	char password[20];
	memset(buffer, 0, 20);

	system("cls");
	printf("\n\n");
	printf("        SEARCH A USER MENU\n");
	printf("        ------------------\n");
	printf(" ---> Input user ID: ");
	value = get_valid_integer(1, 30000);

	while (start <= end)
	{
		//finds midde of array
		half = (start + end) / 2;

		// If the element is present at the middle itself 
		if (user[half].user_id == value)
		{
			if (user[half].is_suspended == 1)
				strcpy(buffer, "True");
			else
				strcpy(buffer, "False");
			if (user[half].is_admin == 1)
				admin = 'Y';
			else
				admin = 'N';

			cipher_password(user[half].user_password, user[half].user_email, password, 1);//decrypts password

			printf("\nID   Email                Password         Admin      Suspended       Total Items\n");
			printf("--   -----                --------         -----      ---------       -----------\n");
			printf("%-4d %-20s %-16s %-10c %-16s%-4d\n",
				user[half].user_id,
				user[half].user_email,
				password,
				admin, buffer, user[half].total_items);

			success = 1;
			break;
		}
		else
		{
			// If element is smaller than mid, then 
			// it can only be present in left subarray 
			if (value > user[half].user_id)
			{
				start = half + 1;
			}
			//Else the element can only be present
			// in right subarray 
			else
			{
				end = half - 1;
			}
		}
	}
	if (success == 0)
	{
		printf("Element not found");
	}
}
/***************************************************************************************
* Function Name: merge_sort(struct User *user, int min, int max)
*
* Funtion Description:
*   -This function is a divide and conquer algorithm.
*   -It first finds the middle point of the list, and recursively divide the list
*    until at the bottom there are only two elements left.
*   -It compares the elements and swap their indexes.
*   -It returns te sorted list once the lenght is less than or 1
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- struct User *user, int min, int max
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): merge sort array
******************************************************************************************/
int merge_sort(struct User *user, int min, int max)
{

	int middle;

	if (min < max)
	{
		middle = (min + max) / 2;//calculate middle value

		//sort first and second halves
		merge_sort(user, min, middle);
		merge_sort(user, middle + 1, max);
		merge(user, min, middle, middle + 1, max);//merge halves back into one
	}

}
/***************************************************************************************
* Function Name: merge(struct User *user, int min, int middle, int middle2, int max)
*
* Funtion Description:
*   This function traverse both arrays and in each iteration add smaller of both
*   elements in temp array
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int min, int middle, int middle2, int max
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): merge arrays halves back
******************************************************************************************/
void merge(struct User *user, int min, int middle, int middle2, int max)
{
	struct User temp[MAX_ACCOUNTS];
	//local variables
	int l = 0;
	int i = min;
	int j = middle2;

	// traverse both arrays and in each iteration add smaller of both elements in temp
	while (i <= middle && j <= max)
	{
		if (user[i].user_id < user[j].user_id)//compare ids
		{
			temp[l++] = user[i++];
		}
		else
		{
			temp[l++] = user[j++];
		}
	}
	// add elements left in the first interval 
	while (i <= middle)
	{
		temp[l++] = user[i++];
	}
	// add elements left in the second interval 
	while (j <= max)
	{
		temp[l++] = user[j++];
	}
	// copy temp to original interval
	for (l = min, j = 0; l <= max; l++, j++)
	{
		user[l] = temp[j];
	}
}
/***************************************************************************************
* Function Name: suspend_user(struct User *user, int count)
*
* Funtion Description:
*   This function allows the admin of the system to suspend a desired user account
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int count
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): suspends a user
******************************************************************************************/
void suspend_user(struct User *user, int count)
{
	//local variables
	int i = 0;
	int id = 0;
	char choice = 0;
	struct User *temp = user;//pointer to struct user

	system("cls");
	printf("\n\n");
	printf("              SUSPEND A USER ACCOUNT\n");
	printf("              -----------------------\n");
	if (count > 1)
	{
		//display all accounts and request selection
		display_all_accounts(user, count);
		printf("\nSelect account to suspend(%d-%d): ", user[1].user_id, user[count - 1].user_id);
		id = get_valid_integer(user[1].user_id, user[count - 1].user_id);

		for (i = 0; i < count; i++)
		{
			if (id == user[i].user_id)
			{
				printf("\nConfirm suspending account?(Y/N): ");
				choice = get_valid_yes_or_no();
				if (choice == 'Y')
				{
					user = user + i;//pointer aritmetic
					user->is_suspended = 1;//suspend user
					user->login_attempts = 0;
					display_all_accounts(temp, count);
					printf("\nAccount succesfully suspended!!!");
					break;
				}
				else
				{
					printf("\nAccount not suspended!!!");
				}
			}
		}
	}
	else
	{
		printf("\nImpossible suspending admin account.\nPlease contact a developer('Maxwell2.Gyamfi@live.uwe.ac.uk')");
	}

}
/***************************************************************************************
* Function Name: unsuspend_user(struct User *user, int count)
*
* Funtion Description:
*   This function allows the admin of the system to unsuspend a desired user account
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int count
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): unsuspends a user
******************************************************************************************/
void unsuspend_user(struct User *user, int count)
{

	//local variables
	int i = 0;
	int id = 0;
	char choice = 0;
	int suspended_counter = 0;
	//memory allocation for array of suspended list
	struct User *suspended_list;
	struct User *temp = user;

	system("cls");
	printf("\n\n");
	printf("              UNSUSPEND A USER ACCOUNT\n");
	printf("              -------------------------\n");

	if (count <= 1)
	{
		printf("\nThere are no accounts to be unsuspended");
		return;
	}
	else
	{
		suspended_list = (struct User*)calloc(MAX_ACCOUNTS, sizeof(struct User));
		{
			if (suspended_list == NULL)
			{
				printf("Error allocating memory");
				return;
			}
		}
		for (i = 0; i < count; i++)
		{
			if (user[i].is_suspended == 1 && user[i].login_attempts == 0)
			{
				//adds suspended users to suspended list
				suspended_list[suspended_counter++] = user[i];
			}
		}
		if (suspended_counter > 0)
		{
			//displays all suspended users and request selection
			display_all_accounts(suspended_list, suspended_counter);
			printf("\nSelect account to unsuspend(%d-%d): ", suspended_list[0].user_id, suspended_list[suspended_counter - 1].user_id);
			id = get_valid_integer(suspended_list[0].user_id, suspended_list[suspended_counter - 1].user_id);

			if (id_exist(suspended_list, suspended_counter, id))
			{
				for (i = 0; i < count; i++)
				{
					if (id == user[i].user_id)
					{
						printf("\nConfirm unsuspending account?(Y/N): ");
						choice = get_valid_yes_or_no();
						if (choice == 'Y')
						{
							user += i;//pointer aritmetic
							user->is_suspended = 0;
							user->login_attempts = 3;
							display_all_accounts(temp, count);
							printf("\nAccount succesfully unsuspended!!!");
							break;
						}
						else
						{
							printf("\nAccount was not unsuspended");
							break;
						}
					}
				}
			}
			else printf("\nIncorrect Account ID selection!!!");
		}
		else printf("\nThere are no accounts to be unsuspended!!!");
		free(suspended_list);//free block of memory allocated
	}
}
/***************************************************************************************
* Function Name: id_exist(struct User*banned, int count,int id)
*
* Funtion Description:
*   This function checks if a user account is suspended by comparing the id to the ids of
*   banned list array
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- struct User*banned, int count,int id
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks if a user is on suspended list
******************************************************************************************/
int id_exist(struct User*banned, int count, int id)
{
	//local variables
	int i = 0;

	//loop and check if account is suspended
	for (i = 0; i < count; i++)
	{
		if (banned[i].user_id == id)
		{
			return 1;
		}
	}
	return 0;
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
/***************************************************************************************
* Function Name: user_account_menu()
*
* Funtion Description:
*   This function displays the main menu of the users account
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
* 2019-17-01 (Maxwell Gyamfi): displays user account menu
******************************************************************************************/
void user_account_menu()
{
	system("cls");//clears screen
	printf("\n\n            USER MENU\n");
	printf("            ---------\n\n");
	printf("  1  ---> Add an Item\n");
	printf("  2  ---> View all items\n");
	printf("  3  ---> Search an Item\n");
	printf("  4  ---> Delete an Item\n");
	printf("  5  ---> Change password\n");
	printf("  6  ---> Delete account\n");
	printf("  7  ---> Return to Main Menu");

}
/******************************************************************************************
* Function Name: user_menu(struct User *user,int count,int position)
*
* Funtion Description:
*   This function allows a user to select an option of user.
*   At first it will check if the user has any previous records in the system. If yes then
*   it will display the user account menu to the user prompting for a selection, otherwise
*   it will load the default file of the warehouse, containing warehouse items.
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- count
*	*IN (Value Parameters):
*			- int count,int position
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): displays user account menu
******************************************************************************************/
int user_menu(struct User *user, int count, int position)
{
	linked_list_items *head = NULL;
	//loads default file if first time accessing system
	if (!read_items_from_file(&head, user[position].user_email))
	{
		load_default_file(&head);
	}
	int choice = 0;

	do
	{
		update_total_elements(head, user, position);//counts amount of elements present in system
		user_account_menu();
		printf("\n\nInput your choice(1-7): ");
		choice = get_valid_integer(1, 7);

		switch (choice)
		{
		case 1:
			append(&head);//allows to add new item to warehouse
			update_total_elements(head, user, position);
			Pause();
			save_items_to_file(head, user[position].user_email);//save warehouse items to file and rename with user email
			break;
		case 2:
			mergesort(&head),//merge sort linked list nodes
				display_items(head);
			Pause();
			break;
		case 3:
			search_item(head);
			Pause();
			break;
		case 4:
			delete_item(&head);//delete nodes
			update_total_elements(head, user, position);
			Pause();
			save_items_to_file(head, user[position].user_email);
			break;
		case 5:
			change_password(user, position);
			Pause();
			break;
		case 6:
			count = remove_account(user, count, position, &head);//remove user account from system
			Pause();
			if (position != 0)//quits and returns to main menu if user deletes account
			{
				return count;
			}
			break;
		}
	} while (choice != 7);
	free_linked_list_items(&head);//free block of memory allocated
	return count;
}
/*******************************************************************************
* Function Name: change_password(struct User *user,int position)
*
* Funtion Description:
*   -This function allows a user to modify an existing password.
*    It will first request current password from user and if it matches it
*    will then give them the possiblity to change password requestig a new one.
*   -It displays appropriate error mesage if incorrect password provided
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int position
*	*IN and OUT (Reference Parameters):
*			- struct User *user
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): changes user password
*********************************************************************************/
void change_password(struct User *user, int position)
{
	//local variables
	char buffer[20];
	char ptr[20];
	int flag = 0;
	char password[20];

	system("cls");//clear screen
	printf("\n\n");
	printf("          CHANGE PASSWORD MENU\n");
	printf("          --------------------\n");


	printf("Input previous password: ");
	get_valid_password(buffer);
	cipher_password(buffer, user[position].user_email, password, 0);//encypts password input

	if (strcmp(password, user[position].user_password) == 0)//compare passwords
	{
		while (flag == 0)
		{
			//request new password and compare
			printf("\n ---> Input new password: ");
			get_valid_password(ptr);
			printf("\n ---> Re-input password: ");
			get_valid_password(buffer);

			if (strcmp(ptr, buffer) == 0)
			{
				cipher_password(ptr, user[position].user_email, buffer, 0);//encrypts password
				strcpy(user[position].user_password, buffer);//saves new password
				printf("\nPassword successfully changed!!!");
				flag = 1;
			}
			else printf("\nInputted password didn't match, try again: ");
		}
	}
	else
	{
		printf("\nIncorrect password!!!");
	}
}
/********************************************************************
* Function Name: send_email(struct User *user, int position)
*
* Funtion Description:
*   -This function sends an email to a user email-address in case they
*    forgot their password.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- struct User *user, int position
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): sends email to user email address
***********************************************************************/
void send_email(struct User *user, int position)
{
	//local varaibles
	char password[20];
	char cmd[100];
	char to[20];
	char body[20];
	char tempFile[100];     // name of tempfile.
	cipher_password(user[position].user_password, user[position].user_email, password, 1);

	strcpy(body, password);
	strcpy(to, user[position].user_email);
	strcpy(tempFile, tempnam("/tmp", "sendmail"));

	FILE *fp = fopen(tempFile, "w"); // open it for writing.
	fprintf(fp, "%s\n", body);        // write body to it.
	fclose(fp);             // close it.

	sprintf(cmd, "sendmail %s < %s", to, tempFile); // prepare command.
	system(cmd);     // execute it.


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
