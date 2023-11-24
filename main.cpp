#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <string.h>
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
    char nro[15];

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

    if(port.readable()){
        port.read(aux,sizeof(aux));
    }

    Timer t;
    t.start();

    while(1){
        int tempo = duration_cast<std::chrono::milliseconds>(t.elapsed_time()).count();
        debugPrint("%d\n", tempo);
        if(port.readable() && tempo <= 15000){
            if(port.read(aux,sizeof(aux)), aux[0] == 0x52)
                modoRead = 1;
            if(modoRead == 1 && port.read(aux,sizeof(aux)), aux[0] >= 0x30 && aux[0] <= 0x39){
                pathLido = 1;
                nro[0] = aux[0];
            }
            if(modoRead == 1 && pathLido == 1){
                char path[15] = "/fl/log00";
                debugPrint("%s\n", strcat(strcat(path, nro), ".bin"));
            }
        }
    }
    return 0;
}

    // st.readFile(&st.flash,file);
