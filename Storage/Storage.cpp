#include "Storage.h"
#include <cstdio>

int Storage::initFlashStorage(){
    int err = 0;
    debugPrint("Starting Flash Block Device...\n");
    flashBlockDevice = new SPIFBlockDevice(FLASH_MOSI,FLASH_MISO,FLASH_SCLK,FLASH_CS);
    debugPrint("Starting Flash LFS...\n");
    flashFS = new LittleFileSystem2(FLASH_ROOT);
    debugPrint("Mounting LFS with Flash Block device...");
    err = flashFS->mount(flashBlockDevice); //Not mounting
    err?debugPrint("Failed\n"):debugPrint("Ok\n");
    #ifndef FORCE_REFORMAT_FLASH
    if(err){
        debugPrint("Flash did not mount, reformatting...");
        err = LittleFileSystem2::format(flashBlockDevice);
        err?debugPrint("Failed!\n"):debugPrint("Ok!\n");
    }
    #else
    debugPrint("Force reformat on, reformatting...");
    err = LittleFileSystem2::format(flashBlockDevice);
    err?debugPrint("Failed!\n"):debugPrint("Ok!\n");
    #endif
    return err;
}

void Storage::createFlashFile(){
    char* nextFName = nextFile(true);
    if(strcmp(nextFName,"nope") == 0){
        // TODO: Treat error, stop and beep error
    }
    filenameFlash = (char*)malloc(FILENAME_SIZE*sizeof(char));
    strcpy(filenameFlash,FLASH_ROOT_DIR);
    strcat(filenameFlash,nextFName);
    fFlash = fopen(filenameFlash, "w+");
}

uint16_t Storage::writeFlashFile(Data data){
    uint16_t writeSize = 0;
    if(fFlash == nullptr){
        debugPrint("Could not write on file at Flash. Perhaps the file is not open\n");
    }
    else{
        writeSize = fwrite((char*)&data, sizeof(char), sizeof(Data), fFlash);
    }
    return writeSize;
}

char* Storage::nextFile(bool isFlash){
    char* next_filename;
    char number[4];
    uint16_t current_filename_index = 0;
    next_filename = (char*)malloc(FILENAME_MAX*sizeof(char));
    if(isFlash){
        dir = opendir(FLASH_ROOT_DIR);
        debugPrint("Reading directory %s...\n",FLASH_ROOT_DIR);
    }
    else{
        dir = opendir(SD_ROOT_DIR);
        debugPrint("Reading directory %s...\n",SD_ROOT_DIR);
    }
    
    while(1){  
        // Defaults to log000.bin, where each 0 can be a number from 0 to 9, starting at 001
        struct dirent *entity = readdir(dir);
        if(!entity)
            break;
        debugPrint("%s\n",entity->d_name);
        if(_CHECK_LOGFILE(entity->d_name,"log")){
            // This pointer points for the char space + 3, being "log" the first 3
            char *ptr = entity->d_name + 3;
            uint16_t i=0;
            while (*ptr >= '0' && *ptr <= '9' && i < 3) {
                number[i] = *ptr;
                i++;
                ptr++;
            }
            number[i] = '\0';
            i = atoi(number);
            if(i > current_filename_index)
                current_filename_index = i;
        }
    }

    openFlashFile();
    if(current_filename_index < 1000)
        sprintf(next_filename,"log%03d.bin",++current_filename_index);
    else
        sprintf(next_filename,"nope");
    return next_filename;
}

void Storage::openFlashFile(){
    fFlash = fopen(FLASH_ROOT_DIR, "w+");
}

void Storage::closeFlashFile(){
    fclose(fFlash);
}

void Storage::readFlashFile(char* path){
    debugPrint("Displaying \"%s\"...", path);
    fflush(stdout); // Cleans the standard output buffer
    if(fFlash != nullptr){
        debugPrint("There's a file already open, trying to open \"%s\"...", path);
        closeFlashFile();
    }
    fFlash = fopen(path,"r");
    if(!fFlash)
        debugPrint("Could not read Flash file. Perhaps the file is not created\n");
    else{
        filePrint("Preamble, Pressure, Temperature, Humdity, gpsFix, Latitude, Longitude, Time, TimeStamp, Acc(x), Acc(y), Acc(z)\n");
        Data tmpData;
        while(!feof(fFlash)){   // While EOF(End Of File) is not found
            fread((char* )&tmpData, sizeof(char), sizeof(Data),fFlash);
            filePrint("%s,%f,%f,%f,%d,%f,%f,%f,%d,%lld,%d,%d,%d\n",
               tmpData.preamble,
               tmpData.pressure,
               tmpData.temperatureLPS22HB,
               tmpData.humidity,
               tmpData.gpsFix,
               tmpData.latitude,
               tmpData.longitude,
               tmpData.elevation,
               tmpData.UTCTime,
               tmpData.timeStamp,
               tmpData.a[0],
               tmpData.a[1],
               tmpData.a[2]);
        }
        fflush(stdout);
        closeFlashFile();
    }
}

void Storage::deinitFlashStorage(){
    closeFlashFile();
    flashFS->unmount();
    // Frees filename string space in memory
    free(filenameFlash);
}

void Storage::eraseFlash(){
    flashBlockDevice->erase(0,flashBlockDevice->size());    // Full erase
}

