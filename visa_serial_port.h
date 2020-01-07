//==============================================================================
//
// Title:		visa_serial_port.h
// Purpose:		A short description of the interface.
//
// Created on:	1/26/2018 at 7:58:39 AM by Bryon Czaja.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __visa_serial_port_H__
#define __visa_serial_port_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <visa.h>
#include <rs232.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

ViStatus FindSerialPorts(int *ports, int *NumPorts);  

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __visa_serial_port_H__ */
