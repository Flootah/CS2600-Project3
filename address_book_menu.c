#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

#define max(a, b)                   \
	(                               \
		{                           \
			__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a > _b ? _a : _b;      \
		})

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */
	printf(msg);
	int option;

	switch (type)
	{
	case NONE:
		// just get an enter get input.
		getc(stdin);
		break;
	case CHAR:
		option = getc(stdin);
		break;
	case NUM:
		option = getc(stdin);
		if (option >= '0' && option <= '9')
			;
		option -= '0';
		break;
	}
	getc(stdin);
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

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	//search("", address_book, address_book->count, 1, msg, e_search);

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
		if ((address_book->count == 0) && (option != e_add_contact))
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
			for (int person = 0; person < address_book->count; person++)
			{
				list_contacts(address_book, "Contacts:", &person, "Press: [n] = next, Press: [p] = previous, Press: [q] | Cancel: ", e_list);
			}
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
void view_contact_menu(ContactInfo *person, Modes mode)
{
	switch (mode)
	{
	case e_add:
		menu_header("Add Contact:");
		break;
	case e_edit:
		menu_header("Edit Contact:");
		break;
	default:
		break;
	}

	printf("\n0. Back");
	printf("\n1. Name       : %s", person->name[0]);
	for(int name = 1; name < NAME_COUNT; name++)
	{
		if(strcmp(person->name[name],""))
		{
			printf("\n%13d : %s", name+1, person->name[name]);
		}
	}
	printf("\n2. Phone No 1 : %s", person->phone_numbers[0]); //prints the most recent entry from add contacts
	for(int phone = 1; phone < PHONE_NUMBER_COUNT; phone++)
	{
		if(strcmp(person->phone_numbers[phone],""))
		{
			printf("\n%13d : %s", phone+1, person->phone_numbers[phone]);
		}
	}
	printf("\n3. Email ID 1 : %s", person->email_addresses[0]);
	for(int email = 1; email < EMAIL_ID_COUNT; email++)
	{
		if(strcmp(person->email_addresses[email],""))
		{
			printf("\n%13d : %s", email+1, person->email_addresses[email]);
		}
	}
	printf("\n");
	printf("Please select an option: ");
}
Status edit_person(ContactInfo *person, MenuOptions option)
{
	int index;
	int string_len;
	char *userInput;
	switch (option)
	{
	case e_first_opt:
		userInput = malloc(sizeof(char) * NAME_LEN);
		printf("Enter Name index to be changed [Max %d]: ", NAME_COUNT);
		fgets(userInput, NAME_LEN, stdin);
		index = atoi(userInput);
		printf("Enter Name %d: [Just enter removes the entry]: ", index);
		fgets(userInput, NAME_LEN, stdin);
		string_len = strlen(userInput) - 1;
		if (userInput[string_len] == '\n')
			userInput[string_len] = '\0';
		strcpy(person->name[index - 1], userInput);
		break;
	case e_second_opt:
		userInput = malloc(sizeof(char) * NAME_LEN);
		printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
		fgets(userInput, NUMBER_LEN, stdin);
		index = atoi(userInput);
		printf("Enter Phone Number %d: [Just enter removes the entry]: ", index);
		fgets(userInput, NUMBER_LEN, stdin);
		string_len = strlen(userInput) - 1;
		if (userInput[string_len] == '\n')
			userInput[string_len] = '\0';
		strcpy(person->phone_numbers[index - 1], userInput);
		break;
	case e_third_opt:
		userInput = malloc(sizeof(char) * NAME_LEN);
		printf("Enter Email ID index to be changed [Max %d]: ", EMAIL_ID_COUNT);
		fgets(userInput, EMAIL_ID_LEN, stdin);
		index = atoi(userInput);
		printf("Enter Email ID %d: [Just enter removes the entry]: ", index);
		fgets(userInput, EMAIL_ID_LEN, stdin);
		string_len = strlen(userInput) - 1;
		if (userInput[string_len] == '\n')
			userInput[string_len] = '\0';
		strcpy(person->email_addresses[index - 1], userInput);
		break;

	default:
		break;
	}
}
Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	char yesOrNo[1]; //array used for 'y' or 'n'
	int option;
	do
	{
		//view_contact_menu("", e_add);

		option = get_option(NUM, "");

		switch (option)
		{
		case e_first_opt: //name option
			printf("\nEnter the name: ");
			fgets(&(address_book->list->name)[0][0], NAME_LEN, stdin);
			break;
		case e_second_opt: //phone number option
			printf("\nEnter phone number 1: ");
			fgets(&(address_book->list->phone_numbers)[0][0], NUMBER_LEN, stdin);

			/* For loop used for alternate phone numbers if user want to input any */
			for (int i = 2; i < PHONE_NUMBER_COUNT; i++)
			{
				printf("\nAdd an another phone number? ('y' for yes and 'n' for no): ");
				fgets(yesOrNo, 2, stdin);
				if (yesOrNo[0] != 'y') //if user input 'n' then breaks out of for loop
				{
					break;
				}
				else //if user input 'y' then asks for i-th phone number
				{
					printf("\nEnter phone number %d: ", i);
					fgets(&(address_book->list->phone_numbers)[i - 1][0], NUMBER_LEN, stdin);
				}
			}
			break;
		case e_third_opt: //email option
			printf("\nEnter email ID 1: ");
			fgets(&(address_book->list->email_addresses)[0][0], EMAIL_ID_LEN, stdin);

			/* For loop used for alternate email IDs if user want to input any */
			for (int i = 2; i < EMAIL_ID_COUNT; i++)
			{
				printf("\nAdd an another email ID? ('y' for yes and 'n' for no): ");
				fgets(yesOrNo, 2, stdin);
				if (yesOrNo[0] != 'y') //if user input 'n' then breaks out of for loop
				{
					break;
				}
				else //if user input 'y' then asks for i-th phone number
				{
					printf("\nEnter email ID %d: ", i);
					fgets(&(address_book->list->email_addresses)[i - 1][0], EMAIL_ID_LEN, stdin);
				}
			}
			break;
		case e_no_opt: //back option
			break;
		}
	} while (option != e_exit);

	return e_success;
}
int exit_search(const char *msg, Modes mode)
{
	int option = get_option(CHAR, msg);
	switch (mode)
	{
	case e_search:
		if (option == 'q')
		{
			return e_exit;
		}
		break;
	case e_edit:
	case e_delete:
		if (option == 'q')
		{
			return e_exit;
		}
		else if (option == 's')
		{
			return e_success;
		}
		break;
	default:
		break;
	}
	return -1;
}

