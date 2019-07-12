#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#if !defined(EFI_PATH)
#define EFI_PATH "/sys/firmware/efi/"
#endif //EFI_PATH

#if !defined(EFIVARS_PATH)
#define EFIVARS_PATH EFI_PATH"efivars/"
#endif //EFIVARS_PATH

#if !defined(EFIVAR_EPCBIOS)
#define EFIVAR_EPCBIOS EFIVARS_PATH"EPCBIOS-c60aa7f6-e8d6-4956-8ba1-fe26298f5e87"
#endif //EFIVAR_EPCBIOS

#if !defined(EFIVAR_EPCSW)
#define EFIVAR_EPCSW EFIVARS_PATH"EPCSW-d69a279b-58eb-45d1-a148-771bb9eb5251"
#endif //EFIVAR_EPCSW

int main() {
  struct {
      uint32_t attrs;
      uint32_t _;
      uint32_t maxepcsz;
  } epcbios;

  struct {
      uint32_t attrs;
      uint32_t maxepcsz;
  } epcsw;

  FILE * fefivar;

  fefivar = fopen(EFIVAR_EPCBIOS, "r");
  if (fefivar == NULL) {
      if (errno == EACCES) {
          printf("No privilege to read "EFIVAR_EPCBIOS"\n");
          return EACCES;
      }
      int err = errno;
      printf("Unexpected error while opening "EFIVAR_EPCBIOS"\n");
      return err;
  }

  if (fread(&epcbios, sizeof(epcbios), 1, fefivar) != 1) {
      fclose(fefivar);
      printf("Unexpected error while reading "EFIVAR_EPCBIOS"\n");
      return 1;
  }

  if (fclose(fefivar)) {
      printf("Unexpected error while closing "EFIVAR_EPCBIOS"\n");
      return 1;
  }

  epcsw.attrs = epcbios.attrs;
  epcsw.maxepcsz = epcbios.maxepcsz;

  fefivar = fopen(EFIVAR_EPCSW, "w");
  if (fefivar == NULL) {
      if (errno == EACCES) {
          printf("No privilege to write "EFIVAR_EPCSW"\n");
          return EACCES;
      }
      int err = errno;
      printf("Unexpected error while opening "EFIVAR_EPCSW"\n");
      return err;
  }

  if (fwrite(&epcsw, sizeof(epcsw), 1, fefivar) != 1) {
      unlink(EFIVAR_EPCSW);
      fclose(fefivar);
      printf("Unexpected error while writing "EFIVAR_EPCSW"\n");
      return 1;
  }

  if (fclose(fefivar)) {
      printf("Unexpected error while closing "EFIVAR_EPCSW"\n");
      return 1;
  }

  return 0;
}

