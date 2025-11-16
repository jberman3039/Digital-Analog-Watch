#define SRCLK_HOUR_PIN 2 // PB2
#define SRCLK_MINUTE_PIN 3 // PB3
#define SRCLR_PIN 4 // PB4

void init_74hc595();
void clear_sr();
void update_hour(unsigned char* rtc_hour);
void update_minute(unsigned char* rtc_minute);
void update_time(unsigned char* rtc_hour, unsigned char* rtc_minute);