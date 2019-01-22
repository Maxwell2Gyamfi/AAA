#pragma once
#include "Linked List.h"
#include "User.h"
/*******************************************************************************
* Function Name: get_valid_integer(int minimum, int maximum)
*
* Funtion Description:
*   -This function requests a user to input an integer value between a mini-
*    mum and a maximum. It will prompt the user to re-input integer value and
*    display a specific error message if wrong input provided. It returns
*    correct integer value if provided.
*
* User-interface variables:-
*	*OUT (Return values):
*			- int value
*	*IN (Value Parameters):
*			- int minimum, int maximum
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): gets valid integer input
*******************************************************************************/
int get_valid_integer(int minimum, int maximum)
{
	//local variables
	int sum = 0;
	int lenght = 0;
	int value = 0;
	int success = 0;
	char buffer[10];
	do
	{

		fgets(buffer, sizeof(buffer), stdin);//request string input
		lenght = get_string_length(buffer);//calculate string lenght
		buffer[lenght - 1] = '\0';
		lenght = lenght - 1;

		if (isfloat(buffer, lenght))//checks if float value
		{
			printf("\nYou entered a float value, please try again(%d-%d): ", minimum, maximum);
		}
		else if (!is_integer(buffer, lenght))//checks if special character inputted
		{
			printf("\nYou didnt enter an integer, please try again(%d-%d): ", minimum, maximum);
		}
		else
		{
			value = convert_string_to_integer(buffer, 0, lenght, sum);//convert value to integer
			if (value< minimum || value > maximum)//changes integer range
			{
				printf("\nThe value is out of range, try again(%d-%d): ", minimum, maximum);
			}
			else
			{
				success = 1;
				return value;
			}
		}

	} while (success == 0);

}

/********************************************************************
* Function Name: char get_valid_yes_or_no()
*
* Funtion Description:
*   -This function requests a user to input a character 'Y'or 'N'
*   -Display specific error message and request to re-input correct
*    input until provided. It will returns the correct character
*
* User-interface variables:-
*	*OUT (Return values):
*			- char input
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): gets valid yes or no
***********************************************************************/
char get_valid_yes_or_no()
{
	//local variables
	char input = 0;
	int success = 0;
	do
	{
		scanf("%c%*c", &input);//request character and discards scanf buffer
		if (isalpha(input))
		{
			input = toupper(input);//convert character to upper-case
			if (input == 'Y' || input == 'N')
			{
				success = 1;
			}
			else
			{
				printf("Wrong input, please input (Y/N): ");
			}
		}
	} while (success == 0);

	return input;
}

/********************************************************************
* Function Name: isfloat(char *string,int length)
*
* Funtion Description:
*   -This function checks if a '.' character is present in an array
*    of characters.
*
* User-interface variables:-
*	*OUT (Return values):
*			bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string,int length
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks if string has '.' value
***********************************************************************/
int isfloat(char *string, int length)
{
	//local variable
	int i = 0;

	//loops and look for '.' character
	for (i = 0; i < length; i++)
	{
		if (string[i] == '.')
		{
			return 1;
		}
	}
	return 0;
}

/********************************************************************
* Function Name: int is_integer(char *string,int length)
*
* Funtion Description:
*   -This function checks if an array of characters contains only
*    numeric values.
*
* User-interface variables:-
*	*OUT (Return values):
*			bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string,int length
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks if string has '.' value
***********************************************************************/
int is_integer(char *string, int length)
{
	//local variable
	int i = 0;

	//loops and checks if all characters in array are numeric
	for (i = 0; i < length; i++)
	{
		if (string[i] >= '0' && string[i] <= '9') {}
		else
		{
			return 0;
		}
	}
	return 1;
}

