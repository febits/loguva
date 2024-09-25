#ifndef LOGUVA_H
#define LOGUVA_H

#include <stdbool.h>
#include <stdio.h>

#define loguva(lv, fmt, ...)                                                   \
  loguva_log(lv, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

enum log_levels { DEBUG, INFO, WARNING, ERROR, FATAL };

#ifdef __cplusplus
extern "C" {
#endif

bool loguva_add_stream(FILE *stream);
FILE *loguva_add_file(const char *path);

bool loguva_log(enum log_levels lv, const char *path, size_t line,
                const char *fmt, ...) __attribute__((format(printf, 4, 5)));

#ifdef __cplusplus
}
#endif

#endif
