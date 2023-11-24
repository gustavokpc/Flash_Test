#include "FATFileSystem.h"
#include "COMPONENT_SD/include/SD/SDBlockDevice.h"
#include "mbed.h"
#include "COMPONENT_SPIF/include/SPIF/SPIFBlockDevice.h"
#include "LittleFileSystem2.h"
#include "../Data.h"
#include "../globalDefines.h"

#define FLASH_ROOT "fl"
#define FLASH_ROOT_DIR "/fl/"
#define SD_ROOT "sd"
#define SD_ROOT_DIR "/sd/"

#define FILENAME_SIZE 64

/* STORAGE FUNCTION-LIKE MACROS */
#define _CHECK_LOGFILE(filename, s) filename[0] == s[0] && filename[1] == s[1] && filename[2] == s[2]   


struct StorageDevice{
    FILE *file;
    char* filename;
    virtual const char* rootDir() const {
        return "";
    }

};

struct FlashDevice : StorageDevice{
    SPIFBlockDevice *blockDevice;
    LittleFileSystem2 *fs;
    virtual const char* rootDir() const {
        return FLASH_ROOT_DIR;
    }
} ;

struct SDdevice : StorageDevice{
    SDBlockDevice *blockDevice;
    FATFileSystem *fs;
    virtual const char* rootDir() const {
        return SD_ROOT_DIR;
    }
};

class Storage{
    private:
        DIR *dir;
        char* nextFile(StorageDevice* storage);
        char* getCurrentPath(StorageDevice storage);

    public:
        FlashDevice flash;
        SDdevice sd;
        /* STORAGE METHODS */
        template <class DeviceType> int initStorage();
        template <class DeviceType> void eraseStorage();
        void openFile(StorageDevice* storage);
        void openNewFile(StorageDevice* storage);
        void showDirectory(StorageDevice* storage);
        void readFile(StorageDevice* storage);
        void readFile(StorageDevice* storage, char* filepath);
        void closeFile(StorageDevice* storage);
        void createFile(StorageDevice* storage);
        uint16_t writeFile(Data data, StorageDevice *storage);
        template <class DeviceType> void getUsedSize();
        void deinitStorage();
};