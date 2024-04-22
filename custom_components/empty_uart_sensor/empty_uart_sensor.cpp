#include "esphome/core/log.h"
#include "empty_uart_sensor.h"

namespace esphome {
namespace empty_uart_sensor {

static const char *TAG = "empty_uart_sensor.sensor";

void EmptyUARTSensor::setup() {
    // Set up UART communication with specific serial configurations
    this->begin(9600, SERIAL_8E1);
    byte enableConfigCommand[] = {0x44, 0x11, 0x00, 0x00, 0x55, 0x4B};
    this->write_array(enableConfigCommand, sizeof(enableConfigCommand));
    delay(1000);

    if (available() > 1) {
      uint8_t received_data;
      read_array(received_data, 1);
      handle_data(received_data);
      ESP_LOGD("LD6001", "Received data: %s", format_hex(received_data).c_str());
    }

    
}

void EmptyUARTSensor::update() {

}

void EmptyUARTSensor::loop() {
    uint8_t command[] = {
    0x44, // Byte0: Header
    0x62, // Byte1: Command ID for getting radar detection data
    0x08, // Byte2: Data Length
    0x00, // Byte3: Reserved
    0x20, // Byte4: Sensitivity property (normal sensitivity)
    0x00, // Byte5: Reserved
    0x00, // Byte6: Reserved
    0x00, // Byte7: Reserved
    0x00, // Byte8: Reserved
    0x00, // Byte9: Reserved
    0x00, // Byte10: Reserved
    0x00, // Byte11: Reserved
    0x00, // Byte12: Checksum (placeholder)
    0x4B  // Byte13: End of message marker
      };

      // Calculate and set the checksum
    for (int i = 0; i < 12; i++) { // Exclude checksum byte itself
        command[12] += command[i];
    }
    command[12] = command[12] % 256; // Ensure checksum is one byte
    this->write_array(command, sizeof(command));

    ESP_LOGD("LD6001", "Sent 'Get Radar Detection Data' command.");
    delay(200);
}

void EmptyUARTSensor::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART sensor");
}

}  // namespace empty_UART_sensor
}  // namespace esphome
