/*
 * Name:    Goran Todorovic (dejakju@gmail.com)
 * Date:    2022-05-07
 * Update:  2022-09-03
 * Desc.:   A brief introduction on how to connect and use the HC-SR04 Ultrasonic Sensor
 */

#include <Arduino.h>

const int PIN_TRIGGER   = 2;
const int PIN_ECHO      = 3;

float duration          = .0f;
float distance          = .0f;

/*
 * Performs the calculation of the distance given by a duration (aka time delay)
 * by the formula: D = (delta t / 2) * c
 * where:   delta t = Time delay
 *          c = speed of sound [~ 343 m/s in dry air @ 20° C]
 * 
 * @param duration - a floating-point number in microseconds
 * @returns the distance in centimeters
 * @remarks deliberately neglecting factors like temperature and humidity for simplicity!
 */
float MicrosecondsToCentimeters(float duration)
{
    return ((duration / 2) * 0.0343f);
}

void setup()
{
    Serial.begin(57600);
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop()
{
    // Initiating the trigger sequence (10ms pulse)
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // Measure the response from the HC-SR04 Echo Pin
    duration = pulseIn(PIN_ECHO, HIGH);

    // Determine distance from duration
    distance = MicrosecondsToCentimeters(duration);

    // Print the result to the serial monitor
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    // Add a small delay to calibrate for consecutive reading, since we are in the main loop
    delay(500);
}

