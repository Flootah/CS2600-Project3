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
	printf(msg);
	printf("\n");
	int option;

	switch(type) {
		case NONE:
		// just get an enter get input.
		getc(stdin);
		break;
		case CHAR:
		option = getc(stdin);
		break;
		case NUM:
		option = getc(stdin);
		if(option >= '0' && option <= '9');
			option -= '0';
		break;
	}
	return option;
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
//Not sure if this will work, feel free to rework if necessary
Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 
/*
	char option;
	int amtOfLists = 0;

	do{
		// Intended to print out 3 at a time and to stop if it is more than array
		menu_header("List of Contacts:\n");
		for (int i = 0 + amtOfLists * 3; i < 3 + amtOfLists*3 && i < address_book->count; i++){
			printf("Name: %s\n", address_book->list->name[i]);
			printf("Phone Number: %s\n", address_book->list->email_addresses[i]);
			printf("Email ID: %s\n", address_book->list->email_addresses[i]);
			printf("Serial No:%s\n", address_book->count);
		}
		option = get_option(CHAR, "Enter Q to move backwards, W to move forward, and N to exit.\n");
		switch (option){
			case 'N':
			//Intended to break.
			break;
			case 'Q':
			// Intended to prevent going under 0
			if (amtOfLists /= 3 <= 0)
			{
				amtOfLists == 0;
			}
			else{
				amtOfLists -= 3;
			}
			case 'W':
			//Intended to prevent going above count
			if (amtOfLists + address_book->count > 3)
			{
				amtOfLists = address_book->count/3;
			}
			else{
				amtOfLists =+ 3;
			}
		}
	}
	while(option!= 'N');
*/


	return e_success;
}

