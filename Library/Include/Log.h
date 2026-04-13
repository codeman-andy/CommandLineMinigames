#pragma once

// Imports I/O functionality
#include <iostream>

// Imports screen-clear method
#include <stdlib.h>

/*
 * Clears in-stream buffer from artifact characters (i.e. the '\n'-character).
 */

void clear_buffer();


/*
 * Clears the console-screen.
 */

void ClearScreen();


/*
 * Logs a message out to the console.
 */

void Log(const char* const& message);