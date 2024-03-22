/*
 * Created on: 21.03.24
 * Author: vadimkim
 *
 */

#include "max30002.h"
#include "mbed.h"

MAX30002::MAX30002(SPI &spi, DigitalOut &cs) : m_spi(spi), m_cs(cs) {
  m_cs.write(1); // disable communication by default
}

int MAX30002::readRegister(REG_map_t reg, uint32_t *data) {
  uint8_t result[4];
  uint8_t data_array[1];
  int32_t success = 0;

  data_array[0] = ((reg << 1) & 0xff) | 1; // read operation
  success = sendSPI(data_array, 1, result, 4);
  // Response has only has 3 meaningful bytes at MAX, so result[0] can be
  // ingored
  *data = (uint32_t)(result[1] << 16) + (result[2] << 8) + result[3];

  if (success != 0) {
    return -1;
  } else {
    return 0;
  }
}

int MAX30002::sendSPI(uint8_t *tx_buf, uint8_t tx_size, uint8_t *rx_buf,
                      uint8_t rx_size) {

  m_cs.write(0);
  for (int i = 0; i < tx_size; i++) {
    m_spi.write(tx_buf[i]);
  }
  for (int i = 0; i < (rx_size - tx_size); i++) {
    rx_buf[i + 1] = m_spi.write(0xFF);
  }
  m_cs.write(1);

  return 0;
}