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
    int size, modoRead, pathLido, tempo = 0;
    char nro[15];
    setupUSBSerial();
    debugPrint("Start program\n");
    // Storage st;
    // st.initStorage<FlashDevice>();
    // st.createFile(&st.flash);
    // st.openNewFile(&st.flash);
    // st.openFile(&st.flash);
    // st.writeFile(data, st.flash.file);
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
        tempo = duration_cast<std::chrono::milliseconds>(t.elapsed_time()).count();
        debugPrint("%d\n", tempo);
        if(port.readable() && tempo <= 15000){
            if(port.read(aux,sizeof(aux)), aux[0] == 0x52)
                modoRead = 1;
            if(modoRead == 1 && port.read(aux,sizeof(aux)), aux[0] >= 0x30 && aux[0] <= 0x39){
                pathLido = 1;
                nro[0] = aux[0];
            }
            if(modoRead == 1 && pathLido == 1 && port.read(aux,sizeof(aux)), aux[0] >= 0x30 && aux[0] <= 0x39){
                pathLido = 2;
                nro[1] = aux[0];
            }
            if(modoRead == 1 && pathLido == 2 && port.read(aux,sizeof(aux)), aux[0] >= 0x30 && aux[0] <= 0x39){
                pathLido = 3;
                nro[2] = aux[0];
            }
            if(modoRead == 1 && pathLido == 3){
                char path[15] = "/fl/log";
                debugPrint("%s\n", strcat(strcat(path, nro), ".bin"));
                // st.readFile(&st.flash,strcat(strcat(path, nro), ".bin"));
            }
        }
    }
    return 0;
}
