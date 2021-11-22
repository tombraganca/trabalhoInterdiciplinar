
#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include "soc/soc.h"          // Brownout error fix
#include "soc/rtc_cntl_reg.h" // Brownout error fix
#include "esp_camera.h"
#include "./CameraModel.h"

#include <AsyncTelegram2.h>

class CameraService
{
public:
    CameraService()
    {
        WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);      // disable brownout detector
        pinMode(LAMP_PIN, OUTPUT);                      // set the lamp pin as output
        ledcSetup(lampChannel, pwmfreq, pwmresolution); // configure LED PWM channel
        setLamp(0);                                     // set default value
        ledcAttachPin(LAMP_PIN, lampChannel);           // attach the GPIO pin to the channel
        Serial.print("Camera env configured... ");
    }

    static esp_err_t init_camera()
    {

        Serial.print("Camera init... ");
        esp_err_t err = esp_camera_init(&camera_config);

        if (err != ESP_OK)
        {
            delay(100); // need a delay here or the next serial o/p gets missed
            Serial.printf("\n\nCRITICAL FAILURE: Camera sensor failed to initialise.\n\n");
            Serial.printf("A full (hard, power off/on) reboot will probably be needed to recover from this.\n");
            return err;
        }
        else
        {
            Serial.println("succeeded");

            // Get a reference to the sensor
            sensor_t *s = esp_camera_sensor_get();
            if (s->id.PID == OV2640_PID)
            {
                Serial.println("OV2640 camera module detected");
            }
            else
            {
                Serial.println("WARNING: Camera module is unknown and not properly supported, will fallback to OV2640 operation");
            }
        }
        return ESP_OK;
    }

    // Take picture with Camera and send to Telegram Instance
    size_t sendPicture(TBMessage &msg, AsyncTelegram2 telegram)
    {

        Serial.println("Camera capture requested");

        setLamp(100);
        camera_fb_t *fb = esp_camera_fb_get();
        setLamp(0);
        if (!fb)
        {
            Serial.println("Camera capture failed");
            return 0;
        }
        size_t len = fb->len;
        if (!telegram.sendPhoto(msg, fb->buf, fb->len))
        {
            len = 0;
            telegram.sendMessage(msg, "Error! Picture not sent.");
        }

        esp_camera_fb_return(fb); // Clear buffer
        return len;
    }

private:
    int lampChannel = 7;         // a free PWM channel (some channels used by camera)
    const int pwmfreq = 50000;   // 50K pwm frequency
    const int pwmresolution = 9; // duty cycle bit range
    const int pwmMax = pow(2, pwmresolution) - 1;

    // Lamp Control
    void setLamp(int newVal)
    {
        if (newVal != -1)
        {
            // Apply a logarithmic function to the scale.
            int brightness = round((pow(2, (1 + (newVal * 0.02))) - 2) / 6 * pwmMax);
            ledcWrite(lampChannel, brightness);
            Serial.print("Lamp: ");
            Serial.print(newVal);
            Serial.print("%, pwm = ");
            Serial.println(brightness);
        }
    }
};

#endif //CAMERA_SERVICE