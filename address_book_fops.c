#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

/**
 * strtok_new	- returns token even if empty field
 * 
 */
char *strtok_new(char *line)
{
	static char *source = NULL;
	char *p, *riturn = 0;
	if (line != NULL)
		source = line;
	if (source == NULL)
		return NULL;
	char pbrk[2];
	strcat(pbrk, FIELD_DELIMITER);
	strcat(pbrk, NEXT_ENTRY);
	if ((p = strpbrk(source, pbrk)) != NULL)
	{
		*p = 0;
		riturn = source;
		source = ++p;
	}
	else // EOF
	{
		riturn = source;
		source = ++p;	
	}
	return riturn;
}
/**
 * getfield	- returns the fieldNumth field from line, based on the FIELD_DELIMITER
 */
const char *getfield(char *buff, char *line, int field_num)
{
	char *tok = strtok_new(line);
	field_num++;
	while (tok)
	{
		if (field_num == 1)
			if (*tok)
			{
				strcpy(buff, strcat(tok, "\0"));
				return buff; // add the null byte to the end of string
			}
			else
			{
				return "";
			}
		printf(""); // reset buffer
		tok = strtok_new(NULL);
		field_num--;
	}
	return tok;
}

/**
 * exists	- checks if parameter filename exists
*/
int exists(char file[])
{
	FILE *fp = fopen(file, "r");
	int ret = (fp != NULL);
	fclose(fp);
	return ret;
}
Status load_file(AddressBook *address_book)
{
	int ret; // boolean if file exists

	/* 
	 * Check for file existance
	 */
	FILE *fp;
	ret = exists(DEFAULT_FILE);
	fp = fopen(DEFAULT_FILE, "r");
	if (ret)
	{
		// count how many entries are in the csv
		int count = 0;
		char c;
		for (c = getc(fp); c != EOF; c = getc(fp))
		{
			if (c == '\n') // Increment count if this character is newline
			{
				count++;
			}
		}
		rewind(fp);
		printf("The file %s has %d entries\n", DEFAULT_FILE, count);

		// create address book based on count
		// address_book = malloc(sizeof(ContactInfo*) + sizeof(FILE*) + sizeof(int));
		address_book->list = malloc(count * sizeof(ContactInfo));
		address_book->fp = fp;
		address_book->count = count;

		// begin file read in
		fp = fopen(DEFAULT_FILE, "r");
		int index = 0;
		char line[1024];
		fgets(line, 1024, fp); // skip header line
		while (index < count)
		{
			fgets(line, 1024, fp);
			char *tmp;
			for (int name = 0; name < NAME_COUNT; name++)
			{
				tmp = strdup(line);
				char buff[NAME_LEN];
				strcpy(((address_book->list) + index)->name[name], getfield(buff, tmp, name));
				free(tmp);
			}
			for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			{
				tmp = strdup(line);
				char buff[NUMBER_LEN];
				strcpy(((address_book->list) + index)->phone_numbers[phone], getfield(buff, tmp, phone + NAME_COUNT));
				free(tmp);
			}
			for (int email = 0; email < EMAIL_ID_COUNT; email++)
			{
				tmp = strdup(line);
				char buff[EMAIL_ID_LEN];
				strcpy(((address_book->list) + index)->email_addresses[email], getfield(buff, tmp, email + NAME_COUNT + PHONE_NUMBER_COUNT));
				free(tmp);
			}
			tmp = strdup(line);
			char buff[32];
			((address_book->list) + index)->si_no = atoi(getfield(buff, tmp, NAME_COUNT + PHONE_NUMBER_COUNT + EMAIL_ID_COUNT));
			free(tmp);
			index++;
		}
		fclose(fp);
	}
	else
	{
		/* Create a file for adding entries */
		printf("Creating new address book...\n");
		address_book->fp = fopen(DEFAULT_FILE, "w");
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
	char *header = "name,phone_number1,phone_number2,phone_number3,phone_number4,phone_number5,email1,email2,email3,email4,email5,si_no";
	fprintf(address_book->fp, "%s", header);
	for (int person = 0; person < address_book->count; person++)
	{
		char line[1024];
		for (int name = 0; name < NAME_COUNT; name++)
			strcat(line, ((address_book->list) + person)->name[name]);
		for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			strcat(line, ((address_book->list) + person)->phone_numbers[phone]);
		for (int email = 0; email < EMAIL_ID_COUNT; email++)
			strcat(line, ((address_book->list) + person)->email_addresses[email]);
		fprintf(address_book->fp, "%s,%d", line, address_book->list->si_no);
	}

	fclose(address_book->fp);
	free(address_book->list);
	free(address_book);
	return e_success;
}
