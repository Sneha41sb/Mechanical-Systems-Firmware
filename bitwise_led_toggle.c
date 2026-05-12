void setup() {
  // Address for Output Enable
  volatile uint32_t *gpio_out_en_reg = (volatile uint32_t *)0x3FF44020;
  // Set Pin 2 (LED) as OUTPUT
  *gpio_out_en_reg |= (1 << 2);
  // Pin 4 is INPUT by default
}

void loop() {
  // Input Register (Reading the world)
  volatile uint32_t *gpio_in_reg = (volatile uint32_t *)0x3FF4403C;
  // Output Register (Changing the world)
  volatile uint32_t *gpio_out_reg = (volatile uint32_t *)0x3FF44004;

  // THEORY: Is Pin 4 HIGH? 
  if (*gpio_in_reg & (1 << 4)) {
      // Logic: If sensor is HIGH, blink/toggle LED
      *gpio_out_reg ^= (1 << 2); 
  } else {
      // Logic: If sensor is LOW, force LED OFF (Emergency State)
      *gpio_out_reg &= ~(1 << 2);
  }

  for(volatile int i = 0; i < 200000; i++); 
}