/********************************************************************
* Function Name: get_string_length(char *string)
*
* Funtion Description:
*   -This function calculates and returns the length of string
*
* User-interface variables:-
*	*OUT (Return values):
*			- int count
*	*IN (Value Parameters):
*			- char *string
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): calculates string length
***********************************************************************/
int get_string_length(char *string)
{
	//local variables
	int count = 0;
	int i = 0;

	//increment counts and i until reaches null character
	while (string[i] != '\0')
	{
		count++;
		i++;
	}
	return count;
}
/*************************************************************************************
* Function Name: convert_string_to_integer(char *string,int count,int lenght,int sum)
*
* Funtion Description:
*   -This function converts a string of integers into an integer value. It calls the
*    appropriate switch case based on the lenght and it sums the character with a
*    power of 10.
*
* User-interface variables:-
*	*OUT (Return values):
*			- int sum
*	*IN (Value Parameters):
*			- char *string,int count,int lenght,int sum
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): converts string to integer
***************************************************************************************/
int convert_string_to_integer(char *string, int count, int lenght, int sum)
{

	char arr_value = '\0';

	//action selection based on string length
	switch (lenght)
	{
	case 1:
		//sums array character with case power of 10 value
		sum = convert_character_to_integer(arr_value, string, sum, 1, count);
		return sum;
		break;
	case 2:
		sum = convert_character_to_integer(arr_value, string, sum, 10, count);
		//recursively call function with different array index and reduce string length
		convert_string_to_integer(string, count + 1, lenght - 1, sum);
		break;
	case 3:
		sum = convert_character_to_integer(arr_value, string, sum, 100, count);
		convert_string_to_integer(string, count + 1, lenght - 1, sum);
		break;
	case 4:
		sum = convert_character_to_integer(arr_value, string, sum, 1000, count);
		convert_string_to_integer(string, count + 1, lenght - 1, sum);
		break;
	case 5:
		sum = convert_character_to_integer(arr_value, string, sum, 10000, count);
		convert_string_to_integer(string, count + 1, lenght - 1, sum);
		break;
	case 6:
		sum = convert_character_to_integer(arr_value, string, sum, 100000, count);
		convert_string_to_integer(string, count + 1, lenght - 1, sum);
		break;
	default:
		sum = atoi(string);//converts character to integer
		return sum;
		break;
	}
}

/*************************************************************************************
* Function Name: convert_character_to_integer(char character, char *string, int sum,
				 int value,int count)
*
* Funtion Description:
*   -This function converts a single character based of array index to integer
*   -It then multiplys converted value to the power of 10 value based
*    on case selection and sums to sum variable

* User-interface variables:-
*	*OUT (Return values):
*			- int sum
*	*IN (Value Parameters):
*			- char character, char *string, int sum, int value,int count
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): converts character to integer
***************************************************************************************/
int convert_character_to_integer(char character, char *string, int sum, int value, int count)
{
	int number = 0;
	character = string[count];//gets character at array index
	number = character - '0';//converts character to integer
	sum += (number * value);//multiply number with power of 10 value and add to sum
	return sum;
}


/***************************************************************************************
* Function Name: void get_valid_password(char *password)
*
* Funtion Description:
*   -This function request a user to input a password.
*   -Will repeat and display specific error message if provided inuput does not meet
*    requirements.
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- char *password
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): gets valid password
******************************************************************************************/
void get_valid_password(char *password)
{
	//local variables
	int i = 0;
	int k = 0;
	int lenght = 0;
	char ch = '\0';
	char buffer[PASSWORD_LENGHT];

	int success = 0;
	do
	{
		k = 0;
		i = 0;
		memset(buffer, 0, sizeof(buffer));//sets array values to 0
		while (k < PASSWORD_LENGHT)
		{
			ch = getch();
			if (ch == '\r')//breaks if new line charater is inputted
			{
				break;
			}
			else if (ch == '\b')
			{
				if (i > 0)
				{
					i--;//removes backspace character from array
					k--;
					printf("\b \b");
				}
			}
			else
			{
				//masks password displaying '*' character
				buffer[i++] = ch;
				ch = '*';
				printf("%c", ch);
				k++;
			}
		}
		lenght = get_string_length(buffer);
		if (lenght > PASSWORD_LENGHT)//checks password length
		{
			printf("\nPassword is too long,try again: ");
		}
		else if (lenght < 8)
		{
			printf("\nPassword too short,try again: ");
		}
		else if (!hasdigit(buffer, lenght))//checks if integer present
		{
			printf("\nYour password should contain at least an integer,try again: ");
		}
		else if (!has_upper_case(buffer, lenght))//checks for uppercase
		{
			printf("\nYour password should contain at least an upper-case character,try again: ");
		}
		else
		{
			copy_string(buffer, password);
			success = 1;

		}

	} while (success == 0);
}

