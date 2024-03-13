#include "TUFAN_LoRa_E32_Config.h"
#include "stm32f1xx.h"
//#include "statesDefine.h"

void setConfiguration(UART_HandleTypeDef *huart, struct CONFIG Configuration, enum PROGRAM_COMMAND saveType){
    uint8_t speedConfig;
    uint8_t optionConfig;
    struct CONFIG config;
    config.HEAD = 0xC0;
    config.ADDH = 0x0;
    config.ADDL = 0x1D;
    config.CHAN = 0x17;
    config.OPTION.FEC = FEC_1_ON;
    config.OPTION.FixedTransmission = FT_FIXED_TRANSMISSION;
    config.OPTION.IODriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
    config.OPTION.TransmissionPower = POWER_30;
    config.OPTION.WirelessWakeupTime = WAKE_UP_250;
    config.SPED.AirDataRate = UART_BPS_2400;
    config.SPED.UartBaudRate = UART_BPS_9600;
    config.SPED.UartParity = MODE_00_8N1;
    speedConfig = (config.SPED.UartParity << 6) | (config.SPED.UartBaudRate <<3) | (config.SPED.AirDataRate);
    optionConfig = (config.OPTION.FixedTransmission << 7) | (config.OPTION.IODriveMode << 6) | (config.OPTION.WirelessWakeupTime << 3) | (config.OPTION.FEC << 2) | (config.OPTION.TransmissionPower);

    USART2 -> DR = config.HEAD;
    USART2 -> DR = config.ADDH; 
    USART2 -> DR = config.ADDL; 
    USART2 -> DR = speedConfig; 
    USART2 -> DR = config.CHAN; 
    USART2 -> DR = optionConfig; 
}
uint8_t getConfiguration(UART_HandleTypeDef *huart){
    uint8_t getConfig = 0xC1;
    uint8_t *pgetConfig = &getConfig;
    uint8_t receivedConfig[48];
    for(int i = 0; i<2;i++){
        HAL_UART_Transmit(huart, pgetConfig, sizeof(getConfig), 1);
        HAL_Delay(100);
    }
    HAL_UART_Receive(huart, receivedConfig, 48, 1);
}
uint8_t getModuleInformation(UART_HandleTypeDef *huart){
    uint8_t getInformation = 0xC3;
    uint8_t *pgetInformation = &getInformation;
    uint8_t receivedInformation[48];
    for(int i = 0; i<2; i++){
        HAL_UART_Transmit(huart, pgetInformation, sizeof(getInformation), 1);
        HAL_Delay(100);
    }
    HAL_UART_Receive(huart, receivedInformation, 48, 1);
}
void resetModule(UART_HandleTypeDef *huart){
    uint8_t reset = 0xC4;
    uint8_t *preset = &reset;
    for(int i = 0; i<2; i++){
        HAL_UART_Transmit(huart, preset, sizeof(reset), 1);
        HAL_Delay(100);
    }
}

void sendFixedMessage(UART_HandleTypeDef *huart, uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, void message){
    USART2 -> DR = ADDH;
    USART2 -> DR = ADDL;
    USART2 -> DR = CHAN;
    USART2 -> DR = message;
}

uint8_t receiveMessage(void){
    //TODO
}
void cleanUARTBuffer(UART_HandleTypeDef *huart){
    HAL_UART_Receive_IT(huart, (uint8_t *)NULL, 0);
}