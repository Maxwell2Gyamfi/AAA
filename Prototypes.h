#pragma once
#pragma warning(disable:4996)

// Standard C library header files (#include ....):
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

//Function prototypes/declarations
void insert(items user_items, linked_list_items **item);
void get_valid_string(char *string);
void display_items(linked_list_items * start);
void append(linked_list_items **linked);
void user_account_menu();
int user_menu(struct User *user, int count, int position);
void Pause();
void admin_account_menu();
int admin_account(struct User *users, int count);
void display_all_accounts(struct User *users, int count);
int remove_account(struct User *users, int count, int position, linked_list_items**head);
int login(struct User *user, int count);
char get_valid_yes_or_no();
void main_display_menu();
int get_valid_integer(int minimum, int maximum);
int isfloat(char *string, int length);
int is_integer(char *string, int length);
int get_string_length(char *string);
int convert_string_to_integer(char *string, int count, int lenght, int sum);
int convert_character_to_integer(char character, char *string, int sum, int value, int count);
int create_account(int *count, struct User *new_user);
void get_valid_password(char *password);
int hasdigit(char *string, int lenght);
int has_upper_case(char *string, int lenght);
void get_valid_email(int number_of_accounts, struct User *users, int login, char *email);
int email_exist(struct User *users, int number_of_accounts, char *string);
int has_at_email(char *string, int lenght);
int has_domain(char *string, int lenght);
void copy_string(char *source, char*destination);
int read_users_file(struct User *users, char *name);
void save_users_files(struct User *users, int count, char *name);
int valid_login_email(struct User *user, int count, char *email);
void save_items_to_file(linked_list_items *item, char *account_email);
void insert(items user_items, linked_list_items **item);
int read_items_from_file(linked_list_items **item, char *account_email);
linked_list_items * sortedmerge(linked_list_items* a, linked_list_items* b);
void frontbacksplit(linked_list_items* head, linked_list_items** aref, linked_list_items** bref);
void mergesort(linked_list_items** headref);
void search_item(linked_list_items* head);
void delete_item(linked_list_items** head);
void change_password(struct User *user, int position);
int check_item_number_duplicate(linked_list_items *head, int item_number);
int load_default_file(linked_list_items** head);
void free_linked_list_items(linked_list_items **head);
int merge_sort(struct User *user, int min, int max);
void merge(struct User *user, int min, int middle, int middle2, int max);
void binary_search_account(struct User *user, int count);
void update_total_elements(linked_list_items *head, struct User *user, int position);
void cipher_password(char *password, char *key, char *pswd, int value);
void suspend_user(struct User *user, int count);
void unsuspend_user(struct User *user, int count);
void send_email(struct User *user, int position);