/***************************************************************************************
* Function Name: hasdigit(char *string,int lenght)
*
* Funtion Description:
*   -This function checks if a string contains a numberic value.
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string,int lenght
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for integer value
******************************************************************************************/
int hasdigit(char *string, int lenght)
{
	//local variable
	int i = 0;

	//loops and check for integer value
	for (i = 0; i < lenght; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			return 1;
		}
	}
	return 0;
}

/***************************************************************************************
* Function Name:  has_upper_case(char *string, int lenght)
*
* Funtion Description:
*   -This function checks if a string contains at least one upper-case alphabet value .
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string,int lenght
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for upper-case alphabet value
******************************************************************************************/
int has_upper_case(char *string, int lenght)
{
	//local variable
	int i = 0;

	//loops and checks for upper-case alphabet
	for (i = 0; i < lenght; i++)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
		{
			return 1;
		}
	}
	return 0;

}
/***************************************************************************************
* Function Name: get_valid_email(int number_of_accounts,
				 struct User *users,int login,char *email)
*
* Funtion Description:
*   -This function prompts a user to input a valid email address.It will display a speci-
*    fic error message and request input if wrong input is provided.
*   -Based on login value it will either copy correct email-value to char email or
	 struct *users
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- int number_of_accounts,struct User *users,int login
*	*IN and OUT (Reference Parameters):
*			- struct User *users,char *email
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): requests and check for valid email address
******************************************************************************************/
void get_valid_email(int number_of_accounts, struct User *users, int login, char *email)
{
	//local varaibles
	char buffer[EMAIL_LENGHT];
	int success = 0;
	int lenght = 0;

	do
	{
		//requests input 
		fgets(buffer, sizeof(buffer), stdin);
		lenght = get_string_length(buffer);
		buffer[lenght - 1] = '\0';
		lenght = lenght - 1;

		if (lenght > EMAIL_LENGHT)//checks string length
		{
			printf("\nEmail is too long,try again: ");
		}
		else if (!has_at_email(buffer, lenght))//checks for '@character'
		{
			printf("\nAn email has at least one '@' character,try again: ");
		}
		else if (!has_domain(buffer, lenght))//checks for correct domain
		{
			printf("\nYou inputted a wrong domain,try again: ");
		}
		else if (email_exist(users, number_of_accounts, buffer))//checks for email existence
		{
			if (login == 1)
			{
				copy_string(buffer, email);
				success = 1;
				break;
			}
			printf("\nYour inputted email exists already, try again: ");
		}
		else
		{
			copy_string(buffer, users[number_of_accounts].user_email);
			success = 1;
		}
	} while (success == 0);
}
/***************************************************************************************
* Function Name: has_at_email(char *string, int lenght)
*
* Funtion Description:
*   -This function checks if a string a has an '@' character
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string, int lenght
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for '@ ' character in string
******************************************************************************************/
int has_at_email(char *string, int lenght)
{
	//local variable
	int i = 0;

	//loops and checks for '@' character
	for (i = 0; i < lenght; i++)
	{
		if (string[i] == '@')
		{
			return 1;
		}
	}
	return 0;
}

