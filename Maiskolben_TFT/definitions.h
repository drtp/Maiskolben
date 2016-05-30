#define VERSION	103
#define EEPROM_CHECK 42
//#define HAS_BATTERY

#define STBY_TEMP	150
//SOFTWARE CAN'T MEASURE MORE THAN 422 DUE TO RESISTOR CONFIGURATION, IF SET TO >= 422 IT'S LIKELY TO KILL YOUR TIP!
//If read 1024 on Analog in, the tip is turned off
#define MAX_TEMP	400
#define MIN_TEMP	100

#define STANDBY_TIMEOUT 240 // seconds without any significant temperature drop, if exceeded it will standby

#define TEMP_THRESHOLD	50 //threshold voltage, that must be exceeded in given time:
#define TEMP_UNDER_THRESHOLD 150 //*10ms
#define THRES_MAX_DECEED 2 //max times the threshold temperature may be undercut by the current temperature

//Temperature in degree to rise at least in given time
#define TEMP_MIN_RISE 10
//Time in that the temperature must rise by the set temperature
#define TEMP_RISE_TIME 1000

#define SW_STBY		2
#define HEATER_PWM	3
#define SW_DOWN		4
#define HEAT_LED	5
#define SW_UP		6
#define SW_T3		7
#define SW_T2		8
#define SW_T1		9
#define TFT_CS		10
#define TEMP_SENSE	A0
#define STBY_NO		A1
#define BAT_C3		A2
#define BAT_C2		A3
#define BAT_C1		A4
#define TFT_DC		A5

#define kp			0.03
#define ki			0.00001
#define kd			0.0

#define TIME_COMPUTE_IN_MS 10
#define TIME_MEASURE_VOLTAGE_IN_MS 200
#define TIME_SW_POLL_IN_MS 10
#define DELAY_BEFORE_MEASURE 10
#define DELAY_MAIN_LOOP 10
#define PID_SAMPLE_TIME 10

#define ADC_TO_TEMP_GAIN 0.39
#define ADC_TO_TEMP_OFFSET 23.9
#define CTRL_GAIN 10

typedef enum POWER_SOURCE {
	NO_INIT,
	POWER_USB,
	POWER_CORD,
	POWER_LIPO
} p_source;
typedef enum ERROR_TYPE {
	NO_ERROR,
	EXCESSIVE_FALL,
	NOT_HEATING,
	NO_TIP,
	BATTERY_LOW,
	USB_ONLY
} error_type;

