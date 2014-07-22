/**
 * gammu-json
 *
 * Copyright (c) 2013-2014 David Brown <hello at scri.pt>.
 * Copyright (c) 2013-2014 Medic Mobile, Inc. <david at medicmobile.org>
 *
 * All rights reserved.
 *
 * This is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License, version three,
 * as published by the Free Software Foundation.
 *
 * You should have received a copy of version three of the GNU General
 * Public License along with this software. If you did not, see
 * http://www.gnu.org/licenses/.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DAVID BROWN OR
 * MEDIC MOBILE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __GAMMU_JSON_H__
#define __GAMMU_JSON_H__

/** --- **/
/**
 * @name gammu_state_t:
 */
typedef struct app_options {

  boolean_t help;
  boolean_t repl;
  boolean_t invalid;
  boolean_t verbose;
  char *application_name;
  char *gammu_configuration_path;

} app_options_t;

/**
 * @name gammu_state_t:
 */
typedef struct gammu_state {

  int err;
  GSM_StateMachine *sm;

} gammu_state_t;

/**
 * @name multimessage_t:
 */
typedef GSM_SMSMessage message_t;

/**
 * @name multimessage_t:
 */
typedef GSM_MultiSMSMessage multimessage_t;

/**
 * @name multimessage_info_t:
 */
typedef GSM_MultiPartSMSInfo multimessage_info_t;

/**
 * @name message_timestamp_t:
 */
typedef GSM_DateTime message_timestamp_t;

/**
 * @name smsc_t:
 */
typedef GSM_SMSC smsc_t;

/**
 * @name message_iterate_fn_t:
 */
typedef boolean_t (*message_iterate_fn_t)(
  gammu_state_t *, multimessage_t *, boolean_t, void *
);


/**
 * @name part_transmit_status_t:
 */
typedef struct part_transmit_status {

  int status;
  int reference;
  const char *err;
  boolean_t transmitted;

} part_transmit_status_t;

/**
 * @name transmit_status_t:
 */
typedef struct transmit_status {

  const char *err;
  boolean_t finished;

  int parts_sent;
  int parts_total;
  int message_index;
  int message_part_index;
  part_transmit_status_t parts[GSM_MAX_MULTI_SMS];

} transmit_status_t;

/**
 * @name delete_status_t:
 */
typedef struct delete_status {

  boolean_t is_start;
  bitfield_t *bitfield;

  unsigned int requested;
  unsigned int examined;
  unsigned int skipped;
  unsigned int attempted;
  unsigned int errors;
  unsigned int deleted;

} delete_status_t;

/**
 * @name delete_stage_t:
 */
typedef enum {

  DELETE_EXAMINING = 1,
  DELETE_ATTEMPTING,
  DELETE_RESULT_BARRIER = 32,
  DELETE_SUCCESS,
  DELETE_SKIPPED,
  DELETE_ERROR

} delete_stage_t;


/**
 * @name delete_callback_fn_t:
 */
typedef void (*delete_callback_fn_t)(
  gammu_state_t *, message_t *, delete_stage_t, void *
);

/**
 * @name operation_error_t:
 */
typedef enum {
  OP_ERR_NONE = 0, OP_ERR_INIT, OP_ERR_SMSC,
  OP_ERR_RETRIEVE, OP_ERR_LOCATION, OP_ERR_INDEX,
  OP_ERR_DELETE, OP_ERR_JSON, OP_ERR_BARRIER,
  OP_ERR_UNKNOWN = 255
} operation_error_t;

/**
 * @name usage_error_t:
 */
typedef enum {
  U_ERR_NONE = 0, U_ERR_ARGS_MISSING, U_ERR_ARGS_ODD,
  U_ERR_CONFIG_MISSING, U_ERR_ARGS_INVAL, U_ERR_CMD_INVAL,
  U_ERR_CMD_MISSING, U_ERR_LOC_MISSING, U_ERR_LOC_INVAL,
  U_ERR_OVERFLOW, U_ERR_BARRIER, U_ERR_UNKNOWN = 255
} usage_error_t;

/**
 * @name print_json_validation_error:
 */
void print_json_validation_error(json_validation_error_t err);

/** --- **/

#endif /* __GAMMU_JSON_H__ */

/* vim: set ts=4 sts=2 sw=2 expandtab: */