/***************************************************************************************
* Function Name: has_domain(char *string, int lenght)
*
* Funtion Description:
*   -This function checks if a string has a correct email domain
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- char *string, int lenght
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for correct email domain
******************************************************************************************/
int has_domain(char *string, int lenght)
{
	//local variables
	int i = 0;
	int j = 0;
	char temp[20];
	char string_domain[25];

	//sets array values to 0;
	memset(temp, 0, sizeof(temp));
	memset(string_domain, 0, sizeof(string_domain));

	//email domains
	char domains[][25] = { "aol.com","att.net","comcast.net","facebook.com","gmail.com",
						 "gmx.com","googlemail.com","google.com","hotmail.com","hotmail.co.uk",
						 "mac.com","me.com", "mail.com","msn.com","live.com","sbcglobal.net",
						 "verizon.net","yahoo.com","yahoo.co.uk","email.com","fastmail.fm",
						 "games.com","gmx.net","hush.com", "hushmail.com","icloud.com",
						 "iname.com","inbox.com","lavabit.com","love.com","outlook.com",
						 "pobox.com","protonmail.com","rocketmail.com","safe-mail.net","wow.com",
						 "ygm.com","ymail.com","zoho.com","yandex.com","hotmail.it","btinternet.com",
						 "virginmedia.com","blueyonder.co.uk","freeserve.co.uk","live.co.uk",
						 "ntlworld.com","o2.co.uk","orange.net","sky.com","talktalk.co.uk",
						 "tiscali.co.uk","virgin.net","wanadoo.co.uk","bt.com","uwe.ac.uk"
	};

	//copy domain starting from '@' character
	while (string[i] != '\0')
	{
		//advance array until character found
		if (string[i] == '@')
		{
			i++;
			while (string[i] != '\0')
			{
				//copy domain to array
				string_domain[j++] = string[i++];
			}
			break;
		}
		i++;
	}
	//loops and compare domain to systems domains
	for (i = 0; i < 56; i++)
	{
		strcpy(temp, domains[i]);
		if (strcmp(string_domain, temp) == 0)
		{
			return 1;
		}
	}
	return 0;
}

/***************************************************************************************
* Function Name: email_exist(struct User *users, int number_of_accounts,char *string)
*
* Funtion Description:
*   -This function checks if user provided email input exists already in the system
*
* User-interface variables:-
*	*OUT (Return values):
*			- bool(1:True,0:False)
*	*IN (Value Parameters):
*			- struct User *users, int number_of_accounts,char *string
*	*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): checks for email presence in system
******************************************************************************************/
int email_exist(struct User *users, int number_of_accounts, char *string)
{
	//local variable
	int i = 0;
	//loops and compare provided email to system emails
	for (i = 0; i < number_of_accounts; i++)
	{
		if (strcmp(string, users[i].user_email) == 0)
		{
			return 1;
		}
	}
	return 0;
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
/******************************************************************************************
* Function Name: get_valid_string(char *string)
*
* Funtion Description:
*   This function allows a user to give a description to an item
*
*
* User-interface variables:-
*	*OUT (Return values):
*			- NONE
*	*IN (Value Parameters):
*			- NONE
*	*IN and OUT (Reference Parameters):
*			- char *string
*
* History [Date (Author): Description)]:-
* 2019-17-01 (Maxwell Gyamfi): get valid string
******************************************************************************************/
void get_valid_string(char *string)
{
	char buffer[MAX_LENGHT_DESCRIPTION];
	int success = 0;
	do
	{
		fgets(buffer, sizeof(buffer), stdin);//request user input
		int lenght = strlen(buffer);
		buffer[lenght - 1] = '\0';

		if (strlen(buffer) < 1)//checks if too short
		{
			printf("Decription too short, try again: ");
		}
		else if (strlen(buffer) > MAX_LENGHT_DESCRIPTION)//checks if too long
		{
			printf("Decription too long, try again: ");
		}
		else
		{
			strcpy(string, buffer);//copy string into string array
			success = 1;
		}
	} while (success == 0);
}



