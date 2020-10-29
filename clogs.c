#include <stdio.h>
#include <string.h>
#include "clogs.h"

void log_open(void)
{
   log_fp = fopen("./test.log", "w");
}

void log_close(void)
{
   fclose(log_fp);
}

void log_write (char *message)
{
   fprintf(log_fp, message);
}

void log_note (char *message)
{
   char note_message[MAX_LOG_LINE_LENGTH]="NOTE: ";
   log_write(strcat(note_message, message));
}

void log_warning (char *message)
{
   char warning_message[MAX_LOG_LINE_LENGTH]="WARNING: ";
   fprintf(log_fp, strcat(warning_message, message));
}

void log_error (char *message)
{
   char error_message[MAX_LOG_LINE_LENGTH]="ERROR: ";
   fprintf(log_fp, strcat(error_message, message));
}

