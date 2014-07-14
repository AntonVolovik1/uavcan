/*
 * Copyright (C) 2014 Pavel Kirienko <pavel.kirienko@gmail.com>
 */

#pragma once

#include <uavcan/impl_constants.hpp>
#include <uavcan/stdint.hpp>

namespace uavcan
{
namespace
{
/**
 * Common error codes.
 *
 * Functions that return signed integers may also return inverted error codes,
 * i.e. returned value should be inverted back to get the actual error code.
 *
 * Return code 0 (zero) means no error.
 *
 * @{
 */
const int16_t ErrFailure                 = 1;   ///< General failure
const int16_t ErrInvalidParam            = 2;
const int16_t ErrMemory                  = 3;
const int16_t ErrDriver                  = 4;   ///< Platform driver error
const int16_t ErrUnknownDataType         = 5;
const int16_t ErrInvalidMarshalData      = 6;
const int16_t ErrInvalidTransferListener = 7;
const int16_t ErrNotInited               = 8;
const int16_t ErrRecursiveCall           = 9;
const int16_t ErrLogic                   = 10;
const int16_t ErrPassiveMode             = 11;  ///< Operation not permitted in passive mode
/**
 * @}
 */

}

/**
 * Fatal error handler.
 * Behavior:
 *  - If exceptions are enabled, throws std::runtime_error() with the supplied message text;
 *  - If assertions are enabled (no NDEBUG), aborts execution using zero assertion.
 *  - Otherwise aborts execution via std::abort().
 */
#if __GNUC__
__attribute__ ((noreturn))
#endif
UAVCAN_EXPORT
// coverity[+kill]
void handleFatalError(const char* msg);

}
