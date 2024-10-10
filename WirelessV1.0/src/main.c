#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/sensor.h>
#include <string.h>
#include <stdio.h>

#define UART_DEVICE_NODE DT_NODELABEL(usart1)

// BME280 Sensor
const struct device *const bme280_dev = DEVICE_DT_GET_ANY(bosch_bme280);

// ESP8266 Module
static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

volatile int32_t temperature, humidity, pressure;
K_MUTEX_DEFINE(temp_mutex);


void print_uart(const char *buf)
{
    int msg_len = strlen(buf);
    for (int i = 0; i < msg_len; i++) {
        uart_poll_out(uart_dev, buf[i]);
    }
}

void read_bme280_data(void)
{
    struct sensor_value temp, hum, press;

    if (sensor_sample_fetch(bme280_dev) < 0) {
        printk("Failed to fetch data from BME280 sensor\n");
        return;
    }

    // Retrieve temperature, humidity, and pressure values
    sensor_channel_get(bme280_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    sensor_channel_get(bme280_dev, SENSOR_CHAN_HUMIDITY, &hum);
    sensor_channel_get(bme280_dev, SENSOR_CHAN_PRESS, &press);

    // Convert + store values
    k_mutex_lock(&temp_mutex, K_FOREVER);
    temperature = sensor_value_to_double(&temp) ;
    humidity = sensor_value_to_double(&hum) ;
    pressure = sensor_value_to_double(&press);
    k_mutex_unlock(&temp_mutex);
}

/* Function to send sensor data to the web server */
void send_sensor_data(void)
{
    char data_to_send[100];
    const char *uid = "Poepje";  // UID

    // Prepare sensor data string 
    k_mutex_lock(&temp_mutex, K_FOREVER);
    sprintf(data_to_send, "Temp=%d&Humidity=%d&Pressure=%d&UID=%s", 
            temperature, humidity, pressure, uid);
    k_mutex_unlock(&temp_mutex);

    // Prepare HTTP request headers
    char http_request[200];
    sprintf(http_request, 
        "POST /Weerstation.php HTTP/1.1\r\n"
        "Host: 195.201.2.165\r\n"
        "Connection: keep-alive\r\n"  // Keep connection alive after request
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s",
        strlen(data_to_send),  // Content length
        data_to_send);         // Actual data to send

    // Calculate length of HTTP request
    print_uart("AT+CIPSEND=");
    char send_length[10];
    sprintf(send_length, "%zu\r\n", strlen(http_request));
    print_uart(send_length);

    k_sleep(K_MSEC(2000));

    // Send HTTP request
    print_uart(http_request);
}

void main(void)
{

    // Set to command mode (non-transparent mode)
    print_uart("AT+CIPMODE=0\r\n");
    k_sleep(K_MSEC(500));

    // Connect to Wi-Fi 
    print_uart("AT+CWJAP=\"//yourWifiDomain\",\"yourWifiPassword\"\r\n");
    k_sleep(K_MSEC(11000));

    // Start TCP connection
    print_uart("AT+CIPSTART=\"TCP\",\"195.201.2.165\",80\r\n");
    k_sleep(K_MSEC(6000));

    while (1) {
        read_bme280_data();
        send_sensor_data();
        k_sleep(K_MSEC(58000));
    }
}