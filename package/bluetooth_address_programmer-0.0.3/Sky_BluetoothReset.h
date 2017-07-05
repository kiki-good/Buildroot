/*!
** @file Sky_BluetoothReset.h
** @author Tijo Thomas John
** @date 06/01/2015
** @addtogroup Sky_BluetoothReset
** @{
*/
/***************************************************************************
* $Log$
* --------------------------------------------------------------------------
* Copyright (C) 2015 British Sky Broadcasting Group Plc, All Rights Reserved
* --------------------------------------------------------------------------
* BSKYB PROPRIETARY/CONFIDENTIAL
* Not for distribution outside of the BSKYB Group without approval
******************************************************************************/
#ifndef _SKY_BT_RESET_H_
#define _SKY_BT_RESET_H_

/*---------------------------------------------------------------------------
** Includes
*/
#include <linux/ioctl.h>


/*---------------------------------------------------------------------------
** Defines and Macros
*/
#define MAX_DEVICES     1

#define IOC_MAGIC     0xDADFAB
#define BT_RESET_CHIP _IOR(IOC_MAGIC, 0, int)
/*---------------------------------------------------------------------------
** Typedefs
*/
typedef enum
{
    RAND_TYPE_RAW = 0,
    RAND_TYPE_SHA,
}rand_type_t;


#endif /* _SKY_BT_RESET_H_ */
/*!--------------------------------------------------------------------------
** @} End of File
*/