void menu_header(const char *str)
{
	//fflush(stdout);
	system("cls");

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
			get_option(NONE, "No entries found!! Would you like to add? Use Add Contacts.");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				add_contacts(address_book);
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
				list_contacts(address_book, "Contacts:", 0, "list of all contacts", e_list);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

void add_contacts_menu(AddressBook *address_book)
{
	menu_header("\nAdd Contact: ");

	printf("\n0. Back");
	printf("\n1. Name       : %s", &(address_book -> list -> name)[address_book -> count][0]);
	printf("\n2. Phone No 1 : %s", &(address_book -> list -> phone_numbers)[address_book -> count][0]);    //prints the most recent entry from add contacts
	printf("\n3. Email ID 1 : %s", &(address_book -> list -> email_addresses)[address_book -> count][0]);

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
			case e_first_opt:	//name option
				printf("\nEnter the name: ");	
				fgets(&(address_book -> list -> name)[0][0], NAME_LEN, stdin);
				break;
			case e_second_opt:	//phone number option
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
			case e_third_opt:	//email option
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
			case e_exit:	//back option
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

void search_contact_menu(void)
{
	menu_header("Search contact by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	printf("\n");
	printf("Please select an option: ");
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	char userInput[NAME_LEN];	//char array for user input.  NOTE: size set at NAME_LEN = 32.  This is ok because Phone No and Email max size is the same.
	int option;
	do
	{
		search_contact_menu();

		option = get_option(NUM, "");

		switch (option)
		{
			case e_first_opt:	//name option
				printf("\nPlease enter the name: ");
				fgets(userInput, NAME_LEN, stdin);
				//would call search() function here (do not know how to implement)
				//then would display the matching contact (again, do not know how to implement)
				break;
			case e_second_opt:	//phone number option
				printf("\nPlease enter the phone number: ");
				fgets(userInput, NUMBER_LEN, stdin);
				//would call search() function here (do not know how to implement)
				//then would display the matching contact (again, do not know how to implement)
				break;
			case e_third_opt:	//email ID option
				printf("\nPlease enter the email ID: ");
				fgets(userInput, EMAIL_ID_LEN, stdin);
				//would call search() function here (do not know how to implement)
				//then would display the matching contact (again, do not know how to implement)
				break;
			case e_fourth_opt:	//serial number option
				printf("\nPlease enter the serial number: ");
				fgets(userInput, 32, stdin);
				//would call search() function here (do not know how to implement)
				//then would display the matching contact (again, do not know how to implement)
				break;
			case e_exit:	//back option
				break;
		}
	} while (option != e_exit);

	return e_success;
}

void edit_contacts_search_menu(AddressBook *address_book)
{
	menu_header("\nSearch Contact to Edit by: "); 
	printf("\n0. Back"); 
	printf("\n1. Name"); 
	printf("\n2. Phone No");
	printf("\n3. Email ID");
	printf("\n4. Serial No");
	printf("\n");
	printf("Please select an option: ");
}

void edit_contacts_menu(AddressBook *address_book)
{
	menu_header("\nEdit Contact: "); 
	printf("\n0. Back"); 
	printf("\n1. Name       : ");
	printf("\n2. Phone No 1 : ");
	printf("\n3. Email ID 1 : ");
	printf("\n");
	printf("Please select an option: ");
}

Status edit_contact(AddressBook *address_book)
{
	char input[NAME_LEN];
	char select[2];
	int option;
	do
	{
		edit_contacts_search_menu(address_book);
		option = get_option(NUM, "");

		switch (option)
		{
			case e_first_opt:
				printf("Enter the name: ");
				fgets(input, NAME_LEN, stdin);
				search_contact(input);
				printf("Press: [s] = Select. [q] | Cancel: ");
					if (fgets(select, 2, stdin) == 's')
					{
						printf("Select a Serial Number (S.No) to Edit: ");
						scanf("%s", NUM);
					}
		
				break;
	
			case e_second_opt:
				printf("\nPlease enter the phone number: ");
				fgets(input, NUMBER_LEN, stdin);
				search_contact(input);
				break; 
			case e_third_opt:
				printf("\nPlease enter the email ID: ");
				fgets(input, EMAIL_ID_LEN, stdin);
				search_contact(input);
				break;
			case e_fourth_opt:
				printf("\nPlease enter the serial number: ");
				fgets(input, 32, stdin);
				search_contact(input);
				break;
			}
	} while (option != e_exit);
	
	/* Add the functionality for edit contacts here */
}

void delete_contacts_menu(void){
	menu_header("Delete Contact: \n");

	printf("0. Back\n");
	printf("1. Delete by Name\n");
	printf("2. Delete by Phone Number\n");
	printf("3. Delete by Email Address\n");
	printf("4. Delete by Serial Number\n");
	printf("\n");
	printf("Please choose an option: ");
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	int option;
	char input[NAME_LEN];
    int amtOfContacts;
	do{
	delete_contacts_menu();
	option = get_option(NUM,"");
    switch (option)
	// Mostly garbage skeleton code, feel free to delete.
    {
        /*case e_first_opt:
        int contactNum;
        char bool[1];
        printf("Please enter the name of the contact you wish to delete.");
        scanf("%s", input);
         if (strcpy(input, string from search statement?) != 0){
                while (strcpy(input, string from search statement?) != 0){
                    printf("Invalid name. Please enter the name of the contact you wish to delete.\n");
                    scanf("%s", input);
                }
            }
        
         some way to get amount of contacts?
         
            printf("Select which contact you would like to choose.\n");
            scanf("%d", contactNum);
            while (contactNum < 0 && contactNum > amtOfContacts)
            {
                printf("Invalid contact. Please select which contact you would like to choose.");
                scanf("%d", contactNum);
            }
            *search & display contact

        search & display contact
        printf("Warning: This will permanently delete the contact.\n");
        printf("Are you sure that this is the contact you would like to choose?\n");
        printf("Enter 'y' to delete the contact; enter any other letter to return to delete menu.\n");
        scanf("%d", bool);
        if (strcpy(bool, 'y') == 0){
            for (int i = )
        }
        else {
            return to 
        }
        
        	break;
		case e_second_opt:
        printf("Please enter the phone number of the contact you wish to delete.");
        scanf("%s", input);
         if (strcpy(input, string from search statement?) != 0){
                while (strcpy(input, string from search statement?) != 0){
                    printf("Invalid phone number. Please enter the name of the contact you wish to delete.\n");
                    scanf("%s", input);
                }
            }
        
         some way to get amount of contacts?
         	int toBeDeleted[amount of contacts that qualify?];
            int contactNum;
            printf("Select which contact you would like to choose.\n");
            scanf("%d", contactNum);
            for (i)
            *search & display contact

        search & display contact
        printf("Warning: This will permanently delete the contact.\n");
        printf("Are you sure that this is the contact you would like to choose?\n");
        printf("Enter 'y' to delete the contact; enter any other letter to return to delete menu.\n");

        */
    }
	}while (option != e_exit);
}
