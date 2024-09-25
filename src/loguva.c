#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "color.h"
#include "loguva.h"

#define MAX_STREAMS 20
#define MAX_STRFTIME 9

static FILE *streams[MAX_STREAMS] = {NULL};
static uint8_t streams_size = 0;

static const char *log_levels_str[] = {"DEBUG", "INFO", "WARNING", "ERROR",
                                       "FATAL"};

static size_t gettime(char *buffer) {
  time_t tm = time(NULL);
  struct tm *ptm = localtime(&tm);

  return strftime(buffer, MAX_STRFTIME, "%X", ptm);
}

bool loguva_add_stream(FILE *stream) {
  if (streams_size < MAX_STREAMS) {
    streams[streams_size++] = stream;

    return true;
  }

  return false;
}

FILE *loguva_add_file(const char *path) {
  if (streams_size < MAX_STREAMS) {
    FILE *stream = fopen(path, "a");
    if (stream == NULL)
      return NULL;

    streams[streams_size++] = stream;

    return stream;
  }

  return NULL;
}

bool loguva_log(enum log_levels lv, const char *path, size_t line,
                const char *fmt, ...) {
  for (uint8_t i = 0; i < streams_size; i++) {
    char timebuff[MAX_STRFTIME + 1] = {0};
    timebuff[gettime(timebuff)] = '\0';

    if (fileno(streams[i]) == STDOUT_FILENO) {
      fprintf(streams[i], "[%s] ", timebuff);

      switch (lv) {
        case DEBUG:
          fprintfc(streams[i], STYLE(MAGENTA, 0, 0), "[%s]%-3s",
                   log_levels_str[lv], " ");
          break;
        case INFO:
          fprintfc(streams[i], STYLE(GREEN, 0, 0), "[%s]%-4s",
                   log_levels_str[lv], " ");
          break;
        case WARNING:
          fprintfc(streams[i], STYLE(YELLOW, 0, 0), "[%s]%-1s",
                   log_levels_str[lv], " ");
          break;
        case ERROR:
          fprintfc(streams[i], STYLE(BRIGHT_RED, 0, 0), "[%s]%-3s",
                   log_levels_str[lv], " ");
          break;
        case FATAL:
          fprintfc(streams[i], STYLE(RED, 0, BOLD), "[%s]%-3s",
                   log_levels_str[lv], " ");
          break;
      }

      fprintfc(streams[i], STYLE(WHITE, 0, DIM), "%s:%lu > ", path, line);

      va_list args;
      va_start(args, fmt);
      vfprintf(streams[i], fmt, args);
      va_end(args);

      fprintf(streams[i], "\n");
    } else {
      fprintf(streams[i], "[%s] ", timebuff);

      switch (lv) {
        case DEBUG:
          fprintf(streams[i], "[%s]%-3s", log_levels_str[lv], " ");
          break;
        case INFO:
          fprintf(streams[i], "[%s]%-4s", log_levels_str[lv], " ");
          break;
        case WARNING:
          fprintf(streams[i], "[%s]%-1s", log_levels_str[lv], " ");
          break;
        case ERROR:
          fprintf(streams[i], "[%s]%-3s", log_levels_str[lv], " ");
          break;
        case FATAL:
          fprintf(streams[i], "[%s]%-3s", log_levels_str[lv], " ");
          break;
      }

      fprintf(streams[i], "%s:%lu > ", path, line);

      va_list args;
      va_start(args, fmt);
      vfprintf(streams[i], fmt, args);
      va_end(args);

      fprintf(streams[i], "\n");
    }
  }

  return true;
}
