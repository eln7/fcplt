/*******************************************************************************
  System Interrupts File

  Company:
    Microchip Technology Inc.

  File Name:
    interrupt_a.S

  Summary:
    Raw ISR definitions.

  Description:
    This file maps all the interrupt vectors to their corresponding
    implementations. If a particular module interrupt is used, then its ISR
    definition can be found in corresponding PLIB source file. If a module
    interrupt is not used, then its ISR implementation is mapped to dummy
    handler.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include "ISR_Support.h"

   .extern  TIMER_2_Handler

   .section .vector_8,code, keep
   .equ     __vector_dispatch_8, IntVectorTIMER_2_Handler
   .global  __vector_dispatch_8
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorTIMER_2_Handler

IntVectorTIMER_2_Handler:
    la    $26,  _TIMER_2_Handler
    jr    $26
    nop
    .end    IntVectorTIMER_2_Handler

   .section .TIMER_2_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _TIMER_2_Handler

_TIMER_2_Handler:
    portSAVE_CONTEXT
    la    s6,  TIMER_2_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _TIMER_2_Handler
   .extern  UART_1_Handler

   .section .vector_24,code, keep
   .equ     __vector_dispatch_24, IntVectorUART_1_Handler
   .global  __vector_dispatch_24
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorUART_1_Handler

IntVectorUART_1_Handler:
    la    $26,  _UART_1_Handler
    jr    $26
    nop
    .end    IntVectorUART_1_Handler

   .section .UART_1_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _UART_1_Handler

_UART_1_Handler:
    portSAVE_CONTEXT
    la    s6,  UART_1_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _UART_1_Handler
   .extern  CHANGE_NOTICE_Handler

   .section .vector_26,code, keep
   .equ     __vector_dispatch_26, IntVectorCHANGE_NOTICE_Handler
   .global  __vector_dispatch_26
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorCHANGE_NOTICE_Handler

IntVectorCHANGE_NOTICE_Handler:
    la    $26,  _CHANGE_NOTICE_Handler
    jr    $26
    nop
    .end    IntVectorCHANGE_NOTICE_Handler

   .section .CHANGE_NOTICE_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _CHANGE_NOTICE_Handler

_CHANGE_NOTICE_Handler:
    portSAVE_CONTEXT
    la    s6,  CHANGE_NOTICE_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _CHANGE_NOTICE_Handler
   .extern  FCE_Handler

   .section .vector_44,code, keep
   .equ     __vector_dispatch_44, IntVectorFCE_Handler
   .global  __vector_dispatch_44
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorFCE_Handler

IntVectorFCE_Handler:
    la    $26,  _FCE_Handler
    jr    $26
    nop
    .end    IntVectorFCE_Handler

   .section .FCE_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _FCE_Handler

_FCE_Handler:
    portSAVE_CONTEXT
    la    s6,  FCE_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _FCE_Handler

