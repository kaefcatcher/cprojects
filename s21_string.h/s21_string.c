#include "s21_string.h"

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

const char *myerror[] = {"Undefined error: 0",
                         "Operation not permitted",
                         "No such file or directory",
                         "No such process",
                         "Interrupted system call",
                         "Input/output error",
                         "Device not configured",
                         "Argument list too long",
                         "Exec format error",
                         "Bad file descriptor",
                         "No child processes",
                         "Resource deadlock avoided",
                         "Cannot allocate memory",
                         "Permission denied",
                         "Bad address",
                         "Block device required",
                         "Resource busy",
                         "File exists",
                         "Cross-device link",
                         "Operation not supported by device",
                         "Not a directory",
                         "Is a directory",
                         "Invalid argument",
                         "Too many open files in system",
                         "Too many open files",
                         "Inappropriate ioctl for device",
                         "Text file busy",
                         "File too large",
                         "No space left on device",
                         "Illegal seek",
                         "Read-only file system",
                         "Too many links",
                         "Broken pipe",
                         "Numerical argument out of domain",
                         "Result too large",
                         "Resource temporarily unavailable",
                         "Operation now in progress",
                         "Operation already in progress",
                         "Socket operation on non-socket",
                         "Destination address required",
                         "Message too long",
                         "Protocol wrong type for socket",
                         "Protocol not available",
                         "Protocol not supported",
                         "Socket type not supported",
                         "Operation not supported",
                         "Protocol family not supported",
                         "Address family not supported by protocol family",
                         "Address already in use",
                         "Can't assign requested address",
                         "Network is down",
                         "Network is unreachable",
                         "Network dropped connection on reset",
                         "Software caused connection abort",
                         "Connection reset by peer",
                         "No buffer space available",
                         "Socket is already connected",
                         "Socket is not connected",
                         "Can't send after socket shutdown",
                         "Too many references: can't splice",
                         "Operation timed out",
                         "Connection refused",
                         "Too many levels of symbolic links",
                         "File name too long",
                         "Host is down",
                         "No route to host",
                         "Directory not empty",
                         "Too many processes",
                         "Too many users",
                         "Disc quota exceeded",
                         "Stale NFS file handle",
                         "Too many levels of remote in path",
                         "RPC struct is bad",
                         "RPC version wrong",
                         "RPC prog. not avail",
                         "Program version wrong",
                         "Bad procedure for program",
                         "No locks available",
                         "Function not implemented",
                         "Inappropriate file type or format",
                         "Authentication error",
                         "Need authenticator",
                         "Device power is off",
                         "Device error",
                         "Value too large to be stored in data type",
                         "Bad executable (or shared library)",
                         "Bad CPU type in executable",
                         "Shared library version mismatch",
                         "Malformed Mach-o file",
                         "Operation canceled",
                         "Identifier removed",
                         "No message of desired type",
                         "Illegal byte sequence",
                         "Attribute not found",
                         "Bad message",
                         "EMULTIHOP (Reserved)",
                         "No message available on STREAM",
                         "ENOLINK (Reserved)",
                         "No STREAM resources",
                         "Not a STREAM",
                         "Protocol error",
                         "STREAM ioctl timeout",
                         "Operation not supported on socket",
                         "Policy not found",
                         "State not recoverable",
                         "Previous owner died",
                         "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

static const char *myerror[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *pdest = dest;
  while (*pdest) pdest++;
  while (*src && n--) *pdest++ = *src++;
  *pdest = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  const char *result = s21_NULL;
  int x = s21_strlen(str) + 1;
  for (int i = 0; i < x; i++) {
    if (str[i] == c) {
      result = (str + i);
      break;
    }
  }
  return (char *)result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int size = 0;
  unsigned int i = 0;
  int flag = 0;
  while (flag == 0 && i < n) {
    if (str1[i] != str2[i]) {
      size = str1[i] - str2[i];
      flag = 1;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
      flag = 1;
    }
    i++;
  }
  return size;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  if (src[i] == '\0' && n > 0 && n > s21_strlen(src)) {
    dest[i] = '\0';
  }
  return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {
  const char *tmp1 = str1;
  size_t count1 = 0;
  size_t count2 = s21_strlen(str1);
  while (*str2 != '\0') {
    while (*str1 != '\0') {
      if (*str1 != *str2) {
        str1++;
        count1++;
      } else {
        break;
      }
    }
    str2++;
    if (count1 <= count2) {
      count2 = count1;
      count1 = 0;
    }
    count1 = 0;
    str1 = tmp1;
  }
  return count2;
}

char *s21_strcat(char *dest, const char *src) {
  int dest_len = s21_strlen(dest);
  int i = 0;

  for (; src[i]; i++) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + i] = '\0';

  return dest;
}

char *s21_strerror(int errnum) {
  char *res = s21_NULL;
  static char arr[128] = {'\0'};
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
    s21_sprintf(arr, "Unknown error: %d", errnum);
    res = arr;
  } else {
    res = (char *)myerror[errnum];
  }
  return res;
}

void s21_errnum_tostring(char *str, int num) {
  int i, rem, len = 0, n;
  n = num;
  while (n != 0) {
    len++;
    n /= 10;
  }
  if (num >= 0) {
    for (i = 0; i < len; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
    }
  } else {
    len++;
    str[0] = '-';
    for (i = 0; i < len - 1; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
      if (i == len - 2) {
        str[len - (i + 1)] = (-1 * rem) + '0';
      }
    }
  }
  str[len] = '\0';
}

s21_size_t s21_strlen(const char *str) {
  int i = 0;
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *tmp;
  int s1, s2;
  while ((s1 = *str1++) != 0) {
    for (tmp = str2; (s2 = *tmp++) != '\0';) {
      if (s2 == s1) {
        return (char *)(str1 - 1);
      }
    }
  }

  return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  char k = c;
  char *res = s21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == k) {
      res = (char *)str;
    }
  }
  if (res == s21_NULL) {
    res = (char *)str;
  }
  return *res == c ? (char *)res : s21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  while (*haystack) {
    const char *h = haystack;
    const char *n = needle;

    while (*h && *n && (unsigned char)*h == (unsigned char)*n) {
      h++;
      n++;
    }

    if (!*n) {
      return (char *)haystack;
    }

    haystack++;
  }

  return s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  register int ch;

  if (str == 0) {
    str = last;
  }
  do {
    if ((ch = *str++) == '\0') {
      return 0;
    }
  } while (s21_strchr(delim, ch));
  --str;
  last = str + s21_strcspn(str, delim);
  if (*last != 0) {
    *last++ = 0;
  }
  return str;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}
