#include <Arduino.h>
#include <Constants.h>
#include <Encoder.h>
#include <Motor.h>
#include <PID.h>

Encoder::Encoder(uint8_t CLK, uint8_t DT, uint16_t revPerWheelSpin) : CLK(CLK),
                                                                      DT(DT)
{

    dir = 0;
    radiansConversionRatio = (2.0 * PI) / (double)revPerWheelSpin;

}

Encoder::~Encoder(void)
{
    detachInterrupt(digitalPinToInterrupt(CLK));
    ISRUsed &= ~_BV(myISRId); // free up the ISR slot for someone else
}

bool Encoder::begin(void)
{
    int8_t irq = digitalPinToInterrupt(CLK);

    if (irq != NOT_AN_INTERRUPT)
    {
        pinMode(CLK, INPUT);
        pinMode(DT, INPUT);

        // assign ourselves a ISR ID ...
        myISRId = UINT8_MAX;
        for (uint8_t i = 0; i < MAX_ISR; i++)
        {
            if (!(ISRUsed & _BV(i))) // found a free ISR Id?
            {
                myISRId = i;                // remember who this instance is
                myInstance[myISRId] = this; // record this instance
                ISRUsed |= _BV(myISRId);    // lock this in the allocations table
                break;
            }
        }
        // ... and attach corresponding ISR callback from the lookup table
        {
            static void((*ISRfunc[MAX_ISR])(void)) =
                {
                    globalISR0,
                    globalISR1,
                    globalISR2,
                    globalISR3,
                    globalISR4,
                    globalISR5,
                    globalISR6,
                    globalISR7,
                };

            if (myISRId != UINT8_MAX)
                attachInterrupt(irq, ISRfunc[myISRId], RISING);
            else
                irq = NOT_AN_INTERRUPT;
        }
        reset();
    }
    return (irq != NOT_AN_INTERRUPT);
}

void Encoder::reset(void) { count = 0; }

float Encoder::angleRadians(void)
{
    return ((float)count) * radiansConversionRatio;
}

int8_t Encoder::direction(void)
{
    return dir;
}

int16_t Encoder::counter(void)
{
    return count;
}

double Encoder::conversionRatio(void)
{
    return radiansConversionRatio;
}

void Encoder::instanceISR(void)
{
    bool DT_state = digitalRead(DT);

    // double check if the directions work out right
    if (!DT_state)
    {
        dir = -1;
        count--;
    }
    else
    {
        dir = +1;
        count++;
    }

} // Instance ISR handler called from static ISR globalISRx

// Interrupt handling declarations required outside the class
uint8_t Encoder::ISRUsed = 0;          // allocation table for the globalISRx()
Encoder *Encoder::myInstance[MAX_ISR]; // callback instance handle for the ISR

// ISR for each myISRId
void Encoder::globalISR0(void) { Encoder::myInstance[0]->instanceISR(); }
void Encoder::globalISR1(void) { Encoder::myInstance[1]->instanceISR(); }
void Encoder::globalISR2(void) { Encoder::myInstance[2]->instanceISR(); }
void Encoder::globalISR3(void) { Encoder::myInstance[3]->instanceISR(); }
void Encoder::globalISR4(void) { Encoder::myInstance[4]->instanceISR(); }
void Encoder::globalISR5(void) { Encoder::myInstance[5]->instanceISR(); }
void Encoder::globalISR6(void) { Encoder::myInstance[6]->instanceISR(); }
void Encoder::globalISR7(void) { Encoder::myInstance[7]->instanceISR(); }