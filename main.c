#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

// --- Définition des broches ---
#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define BTN1 PD2
#define BTN2 PD3
#define BTN3 PD4

// --- Définition des bits d’événements ---
#define EVT1 (1 << 0)
#define EVT2 (1 << 1)
#define EVT3 (1 << 2)

// --- Handle du groupe d’événements ---
EventGroupHandle_t xEventGroup;

// --- Initialisation GPIO ---
void GPIO_Init(void) {
    DDRB |= (1 << LED1) | (1 << LED2) | (1 << LED3);   // LEDs en sortie
    DDRD &= ~((1 << BTN1) | (1 << BTN2) | (1 << BTN3)); // Boutons en entrée
    PORTD |= (1 << BTN1) | (1 << BTN2) | (1 << BTN3);   // Pull-up internes
}

// --- Tâche 1 ---
void Task_Event1(void *pvParameters) {
    for (;;) {
        if (PIND & (1 << BTN1)) { // Bouton pressé
            xEventGroupSetBits(xEventGroup, EVT1);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// --- Tâche 2 ---
void Task_Event2(void *pvParameters) {
    for (;;) {
        if (PIND & (1 << BTN2)) {
            xEventGroupSetBits(xEventGroup, EVT2);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// --- Tâche 3 ---
void Task_Event3(void *pvParameters) {
    for (;;) {
        if (PIND & (1 << BTN3)) {
            xEventGroupSetBits(xEventGroup, EVT3);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// --- Tâche 4 : Gestionnaire d’événements ---
void Task_Manager(void *pvParameters) {
    EventBits_t uxBits;
    for (;;) {
        // Attente d’un ou plusieurs événements
        uxBits = xEventGroupWaitBits(
            xEventGroup,
            EVT1 | EVT2 | EVT3,
            pdTRUE,    // Effacer les bits après lecture
            pdTRUE,   // Attendre un seul ou plusieurs bits
            portMAX_DELAY
        );

        if (uxBits & EVT1) PORTB |= (1 << LED1);
        if (uxBits & EVT2) PORTB |= (1 << LED2);
        if (uxBits & EVT3) PORTB |= (1 << LED3);
    }
}

// --- MAIN ---
int main(void) {
    GPIO_Init();

    // Créer le groupe d’événements
    xEventGroup = xEventGroupCreate();

    // Créer les tâches
    xTaskCreate(Task_Event1, "Evt1", 128, NULL, 1, NULL);
    xTaskCreate(Task_Event2, "Evt2", 128, NULL, 1, NULL);
    xTaskCreate(Task_Event3, "Evt3", 128, NULL, 1, NULL);
    xTaskCreate(Task_Manager, "Manager", 128, NULL, 2, NULL);

    // Lancer le scheduler
    vTaskStartScheduler();

    while (1);
}

// --- Hook d’inactivité requis par FreeRTOS ---
void vApplicationIdleHook(void)
{
    // Rien à faire ici (fonction vide)
    // Tu peux y mettre une mise en veille CPU si tu veux économiser de l’énergie
} 