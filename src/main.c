#include "main.h"

int main(int argc, char const *argv[])
{
  const char *programName = argv[ARG_NAME];
  if (argc != ARG_NARGS)
  {
    usage(programName);
    return 1;
  }

  FLAG flags[TOTAL_FLAGS] = {
      {false, 0},
      {false, 0},
  };

  int ctr = 1;
  while (ctr < argc && argv[ctr][0] == '-')
  {
    char flag = argv[ctr][1];
    switch (flag)
    {
    case 'h':
      usage(programName);
      return 1;
    case 'm':
      flags[M_FLAG].state = true;
      flags[M_FLAG].value = strtof(argv[ctr + 1], NULL);
      ctr += 2;
      break;
      case 'f':
      flags[F_FLAG].state = true;
      flags[F_FLAG].value = strtof(argv[ctr + 1], NULL);
      ctr += 2;
      break;
    default:
      printf("ERROR: incorrect flag option %s\n", argv[1]);
      break;
    }
  }

  double a4 = strtof(argv[ARG_ROOT_FREQ], NULL);
  if (a4 < 0)
  {
    printf("ERROR: %s frequency isn't valid root frequency; Enter a value greater than 0\n", argv[ARG_ROOT_FREQ]);
    return 1;
  }

  int octaveDiv = strtol(argv[ARG_OCTAVE_DIV], NULL, 10);
  if (octaveDiv < 5)
  {
    printf("ERROR: %s isn't a valid division of octaves. Make sure your division is above 5.\n", argv[ARG_OCTAVE_DIV]);
    return 1;
  }

  int midinote = 0;
  double frequency = 0;
  if (flags[M_FLAG].state == true)
  {
    midinote = strtol(argv[ARG_FREQMIDI], NULL, 10);
    if (midinote < 0 || midinote > 127)
    {
      printf("ERROR: %s isn't a valid MIDI note. Make sure your note is in the range 0-127.\n", argv[ARG_FREQMIDI]);
      return 1;
    }
    
    // Calculation of frequency for provided MIDI note
    frequency = a4 * pow(2, (midinote - 69.0) / octaveDiv);

    printf("MIDI note: %d has a frequency of %.2f\n", midinote, frequency);
  }
  else //F_FLAG is true
  {
    frequency = strtof(argv[ARG_FREQMIDI], NULL);
    if (frequency < 0)
    {
      printf("ERROR: %s frequency isn't a valid root frequency. Enter a value 0 or greater.\n", argv[ARG_FREQMIDI]);
      return 1;
    }

    // Formula to find nearest MIDI note; Made through algebra on other func
    double fracmidi = octaveDiv * log2(frequency / a4) + 69;
    midinote = (int)(fracmidi + 0.5);

    printf("The nearest MIDI note to the frequency %.2f is %d\n", frequency, midinote);
  }

  return 0;
}

void usage(const char *filename)
{
  printf("%s: Converts MIDI note to frequency or finds MIDI note closest to provided frequency\n\n", filename);
  printf("usage: %s [options] rootFreq freq/midinote octaveDivision\n", filename);
  printf("\t-h: Show documentation\n");
  printf("\t-m: Find midinote closest to frequency instead\n");
  printf("\t-f: Find frequency of midinote\n\n");
}
