#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

const char *getfield(char *line, int num)
{
	const char *tok;
	for (tok = strtok(line, FIELD_DELIMITER);
		 tok && *tok;
		 tok = strtok(NULL, strcat(FIELD_DELIMITER, "\n")))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}

Status load_file(AddressBook *address_book)
{
	int ret; // boolean if file exists

	/* 
	 * Check for file existance
	 */
	FILE *fp;
	ret = (fp = fopen(DEFAULT_FILE, "r"));
	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		int count = 0, c;
		while (c != EOF)
		{
			c = fgetc(fp);
			if (c == NEXT_ENTRY)
				count++;
		}
		rewind(fp);
		printf("The file %s has %d lines\n ", DEFAULT_FILE, count);

		ContactInfo *list = (ContactInfo *)malloc(count * sizeof(ContactInfo));

		fp = fopen(DEFAULT_FILE, "r");
		int index = 0;
		char line[1024];
		while (fgets(line, 1024, fp))
		{
			char *tmp = strdup(line);
			for (int name = 0; name < NAME_COUNT; name++)
			{
				strcpy((list + index)->name[name], getfield(tmp, name + 1)); // the plus one is because items start at 1
			}
			for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			{
				strcpy((list + index)->phone_numbers[phone], getfield(tmp, phone + NAME_COUNT + 1)); // the plus one is because items start at 1
			}
			for (int email = 0; email < EMAIL_ID_COUNT; email++)
			{
				strcpy((list + index)->email_addresses[email], getfield(tmp, email + NAME_COUNT + PHONE_NUMBER_COUNT + 1)); // the plus one is because items start at 1
			}
			list->si_no = getfield(tmp, NAME_COUNT + PHONE_NUMBER_COUNT + EMAIL_ID_COUNT + 1);
			free(tmp);
			index++;
		}
		fclose(fp);

		address_book->fp = fp;
		address_book->list = list;
		address_book->count = count - 1; // minus 1 for header line
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		address_book->list;
		address_book->count = 0;
		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */
	char *header[] = "name,phone_number1,phone_number2,phone_number3,phone_number4,phone_number5,email1,email2,email3,email4,email5,si_no";
	fprintf("%s", header);
	for (int person = 0; person < address_book->count; person++)
	{
		char line[1024];
		for(int name = 0; name < NAME_COUNT; name++)
			strcat(line, address_book->list->name[name]);
		for(int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			strcat(line, address_book->list->phone_numbers[phone]);
		for(int email = 0; email < EMAIL_ID_COUNT; email++)
			strcat(line, address_book->list->email_addresses[email]);
		fprintf("%s,%d", line, address_book->list->si_no);
	}

	fclose(address_book->fp);

	return e_success;
}
