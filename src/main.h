#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

enum
{
  ARG_NAME = 0,
  ARG_FLAG,
  ARG_ROOT_FREQ,
  ARG_FREQMIDI,
  ARG_OCTAVE_DIV,
  ARG_NARGS
};

typedef struct
{
  bool state;
  int value;
} FLAG;

enum
{
  M_FLAG = 0,
  F_FLAG,
  TOTAL_FLAGS
};

void usage(const char *filename);