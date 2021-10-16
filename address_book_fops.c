#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

const char *getfield(char* line, int fieldNum)
{
  const char *tok;
  for (tok = strtok(line, FIELD_DELIMITER);
       tok && *tok;
       tok = strtok(NULL, FIELD_DELIMITER))
  {
    if (!fieldNum--)
    {
      return tok;
    }
    strchr(line, ',');
  }

  return NULL;
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
  if (ret == 1)
  {
    /* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
    int count = 0;
    char c;

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
      if (c == '\n') // Increment count if this character is newline
      {
        count++;
      }
    }
    // while (!feof(fp))
    // {
    // 	c = fgetc(fp);
    // 	if (c == NEXT_ENTRY)
    // 		count++;
    // }

    rewind(fp);
    printf("The file %s has %d entries\n", DEFAULT_FILE, count);

    address_book = malloc(sizeof(ContactInfo*) + sizeof(FILE*) + sizeof(int));
    address_book->list = malloc(count * sizeof(ContactInfo));

    fp = fopen(DEFAULT_FILE, "r");
    int index = 0;
    char line[1024];
    fgets(line, 1024, fp); // skip header
    while (index < count)
    {
      fgets(line, 1024, fp);
      char *tmp;
      for (int name = 0; name < NAME_COUNT; name++)
      {
        tmp = strdup(line);
        strcpy(((address_book->list)+index)->name[name], getfield(tmp, name));
        free(tmp);
      }
      for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
      {
        tmp = strdup(line);
        strcpy((address_book->list + index)->phone_numbers[phone], getfield(tmp, phone + NAME_COUNT)); 
        free(tmp);
      }
      for (int email = 0; email < EMAIL_ID_COUNT; email++)
      {
        tmp = strdup(line);
        strcpy((address_book->list + index)->email_addresses[email], getfield(tmp, email + NAME_COUNT + PHONE_NUMBER_COUNT));
        free(tmp);
      }
      (address_book->list + index)->si_no = atoi(getfield(tmp, NAME_COUNT + PHONE_NUMBER_COUNT + EMAIL_ID_COUNT));
      index++;
    }
    fclose(fp);
    address_book->fp = fp;
    address_book->count = count; 
  }
  else
  {
    /* Create a file for adding entries */
    printf("Creating new address book...\n");
    address_book = malloc(sizeof(FILE*) + sizeof(ContactInfo*)+ sizeof(int));
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
		for(int name = 0; name < NAME_COUNT; name++)
			strcat(line, address_book->list->name[name]);
		for(int phone = 0; phone < PHONE_NUMBER_COUNT; phone++)
			strcat(line, address_book->list->phone_numbers[phone]);
		for(int email = 0; email < EMAIL_ID_COUNT; email++)
			strcat(line, address_book->list->email_addresses[email]);
		fprintf(address_book->fp, "%s,%d", line, address_book->list->si_no);
	}

	fclose(address_book->fp);
	free(address_book->list);
	free(address_book);
	return e_success;
}
