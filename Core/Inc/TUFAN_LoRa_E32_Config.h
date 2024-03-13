#include <stdint.h>
#include "statesDefine.h"
#include "stm32f1xx.h"

//LoRa Mode Type
enum MODE_TYPE {
    MODE_O_NORMAL           = 0,        //UART and wireless channel are open M0: 0, M1:0        
    MODE_1_WAKE_UP          = 1,        //It will add a code before data packet and awaken receiver works in mode 2 M0: 0, M1: 1
    MODE_2_POWER_SAVING     = 2,        //UART is disabled, wireless module works at WOR mode M0: 1, M1: 0
    MODE_3_SLEEP            = 3,        //Sleep & Parameter setting    
    MODE_4_PROGRAM          = 3,
};

enum PROGRAM_COMMAND {
    SET_CFG_PWR_DWN_SAVE    = 0xC0,     //Set config, save it when power off
    READ_CONFIGURATION      = 0xC1,     //Send three 0xC1, module returns the saved parameters   
    SET_CFG_PWR_DWN_LOSE    = 0xC2,     //Set config, do not save it when power off
    READ_MODULE_VERSION     = 0xC3,     //Send three 0xC3, module returns the version informations
    RESET_MODULE            = 0xC4      //Send three 0xC4, module will reset one time 
};


struct SPEED {
    uint8_t AirDataRate     : 3;        //4. byte; 2, 1, 0. bits  
    uint8_t UartBaudRate    : 3;        //4. byte; 5, 4, 3. bits 
    uint8_t UartParity      : 2;        //4. byte; 7, 6. bits
};


struct OPTION {
    uint8_t TransmissionPower  : 2;     //5. byte; 1, 0. bits
    uint8_t FEC                : 1;     //5. byte; 2. bit
    uint8_t WirelessWakeupTime : 3;     //5. byte; 5, 4, 3. b,ts
    uint8_t IODriveMode       : 1;      //5. byte; 6. bit
    uint8_t FixedTransmission  : 1;     //5. byte; 7. bit
};

struct CONFIG {
    uint8_t HEAD;                       //0. byte must be 0xC0 or 0xC2
    uint8_t ADDL;                       //2. byte, Low adress byte of module 00H - FFH (Default 00H)
    uint8_t ADDH;                       //1. byte, HIGH adress byte of module 00H - FFH (Default OOH)        
    struct SPEED SPED;                  //3. byte has 8 bits
    uint8_t CHAN;                       //4. byte,  00H - 1FH correspond to 410 ~ 441 MHz (Default 17, 433 MHz)
    struct OPTION OPTION;               //5. byte, has 8 bits

};

struct MODULE_INFORMATION {
    uint8_t HEAD;
    uint8_t FREQ;
    uint8_t VERSION;
    uint8_t FEATURES;
};




void LoRa_Init(uint8_t Rx_Pin, uint8_t Tx_Pin, uint8_t AUX_Pin, uint8_t M0_Pin, uint8_t M1_Pin, enum UART_BPS_RATE bpsRate);
void setConfiguration(UART_HandleTypeDef *huart, struct CONFIG Configuration, enum PROGRAM_COMMAND saveType);
uint8_t getConfiguration(UART_HandleTypeDef *huart);
uint8_t getModuleInformation(UART_HandleTypeDef *huart);
void resetModule(UART_HandleTypeDef *huart);
void sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, void* message);
uint8_t receiveMessage(void);
void cleanUARTBuffer(UART_HandleTypeDef *huart);
void setLoRaMode(uint8_t M0_Pin, uint8_t M1_Pin, enum MODE_TYPE mode);
//void waitCompleteResponse(void);
