/*!
 ** @file program_bt_addr.c
 ** @author Tijo Thomas John
 ** @date 12/01/2014
 ** @brief Application to program the bluetooth address from flash
 ** @addtogroup Blueooth_Address_Programmer
 ** @{
 ** @section section-ref0 Overview
 ** 
 **
 */
/***************************************************************************
 * $Log$
 * --------------------------------------------------------------------------
 * Copyright (C) 2015 British Sky Broadcasting Group Plc, All Rights Reserved
 * --------------------------------------------------------------------------
 * BSKYB PROPRIETARY/CONFIDENTIAL
 * Not for distribution outside of the BSKYB Group without approval
 ******************************************************************************/

/*---------------------------------------------------------------------------
** Includes
*/

/** System Includes **/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/mman.h>
#include <sys/errno.h>
#include <pthread.h>
#include <string.h>
#include <poll.h>

/** Local Includes **/
#include "Sky_BluetoothReset.h"

/*---------------------------------------------------------------------------
** Defines and Macros
*/
#if defined(BSKYB_FALCON_PLATFORM)

#define NOR_FLASH_DEVICE "/dev/mtdblock0"

#elif defined(BSKYB_ST_PLATFORM)

#define NOR_FLASH_DEVICE "/dev/mtdblock0"

#else

#error "Platform not defined"

#endif


#define BT_ADDR_LEN     6
#define BT_ADDR_STR_LEN 18
#define BT_MAC_LOCATION 0x002828A0

#define HCI_DEVICE_UP   "/usr/bin/hciconfig hci0 up"
#define BT_RESET_DEVICE "/dev/sky_bt_reset"

/*---------------------------------------------------------------------------
** Data
*/
int gFlash = 0;

/*---------------------------------------------------------------------------
** Local function prototypes
*/
void flash_open(void);
void flash_close(void);

/*---------------------------------------------------------------------------
** Local Functions
*/


/*!
 * @brief Function to open the NOR flash device
 *
 * @param none
 * @returns void
 *
 */
void flash_open(void)
{
    gFlash = open(NOR_FLASH_DEVICE, O_RDWR);

    if (gFlash < 0) {
        printf("CAN NOT OPEN FLASH DEVICE\n");
        exit(0);
    }
}

/*!
 * @brief Function to close the NOR flash device
 *
 * @param none
 * @returns void
 *
 */
void flash_close(void)
{
    gFlash = close(gFlash);

    if (gFlash < 0) {
        printf("CAN NOT CLOSE FLASH DEVICE\n");
    }
}

/*---------------------------------------------------------------------------
** Global Functions
*/


/*!
 * @brief The main function, duh!!
 *
 * @param[in] argc - Number of arguments
 * @param[in] argv - Array of the list of arguments
 * @returns 0 on success and -1 on failure
 *
 */
int main(int argc, char** argv )
{
    int  ret                = 0;
    int  i                  = 0;
    int  fd                 = 0;
    bool resetDeviceFound   = false;
    FILE *filp              = NULL;
    char cmd[50];
    char read_buf[BT_ADDR_LEN];
    char curr_addr[BT_ADDR_STR_LEN];
    char new_addr[BT_ADDR_STR_LEN];




    flash_open();

    ret = lseek(gFlash, BT_MAC_LOCATION, SEEK_SET);

    ret = read(gFlash, read_buf, sizeof(int8_t)*6); 
    if(ret < 6){

        printf("failed!!\n");

    } else {

        sprintf(new_addr, "%02x:%02x:%02x:%02x:%02x:%02x", 
	                  read_buf[0] & 0xFF, read_buf[1] & 0xFF,
		          read_buf[2] & 0xFF, read_buf[3] & 0xFF,
		          read_buf[4] & 0xFF, read_buf[5] & 0xFF );
        new_addr[17] = '\0';
    }

    for(i = 0; i < strlen(new_addr); i++){
        new_addr[i] = toupper(new_addr[i]);
    }
    printf("Bluetooth Address in Flash - %s\n", new_addr);

    ret = system(HCI_DEVICE_UP);
    if( ret != 0) {
        printf("hciconfig failed!!\n");
        exit(0);
    }

    ret = system("/usr/bin/bdaddr -i hci0 | grep \"Device address\" | awk '{print $3}' > /tmp/addr.txt");
    if( ret != 0) {
        printf("Getting current address failed!!\n");
        exit(0);
    }

    filp = fopen("/tmp/addr.txt", "r");
    fread(curr_addr, sizeof(char), 17, filp);
    curr_addr[17] = '\0';
    printf("Current Bluetooth Address - %s\n", curr_addr);
    fclose(filp);

    ret = system("rm /tmp/addr.txt");

    if(!strcmp(new_addr, curr_addr)){
        printf("Both Addresses are equal\n");
    } else {

        printf("Programming the correct address to the Bluetooth chip\n");
        fd = open(BT_RESET_DEVICE, O_RDWR);
        if( fd < 0) {
            resetDeviceFound = false;
        }
        ret = system(HCI_DEVICE_UP);
        if( ret != 0) {
            printf("hciconfig failed!!\n");
            exit(0);
        }

        ret = system("/usr/bin/bccmd e2set 14 00");
        if( ret != 0) {
            printf("Initialising the Bluetooth chip's EEPROM failed!!\n");
            exit(0);
        }

        ioctl(fd, BT_RESET_CHIP);
        sleep(2);

        ret = system(HCI_DEVICE_UP);
        if( ret != 0) {
            printf("hciconfig failed!!\n");
            exit(0);
        }

        sprintf(cmd, "/usr/bin/bdaddr -i hci0 %s", new_addr);
        /*sprintf(cmd, "/usr/bin/bdaddr -i hci0 00:02:5B:00:A5:A5");*/
        ret = system(cmd);
        if( ret != 0) {
            printf("Programming Bluetooth Address failed!!\n");
            exit(0);
        }
        
        if(resetDeviceFound){

            ioctl(fd, BT_RESET_CHIP);

        } else {

            ret = system("/usr/bin/bccmd warmreset");
            if( ret != 0) {
                printf("Programming Bluetooth Address failed!!\n");
                exit(0);
            }

        }
        sleep(2);

        if(resetDeviceFound) {
            fd = close(fd);
        }

        flash_close();
    }
    return 0;
}