/**
 * search	- 	performs a search on address_book. it tries to find the field 
 * 				that matches str and prints result.
 * 
 * 	@param	str				string to match	
 * 	@param	address_book	address book to search through
 * 	@param	loop_count		unknown kappa
 * 	@param	field			field of address book that is being matched against
 * 	@param	msg				message to print to exit
 * 	@param	mode			mode calling search to know which keys are valid to exit
 */
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	int exit_status;
	Status ret; //function will assign e_fail or e_success to this and return this.
	do
	{
		menu_header("Search result:\n\n");
		printf(":======:==================================:==================================:==================================:\n"
			   ": S.No : Name                             : Phone No                         : Email                            :\n"
			   ":======:==================================:==================================:==================================:\n");

		switch (field)
		{
		case e_first_opt: // search by name

			for (int person = 0; person < loop_count; person++)
			{
				for (int name = 0; name < NAME_COUNT; name++)
				{
					//checks if there is a name in name[] that matches the name that it is searching for
					if (strstr(((address_book->list) + person)->name[name], str) != NULL)
					{
						ret = e_success; //if match is found, return e_success.
						// print main information
						printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
						// print additional information
						for (int person_name = 1; person_name < max(max(NAME_COUNT, PHONE_NUMBER_COUNT), EMAIL_ID_COUNT); person_name++)
						{
							char name_buffer[NAME_LEN];
							if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
								strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
							else
								strcpy(name_buffer, " ");

							char phone_buffer[NUMBER_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
								strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
							else
								strcpy(phone_buffer, " ");

							char email_buffer[EMAIL_ID_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
								strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
							else
								strcpy(email_buffer, " ");
							printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
							printf("\n");
						}
						break;
					}
					else
					{
						ret = e_no_match; //if no match if found, return e_fail.
						break;
					}
				}
			}
			break;
		case e_second_opt: // search by phone number

			for (int person = 0; person < loop_count; person++)
			{
				for (int phone_number = 0; phone_number < PHONE_NUMBER_COUNT; phone_number++)
				{
					//checks if there is a name in name[] that matches the name that it is searching for
					if (strstr(((address_book->list) + person)->phone_numbers[phone_number], str) != NULL)
					{
						ret = e_success; //if match is found, return e_success.
						// print main information
						printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
						// print additional information
						for (int person_name = 1; person_name < max(max(NAME_COUNT, PHONE_NUMBER_COUNT), EMAIL_ID_COUNT); person_name++)
						{
							char name_buffer[NAME_LEN];
							if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
								strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
							else
								strcpy(name_buffer, " ");

							char phone_buffer[NUMBER_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
								strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
							else
								strcpy(phone_buffer, " ");

							char email_buffer[EMAIL_ID_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
								strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
							else
								strcpy(email_buffer, " ");
							printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
							printf("\n");
						}
						break;
					}
					else
					{
						ret = e_no_match; //if no match if found, return e_fail.
						break;
					}
				}
			}
			break;
		case e_third_opt: // search by email

			for (int person = 0; person < loop_count; person++)
			{
				for (int email_id = 0; email_id < EMAIL_ID_COUNT; email_id++)
				{
					//checks if there is a name in name[] that matches the name that it is searching for
					if (strstr(((address_book->list) + person)->email_addresses[email_id], str) != NULL)
					{
						ret = e_success; //if match is found, return e_success.
						// print main information
						printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
						// print additional information
						for (int person_name = 1; person_name < max(max(NAME_COUNT, PHONE_NUMBER_COUNT), EMAIL_ID_COUNT); person_name++)
						{
							char name_buffer[NAME_LEN];
							if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
								strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
							else
								strcpy(name_buffer, " ");

							char phone_buffer[NUMBER_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
								strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
							else
								strcpy(phone_buffer, " ");

							char email_buffer[EMAIL_ID_LEN];
							if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
								strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
							else
								strcpy(email_buffer, " ");
							printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
							printf("\n");
						}
						break;
					}
					else
					{
						ret = e_no_match; //if no match if found, return e_fail.
						break;
					}
				}
			}

			break;
		case e_fourth_opt: // search si_no

			for (int person = 0; person < loop_count; person++)
			{
				//checks if there is a name in name[] that matches the name that it is searching for
				if (((address_book->list) + person)->si_no == atoi(str))
				{
					ret = e_success; //if match is found, return e_success.
					// print main information
					printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
					// print additional information
					for (int person_name = 1; person_name < max(max(NAME_COUNT, PHONE_NUMBER_COUNT), EMAIL_ID_COUNT); person_name++)
					{
						char name_buffer[NAME_LEN];
						if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
							strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
						else
							strcpy(name_buffer, " ");

						char phone_buffer[NUMBER_LEN];
						if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
							strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
						else
							strcpy(phone_buffer, " ");

						char email_buffer[EMAIL_ID_LEN];
						if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
							strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
						else
							strcpy(email_buffer, " ");
						printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
						printf("\n");
					}
					break;
				}
			}
			ret = e_no_match; //if no match if found, return e_fail.
			break;
		default:
			break;
		}
		printf(":======:==================================:==================================:==================================:\n");
		ret = exit_search(msg, mode);
	} while (!(ret == e_exit || ret == e_success));
	return ret;
}

void search_contact_menu(Modes mode)
{
	char buff[40];
	switch (mode)
	{
	case e_search:
		strcpy(buff, "Search contact by:");
		break;
	case e_edit:
		strcpy(buff, "Search contact to Edit by:");
		break;
	case e_delete:
		strcpy(buff, "Search contact to Delete by:");
		break;
	default:
		break;
	}
	menu_header(buff);

	printf("\n0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	printf("\n");
	printf("Please select an option: ");
}

Status search_contact(AddressBook *address_book)
{
	int string_len;
	char userInput[max(max(NAME_LEN, EMAIL_ID_LEN), NUMBER_LEN)]; //char array for user input.  NOTE: size set at NAME_LEN = 32.  This is ok because Phone No and Email max size is the same.
	MenuOptions option;
	char *msg = "Press: [q] | Cancel: ";
	do
	{
		search_contact_menu(e_search);
		option = get_option(NUM, "");
		if (option == e_exit)
		{
			return e_success;
		}
		switch (option) // search based on the field specified in option
		{
		case e_first_opt: //name option
			printf("Enter the Name: ");
			fgets(userInput, NAME_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput th a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_second_opt: //phone number option
			printf("Enter the Phone Number: ");
			fgets(userInput, NUMBER_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_third_opt: //email ID option
			printf("Enter the Email ID: ");
			fgets(userInput, EMAIL_ID_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_fourth_opt: //serial number option
			printf("Enter the Serial Number: ");
			fgets(userInput, 32, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_no_opt: //back option
			break;
		default:
			break;
		}
		search(userInput, address_book, address_book->count, option, msg, e_search);
	} while (option != e_exit);

	return e_success;
}
ContactInfo *getPersonBySI_NO(AddressBook *address_book, int si_no)
{
	for (int person = 0; person < address_book->count; person++)
	{
		//checks if there is a name in name[] that matches the name that it is searching for
		if (((address_book->list) + person)->si_no == si_no)
		{
			return ((address_book->list) + person);
		}
	}
	return NULL;
}

Status edit_contact(AddressBook *address_book)
{
	int string_len;
	char userInput[max(max(NAME_LEN, EMAIL_ID_LEN), NUMBER_LEN)]; //char array for user input.  NOTE: size set at NAME_LEN = 32.  This is ok because Phone No and Email max size is the same.
	MenuOptions option;
	char *msg = "Press: [s] = Select, Press: [q] | Cancel: ";
	do
	{
		ContactInfo *person;
		search_contact_menu(e_edit);
		option = get_option(NUM, "");
		if (option == e_exit)
		{
			return e_success;
		}
		switch (option) // search based on the field specified in option
		{
		case e_first_opt: //name option
			printf("Enter the Name: ");
			fgets(userInput, NAME_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput th a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_second_opt: //phone number option
			printf("Enter the Phone Number: ");
			fgets(userInput, NUMBER_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_third_opt: //email ID option
			printf("Enter the Email ID: ");
			fgets(userInput, EMAIL_ID_LEN, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_fourth_opt: //serial number option
			printf("Enter the Serial Number: ");
			fgets(userInput, 32, stdin); // actually write to buffer
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n') //sets the \n at the end of userInput to a NULL byte
				userInput[string_len] = '\0';
			break;
		case e_no_opt: //back option
			break;
		default:
			break;
		}
		do
		{
			if (search(userInput, address_book, address_book->count, option, msg, e_edit) == e_exit)
			{
				return e_success;
			}
			printf("Select a Serial Number (S.No) to Edit: ");
			person = getPersonBySI_NO(address_book, get_option(NUM, ""));
		} while (person == NULL);
		do
		{
			view_contact_menu(person, e_edit);
			option = get_option(NUM, "");
			switch (option)
			{
			case e_first_opt:
			case e_second_opt:
			case e_third_opt:
				edit_person(person, option);
				break;
			default:
				break;
			}
		} while (option != e_exit);
	} while (option != e_exit);

	return e_success;
}

void delete_contacts_menu(void)
{
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
	do
	{
		delete_contacts_menu();
		option = get_option(NUM, "");
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
	} while (option != e_exit);
}
