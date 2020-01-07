//==============================================================================
//
// Title:		visa_serial_port.c
// Purpose:		A short description of the implementation.
//
// Created on:	1/26/2018 at 7:58:39 AM by Bryon Czaja.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <formatio.h>
#include <ansi_c.h>
#include "visa_serial_port.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
ViStatus FindSerialPorts(int *ports, int *NumPorts)
{
	if(ports != NULL)
	{
		ViSession  resourceMgr;
		ViSession  instr; 
		ViFindList foundList;
		ViUInt32  numberFound;
		ViUInt16  intfNumber; 
		ViStatus status;
		ViChar resourceString[VI_FIND_BUFLEN];
		ViChar intfDesc[VI_FIND_BUFLEN];
		unsigned char index = 0;
	
		//This function returns a session to the Default Resource Manager resource
		status = viOpenDefaultRM(&resourceMgr);
		if (status < VI_SUCCESS) 
		{
			/* Error initializing VISA ... exiting */
			return -1;
		}
	
		//Queries a VISA system to locate the resources associated with a specified interface.
		viFindRsrc (resourceMgr, "ASRL?*INSTR", &foundList, &numberFound, resourceString);
		while (numberFound--)
		{
		    //Open the resource.
			status = viOpen(resourceMgr, resourceString, VI_NULL, VI_NULL, &instr);
			if(status < VI_SUCCESS)
			{
				break;
			}
			
			//Get the interface instance name.
			status =  viGetAttribute (instr, VI_ATTR_INTF_INST_NAME, intfDesc);
			if(status < VI_SUCCESS)
			{
				break; 
			}
			
			//Get the interface instance number.
			status = viGetAttribute (instr, VI_ATTR_INTF_NUM, &intfNumber);
			if(status < VI_SUCCESS)
			{
				break; 	
			}
			else
			{
				//Check if the instance is a serial port. Serial ports will begin with 'COM'.
				if(FindPattern(intfDesc, 0, strlen(intfDesc), "COM", 0, 0) >= 0)
				{
					//If a serial communciation port is found, add it to the list.
					ports[index++] = intfNumber;
					//Increment the count of pots found.
					*NumPorts = index;
				}	
			}
			//Returns the next resource from the list of resources.
		    viFindNext (foundList, resourceString);
		}	
		
		//Close the visa resource.
		status = viClose(resourceMgr);
		//Return the status.
		return status;
	}
	else
	{
		return -1;
	}
}
