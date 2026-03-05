#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"

#define LED 2

static const char *TAG = "BLINK_APP";
static uint8_t led_level = 0;

// Inicializar LED
esp_err_t init_led(void)
{
    ESP_LOGI(TAG, "Inicializando LED...");

    gpio_reset_pin(LED);
    esp_err_t err = gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error al configurar el GPIO");
    } else {
        ESP_LOGI(TAG, "GPIO configurado correctamente");
    }

    return err;
}

// Cambiar estado del LED
esp_err_t blink_led(void)
{
    led_level = !led_level;

    if (led_level) {
        ESP_LOGW(TAG, "LED ENCENDIDO");
    } else {
        ESP_LOGW(TAG, "LED APAGADO");
    }

    ESP_LOGD(TAG, "Nivel actual del LED: %d", led_level);

    return gpio_set_level(LED, led_level);
}

void app_main(void)
{
    // 🔹 Aquí eliges el nivel de log
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    // Puedes cambiar a:
    // ESP_LOG_ERROR
    // ESP_LOG_WARN
    // ESP_LOG_INFO
    // ESP_LOG_DEBUG

    ESP_LOGI(TAG, "Iniciando aplicación Blink");

    ESP_ERROR_CHECK(init_led());

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));  // Retardo de 1 segundo
        ESP_ERROR_CHECK(blink_led());
    }
}