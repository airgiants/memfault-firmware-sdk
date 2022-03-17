/* Console example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_task.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"
#include "esp_vfs_fat.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "Arduino.h"
#include "Wire.h"


#include "memfault/core/compiler.h"
#include "memfault/core/debug_log.h"
#include "memfault/esp_port/cli.h"
#include "memfault/esp_port/core.h"
#include "memfault/esp_port/http_client.h"
#include "memfault/metrics/platform/timer.h"
#include "memfault/metrics/metrics.h"
#include "memfault/panics/assert.h"


#include "pressure/pressure.h"
#include "imu/imu.h"
#include "ota_update/ota_update.h"
#include "config/config.h"
    
#include <WiFi.h>
#include <WiFiMulti.h>




static const char* TAG = "example";

/* Console command history can be stored to and loaded from a file.
 * The easiest way to do this is to use FATFS filesystem on top of
 * wear_levelling library.
 */
#if CONFIG_STORE_HISTORY

#define MOUNT_PATH "/data"
#define HISTORY_PATH MOUNT_PATH "/history.txt"

static void initialize_filesystem()
{
    static wl_handle_t wl_handle;
    const esp_vfs_fat_mount_config_t mount_config = {
            .format_if_mount_failed = true,
            .max_files = 4
    };
    esp_err_t err = esp_vfs_fat_spiflash_mount(MOUNT_PATH, "storage", &mount_config, &wl_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
        return;
    }
}
#endif // CONFIG_STORE_HISTORY

static void initialize_nvs() {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK( nvs_flash_erase() );
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK(err);
}

// Name change at version 4.x
#if defined(ESP_IDF_VERSION_MAJOR) && ESP_IDF_VERSION_MAJOR > 3
#define CONFIG_CONSOLE_UART_NUM CONFIG_ESP_CONSOLE_UART_NUM
#endif


// Put this buffer in the IRAM region. Accesses on the instruction bus must be word-aligned
// while data accesses don't have to be. See "1.3.1 Address Mapping" in the ESP32 technical reference manual.
MEMFAULT_ALIGNED(4) static IRAM_ATTR uint8_t s_my_buf[10];
void *g_unaligned_buffer;

// Periodically post any Memfault data that has not yet been posted.
static void prv_poster_task(void *args) {
  const uint32_t interval_sec = 60;
  const TickType_t delay_ms = (1000 * interval_sec) / portTICK_PERIOD_MS;

  MEMFAULT_LOG_INFO("Data poster task up and running every %us.", interval_sec);
  while (true) {
    MEMFAULT_LOG_DEBUG("Checking for memfault data to send");
    memfault_esp_port_http_client_post_data();
    memfault_metrics_heartbeat_add(MEMFAULT_METRICS_KEY(PosterTaskNumSchedules), 1);
    vTaskDelay(delay_ms);
  }
}

Pressure psensor; 
  void sensor_update(){
    psensor.update();
  }

Imu imu;

WiFiMulti wifiMulti;
Board board;

#define WiFi_timeout 10000  // 10sec Wifi connection timeout

const char* ssid0 = "VM5359006";
const char* pass0 = "mk3rmXtfdmwc";

const char* ssid1 = "AirGiants";
const char* pass1 = "airgiants123";

const char* ssid2 = "BTBHub6-JT8K";
const char* pass2 = "igd6HaHTmkxP";




// This task started by cpu_start.c::start_cpu0_default().
extern "C" void app_main() {
  extern void memfault_platform_device_info_boot(void);
  memfault_platform_device_info_boot();
  g_unaligned_buffer = &s_my_buf[1];

  initialize_nvs();

#if CONFIG_STORE_HISTORY
  initialize_filesystem();
#endif


  // We need another task to post data since we block waiting for user
  // input in this task.
  const portBASE_TYPE res = xTaskCreate(prv_poster_task, "poster",
                                        ESP_TASK_MAIN_STACK, NULL,
                                        ESP_TASK_MAIN_PRIO, NULL);
  MEMFAULT_ASSERT(res == pdTRUE);

  /* Register commands */
  //esp_console_register_help_command();

  //register_system();
  //register_wifi();


    initArduino();

    /* SETUP */
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(10000);
    psensor.begin();


   // imu.begin();

    if(!imu.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
   //
    //while(1);
  }
    //imu.begin();

  wifiMulti.addAP(ssid0, pass0);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);


if (wifiMulti.run(WiFi_timeout) == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  //print IP of the connected WiFi network
    ota_setup();
  }
  else  // if not WiFi not connected
  {
    Serial.println("WiFi not Connected");
  }





#define HEARTBEAT_PERIOD (1*60*1000L)
unsigned long target_time = 0L ;



  /* Main loop */
  while(true) {
if (millis () - target_time >= HEARTBEAT_PERIOD)
  {
    target_time += HEARTBEAT_PERIOD ;   // change scheduled time exactly, no slippage will happen
    
  //prv_heartbeat_timer();
  }
  
  sensor_update();
  ota_handle();
  board.update();
//    Serial.print("Pressure: ");
//     Serial.print(psensor.get_pressure());
//     Serial.print("  Temp: ");
//     Serial.print(psensor.get_temperature());
//     Serial.print("  Angle:");
//     Serial.println(imu.get_angle());
//  if (wifiMulti.run() != WL_CONNECTED) {
//     Serial.println("WiFi not connected!");
//   }

//   // Do more things.
//   delay(1000);
  }
}




  //  Serial.begin(115200);
  //       Serial.println("A");
  //       Wire.begin();
  //     psensor.begin();

  //   sensor.measureStart(sensor.VERY_ACCURATE);
  //           Serial.println("B");



