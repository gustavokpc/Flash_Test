#include <cstdint>
#include <cstdio>
#include <stdio.h>
#include <mbed.h>
#include "BufferedSerial.h"

#include "Data.h"
#include "Storage.h"

Data data;
DigitalOut debugLED(LED1);
static BufferedSerial port(USBTX,USBRX,115200);
FileHandle *mbed::mbed_override_console(int fd) { return &port; }
void setupUSBSerial()
{
    port.set_format(8);
}

int main(){
    setupUSBSerial();
    debugPrint("Start program\n");
    Storage st;
    st.initFlashStorage();
    st.createFlashFile();
    st.closeFlashFile();
    while(1){
    }
    return 0;
}
