//
// Created by Pavel Prokofyev on 2019-01-05.
//

#include <stdint.h>
#include <stdio.h>

extern unsigned char *USBDevice;
extern size_t USBDeviceSize;
extern unsigned char *USBConfiguration;
extern size_t USBConfigurationSize;

void print_data(unsigned char *p, long size) {
  printf("Size: %lu\n", size);

  for (int i = 0; i < size; ++i) {
    if (i && i % 10 == 0) {
      printf("\n");
    }

    printf("%02x ", *(p + i));
  }
  printf("\n");
}

int main() {
  print_data(USBDevice, USBDeviceSize);
  print_data(USBConfiguration, USBConfigurationSize);
}
