/*
 * Created on: 21.03.24
 * Author: vadimkim
 *
 */

#include "mbed.h"
#include <cstdint>

class MAX30002 {
public:
  typedef enum { // register map
    STATUS = 0x01,
    EN_INT = 0x02,
    EN_INT2 = 0x03,
    MNGR_INT = 0x04,
    MNGR_DYN = 0x05,
    SW_RST = 0x08,
    SYNCH = 0x09,
    FIFO_RST = 0x0A,
    INFO = 0x0F,
    CNFG_GEN = 0x10,
    CNFG_BMUX = 0x17,
    CNFG_BIOZ = 0x18,
    FIFO_BURST = 0x22,
    FIFO = 0x23
  } REG_map_t;

  /*
   * @brief INFO (0x0F)
   */
  union max30002_info_reg {
    uint32_t all;
    struct {
      uint32_t reserved : 16; // [0:15]
      uint32_t rev_id : 4;    // [16:19]
      uint32_t fixed : 12;    // [20:31]
    } bit;
  };

  /*
   * @brief MAX30002 constructor
   * @param spi SPI object
   * @param cs PIN for chip select
   */
  MAX30002(SPI &spi, DigitalOut &cs);

  /* Public functions */
  int readRegister(REG_map_t reg, uint32_t *data);

private:
  /**
   * @brief Transmit and recieve 32bit SPI data
   * @param tx_buf transmit buffer
   * @param tx_size number of bytes to transmit
   * @param rx_buf recieve buffer
   * @param rx_size number of bytes to recieve
   */
  int sendSPI(uint8_t *tx_buf, uint8_t tx_size, uint8_t *rx_buf,
              uint8_t rx_size);
  SPI &m_spi;
  DigitalOut &m_cs;

}; // end of class