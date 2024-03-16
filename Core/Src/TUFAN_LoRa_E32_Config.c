#include "TUFAN_LoRa_E32_Config.h"
#include "stm32f1xx.h"


void setConfiguration(struct CONFIG Configuration){
    uint8_t speedConfig;
    uint8_t optionConfig;

    speedConfig = (Configuration.SPED.UartParity << 6) | (Configuration.SPED.UartBaudRate <<3) | (Configuration.SPED.AirDataRate);
    optionConfig = (Configuration.OPTION.FixedTransmission << 7) | (Configuration.OPTION.IODriveMode << 6) | (Configuration.OPTION.WirelessWakeupTime << 3) | (Configuration.OPTION.FEC << 2) | (Configuration.OPTION.TransmissionPower);

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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
    uint8_t getConfig = 0xC1;
    uint8_t *pgetConfig = &getConfig;
    uint8_t receivedConfig[48];
    for(int i = 0; i<=2;i++){
        HAL_UART_Transmit(huart, pgetConfig, sizeof(getConfig), 1);

    }
    HAL_UART_Receive(huart, receivedConfig, 48, 1);
}
void getModuleInformation(UART_HandleTypeDef *huart){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
    uint8_t getInformation = 0xC3;
    uint8_t *pgetInformation = &getInformation;
    uint8_t receivedInformation[48];
    for(int i = 0; i<=2; i++){
        HAL_UART_Transmit(huart, pgetInformation, sizeof(getInformation), 1);
    }
    HAL_UART_Receive(huart, receivedInformation, 48, 1);
}
void resetModule(UART_HandleTypeDef *huart){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
    uint8_t reset = 0xC4;
    uint8_t *preset = &reset;
    for(int i = 0; i<=2; i++){
        HAL_UART_Transmit(huart, preset, sizeof(reset), 1);
    }
}

void sendFixedMessage(UART_HandleTypeDef *huart, uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, uint8_t message){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
    uint8_t RxMessage;
    uint8_t *pRXMessage = &RxMessage;
    HAL_UART_Receive(huart, pRXMessage, sizeof(1), 1);

}
void cleanUARTBuffer(UART_HandleTypeDef *huart){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
    HAL_UART_Receive_IT(huart, (uint8_t *)NULL, 0);
}