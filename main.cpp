#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "frequencycounter.h"

using namespace std;

void print_usage() {
  puts("usage: wordfreq [OPTION]... FILE...");
  puts("List the word frequency in the given text FILEs\n");
  puts("  -o OUTFILE    save csv output to file");
  puts("");
  puts("Report bugs to <r1tschy@yahoo.de>");
}

int main(int argc, char** argv) {
  char *output_filename = NULL;
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "ho:")) != -1) {
    switch (c) {
    case 'o':
      output_filename = optarg;
      break;

    case 'h':
      print_usage();
      return EXIT_SUCCESS;

    case '?':
      if (optopt == 'c') {
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      } else if (isprint(optopt)) {
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      } else {
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      }
      return EXIT_FAILURE;

    default:
      abort();
    }
  }

  if (optind >= argc) {
    fputs("filenames as argument expected.", stderr);
    return EXIT_FAILURE;
  }

  FrequencyCounter wordfreq;
  for (int index = optind; index < argc; index++) {
    wordfreq.addWordsInFile(argv[index]);
  }

  if (output_filename == NULL) {
    puts("Ausgabe ...");
    //wordfreq.print(true);
  } else {
  printf("Ausgabe in Datei %s\n", output_filename);
    wordfreq.saveCSV(output_filename, true);
  }

  return EXIT_SUCCESS;
}

