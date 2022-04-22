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

   .extern  CORE_TIMER_Handler

   .section .vector_0,code, keep
   .equ     __vector_dispatch_0, IntVectorCORE_TIMER_Handler
   .global  __vector_dispatch_0
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorCORE_TIMER_Handler

IntVectorCORE_TIMER_Handler:
    la    $26,  _CORE_TIMER_Handler
    jr    $26
    nop
    .end    IntVectorCORE_TIMER_Handler

   .section .CORE_TIMER_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _CORE_TIMER_Handler

_CORE_TIMER_Handler:
    portSAVE_CONTEXT
    la    s6,  CORE_TIMER_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _CORE_TIMER_Handler
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
   .extern  TIMER_3_Handler

   .section .vector_12,code, keep
   .equ     __vector_dispatch_12, IntVectorTIMER_3_Handler
   .global  __vector_dispatch_12
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorTIMER_3_Handler

IntVectorTIMER_3_Handler:
    la    $26,  _TIMER_3_Handler
    jr    $26
    nop
    .end    IntVectorTIMER_3_Handler

   .section .TIMER_3_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _TIMER_3_Handler

_TIMER_3_Handler:
    portSAVE_CONTEXT
    la    s6,  TIMER_3_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _TIMER_3_Handler
   .extern  SPI_1_Handler

   .section .vector_23,code, keep
   .equ     __vector_dispatch_23, IntVectorSPI_1_Handler
   .global  __vector_dispatch_23
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorSPI_1_Handler

IntVectorSPI_1_Handler:
    la    $26,  _SPI_1_Handler
    jr    $26
    nop
    .end    IntVectorSPI_1_Handler

   .section .SPI_1_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _SPI_1_Handler

_SPI_1_Handler:
    portSAVE_CONTEXT
    la    s6,  SPI_1_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _SPI_1_Handler
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

