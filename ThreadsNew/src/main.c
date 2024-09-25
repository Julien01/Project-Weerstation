#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <string.h>

/* Definieer de grootte van de stack voor de threads */
#define STACKSIZE 1024
#define PRIORITY 7

/* LED node definities */
#define LED0_NODE DT_ALIAS(led0) // Definieer de alias voor LED0
#define LED1_NODE DT_ALIAS(led1) // Definieer de alias voor LED1

/* Sensor apparaat aanroepen */
const struct device *const bme280_dev = DEVICE_DT_GET_ANY(bosch_bme280); // Verkrijg de BME280 sensor

/* Gedeelde temperatuur variabele */
volatile int32_t temperature; // Variabele om de temperatuur op te slaan
K_MUTEX_DEFINE(temp_mutex); // Mutex om toegang tot de temperatuur te synchroniseren

/* Structuur voor LED's */
struct led {
    struct gpio_dt_spec spec; // Specificaties van de GPIO
    uint8_t num;              // Nummer van de LED
};

/* Initialiseer LED0 */
static const struct led led0 = {
    .spec = GPIO_DT_SPEC_GET_OR(LED0_NODE, gpios, {0}), // Verkrijg GPIO specificaties voor LED0
    .num = 0, // Nummer van LED0
};

/* Initialiseer LED1 */
static const struct led led1 = {
    .spec = GPIO_DT_SPEC_GET_OR(LED1_NODE, gpios, {0}), // Verkrijg GPIO specificaties voor LED1
    .num = 1, // Nummer van LED1
};

/* Functie om de LED's te laten knipperen op basis van de temperatuur */
void blink_leds(void)
{
    // Configureer de LED's als output
    int ret = gpio_pin_configure_dt(&led0.spec, GPIO_OUTPUT_ACTIVE);
    ret |= gpio_pin_configure_dt(&led1.spec, GPIO_OUTPUT_ACTIVE);

    if (ret < 0) {
        printk("Kon LED's niet configureren\n"); // Foutmelding als configuratie mislukt
        return;
    }

    while (1) {
        k_mutex_lock(&temp_mutex, K_FOREVER); // Vergrendel mutex om toegang tot temperatuur te verkrijgen
        int32_t current_temp = temperature; // Verkrijg de huidige temperatuur
        k_mutex_unlock(&temp_mutex); // Ontgrendel de mutex

        // Controleer de temperatuur en pas de LED's aan
        if (current_temp > 25000000) { // Hoger dan 25°C (25000000 micrograden)
            gpio_pin_set_dt(&led0.spec, 1);  // Zet LED0 (groen) aan
            gpio_pin_set_dt(&led1.spec, 0);  // Zet LED1 (rood) uit
        } else if (current_temp < 24000000) { // Lager dan 24°C (24000000 micrograden)
            gpio_pin_set_dt(&led0.spec, 0);  // Zet LED0 (groen) uit
            gpio_pin_set_dt(&led1.spec, 1);  // Zet LED1 (rood) aan
        } else {
            gpio_pin_set_dt(&led0.spec, 0);  // Zet beide LED's uit
            gpio_pin_set_dt(&led1.spec, 0);
        }

        k_msleep(500); // Wacht 1 seconde voordat je opnieuw controleert
    }
}

/* Thread om de temperatuur te lezen */
void read_temperature(void)
{
    // Controleer of de sensor klaar is
    if (!device_is_ready(bme280_dev)) {
        printk("Sensor niet gereed\n"); // Foutmelding als sensor niet klaar is
        return;
    }

    struct sensor_value temp; // Struct om temperatuurwaarde op te slaan

    while (1) {
        sensor_sample_fetch(bme280_dev); // Verkrijg een nieuwe temperatuurmeting
        sensor_channel_get(bme280_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp); // Verkrijg de temperatuurwaarde

        k_mutex_lock(&temp_mutex, K_FOREVER); // Vergrendel mutex om toegang tot de temperatuurvariabele te verkrijgen
        temperature = temp.val1 * 1000000 + temp.val2; // Zet temperatuur om naar micrograden
        k_mutex_unlock(&temp_mutex); // Ontgrendel de mutex

        printk("Temperatuur: %d.%06d C\n", temp.val1, temp.val2); // Print de temperatuur
        k_msleep(1000); // Wacht 1 seconde voordat je opnieuw leest
    }
}

/* Definieer de threads voor temperatuurmeting en LED knipperen */
K_THREAD_DEFINE(sensor_thread_id, STACKSIZE, read_temperature, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(led_thread_id, STACKSIZE, blink_leds, NULL, NULL, NULL, PRIORITY, 0, 0);

int main()
{
    printk("Systeem gestart\n"); // Meld dat het systeem is gestart
    return 0; // Eindig de hoofdthread
}