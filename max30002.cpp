/*
 * Created on: 21.03.24
 * Author: vadimkim
 *
 */

#include "max30002.h"
#include "mbed.h"

MAX30002::MAX30002(SPI &spi, DigitalOut &cs) : m_spi(spi), m_cs(cs) {
  m_cs = 1;
}