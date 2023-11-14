#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <float.h>

#define PRINTF_NTOA_BUFFER_SIZE 32U
#define PRINTF_FTOA_BUFFER_SIZE 32U
#define PRINTF_MAX_FLOAT 1e9

typedef void (*out_fct_type)(char character, void* buffer, size_t idx, size_t maxlen);

typedef struct {
  void (*fct)(char character, void* arg);
  void* arg;
} out_fct_wrap_type;

static inline void _out_char(char character, void* buffer, size_t idx, size_t maxlen) {
  (void)buffer; (void)idx; (void)maxlen;
  if (character) _putchar(character);
}

static inline void _out_buffer(char character, void* buffer, size_t idx, size_t maxlen) {
  if (idx < maxlen) ((char*)buffer)[idx] = character;
}

static inline void _out_null(char character, void* buffer, size_t idx, size_t maxlen) {
  (void)character; (void)buffer; (void)idx; (void)maxlen;
}

static inline void _out_fct(char character, void* buffer, size_t idx, size_t maxlen) {
  (void)idx; (void)maxlen;
  if (character) ((out_fct_wrap_type*)buffer)->fct(character, ((out_fct_wrap_type*)buffer)->arg);
}

// Internal vsnprintf
static int _vsnprintf(out_fct_type out, char* buffer, const size_t maxlen, const char* format, va_list va);

int printf_(const char* format, ...);
int sprintf_(char* buffer, const char* format, ...);
int snprintf_(char* buffer, size_t count, const char* format, ...);

