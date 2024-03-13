#include "TUFAN_LoRa_E32_Config.h"
#include "stm32f1xx.h"
//#include "statesDefine.h"

void setConfiguration(UART_HandleTypeDef *huart, struct CONFIG Configuration /*,enum PROGRAM_COMMAND saveType*/){
    uint8_t speedConfig;
    uint8_t optionConfig;
    // struct CONFIG config;
    // config.HEAD = 0xC0;
    // config.ADDH = 0x0;
    // config.ADDL = 0x1D;
    // config.CHAN = 0x17;
    // config.OPTION.FEC = FEC_1_ON;
    // config.OPTION.FixedTransmission = FT_FIXED_TRANSMISSION;
    // config.OPTION.IODriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
    // config.OPTION.TransmissionPower = POWER_30;
    // config.OPTION.WirelessWakeupTime = WAKE_UP_250;
    // config.SPED.AirDataRate = UART_BPS_2400;
    // config.SPED.UartBaudRate = UART_BPS_9600;
    // config.SPED.UartParity = MODE_00_8N1;
    speedConfig = (Configuration.SPED.UartParity << 6) | (Configuration.SPED.UartBaudRate <<3) | (Configuration.SPED.AirDataRate);
    optionConfig = (Configuration.OPTION.FixedTransmission << 7) | (Configuration.OPTION.IODriveMode << 6) | (Configuration.OPTION.WirelessWakeupTime << 3) | (Configuration.OPTION.FEC << 2) | (Configuration.OPTION.TransmissionPower);

    //HAL_UART_Transmit(huart, Configuration.HEAD, sizeof(Configuration.HEAD), 1);
    USART2 -> DR = Configuration.HEAD; 
    HAL_Delay(1);
    USART2 -> DR = Configuration.ADDH; 
    HAL_Delay(1);
    USART2 -> DR = Configuration.ADDL;
    HAL_Delay(1);
    USART2 -> DR = speedConfig; 
    HAL_Delay(1);
    USART2 -> DR = Configuration.CHAN; 
    HAL_Delay(1);
    USART2 -> DR = optionConfig; 
}
void getConfiguration(UART_HandleTypeDef *huart){
    uint8_t getConfig = 0xC1;
    uint8_t *pgetConfig = &getConfig;
    uint8_t receivedConfig[48];
    for(int i = 0; i<=2;i++){
        HAL_UART_Transmit(huart, pgetConfig, sizeof(getConfig), 1);

    }
    HAL_UART_Receive(huart, receivedConfig, 48, 1);
    HAL_Delay(1000);
}
void getModuleInformation(UART_HandleTypeDef *huart){
    uint8_t getInformation = 0xC3;
    uint8_t *pgetInformation = &getInformation;
    uint8_t receivedInformation[48];
    for(int i = 0; i<=2; i++){
        HAL_UART_Transmit(huart, pgetInformation, sizeof(getInformation), 1);
    }
    HAL_UART_Receive(huart, receivedInformation, 48, 1);
    HAL_Delay(1000);
}
void resetModule(UART_HandleTypeDef *huart){
    uint8_t reset = 0xC4;
    uint8_t *preset = &reset;
    for(int i = 0; i<=2; i++){
        HAL_UART_Transmit(huart, preset, sizeof(reset), 1);
    }
}

void sendFixedMessage(UART_HandleTypeDef *huart, uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, uint8_t message){
    uint8_t *pADDH = &ADDH;
    uint8_t *pADDL = &ADDL;
    uint8_t *pCHAN = &CHAN;
    uint8_t *pmessage = &message;
    HAL_UART_Transmit(huart, pADDH, sizeof(ADDH), 1);
    HAL_UART_Transmit(huart, pADDL, sizeof(ADDL), 1);
    HAL_UART_Transmit(huart, pCHAN, sizeof(CHAN), 1);
    HAL_UART_Transmit(huart, pmessage, sizeof(message), 1);

    // USART2 -> DR = ADDH;
    // HAL_Delay(1);
    // USART2 -> DR = ADDL;
    // HAL_Delay(1);
    // USART2 -> DR = CHAN;
    // HAL_Delay(1);
    // USART2 -> DR = message;
}

void receiveMessage(UART_HandleTypeDef *huart){
    uint8_t RxMessage;
    uint8_t *pRXMessage = &RxMessage;
    HAL_UART_Receive(huart, *pRXMessage, sizeof(1), 1);

}
void cleanUARTBuffer(UART_HandleTypeDef *huart){
    HAL_UART_Receive_IT(huart, (uint8_t *)NULL, 0);
}