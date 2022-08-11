#ifndef Zipline_h
#define Zipline_h

#include <Constants.h>
#include <Motor.h>

class Zipline {
    public:
    
    //Construct zipline
    Zipline (Motor motor);

    /**
     * @brief extend zipline by assigning DC motor a specific speed
     * 
     * @param speed 
     */
    void extendZipline(int speed, int time);
    
    /**
     * @brief Stop the zipline 
     * 
     */
    void stopZipline();

    /**
     * @brief Descend zipline
     * 
     */
    void descendZipline(int speed, int time);

    private:
        Motor motor;
        
};


#endif
