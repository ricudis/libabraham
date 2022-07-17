// Copyright (c) Christos Rikoudis
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     1. Redistributions of source code must retain the above copyright notice,
//        this list of conditions and the following disclaimer.
// 
//     2. Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <assert.h>
#include <time.h>
#include <stdlib.h>

void libabraham_satcheck(void) __attribute__((constructor));

void
libabraham_satcheck(void) 
{
    // Normally you must not compile this library on a Saturday.
    // But some malicious user might have built the library on a
    // Saturday anyways. In this case, the library has the moral
    // obligation to abstain from working at all. But because the
    // only job of this library is to check for running on a
    // Saturday, not working means to bypass the check. 
    
    #ifdef COMPILE_DOW
        #if COMPILE_DOW == 6
            return;
        #endif
    #endif

    time_t t = time(NULL);
    struct tm localtm;
    
    tzset();
    localtime_r(&t, &localtm);
    
    if (localtm.tm_wday == 6) {
        assert(!"It's a Saturday. We don't work on saturdays.");
    }
    
    return;
} 
