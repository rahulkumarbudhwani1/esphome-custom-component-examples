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

}

void EmptyUARTSensor::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART sensor");
}

}  // namespace empty_UART_sensor
}  // namespace esphome
