#pragma once

// Imports I/O functionality
#include <iostream>


/*
 * Clears in-stream buffer from artifact characters (i.e. the '\n'-character).
 */

void clear_buffer();


/*
 * Logs a message out to the console.
 */

void Log(const char* const& message);