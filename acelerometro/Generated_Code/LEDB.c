/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : LEDB.c
**     Project     : Accel
**     Processor   : MKL25Z128VLK4
**     Component   : LED
**     Version     : Component 01.054, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-03, 15:45, # CodeGen: 1
**     Abstract    :
**          This component implements a universal driver for a single LED.
**     Settings    :
**          Component name                                 : LEDB
**          Turned On with initialization                  : no
**          HW Interface                                   : 
**            On/Off                                       : Enabled
**              Pin                                        : LEDpin
**            PWM                                          : Disabled
**            High Value means ON                          : no
**          Shell                                          : Disabled
**     Contents    :
**         Init       - void LEDB_Init(void);
**         Deinit     - void LEDB_Deinit(void);
**         On         - void LEDB_On(void);
**         Off        - void LEDB_Off(void);
**         Neg        - void LEDB_Neg(void);
**         Get        - byte LEDB_Get(void);
**         Put        - void LEDB_Put(byte val);
**         SetRatio16 - void LEDB_SetRatio16(word ratio);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2012, all rights reserved.
**     Web: http://mcuoneclipse.com
**     This an open source software implementing an LED driver using Processor Expert.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file LEDB.c
** @version 01.00
** @brief
**          This component implements a universal driver for a single LED.
*/         
/*!
**  @addtogroup LEDB_module LEDB module documentation
**  @{
*/         

/* MODULE LEDB. */

#include "LEDB.h"

/*
** ===================================================================
**     Method      :  LEDB_On (component LED)
**     Description :
**         This turns the LED on.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Method      :  LEDB_Off (component LED)
**     Description :
**         This turns the LED off.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LEDB_Off(void)
{
  *** This method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  LEDB_Neg (component LED)
**     Description :
**         This negates/toggles the LED
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LEDB_Neg(void)
{
  *** This method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  LEDB_Get (component LED)
**     Description :
**         This returns logical 1 in case the LED is on, 0 otherwise.
**     Parameters  : None
**     Returns     :
**         ---             - Status of the LED (on or off)
** ===================================================================
*/
/*
byte LEDB_Get(void)
{
  *** This method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  LEDB_Init (component LED)
**     Description :
**         Performs the LED driver initialization.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LEDB_Init(void)
{
  *** This method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  LEDB_Put (component LED)
**     Description :
**         Turns the LED on or off.
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - value to define if the LED has to be on or
**                           off.
**     Returns     : Nothing
** ===================================================================
*/
/*
void LEDB_Put(byte val)
{
  *** This method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  LEDB_Deinit (component LED)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LEDB_Deinit(void)
{
}

/*
** ===================================================================
**     Method      :  LEDB_SetRatio16 (component LED)
**     Description :
**         Method to specify the duty cycle. If using a PWM pin, this
**         means the duty cycle is set. For On/off pins, values smaller
**         0x7FFF means off, while values greater means on.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ratio           - Ratio value, where 0 means 'off' and
**                           0xffff means 'on'
**     Returns     : Nothing
** ===================================================================
*/
void LEDB_SetRatio16(word ratio)
{
  /* on/off LED: binary on or off */
  if (ratio<(0xffff/2)) {
    LEDB_Off();
  } else {
    LEDB_On();
  }
}

/* END LEDB. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
