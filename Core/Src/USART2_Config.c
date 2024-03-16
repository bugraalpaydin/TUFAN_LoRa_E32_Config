 #include "stm32f1xx.h"

void USART2_Init(void){
    RCC -> APB2ENR |= (1<<0);
    RCC -> APB2ENR |= (1<<2);
    RCC -> APB1ENR |= (1<<17);

    GPIOA->CRL = 0;
    GPIOA->CRL |= (3<<8);   // output mode 50 MHz for PA2
    GPIOA->CRL |= (2<<10);  // Alternate Func Push Pull For PA2
    
    GPIOA->CRL &= ~(3<<12);   // Intput Mode For PA3
    GPIOA->CRL |= (2<<14);  // Input Pull Up/ Down For PA3	
    
    
    USART2->CR1 |= (1<<13);
    USART2->CR1 &= ~(1<<12);
    
    USART2->CR1 |= (1<<3);
    
    USART2->CR1 |= (1<<2);
    
    USART2->CR2 &= ~(1<<12);
    USART2->CR2 &= ~(1<<13);

    USART2->BRR = (234<<4) | (6<<0);
}
void USART2_SendData(uint8_t data){
    USART2->DR = (data);
}
void USART2_ReceiveData(uint8_t data){
    if ((USART2->SR & USART_SR_RXNE) != RESET)
    {
        data = USART2->DR;
    }
}