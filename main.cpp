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
    char aux[1]= {0x0};
    int size = 0;
    int modoRead = 0;
    int pathLido = 0;
    char nro = '0';

    // setupUSBSerial();
    // debugPrint("Start program\n");
    // Storage st;
    // st.initStorage<FlashDevice>();
    // st.createFile(&st.flash);
    // st.openNewFile(&st.flash);
    // st.openFile(&st.flash);
    // st.writeFile(data, &st.flash);
    // st.closeFile(&st.flash);
    // st.showDirectory(&st.flash);
    // char file[] = "/fl/log001.bin";
    // st.readFile(&st.flash,file);
    // Timer t;

    if(port.readable()){
        port.read(aux,sizeof(aux));
    }
    // t.start();
    while(1){
        // float tempo = t.read();
        // debugPrint("%f\n", tempo);
        debugPrint("ASDASD\n");
        if(port.readable()){
            if(port.read(aux,sizeof(aux)), aux[0] == 0x52)
                modoRead = 1;
            if(modoRead == 1 && port.read(aux,sizeof(aux)), aux[0] >= 0x31 && aux[0] <= 0x39){
                pathLido = 1;
                nro = aux[0];
            }
            if(modoRead == 1 && pathLido == 1){
                char path[] = "/fl/log001.bin";
                debugPrint("%s", path);
            }
        }
    }
    return 0;
}
    // st.readFile(&st.flash,file);

