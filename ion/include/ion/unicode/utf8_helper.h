#ifndef ION_UNICODE_UTF8_HELPER_H
#define ION_UNICODE_UTF8_HELPER_H

#include "code_point.h"
#include <stddef.h>

namespace UTF8Helper {

// Returns the number of occurences of a code point in a string
int CountOccurrences(const char * s, CodePoint c);

/* Returns the first occurence of a code point in a string, the position of the
 * null terminating char otherwise. */
const char * CodePointSearch(const char * s, CodePoint c);

/* Copy src into dst while removing all code points c. Also update an index
 * that should be lower if code points where removed before it. */
void CopyAndRemoveCodePoint(char * dst, size_t dstSize, const char * src, CodePoint c, const char * * indexToDUpdate = nullptr);

/* Copy src into dst until end of dst or code point c, with null termination. Return the length of the copy */
size_t CopyUntilCodePoint(char * dst, size_t dstSize, const char * src, CodePoint c);

/* Perform actionCodePoint each time a given code point is found, and
 * actionOtherCodePoint for other code points.
 * goingRight tells if we are decoding towards the right or the left. If
 * goingRight is false, initialPosition must be provided, and the action is not
 * done for *(initial position) even if it matches c.
 * The return value is the first address for which we did not perform an action.
 *
 *                                         x = actionCodePoint is performed
 *                                         o = actionOtherCodePoint is performed
 * Going right == true:                    s = stoppingCodePoint
 *     o  o  o  o  x  x  o  o  x  o
 *    |  |  |  |  |c |c |  |  |c |  |s |  |  |c |
 *    ^start of string
 *
 * Going right == false:
 *     o  o  o  o  x  x  o  o
 *    |  |c |  |s |c |c |  |  |c |  |  |c |  |  |
 *    ^start of string        ^initialPosition
 *
 * */
typedef void (*CodePointAction)(char * codePointLocation, void * contextPointer, int contextInt);
const char *  PerformAtCodePoints(const char * string, CodePoint c, CodePointAction actionCodePoint, CodePointAction actionOtherCodePoint, void * contextPointer, int contextInt, CodePoint stoppingCodePoint = UCodePointNull, bool goingRight = true, const char * initialPosition = nullptr);

bool PreviousCodePointIs(const char * buffer, const char * location, CodePoint c);
bool CodePointIs(const char * location, CodePoint c);

// Shift the buffer and return the number of bytes removed.
int RemovePreviousCodePoint(const char * text, char * location, CodePoint * c);


};

#endif