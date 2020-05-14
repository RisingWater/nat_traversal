#include <string.h>

static int optind = 0;
static char *optarg;

///////////////////////////////////////////////////////////////////////////////
//
//
//  NAME
//       getopt -- parse command line options
//
//  SYNOPSIS
//       int getopt(int argc, char *argv[], char *optstring)
//
//       extern char *optarg;
//       extern int optind;
//
//  DESCRIPTION
//       The getopt() function parses the command line arguments. Its
//       arguments argc and argv are the argument count and array as
//       passed into the application on program invocation.  In the case
//       of Visual C++ programs, argc and argv are available via the
//       variables __argc and __argv (double underscores), respectively.
//       getopt returns the next option letter in argv that matches a
//       letter in optstring.  (Note:  Unicode programs should use
//       __targv instead of __argv.  Also, all character and string
//       literals should be enclosed in ( ) ).
//
//       optstring is a string of recognized option letters;  if a letter
//       is followed by a colon, the option is expected to have an argument
//       that may or may not be separated from it by white space.  optarg
//       is set to point to the start of the option argument on return from
//       getopt.
//
//       Option letters may be combined, e.g., "-ab" is equivalent to
//       "-a -b".  Option letters are case sensitive.
//
//       getopt places in the external variable optind the argv index
//       of the next argument to be processed.  optind is initialized
//       to 0 before the first call to getopt.
//
//       When all options have been processed (i.e., up to the first
//       non-option argument), getopt returns -1, optarg will point
//       to the argument, and optind will be set to the argv index of
//       the argument.  If there are no non-option arguments, optarg
//       will be set to NULL.
//
//       The special option "--" may be used to delimit the end of the
//       options;  -1 will be returned, and "--" (and everything after it)
//       will be skipped.
//
//  RETURN VALUE
//       For option letters contained in the string optstring, getopt
//       will return the option letter.  getopt returns a question mark (?)
//       when it encounters an option letter not included in optstring.
//       -1 is returned when processing is finished.
//
//  BUGS
//       1)  Long options are not supported.
//       2)  The GNU double-colon extension is not supported.
//       3)  The environment variable POSIXLY_CORRECT is not supported.
//       4)  The + syntax is not supported.
//       5)  The automatic permutation of arguments is not supported.
//
//  EXAMPLE
//       int main(int argc, char *argv[])
//       {
//           int c;
//
//           while ((c = getopt(argc, argv, ("aBn:"))) != -1)
//           {
//               switch (c)
//               {
//                   case ('a'):
//                       LRACE(("option a\n"));
//                       //
//                       // set some flag here
//                       //
//                       break;
//
//                   case ('B'):
//                       LRACE( ("option B\n"));
//                       //
//                       // set some other flag here
//                       //
//                       break;
//
//                   case ('n'):
//                       LRACE(("option n: value=%d\n"), atoi(optarg));
//                       //
//                       // do something with value here
//                       //
//                       break;
//
//                   case ('?'):
//                       LRACE(("ERROR: illegal option %s\n"), argv[optind-1]);
//                       return -1;
//                       break;
//
//                   default:
//                       LRACE(("WARNING: no handler for option %c\n"), c);
//                       return -1;
//                       break;
//               }
//           }
//           //
//           // check for non-option args here
//           //
//           return TRUE;
//       }
//
///////////////////////////////////////////////////////////////////////////////
static int getopt(int argc, char *argv[], char *optstring)
{
    static char *next = NULL;
    char c;
    char *cp;

    if ( optind == 0 )
    {
        next = NULL;
    }

    optarg = NULL;
    if ( next == NULL || *next == '\0')
    {
        if ( optind == 0 )
        {
            optind++;
        }

        if ( optind >= argc || argv[optind][0] != ('-') || argv[optind][1] == ('\0') )
        {
            optarg = NULL;
            if ( optind < argc )
            {
                optarg = argv[optind];
            }
            return -1;
        }

        if (strcmp(argv[optind], ("--")) == 0 )
        {
            optind++;
            optarg = NULL;
            if ( optind < argc )
            {
                optarg = argv[optind];
            }
            return -1;
        }

        next = argv[optind];
        next++;     // skip past -
        optind++;
    }

    c = *next++;
    cp = strchr(optstring, c);

    if ( cp == NULL || c == (':') )
    {
        return ('?');
    }

    cp++;
    if ( *cp == (':') )
    {
        if ( *next != ('\0'))
        {
            optarg = next;
            next = NULL;
        }
        else if ( optind < argc )
        {
            optarg = argv[optind];
            optind++;
        }
        else
        {
            return ('?');
        }
    }

    return c;
}
