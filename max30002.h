/*
 * Created on: 21.03.24
 * Author: vadimkim
 *
 */

#include "mbed.h"
#include <cstdint>

class MAX30002 {
public:
  enum class REG_map_t : uint8_t { // register map
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
  };

  /*
   * @brief INFO (0x0F)
   */
  union max30001_info_reg {
    uint8_t all;
    struct {
      uint8_t reserved : 4;
      uint8_t rev_id : 4;
    } bit;
  };

  /*
   * @brief MAX30002 constructor
   * @param spi SPI object
   * @param cs PIN for chip select
   */
  MAX30002(SPI &spi, DigitalOut &cs);

private:
  SPI &m_spi;
  DigitalOut &m_cs;

}; // end of class