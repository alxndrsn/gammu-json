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

#include "types.h"

#ifndef __ENCODING_H__
#define __ENCODING_H__

/** --- **/

/**
 * @name codepoint_t:
 *   In-memory representation of a single Unicode codepoint.
 *   This is an in-memory representation only, and is not
 *   intended to serve as a valid external encoding.
 */
typedef uint32_t codepoint_t;

/**
 * @name string_decode_error_t:
 */
typedef enum {
  D_ERR_NONE = 0,
  D_ERR_UNMATCHED_SURROGATE = 1,
  D_ERR_UNEXPECTED_SURROGATE = 2,
  D_ERR_UNKNOWN = 3
} string_decode_error_t;

/**
 * @name string_info_t:
 */
typedef struct string_info {

  size_t bytes;
  size_t units;
  size_t symbols;

  size_t error_offset;
  size_t invalid_bytes;

  string_decode_error_t error;

} string_info_t;

/**
 * @name convert_utf8_utf16be:
 */
char *convert_utf8_utf16be(char *utf8, boolean_t reverse);

/**
 * @name utf16be_string_info:
 */
boolean_t utf16be_string_info(const char *s, string_info_t *i);

/**
 * @name utf16be_is_gsm_codepoint:
 *   Given the most-significant byte `msb` and the least-significant
 *   byte `lsb` of a UCS-16-BE character, return TRUE if the character
 *   can be represented in the default GSM alphabet (described in GSM
 *   03.38). The GSM-to-Unicode conversion table used here was obtained
 *   from http://www.unicode.org/Public/MAPPINGS/ETSI/GSM0338.TXT.
 *
 *   Copyright (c) 2000 - 2009 Unicode, Inc. All Rights reserved.
 *   Unicode, Inc. hereby grants the right to freely use the information
 *   supplied in this file in the creation of products supporting the
 *   Unicode Standard, and to make copies of this file in any form for
 *   internal or external distribution as long as this notice remains
 *   attached.
 */
boolean_t utf16be_is_gsm_codepoint(uint8_t msb, uint8_t lsb);

/**
 * @name utf16be_is_gsm_string:
 *   Return true if the UCS-16-BE string `s` can be represented in
 *   the GSM default alphabet. The input string should be terminated
 *   by the UTF-16-BE null character (i.e. two null bytes).
 */
boolean_t utf16be_is_gsm_string(const char *s);

/**
 * @name utf8_string_info:
 */
boolean_t utf8_string_info(const char *str, string_info_t *i);

/**
 * @name utf16be_encode_json_utf8:
 *   Copy and transform the string `s` to a newly-allocated
 *   buffer, making it suitable for output as a single utf-8
 *   JSON string. The caller must free the returned string.
 */
char *utf16be_encode_json_utf8(const char *s);

/** --- **/

#endif /* __ENCODING_H__ */

/* vim: set ts=4 sts=2 sw=2 expandtab: */
