# FreeRTOS Workspace — FRDM-KL46Z

Workspace de **MCUXpresso IDE** con una colección progresiva de ejemplos de **FreeRTOS** sobre la placa **NXP FRDM-KL46Z** (MKL46Z256, ARM Cortex-M0+), usado como material de la asignatura **Sistemas Digitales 2 (SD2)** del Departamento de Sistemas e Informática (DSI), FCEIA – Universidad Nacional de Rosario.

Cada carpeta `frdmkl46z_freertos_*` es un proyecto independiente que aborda **un concepto del RTOS por vez**: tareas, prioridades, hooks, semáforos, notificaciones, colas, timers de software e interacción con interrupciones y periféricos.

---

## Contenido

- [Requisitos](#requisitos)
- [Cómo usar el workspace](#cómo-usar-el-workspace)
- [Estructura de un proyecto](#estructura-de-un-proyecto)
- [Ejemplos](#ejemplos)
- [Recorrido sugerido](#recorrido-sugerido)
- [Módulos propios de la cátedra](#módulos-propios-de-la-cátedra)
- [Configuración de FreeRTOS](#configuración-de-freertos)
- [Salida por consola](#salida-por-consola)
- [Depuración con TAD](#depuración-con-tad)
- [Licencias](#licencias)

---

## Requisitos

| Elemento | Detalle |
|---|---|
| Placa | NXP FRDM-KL46Z |
| MCU | MKL46Z256VLL4 — Cortex-M0+, 256 KB Flash, 32 KB RAM |
| IDE | MCUXpresso IDE (workspace generado con v25.6) |
| SDK | MCUXpresso SDK 2.x para FRDM-KL46Z |
| RTOS | FreeRTOS Kernel **V10.0.1** (incluido en cada proyecto, `amazon-freertos/`) |
| Debug probe | OpenSDA de la placa (P&E Micro o J-Link, según firmware cargado) |
| Cable | USB mini/micro, conectado al puerto **OpenSDA** |

## Cómo usar el workspace

1. Clonar el repositorio:
   ```bash
   git clone https://github.com/sea2-dsi-fceia/FreeRTOS_Workspace.git
   ```
2. En MCUXpresso IDE: **File → Switch Workspace → Other…** y seleccionar la carpeta clonada.
   Si los proyectos no aparecen: **File → Import → General → Existing Projects into Workspace**, apuntando a la raíz del repositorio.
3. Instalar el SDK de la FRDM-KL46Z en la vista *Installed SDKs* (si no estuviera instalado).
4. Seleccionar el proyecto, compilar (**Build**, 🔨) y depurar con la configuración de lanzamiento incluida (`* PE Debug.launch` o `* JLink Debug.launch`, según la probe).

> Cada proyecto es autocontenido: incluye sus drivers, CMSIS, startup y una copia del kernel de FreeRTOS. Se pueden abrir y modificar de forma independiente sin afectar a los demás.

## Estructura de un proyecto

```
frdmkl46z_freertos_<ejemplo>/
├── source/              ← Código de la aplicación (lo que interesa leer)
│   ├── freertos_*.c     ← main() y tareas
│   ├── FreeRTOSConfig.h ← Configuración del kernel
│   └── SD2_board.c/.h   ← Abstracción de LEDs y pulsadores (cátedra)
├── amazon-freertos/     ← Kernel FreeRTOS V10.0.1 + port Cortex-M0+ + heap_4
├── freertos/portable/   ← Soporte tickless de NXP
├── board/               ← pin_mux, clock_config, board.c (generados por el SDK)
├── drivers/             ← Drivers fsl_* del SDK (GPIO, LPSCI/UART, ADC16, ...)
├── CMSIS/               ← Headers del núcleo y del MKL46Z4
├── startup/             ← Tabla de vectores y arranque
├── utilities/           ← Consola de debug (PRINTF)
└── doc/readme.txt       ← Descripción original del ejemplo (proyectos basados en el SDK)
```

## Ejemplos

### 1. Tareas y scheduler

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_hello` | Primera tarea | Crea una tarea que imprime `Hello world.` y se suspende con `vTaskSuspend(NULL)`. |
| `frdmkl46z_freertos_hello_board` | Tarea + placa | Igual al anterior, pero inicializa `SD2_board` y conmuta el LED rojo. |
| `frdmkl46z_freertos_leds_blinky` | Dos tareas concurrentes | Dos tareas con la misma prioridad hacen parpadear el LED verde y el rojo con `vTaskDelay()`. |
| `frdmkl46z_freertos_task_param` | Parámetros de tarea | **Una sola función** de tarea instanciada dos veces; cada instancia recibe por `pvParameters` una estructura con el LED y el semiperíodo. |
| `frdmkl46z_freertos_priority` | Prioridades y *time slicing* | Tres tareas de igual prioridad con retardos activos (`while (i--)`). Incluye alternativas comentadas (`taskYIELD()`, `vTaskDelay()`, `vTaskSuspend()`) para observar su efecto sobre la planificación. |
| `frdmkl46z_freertos_board_sw_led` | Lectura por polling | Una tarea lee SW1 cada 100 ms y conmuta el LED rojo; otra hace parpadear el LED verde. |

### 2. Hooks del kernel

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_idle_hook` | `vApplicationIdleHook` | La tarea conmuta el LED rojo y se bloquea; mientras tanto el *idle hook* conmuta el LED verde, lo que evidencia cuándo el CPU está ocioso. |
| `frdmkl46z_freertos_board_sw_led_key` | `vApplicationTickHook` | El antirrebote de pulsadores (`key_periodicTask1ms()`) se ejecuta desde el *tick hook*; la tarea consume eventos de pulsación con `key_getPressEv()`. |

### 3. Sincronización y comunicación entre tareas

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_semaphore_leds` | Semáforo binario | `task2` libera el semáforo cada 500 ms; `task1` se bloquea en `xSemaphoreTake()` y conmuta el LED rojo. El *idle hook* enciende el LED verde. |
| `frdmkl46z_freertos_semaphore` | Rendezvous (SDK) | Un productor y tres consumidores sincronizados con dos semáforos (patrón *bilateral rendezvous*). |
| `frdmkl46z_freertos_mutex` | Mutex (SDK) | Dos instancias de una tarea comparten la consola; el mutex evita que los mensajes se mezclen. |
| `frdmkl46z_freertos_queue` | Colas (SDK) | Mecanismo de *logging* por paso de mensajes: `log_add()` encola, `log_task` imprime. |
| `frdmkl46z_freertos_event` | Event groups (SDK) | Dos tareas activan los bits 0 y 1 de un grupo de eventos; una tercera espera cualquiera de ellos. |
| `frdmkl46z_freertos_generic` | Integración (SDK) | Combina cola, timer de software, *tick hook* y semáforo en una sola aplicación. |

### 4. Notificaciones directas a tarea

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_task_notify_leds` | Notificación como semáforo | `task2` llama a `xTaskNotifyGive()`; `task1` espera con `ulTaskNotifyTake()` y *timeout* de 2 s. |
| `frdmkl46z_freertos_task_notify_value` | Notificación como contador | `task1` envía cuatro notificaciones seguidas; `task2` las recibe con `ulTaskNotifyTake(pdFALSE, …)` para observar la diferencia entre limpiar o decrementar el valor. |
| `frdmkl46z_freertos_task_notify_value_action` | Notificación con valor | `task1` envía un valor con `xTaskNotify()` (acción `eNoAction`); `task2` lo recibe con `xTaskNotifyWait()`. Punto de partida para probar las demás acciones (`eSetValueWithOverwrite`, `eIncrement`, `eSetBits`, …). |

### 5. Timers de software

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_swtimer` | Timer periódico (SDK) | Un timer *auto-reload* cuyo *callback* imprime `Tick.` |
| `frdmkl46z_freertos_swtimer_modes` | One-shot vs. auto-reload | Dos timers (2 s *one-shot* y 1 s *auto-reload*) comparten un único *callback* y se distinguen por su **Timer ID** (`pvTimerGetTimerID()`). |

### 6. Interrupciones y RTOS (UART0)

La UART0 (LPSCI) se configura a **9600 bps, 8N1** en PTA1 (RX) / PTA2 (TX), que corresponden al **puerto COM virtual de OpenSDA**. Se envían caracteres desde una terminal serie en la PC.

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_uart_irq_semaphore` | ISR → semáforo | La ISR de recepción hace `xSemaphoreGiveFromISR()` + `portYIELD_FROM_ISR()`; la tarea de proceso (mayor prioridad) conmuta el LED rojo. Procesamiento diferido de interrupciones. |
| `frdmkl46z_freertos_uart_irq_sema_process` | Proceso largo diferido | Variante donde la tarea de proceso ejecuta un trabajo prolongado (20 conmutaciones con retardo activo); permite observar la interacción con la tarea `Blink` de menor prioridad. |
| `frdmkl46z_freertos_uart_irq_queue` | ISR → cola | La ISR encola cada byte con `xQueueSendFromISR()`; la tarea interpreta comandos: **`E`** enciende y **`A`** apaga el LED rojo. Maneja también el flag de *overrun*. |

### 7. Periféricos con RTOS

| Proyecto | Concepto | Descripción |
|---|---|---|
| `frdmkl46z_freertos_adc` | ADC por timer + cola | Un timer de software dispara conversiones del ADC0 (canal 3, **PTE22**) cada 500 ms; la ISR del ADC entrega el resultado en una cola y la tarea lo lee con `adc_getValueBlocking()` (*timeout* de 1 s). |
| `frdmkl46z_freertos_acc` | Acelerómetro I²C | Lectura del **MMA8451Q** de la placa por I²C con interrupción de dato listo (semáforo). El eje X enciende el LED rojo (> 50) o el verde (< −50). |

## Recorrido sugerido

```
hello → hello_board → leds_blinky → task_param → priority
      → board_sw_led → idle_hook → board_sw_led_key
      → semaphore_leds → task_notify_leds → task_notify_value → task_notify_value_action
      → swtimer → swtimer_modes
      → uart_irq_semaphore → uart_irq_sema_process → uart_irq_queue
      → adc → acc
```

Los ejemplos marcados como **(SDK)** (`semaphore`, `mutex`, `queue`, `event`, `generic`, `swtimer`) son los ejemplos originales de NXP y se usan como referencia complementaria; su `doc/readme.txt` describe el comportamiento esperado.

## Módulos propios de la cátedra

| Módulo | API principal | Uso |
|---|---|---|
| `SD2_board` | `board_init()`, `board_setLed(id, msg)`, `board_getSw(id)` | Abstracción de los LEDs (`BOARD_LED_ID_ROJO`, `BOARD_LED_ID_VERDE`) y pulsadores (`BOARD_SW_ID_1`, `BOARD_SW_ID_3`) de la placa. Acciones: `OFF`, `ON`, `TOGGLE`. |
| `key` | `key_init()`, `key_getPressEv(id)`, `key_periodicTask1ms()` | Antirrebote y detección de eventos de pulsación; requiere llamar a `key_periodicTask1ms()` cada 1 ms (desde el *tick hook*). |
| `adc` | `adc_init(sampleTime)`, `adc_getValueBlocking(&val, timeout)` | ADC16 disparado por timer de software, resultados vía cola. |
| `mma8451` | `mma8451_init()`, `mma8451_getAcX()`, `mma8451_setDataRate()` | Driver del acelerómetro MMA8451Q. |
| `SD2_I2C` | `SD2_I2C_init()` | Inicialización del bus I²C usado por el acelerómetro. |

## Configuración de FreeRTOS

Valores relevantes de `FreeRTOSConfig.h` (comunes a los proyectos; revisar cada uno ante cambios puntuales):

| Parámetro | Valor |
|---|---|
| `configTICK_RATE_HZ` | 200 Hz (tick de 5 ms) en la mayoría; **1000 Hz** en `board_sw_led`, `board_sw_led_key`, `adc` y `acc` |
| `configTOTAL_HEAP_SIZE` | 10 KB |
| Esquema de memoria | `heap_4` |
| `configUSE_TIMERS` | 1 |

> Los proyectos que llaman a `key_periodicTask1ms()` desde el *tick hook* necesitan un tick de 1 ms (`configTICK_RATE_HZ = 1000`). Si se copia ese módulo a un proyecto con tick de 200 Hz, el antirrebote se ejecutará cada 5 ms y sus tiempos quedarán multiplicados por cinco.

Varios proyectos definen `vApplicationStackOverflowHook()` con un lazo infinito: si el programa queda detenido allí, la causa es un desborde de pila de alguna tarea (aumentar el tamaño en `xTaskCreate()`).

## Salida por consola

Los proyectos se compilan con `SDK_DEBUGCONSOLE=0`, por lo que `PRINTF()` se redirige por **semihosting**: los mensajes aparecen en la vista *Console* de MCUXpresso **solo durante una sesión de depuración**. El semihosting es lento y detiene brevemente el CPU en cada impresión, lo que puede alterar la temporización observada.

En los ejemplos de UART, la terminal serie (9600 bps) se usa para **enviar** caracteres a la placa.

## Depuración con TAD

MCUXpresso incluye el **Task Aware Debugger (TAD)** para FreeRTOS, que permite ver durante la depuración la lista de tareas y su estado, colas, semáforos, timers y el uso de heap. Las carpetas `FreeRTOS_TAD_logs/`, `AzureRTOS_TAD_logs/` y `ZephyrRTOS_TAD_logs/` contienen los registros que genera el IDE al usarlo.

Para que colas y semáforos aparezcan con nombre en el TAD, se pueden registrar con `vQueueAddToRegistry(handle, "nombre")`.

## Licencias

- Código del SDK de NXP (drivers, board, CMSIS, ejemplos base): licencia **BSD-3-Clause**, según los encabezados de cada archivo.
- **FreeRTOS Kernel**: licencia **MIT** (`amazon-freertos/license/LICENSE`).
- Código de la cátedra (módulos `SD2_*`, `key`, `adc`, `mma8451` y ejemplos propios): material didáctico de SD2 – DSI – FCEIA – UNR.

---

**Autor:** Prof. Ing. Daniel Márquez — Sistemas Digitales 2, DSI, FCEIA, Universidad Nacional de Rosario.
