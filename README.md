# Loguva

Loguva (Log + [Uva](https://en.wikipedia.org/wiki/Grape)) is a library that aims to include a simple and lightweight interface for logs.

Features:
- Multiple log destinations.
- Multiple log levels.
- Fancy stdout.

## Installation

```bash
git clone https://github.com/febits/loguva
```

```bash
cd loguva
```

```bash
make all
```

```bash
sudo make install
```

## Usage

Firstly, you need to include the main header file: `loguva.h`. Don't forget to pass the `-lloguva` to the linker.

Basically, the loguva allows adding up to 20 instances of `FILE *` by calling one of the following functions below:

```c
bool loguva_add_stream(FILE *stream);
bool loguva_add_file(const char *path);
```

Once you call the macro below passing the log level and the message, you are logging:

```c
#define loguva(lv, fmt, ...)                                                   \
  loguva_log(lv, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
```

Log levels:

```c
enum log_levels { DEBUG, INFO, WARNING, ERROR, FATAL };
```

Let's suppose that you want to log both `STDOUT` and some `FILE *`:

```c
#include <loguva.h>

int main(void) {
    
    loguva_add_stream(stdout);
    loguva_add_file("/tmp/loguva.log");

    int x = 50;

    loguva(DEBUG, "The value of X: %d", x);

    return 0;
}
```

When you call `loguva()`, all instances of `FILE *` will be used to write the full log message. As you can see above, both `STDOUT` and `/tmp/loguva.log`.

## Samples

![Loguva Print from STDOUT](https://imgur.com/USVkiUl.png)

```bash
make run_samples
```
