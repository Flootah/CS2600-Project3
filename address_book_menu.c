#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				search_contact(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

/* Chris Choi stuff */
void add_contacts_menu(AddressBook *address_book)
{
	menu_header("\nAdd Contact: ");

	printf("\n0. Back");
	printf("\n1. Name       : %s", &(address_book -> list -> name)[0][0]);
	printf("\n2. Phone No 1 : %s", &(address_book -> list -> phone_numbers)[0][0]);
	printf("\n3. Email ID 1 : %s", &(address_book -> list -> email_addresses)[0][0]);

	printf("\n");
	printf("Please select an option: ");
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	char yesOrNo[1];	//array used for 'y' or 'n'
	int option;
	do
	{
		add_contacts_menu(address_book);

		option = get_option(NUM, "");

		switch (option)
		{
			case e_first_opt:
				printf("\nEnter the name: ");	
				fgets(&(address_book -> list -> name)[0][0], NAME_LEN, stdin);
				break;
			case e_second_opt:
				printf("\nEnter phone number 1: ");
				fgets(&(address_book -> list -> phone_numbers)[0][0], NUMBER_LEN, stdin);
				/* For loop used for alternate phone numbers if user want to input any */
				for (int i = 2; i < PHONE_NUMBER_COUNT; i++)
				{
					printf("\nAdd an another phone number? ('y' for yes and 'n' for no): ");
					fgets(yesOrNo, 2, stdin);
					if (yesOrNo[0] != 'y')	//if user input 'n' then breaks out of for loop
					{
						break;
					}
					else	//if user input 'y' then asks for i-th phone number
					{
						printf("\nEnter phone number %d: ", i);
						fgets(&(address_book -> list -> phone_numbers)[i-1][0], NUMBER_LEN, stdin);
					}
				}
				break;
			case e_third_opt:
				printf("\nEnter email ID 1: ");
				fgets(&(address_book -> list -> email_addresses)[0][0], EMAIL_ID_LEN, stdin);
				/* For loop used for alternate email IDs if user want to input any */
				for (int i = 2; i < EMAIL_ID_COUNT; i++)
				{
					printf("\nAdd an another email ID? ('y' for yes and 'n' for no): ");
					fgets(yesOrNo, 2, stdin);
					if (yesOrNo[0] != 'y')	//if user input 'n' then breaks out of for loop
					{
						break;
					}
					else	//if user input 'y' then asks for i-th phone number
					{
						printf("\nEnter email ID %d: ", i);
						fgets(&(address_book -> list -> email_addresses)[i-1][0], EMAIL_ID_LEN, stdin);
					}
				}				
				break;
		}
	} while (option != e_exit);

	return e_success;
}
/*end of chris choi stuff*/

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
