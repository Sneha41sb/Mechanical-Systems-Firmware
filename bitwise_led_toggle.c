void setup() {
  // Address for Output Enable
  volatile uint32_t *gpio_out_en_reg = (volatile uint32_t *)0x3FF44020;
  // Set Pin 2 (LED) as OUTPUT
  *gpio_out_en_reg |= (1 << 2);

}

void loop() {
 
  volatile uint32_t *gpio_in_reg = (volatile uint32_t *)0x3FF4403C;
 
  volatile uint32_t *gpio_out_reg = (volatile uint32_t *)0x3FF44004;

  
  if (*gpio_in_reg & (1 << 4)) {
    
      *gpio_out_reg ^= (1 << 2); 
  } else {
      *gpio_out_reg &= ~(1 << 2);
  }

  for(volatile int i = 0; i < 200000; i++); 
}
