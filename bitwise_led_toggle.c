//xor
void setup() {
  volatile uint32_t *gpio_out_en_reg = (volatile uint32_t *)0x3FF44020;
  *gpio_out_en_reg |= (1 << 2); 
}

void loop() {
  volatile uint32_t *gpio_out_reg = (volatile uint32_t *)0x3FF44004;
  *gpio_out_reg ^= (1 << 2); 
  for(volatile int i = 0; i < 500000; i++); 
}
