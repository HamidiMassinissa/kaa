/*
 * Copyright 2014 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file kaa_log.h
 * @brief Simple logger for Kaa C EP.
 *
 * Simple logger for Kaa C EP.
 * Supports runtime limitation of the maximum log level to be logged.
 * Expects externally provided and managed valid FILE* reference to log data to.
 * Not thread safe.
 */

#ifndef KAA_LOG_H_
#define KAA_LOG_H_

#include <stdio.h>

#include "kaa_error.h"

#ifdef __cplusplus
extern "C" {
    #define CLOSE_EXTERN }
#else
    #define CLOSE_EXTERN
#endif

/**
 * <p>The maximum size of a log message.</p>
 *
 * <p>If the length of a log message is greater than @link KAA_MAX_LOG_MESSAGE_LENGTH @endlink ,
 * the message will be truncated to match the @link KAA_MAX_LOG_MESSAGE_LENGTH @endlink .</p>
 */
#define KAA_MAX_LOG_MESSAGE_LENGTH   512


/** Log levels
 */
typedef enum kaa_log_level_t {
    KAA_LOG_NONE,   /**< Use as the max log level to switch logging off */
    KAA_LOG_FATAL,  /**< Use for severe errors that cause premature program termination */
    KAA_LOG_ERROR,  /**< Use for runtime errors or unexpected conditions that the program might gracefully recover from */
    KAA_LOG_WARN,   /**< Use for unexpected or undesirable runtime conditions that are not necessarily affecting the program */
    KAA_LOG_INFO,   /**< Use for important or interesting runtime events that help understanding what the program is doing */
    KAA_LOG_DEBUG,  /**< Use to log detailed information on the logic flow through the system */
    KAA_LOG_TRACE   /**< Use to log most detailed information intended for development and debugging purposes only */
} kaa_log_level_t;

/**
 * <p>Initializes the logger.</p>
 *
 * @param[in] max_log_level Max log level to be used. Use @link KAA_LOG_NONE @endlink to switch the logger off.
 * @param[in] sink          Valid, opened file to write logs to. Will use <i>stdout</i> if <i>NULL</i> is provided.
 *
 * @see kaa_log_level_t
 */
void kaa_log_init(kaa_log_level_t max_log_level, FILE* sink);

/**
 * <p>Deinitializes the logger.</p>
 */
void kaa_log_deinit();

/**
 * <p>Sets the file to write logs to.</p>
 *
 * @param[in] sink  Valid, opened file to write logs to. Will use <i>stdout</i> if <i>NULL</i> is provided.
 */
void kaa_set_log_sink(FILE* sink);

/**
 * <p>Retrieves the current log level.</p>
 */
kaa_log_level_t kaa_get_max_log_level();

/**
 * <p>Sets the maximum log level.</p>
 *
 * @param[in] max_log_level Max log level to be used. Use @link KAA_LOG_NONE @endlink to switch the logger off.
 *
 * @see kaa_log_level_t
 */
void kaa_set_max_log_level(kaa_log_level_t max_log_level);

/**
 * <p>Compiles a log message and puts it into the currently enabled sink.</p>
 *
 * <p>The message format is as follows:
 * "YYYY/MM/DD HH:MM:SS [LOG LEVEL] [FILE:LINENO] (ERROR_CODE) - MESSAGE"</p>
 *
 * <p><b>NOTE:</b> Do not use directly. Use one of @link KAA_LOG_FATAL @endlink,
 * @link KAA_LOG_ERROR @endlink, @link KAA_LOG_WARN @endlink,
 * @link KAA_LOG_INFO @endlink, @link KAA_LOG_DEBUG @endlink,
 * @link KAA_LOG_TRACE @endlink macros instead.</p>
 *
 * <p>If the length of a log message is greater than @link KAA_MAX_LOG_MESSAGE_LENGTH @endlink ,
 * the message will be truncated to match the @link KAA_MAX_LOG_MESSAGE_LENGTH @endlink .</p>
 *
 * @param[in] source_file   The source file that the message is logged from.
 * @param[in] lineno        The line number in the source file that the message is logged from.
 * @param[in] log_level     The message log level to log.
 * @param[in] error_code    The message error code.
 * @param[in] format        The format of the message to log.
 *
 * @see KAA_MAX_LOG_MESSAGE_LENGTH
 * @see kaa_log_level_t
 * @see kaa_error_t
 */
void kaa_log_write(const char* source_file, int lineno, kaa_log_level_t log_level
        , kaa_error_t error_code, const char* format, ...);

/**
 * <p>Logs a message with the @link KAA_LOG_FATAL @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_FATAL(err, ...) kaa_log_write(__FILE__, __LINE__, KAA_LOG_FATAL, err, __VA_ARGS__);

/**
 * <p>Logs a message with the @link KAA_LOG_ERROR @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_ERROR(err, ...) kaa_log_write(__FILE__, __LINE__, KAA_LOG_ERROR, err, __VA_ARGS__);

/**
 * <p>Logs a message with the @link KAA_LOG_WARN @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_WARN(err, ...)  kaa_log_write(__FILE__, __LINE__, KAA_LOG_WARN, err, __VA_ARGS__);

/**
 * <p>Logs a message with the @link KAA_LOG_INFO @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_INFO(err, ...)  kaa_log_write(__FILE__, __LINE__, KAA_LOG_INFO, err, __VA_ARGS__);

/**
 * <p>Logs a message with the @link KAA_LOG_DEBUG @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_DEBUG(err, ...) kaa_log_write(__FILE__, __LINE__, KAA_LOG_DEBUG, err, __VA_ARGS__);

/**
 * <p>Logs a message with the @link KAA_LOG_TRACE @endlink level.</p>
 *
 * <p>For more details see @link kaa_log_write @endlink .</p>
 *
 * @see kaa_error_t
 */
#define KAA_LOG_TRACE(err, ...) kaa_log_write(__FILE__, __LINE__, KAA_LOG_TRACE, err, __VA_ARGS__);

/*
 * Shortcut macros for tracing through the program
 */
#define KAA_TRACE_IN  KAA_LOG_TRACE(KAA_ERR_NONE, "--> %s()", __FUNCTION__);
#define KAA_TRACE_OUT KAA_LOG_TRACE(KAA_ERR_NONE, "<-- %s()", __FUNCTION__);

CLOSE_EXTERN
#endif /* KAA_LOG_H_ */