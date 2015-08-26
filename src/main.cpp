#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>

bool accInit(MMA7455& acc);

int main() {
  DigitalOut led1(LED1);
	AnalogIn pot(p15);
	MMA7455 acc(P0_27, P0_28);
  LM75B lm75b(P0_27, P0_28, LM75B::ADDRESS_1);
	Serial s(USBTX, USBRX);
	float potVal = 0.0;
	float tempVal = 0.0;
	int32_t accVal[3];
	
	s.baud(115200);
	printf("Hello World\n");
	accInit(acc);
	lm75b.open();
	while (true) {
	  led1 = 1;
	  wait(0.5);
	  led1 = 0;
	  wait(0.5);
		potVal = pot.read();
		tempVal = lm75b.temp();
		acc.read(accVal[0], accVal[1], accVal[2]);
		printf("Pot  : %1.2f\n", potVal);
		printf("Temp : %03.1f\n", tempVal);
		printf("Acc  : %05d, %05d, %05d\n", accVal[0], accVal[1], accVal[2]); 
	}
}

bool accInit(MMA7455& acc) {
	bool result = true;
  if (!acc.setMode(MMA7455::ModeMeasurement)) {
    printf("Unable to set mode for MMA7455!\n");
    result = false;
  }
	if (!acc.calibrate()) {
    printf("Failed to calibrate MMA7455!\n");
    result = false;
  }
	printf("MMA7455 initialised\n");
  return result;
}

