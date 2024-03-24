/*
 * Created on: 21.03.24
 * Author: vadimkim
 *
 */
#ifndef _MAX30002_H_
#define _MAX30002_H_

#include "mbed.h"

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

  /************* Registers *********************/
  /**
   * @brief STATUS (0x01)
   */
  union status_reg {
    uint32_t all;
    struct {
      uint32_t ldoff_nl : 1;  //[0]
      uint32_t ldoff_nh : 1;  //[1]
      uint32_t ldoff_pl : 1;  //[2]
      uint32_t ldoff_ph : 1;  //[3]
      uint32_t bcgmn : 1;     //[4]
      uint32_t bcgmp : 1;     //[5]
      uint32_t reserved1 : 1; //[6]
      uint32_t reserved2 : 1; //[7]

      uint32_t pllint : 1;    //[8]
      uint32_t samp : 1;      //[9]
      uint32_t reserved3 : 1; //[10]
      uint32_t lonint : 1;    //[11]
      uint32_t reserved4 : 3; //[12:14]
      uint32_t bcgmon : 1;    //[15]

      uint32_t bundr : 1;     //[16]
      uint32_t bover : 1;     //[17]
      uint32_t bovf : 1;      //[18]
      uint32_t bint : 1;      //[19]
      uint32_t dcloffint : 1; //[20]

      uint32_t reserved5 : 11; //[21:31]
    } bit;
  };

  /**
   * @brief INFO (0x0F)
   */
  union info_reg {
    uint32_t all;
    struct {
      uint32_t reserved : 16; // [0:15]
      uint32_t rev_id : 4;    // [16:19]
      uint32_t fixed : 12;    // [20:31]
    } bit;
  };

  /**
   * @brief CNFG_GEN (0x10)
   */
  union cnfg_gen_reg {
    uint32_t all;
    struct {
      uint32_t rbiasn : 1;   //[0]
      uint32_t rbiasp : 1;   //[1]
      uint32_t rbiasv : 2;   //[2:3]
      uint32_t en_rbias : 2; //[4:5]
      uint32_t vth : 2;      //[6:7]

      uint32_t imag : 3;      //[8:10]
      uint32_t ipol : 1;      //[11]
      uint32_t en_dcloff : 2; //[12:13]
      uint32_t en_bloff : 2;  //[14:15]

      uint32_t reserved1 : 2;  //[16:17]
      uint32_t en_bioz : 1;    //[18]
      uint32_t reserved2 : 1;  //[19]
      uint32_t fmstr : 2;      //[20:21]
      uint32_t en_ulp_lon : 2; //[22:23]

      uint32_t reserved3 : 8; //[24:31]
    } bit;
  };

  /**
   * @brief CNFG_BIOZ   (0x18)
   */
  union bioz_reg {
    uint32_t all;
    struct {
      uint32_t phoff : 4; //[0:3]
      uint32_t cgmag : 3; //[4:6]
      uint32_t cgmon : 1; //[7]

      uint32_t fcgen : 4; //[8:11]
      uint32_t dlpf : 2;  //[12:13]
      uint32_t dhpf : 2;  //[14:15]

      uint32_t gain : 2;        //[16:17]
      uint32_t inapow_mode : 1; //[18]
      uint32_t ext_rbias : 1;   //[19]
      uint32_t ahpf : 3;        //[20:22]
      uint32_t rate : 1;        //[23]

      uint32_t reserved : 8; //[24:31]
    } bit;
  };

  /****** End of reegisters definition *********/

  /**
   * @brief MAX30002 constructor
   * @param spi SPI object
   * @param cs PIN for chip select
   */
  MAX30002(SPI &spi, DigitalOut &cs);

  /* Public functions */
  int readRegister(REG_map_t reg, uint32_t *data);
  int writeRegister(REG_map_t reg, uint32_t data);

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

#endif //_MAX30002_H_