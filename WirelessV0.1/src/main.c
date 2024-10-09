
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include <string.h>

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_NODELABEL(usart1)

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/*
 * Print a null-terminated string character by character to the UART interface
 */
void print_uart(char *buf)
{
    int msg_len = strlen(buf);
    for (int i = 0; i < msg_len; i++) {
        uart_poll_out(uart_dev, buf[i]);
    }
}

int main(void)
{
    if (!device_is_ready(uart_dev)) {
        printk("UART device not found!");
        return 0;
    }

    /* Initialize UART */
    print_uart("AT\r\n");
    k_sleep(K_MSEC(500));
    
    /* Set ESP8266 to Transparent Mode */
    print_uart("AT+CIPMODE=1\r\n");
    k_sleep(K_MSEC(500));
    
    /* Connect to WiFi */
    print_uart("AT+CWJAP=\"AvansWlan\",\"\"\r\n");
    k_sleep(K_MSEC(10000));
    
    /* Establish TCP connection */
    print_uart("AT+CIPSTART=\"TCP\",\"http://localhost/Weerstation/Weerstation.php\",80\r\n");
    k_sleep(K_MSEC(10000));
    
    /* Send Data */
    print_uart("AT+CIPSEND=\"47\"\r\n");
    k_sleep(K_MSEC(10000));
    print_uart("Temp=22.5&Humidity=55&Pressure=1013&UID=Poepje\r\n");
} 