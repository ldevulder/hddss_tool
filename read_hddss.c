#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <byteswap.h>

#include "hddss.h"

const uint8_t unknown_map[] =
{
  0x3b, 0x0f, 0xd7, 0x3f, 0x82, 0x77, 0xfe, 0x41,
  0xc6, 0xf6, 0xa2, 0x5d, 0xfc, 0x17, 0x2c, 0x17,
  0x7a, 0xd4, 0xf8, 0xd6
};

const uint8_t unknown2_map[] =
{
  0x0a, 0xc2
};

static uint8_t * to_string(const uint8_t *array, int size)
{
  uint8_t *string;

  /*
  string = malloc(sizeof(array) + 1);
  memset(&string[0], 0x00, sizeof*(array) + 1);
  memcpy(&string[0], &array[0], sizeof(*array));
  */
  string = malloc(size + 1);
  memset(&string[0], 0x00, size + 1);
  memcpy(&string[0], &array[0], size);

  return string;
}

static void print_header(const struct HddSsHeader *hdr)
{
  printf("Serial number: %s\n", to_string(hdr->serial, sizeof(hdr->serial)));
  printf("Firmware version: %s\n", to_string(hdr->fw_ver, sizeof(hdr->fw_ver)));
  printf("Model number: %s\n", to_string(hdr->model, sizeof(hdr->model)));
  printf("Unknown: %x\n", hdr->unknown);
  printf("Total LBAs: %x\n", hdr->total_lba);
  printf("\n");
}

int main(int argc, char *argv[])
{
  FILE *fin, *fout;
  struct HddSsHeader *hdr;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s input output\n", argv[0]);
    return 1;
  }
  const char *input = argv[1];
  const char *output = argv[2];
  
  /* Initialize the header */
  hdr = malloc(sizeof(struct HddSsHeader));
  /*
  memcpy(hdr->unknown, unknown_map, sizeof(unknown_map));
  memcpy(hdr->unknown2, unknown2_map, sizeof(unknown2_map));
  */

  /* Open the binary file to modify */
  fin = fopen(input, "rb");
  if (fin == NULL) {
    fprintf(stderr, "error while opening %s\n", input);
    perror(input);
    return EXIT_FAILURE;
  }

  /* Open the binary file to generate */
  fout = fopen(output, "wb");
  if (fout == NULL) {
    fprintf(stderr, "error while opening %s\n", output);
    perror(output);
    return EXIT_FAILURE;
  }

  /* Read the data */
  if (!fread(hdr, sizeof(*hdr), 1, fin))
    return EXIT_FAILURE;

  /* Print the file informations */
  print_header(hdr);

  /* Write the data */
  if (!fwrite(hdr, sizeof(*hdr), 1, fout))
    return EXIT_FAILURE;

  /* Close the files */
  if (!fclose(fout)) {
    perror(output);
    return EXIT_FAILURE;
  }
  if (!fclose(fin)) {
    perror(input);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
