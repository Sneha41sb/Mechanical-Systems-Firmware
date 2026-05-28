#include <stdint.h>


typedef struct {
    volatile uint32_t out;          // Address Offset 0x00: Controls Output states (High/Low)
    volatile uint32_t out_w1ts;     // Address Offset 0x04: Write 1 to Set specific output pins HIGH
    volatile uint32_t out_w1tc;     // Address Offset 0x08: Write 1 to Clear specific output pins LOW
    volatile uint32_t enable;       // Address Offset 0x0C: Controls Pin Direction (Input vs Output)
    uint32_t reserved[11];          // Memory Padding: Skips unneeded hardware registers in between
    volatile uint32_t in;           // Address Offset 0x3C: Reads physical Input voltage states
} Industrial_GPIO_t;

// Define base address for ESP32 GPIO block
#define GPIO_BASE_ADDRESS 0x3FF44004

void setup() {
    // 2. HARDWARE STRUCT POINTER INTERLOCK
    // Map our physical base register memory location to our structured layout template
    Industrial_GPIO_t *GPIO_Panel = (Industrial_GPIO_t *)GPIO_BASE_ADDRESS;

    // Set GPIO 2 (LED Actuator) as an OUTPUT pin
    // Using bitwise OR (|) to set bit 2 high without shifting other configurations
    GPIO_Panel->enable |= (1 << 2);

    // Ensure GPIO 4 (Safety Interlock) is explicitly set as an INPUT pin
    // Using bitwise AND-NOT (~&) to surgically clear bit 4 to zero
    GPIO_Panel->enable &= ~(1 << 4);
}

void loop() {
    // Re-instantiate the reference pointer to our hardware structure
    Industrial_GPIO_t *GPIO_Panel = (Industrial_GPIO_t *)GPIO_BASE_ADDRESS;

    // 3. TESTING BITS VIA MASKING
    // Check if the physical Input data register has bit 4 set high (Switch turned to 3.3V position)
    if (GPIO_Panel->in & (1 << 4)) {
        
        // INTERLOCK ACTIVE: Toggle the Indicator LED (Bit 2) using Bitwise XOR (^)
        GPIO_Panel->out ^= (1 << 2);
        
        // Mechanical control loop timing buffer
        for(volatile uint32_t i = 0; i < 150000; i++);
    } else {
        // INTERLOCK SAFE: Force the system state low using Write-1-to-Clear Register
        // This is a highly efficient way to instantly clear an output bit safely
        GPIO_Panel->out_w1tc = (1 << 2);
    }
}
