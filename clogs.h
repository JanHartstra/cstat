#define MAX_LOG_LINE_LENGTH 256

static FILE *log_fp;

void log_open(void);
void log_close(void);
void log_write (char *message);
void log_note (char *message);
void log_warning (char *message);
void log_error (char *message);

