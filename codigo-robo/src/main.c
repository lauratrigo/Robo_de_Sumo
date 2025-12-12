#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

// --- Sensores segue-faixa ---
#define SF_DIR_GPIO 14
#define SF_CEN_GPIO 26
#define SF_ESQ_GPIO 27

// --- LEDs / motores ---
#define LED_VERMELHO GPIO_NUM_32
#define LED_AZUL GPIO_NUM_33
#define LED_ROXO GPIO_NUM_18
#define LED_CIANO GPIO_NUM_19

// --- Sensores ultrassônicos ---
#define TRIG1_GPIO 23
#define ECHO1_GPIO 22
#define TRIG2_GPIO 21
#define ECHO2_GPIO 25

// --- Protótipos ---
void setup();
void loop();
void app_main();
void setup_hc_sr04(int trig_pin, int echo_pin);
int ler_HC_SR04(int trig_pin, int echo_pin);
void move_motores(int fv, int fa, int rv, int rc);

// ======================================================
// Função motor lento (PWM manual)
// ======================================================
void motor_lento(int pino, int estado, int duty)
{
    static uint64_t ultimo_tempo = 0;
    uint64_t agora = esp_timer_get_time();

    const int periodo = 3000; // 3 ms

    if (agora - ultimo_tempo >= periodo)
        ultimo_tempo = agora;

    int tempo_ligado = (periodo * duty) / 100;

    if (estado == 1)
    {
        if ((agora - ultimo_tempo) < tempo_ligado)
            gpio_set_level(pino, 1);
        else
            gpio_set_level(pino, 0);
    }
    else
        gpio_set_level(pino, 0);
}

// ======================================================
// Função que aplica os estados aos motores
// ======================================================
void move_motores(int fv, int fa, int rv, int rc)
{
    motor_lento(LED_VERMELHO, fv, 20);
    motor_lento(LED_AZUL, fa, 20);
    motor_lento(LED_ROXO, rv, 20);
    motor_lento(LED_CIANO, rc, 20);
}

// ======================================================
// Ultrassônico
// ======================================================
void setup_hc_sr04(int trig_pin, int echo_pin)
{
    gpio_set_direction(trig_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(echo_pin, GPIO_MODE_INPUT);
    gpio_set_level(trig_pin, 0);
}

int ler_HC_SR04(int trig_pin, int echo_pin)
{
    gpio_set_level(trig_pin, 1);
    esp_rom_delay_us(10);
    gpio_set_level(trig_pin, 0);

    uint64_t inicio_wait = esp_timer_get_time();
    while (gpio_get_level(echo_pin) == 0)
    {
        if (esp_timer_get_time() - inicio_wait > 25000)
            return -1;
    }

    uint64_t inicio_echo = esp_timer_get_time();
    while (gpio_get_level(echo_pin) == 1)
    {
        if (esp_timer_get_time() - inicio_echo > 25000)
            return -1;
    }

    uint64_t fim_echo = esp_timer_get_time();
    double tempo = (fim_echo - inicio_echo) / 1000000.0;

    return (int)((tempo * 34300) / 2.0);
}

// ======================================================
// SETUP
// ======================================================
void setup()
{
    gpio_set_direction(SF_DIR_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SF_DIR_GPIO, GPIO_PULLDOWN_ONLY);

    gpio_set_direction(SF_CEN_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SF_CEN_GPIO, GPIO_PULLDOWN_ONLY);

    gpio_set_direction(SF_ESQ_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SF_ESQ_GPIO, GPIO_PULLDOWN_ONLY);

    gpio_set_direction(LED_VERMELHO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_AZUL, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_ROXO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_CIANO, GPIO_MODE_OUTPUT);

    setup_hc_sr04(TRIG1_GPIO, ECHO1_GPIO);
    setup_hc_sr04(TRIG2_GPIO, ECHO2_GPIO);
}

// ======================================================
// LOOP PRINCIPAL
// ======================================================
void loop()
{
    vTaskDelay(pdMS_TO_TICKS(5000));

    while (1)
    {
        int distancia1 = ler_HC_SR04(TRIG1_GPIO, ECHO1_GPIO);
        int distancia2 = ler_HC_SR04(TRIG2_GPIO, ECHO2_GPIO);

        int dir = gpio_get_level(SF_DIR_GPIO);
        int cen = gpio_get_level(SF_CEN_GPIO);
        int esq = gpio_get_level(SF_ESQ_GPIO);

        // Prioridade 1: Ultrassônico
        if (distancia1 > 0 && distancia1 < 20)
        {
            move_motores(0, 0, 1, 1); // dá ré devagar
            continue;                 // não faz nada mais neste loop
        }
        else if (distancia2 > 0 && distancia2 < 20)
        {
            move_motores(1, 1, 0, 0); // vai pra frente devagar
            continue;                 // não faz nada mais neste loop
        }

        // Prioridade 2: Segue-faixa
        int frenteV = 0, frenteA = 0, reV = 1, reC = 0;

        if (cen == 0)
        {
            frenteV = 1;
            frenteA = 1;
            reV = 0;
            reC = 0;
        }
        else if (dir == 0 && esq == 0)
        {
            frenteV = 0;
            frenteA = 0;
            reV = 1;
            reC = 1;
        }
        else if (esq == 0)
        {
            frenteV = 0;
            frenteA = 1;
            reV = 1;
            reC = 0;
        }
        else if (dir == 0)
        {
            frenteV = 1;
            frenteA = 0;
            reV = 0;
            reC = 1;
        }

        move_motores(frenteV, frenteA, reV, reC);

        vTaskDelay(pdMS_TO_TICKS(5)); // pequena pausa
    }
}
void app_main()
{
    setup();
    loop();
}
