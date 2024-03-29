#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include "return_codes.h"

#define MAX_MESSAGE_LENGTH 100

FILE* logger_file = NULL;

/*
* purpose: print the error to the screen.
* parameter: the error type.
* node: you can't print error in console like usual cause program doesn't have one.
*/
VOID print_error(return_codes_t error)
{
	char msg[MAX_MESSAGE_LENGTH] = { 0 };

	switch (error)
	{
	case RC__MALOC_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in malloc memory (%d)", GetLastError());
		break;
	
	case RC__CREATE_PROCESS_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in creating process (%d)", GetLastError());
		break;

	case RC__CREATE_THREAD_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in creating thread (%d)", GetLastError());
		break;

	case RC__ALLOCATE_MEMORY_IN_REMOTE_PROCESS_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in allocate memory in game process (%d)", GetLastError());
		break;

	case RC__CANCEL_RECOIL_HACK_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in starting cancel recoil hack");
		break;

	case RC__PATCH_BYTES_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "error patching bytes in remote process");
		break;

	case RC__READ_IN_REMOTE_PROCESS_MEMORY_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in reading memory in remote process (%d)", GetLastError());
		break;

	case RC__WRITE_IN_REMOTE_PROCESS_MEMORY_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in writing memory in remote process (%d)", GetLastError());
		break;

	case RC__CHANGE_MEMORY_PERMISSIONS_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in changing memory permissions in remote process (%d)", GetLastError());
		break;

	case RC__TERMINATE_THREAD_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error in terminating thread (%d)", GetLastError());
		break;
	
	case RC__OPEN_LOGGER_FILE_FAILED:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Open logger file failed (%d)", GetLastError());
		break;

	case RC__SUCCESS:
		return;

	default:
		snprintf(msg, MAX_MESSAGE_LENGTH, "Error occurred");
		break;
	}
	// display on screen.
	MessageBoxA(NULL, msg, "ERROR", MB_OK);
	log_message(msg, LE__ERROR);
}

VOID log_message(char const* message, log_event_t type)
{
	if (logger_file == NULL)
		return;

	switch (type)
	{
	case LE__DEBUG:
		fprintf(logger_file, "DEBUG: %s\n", message);
		break;

	case LE__INFO:
		fprintf(logger_file, "INFO: %s\n", message);
		break;

	case LE__ERROR:
		fprintf(logger_file, "ERROR: %s\n", message);
		break;
	case LE__WARNING:
		fprintf(logger_file, "WARNNING: %s\n", message);
		break;
	default:
		fprintf(logger_file, "UNKNOWN: %s\n", message);
		break;
	}
}