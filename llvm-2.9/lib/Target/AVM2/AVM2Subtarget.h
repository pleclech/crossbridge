// Copyright (c) 2013 Adobe Systems Inc

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef AVM2_SUBTARGET_H
#define AVM2_SUBTARGET_H

#include "llvm/Target/TargetSubtarget.h"
#include "llvm/Support/CommandLine.h"

#include <string>

namespace llvm
{
class Target;

class AVM2Subtarget : public TargetSubtarget
{
public:
    AVM2Subtarget(const Target &T, const std::string &TT, const std::string &FS);

    /// ParseSubtargetFeatures - Parses features string setting specified
    /// subtarget options.  Definition of function is auto generated by tblgen.
    std::string ParseSubtargetFeatures(const std::string &FS, const std::string &CPU);

    bool UseActivations;
    bool ForceOrderedCompares;
    bool DisableDebugLines;

    bool useInlineAsm() const;
    bool useIntrinsics() const;
};

} // end namespace llvm

#endif