const unsigned char maiskolben [] PROGMEM =  {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xcf, 0xff, 0xa0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xdc, 0xf7, 
0x18, 0x47, 0x89, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 
0x26, 0x78, 0xc6, 0x33, 0x9c, 0x7f, 0x0c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x08, 0x23, 0x49, 0xe6, 0x1b, 0xff, 0xf8, 0x39, 0xd0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xc5, 0x31, 0xcf, 0xe7, 0x3f, 0xfe, 0x14, 0x21, 0x08, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x47, 0xf9, 0xff, 0xff, 0xcc, 
0x40, 0x08, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x4e, 
0x0f, 0xc1, 0x08, 0x04, 0x63, 0x00, 0x21, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x47, 0xe0, 0x0c, 0x01, 0x08, 0x07, 0xaf, 0x80, 0x60, 0x84, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x02, 0x0c, 0x01, 0x8c, 0xc7, 0xa4, 0x80, 0xe0, 0xf4, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x0c, 0x60, 0x9f, 0xc7, 
0xf0, 0xf3, 0x33, 0xf4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x83, 
0x0e, 0xe0, 0x77, 0x69, 0x9a, 0xf7, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x0c, 0xfd, 0xb7, 0xb6, 0x67, 0x79, 0x9f, 0xfe, 0xee, 0x12, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xfc, 0xf3, 0xbe, 0xff, 0xfb, 0xff, 0xf8, 0x46, 0x12, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xcd, 0xcf, 0xbc, 0x63, 0x18, 0x6e, 
0x21, 0x80, 0x42, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8c, 0xfe, 
0x08, 0x42, 0x08, 0x44, 0x21, 0x48, 0x42, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x06, 0x84, 0xe2, 0x1e, 0x4a, 0x18, 0x44, 0xe1, 0xc0, 0x63, 0x0f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x63, 0x3c, 0x7b, 0x18, 0x6e, 0x60, 0x80, 0x31, 0x07, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x65, 0xec, 0x71, 0x08, 0x22, 
0x10, 0x00, 0x20, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x39, 
0x84, 0x21, 0x8c, 0x33, 0x10, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x08, 0x38, 0x84, 0x00, 0x08, 0x32, 0x10, 0x02, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x58, 0x10, 0x84, 0x00, 0x08, 0x20, 0x10, 0x03, 0xf1, 0x9f, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x70, 0x44, 0x60, 0x08, 0x23, 
0x30, 0xc4, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x00, 
0xc7, 0x1f, 0xff, 0xff, 0x1f, 0x84, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x08, 0xc0, 0x7f, 0x82, 0x10, 0x8c, 0x03, 0x08, 0x84, 0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x78, 0x82, 0x10, 0x88, 0x01, 0x08, 0x84, 0x10, 0x87, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7c, 0x28, 0x82, 0x18, 0xc8, 0x21, 
0x08, 0x82, 0x10, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x28, 
0x42, 0x08, 0xc0, 0x21, 0x8c, 0x42, 0x10, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 
0x00, 0x3f, 0xfc, 0x18, 0x42, 0x08, 0xc4, 0x11, 0x8c, 0x42, 0x10, 0x83, 0x80, 0x00, 0x00, 0x00, 
0x7f, 0xff, 0xfe, 0x89, 0xfc, 0xff, 0x94, 0x0c, 0x42, 0x08, 0x44, 0x30, 0x88, 0x42, 0x10, 0x03, 
0x18, 0x00, 0x00, 0x00, 0x06, 0xff, 0xff, 0xff, 0xff, 0x00, 0x04, 0x0c, 0x62, 0x00, 0x04, 0x00, 
0x88, 0x42, 0x10, 0x03, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x04, 0x1c, 
0x20, 0x00, 0x88, 0x00, 0x88, 0x42, 0x10, 0xc7, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x80, 0x1c, 0x23, 0x10, 0xc8, 0x00, 0x8c, 0x43, 0x30, 0xf9, 0x01, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x37, 0x9d, 0xbc, 0x30, 0xfe, 0xe7, 0x6f, 0x11, 
0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x04, 0x4c, 0xe7, 0x9e, 0x2f, 
0x31, 0x8e, 0x64, 0x31, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xce, 0x23, 
0x8f, 0xe7, 0x1d, 0xc7, 0x31, 0x8c, 0x64, 0x11, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x02, 0x46, 0x30, 0xcf, 0xf6, 0x1c, 0xe6, 0x39, 0xcc, 0x64, 0x11, 0x00, 0x06, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x44, 0x38, 0xcc, 0x76, 0x18, 0xc2, 0x3d, 0x2c, 0x6c, 0x13, 
0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x44, 0x38, 0xcc, 0x66, 0x10, 0x86, 
0x31, 0x08, 0x48, 0x13, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x44, 0x38, 
0xc0, 0x44, 0x10, 0x84, 0x21, 0x00, 0x48, 0x12, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0x40, 0x30, 0x80, 0x44, 0x01, 0x04, 0x20, 0x00, 0x48, 0x1e, 0x00, 0x01, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x84, 0x44, 0x21, 0x04, 0x20, 0x0c, 0xfc, 0x26, 
0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x86, 0xcc, 0x21, 0x04, 
0x23, 0x0f, 0x8e, 0xc2, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 
0x8e, 0xff, 0xff, 0x0f, 0xfb, 0xf9, 0x84, 0x46, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x80, 0x71, 0xf0, 0x6c, 0x31, 0xc4, 0x40, 0x19, 0x00, 0x46, 0x00, 0x00, 0x30, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xb8, 0x30, 0x4c, 0x21, 0x04, 0x40, 0x11, 0x00, 0x46, 
0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x20, 0x20, 0x48, 0x20, 0x00, 
0x02, 0x11, 0x08, 0x44, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x28, 
0x20, 0x08, 0x02, 0x00, 0x80, 0x11, 0x08, 0x4c, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x22, 0x18, 0x20, 0x00, 0x02, 0x00, 0x80, 0x13, 0x1c, 0xd8, 0x00, 0x00, 0x03, 0x40, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x18, 0x20, 0x00, 0x42, 0x08, 0x84, 0x1d, 0xe6, 0x38, 
0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x18, 0x21, 0x1c, 0x7e, 0x0e, 
0x7f, 0x90, 0x44, 0x38, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7c, 
0x7c, 0xcc, 0x31, 0x88, 0x42, 0x10, 0x44, 0x38, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1e, 0x42, 0x10, 0x08, 0x21, 0x08, 0x42, 0x10, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x40, 0x00, 0x08, 0x20, 0x08, 0x62, 0x10, 0x8c, 0x70, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x08, 0x00, 0x08, 
0xc6, 0x21, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xd8, 
0x60, 0x08, 0x44, 0x3f, 0xff, 0xe7, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
