#include <stdint.h>

typedef struct {
    volatile uint32_t out;        
    volatile uint32_t out_w1ts;   
    volatile uint32_t out_w1tc;    
    volatile uint32_t enable;     
} GPIO_Reg_t;

void setup() {
    GPIO_Reg_t *GPIO = (GPIO_Reg_t *)0x3FF44004;  
    GPIO->enable |= (1 << 2);
}

void loop() {
    GPIO_Reg_t *GPIO = (GPIO_Reg_t *)0x3FF44004;
    GPIO->out ^= (1 << 2);
    for(volatile int i = 0; i < 500000; i++);
}
