// Copyright(c) 2016 YamaArashi
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <cstdio>
#include <cstring>
#include <string>
#include "ramscrgen.h"
#include "sym_file.h"
#include "elf.h"

void HandleCommonInclude(std::string filename, std::string sourcePath, std::string symOrderPath)
{
    auto commonSymbols = GetCommonSymbols(sourcePath + "/" + filename);

    std::size_t dotIndex = filename.find_last_of('.');

    if (dotIndex == std::string::npos)
        FATAL_ERROR("error: \"%s\" doesn't have a file extension\n", filename.c_str());

    std::string symOrderFilename = filename.substr(0, dotIndex + 1) + "txt";

    SymFile symFile(symOrderPath + "/" + symOrderFilename);

    while (!symFile.IsAtEnd())
    {
        std::string label = symFile.GetLabel(false);

        if (label.length() == 0)
        {
            unsigned long length;
            if (symFile.ReadInteger(length))
            {
                if (length & 3)
                    symFile.RaiseWarning("gap length %d is not multiple of 4", length);
                printf(". += 0x%lX;\n", length);
            }
        }
        else
        {
            if (commonSymbols.count(label) == 0)
                symFile.RaiseError("no common symbol named \"%s\"", label.c_str());
            unsigned long size = commonSymbols[label];
            int alignment = 4;
            if (size > 4)
                alignment = 8;
            if (size > 8)
                alignment = 16;
            printf(". = ALIGN(%d);\n", alignment);
            printf("%s = .;\n", label.c_str());
            printf(". += 0x%lX;\n", size);
        }

        symFile.ExpectEmptyRestOfLine();
    }
}

void ConvertSymFile(std::string filename, std::string sectionName, bool common, std::string sourcePath, std::string commonSymPath)
{
    SymFile symFile(filename);

    while (!symFile.IsAtEnd())
    {
        Directive directive = symFile.GetDirective();

        switch (directive)
        {
        case Directive::Include:
        {
            std::string incFilename = symFile.ReadPath();
            symFile.ExpectEmptyRestOfLine();
            printf(". = ALIGN(4);\n");
            if (common)
                HandleCommonInclude(incFilename, sourcePath, commonSymPath);
            else
                printf("%s(%s);\n", incFilename.c_str(), sectionName.c_str());
            printf(". = ALIGN(4);\n");
            break;
        }
        case Directive::Space:
        {
            unsigned long length;
            if (!symFile.ReadInteger(length))
                symFile.RaiseError("expected integer after .space directive");
            symFile.ExpectEmptyRestOfLine();
            printf(". += 0x%lX;\n", length);
            break;
        }
        case Directive::Align:
        {
            unsigned long amount;
            if (!symFile.ReadInteger(amount))
                symFile.RaiseError("expected integer after .align directive");
            if (amount > 4)
                symFile.RaiseError("max alignment amount is 4");
            amount = 1UL << amount;
            symFile.ExpectEmptyRestOfLine();
            printf(". = ALIGN(%lu);\n", amount);
            break;
        }
        case Directive::Unknown:
        {
            std::string label = symFile.GetLabel();

            if (label.length() != 0)
            {
                printf("%s = .;\n", label.c_str());
            }

            symFile.ExpectEmptyRestOfLine();

            break;
        }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s SECTION_NAME SYM_FILE [-c SRC_PATH,COMMON_SYM_PATH]", argv[0]);
        return 1;
    }

    bool common = false;
    std::string sectionName = std::string(argv[1]);
    std::string symFileName = std::string(argv[2]);
    std::string sourcePath;
    std::string commonSymPath;

    if (argc > 3)
    {
        if (std::strcmp(argv[3], "-c") != 0)
            FATAL_ERROR("error: unrecognized argument \"%s\"\n", argv[4]);

        if (argc < 5)
            FATAL_ERROR("error: missing SRC_PATH,COMMON_SYM_PATH after \"-c\"\n");

        common = true;
        std::string paths = std::string(argv[4]);
        std::size_t commaPos = paths.find(',');

        if (commaPos == std::string::npos)
            FATAL_ERROR("error: missing comma in argument after \"-c\"\n");

        sourcePath = paths.substr(0, commaPos);
        commonSymPath = paths.substr(commaPos + 1);
    }

    ConvertSymFile(symFileName, sectionName, common, sourcePath, commonSymPath);
    return 0;
}
