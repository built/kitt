void led_on(int port);
void led_off(int port);
void led_config(int port);
void knight_rider(void);
void chase(void);
void follow(void);
void step(void);
int prev(int position);
int next(int position);
void demo(void);
void configure_LEDs(void);
void wait_for_usb_connection(void);
void configure_teensy(void);
int is_valid_control_key(int16_t cmd);
int is_valid_cmd(int16_t cmd);
void configure_usb(void);
void adjust_speed(unsigned);
void nop(void);

// Why aren't these getting included by usb_serial.h ??
uint8_t usb_serial_get_control(void);	// get the RTS and DTR signal state
int16_t usb_serial_getchar(void);	// receive a character (-1 if timeout/error)
#define USB_SERIAL_DTR 0x01
