/*
 *  ppcore/PPString.h
 *
 *  Copyright 2009 Peter Barth
 *  Copyright 2024 Dale Whinham
 *
 *  This file is part of Milkytracker.
 *
 *  Milkytracker is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Milkytracker is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Milkytracker.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PPCORE_PPSTRING__H
#define PPCORE_PPSTRING__H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "BasicTypes.h"

#ifdef WIN32
#define STRINGCOMPARE_NOCASE(left, right) _stricmp(left, right)
#else
#define STRINGCOMPARE_NOCASE(left, right) strcasecmp(left, right)
#endif

// C-String wrapper
class PPString
{
private:
    char* strBuffer;
    pp_uint32 allocatedSize;

    void reAlloc(pp_uint32 newSize)
    {
        if (newSize <= allocatedSize)
            return;

        char* newStrBuffer = new char[newSize];
        memcpy(newStrBuffer, strBuffer, allocatedSize);

        delete[] strBuffer;
        strBuffer = newStrBuffer;
        allocatedSize = newSize;
    }

public:
    // Empty string
    PPString() :
        strBuffer(new char[8]),
        allocatedSize(8)
    {
        *strBuffer = 0;        
    }

    // String from single character
    PPString(char c) :
        strBuffer(new char[8]),
        allocatedSize(8)
    {
        *strBuffer = c;
        *(strBuffer+1) = 0;
    }

    PPString(const char* str) :
        strBuffer(new char[strlen(str) + 1]),
        allocatedSize((pp_uint32)strlen(str) + 1)        
    {
        strcpy(strBuffer, str);        
    }

    PPString(const char* str, pp_uint32 length) :
        strBuffer(new char[length + 1]),
        allocatedSize(length + 1)
    {
        memcpy(strBuffer, str, length);
        strBuffer[length] = 0;
    }

    // copy c'tor
    PPString(const PPString& str) :
        strBuffer(new char[str.allocatedSize]),
        allocatedSize(str.allocatedSize)
    {
        memcpy(strBuffer, str.strBuffer, str.allocatedSize);
    }

    operator const char*() const
    {
        return strBuffer;
    }

    const char* getStrBuffer() const
    {
        return strBuffer;
    }

    // assignment operator
    PPString& operator=(const PPString& str)
    {
        if (this != &str)
        {
            if (str.allocatedSize <= allocatedSize)
            {
                memcpy(strBuffer, str.strBuffer, str.allocatedSize);
            }
            else
            {
                delete[] strBuffer;            
                strBuffer = new char[str.allocatedSize];
                memcpy(strBuffer, str.strBuffer, str.allocatedSize);
                allocatedSize = str.allocatedSize;
            }
        }
    
        return *this;
    }

    PPString& operator=(const char* str)
    {
        pp_uint32 len = (unsigned)strlen(str)+1;

        if (len <= allocatedSize)
        {
            strcpy(strBuffer, str);
        }
        else
        {
            delete[] strBuffer;
            strBuffer = new char[len];
            strcpy(strBuffer, str);
            allocatedSize = len;
        }
        
        return *this;
    }

    // comparison is necessary too
    bool operator==(const PPString& str) const
    {
        return strcmp(strBuffer, str.strBuffer) == 0;
    }

    bool operator!=(const PPString& str) const
    {
        return strcmp(strBuffer, str.strBuffer) != 0;
    }

    pp_int32 compareTo(const PPString& str) const
    {
        return strcmp(strBuffer, str.strBuffer);
    }

    pp_int32 compareToNoCase(const PPString& str) const
    {
        return STRINGCOMPARE_NOCASE(strBuffer, str.strBuffer);
    }

    bool startsWith(const PPString& str) const
    {
        if (length() < str.length())
            return false;
            
        for (pp_uint32 i = 0; i < str.length(); i++)
            if (strBuffer[i] != str.strBuffer[i])
                return false;
                
        return true;
    }
    
    ~PPString()
    {
        delete[] strBuffer;
    }

    pp_uint32 length() const
    {
        return (pp_uint32)strlen(strBuffer);
    }

    char charAt(pp_uint32 index) const
    {
        if (index < length())
            return strBuffer[index];
            
        return 0;
    }

    void insertAt(pp_uint32 i, const PPString& s)
    {
        // doesn't work
        if (i > length())
            return;

        allocatedSize = length() + s.length() + 1;

        char* newStr = new char[allocatedSize];
        
        memcpy(newStr, strBuffer, i);
        memcpy(newStr + i, s.strBuffer, s.length());
        memcpy(newStr + i + s.length(), strBuffer + i, length() - i);
        newStr[length() + s.length()] = 0;

        delete[] strBuffer;

        strBuffer = newStr;
    }

    void append(const PPString& s)
    {
        insertAt(length(), s);
    }

    void append(char c)
    {
        PPString s(c);
        append(s);
    }

    void deleteAt(pp_uint32 i, pp_uint32 numChars)
    {
        // not possible
        if (i > length())
            return;

        // nothing to delete
        if ((signed)length() - (signed)numChars < 0)
            return;

        // nothing to delete
        if (strBuffer[i] == 0)
            return;

        allocatedSize = length() - numChars + 1;

        char* newStr = new char[allocatedSize];
        
        memcpy(newStr, strBuffer, i);
        memcpy(newStr + i, strBuffer + i + numChars, length() - i - numChars);
        newStr[length() - numChars] = 0;

        delete[] strBuffer;

        strBuffer = newStr;
    }

    PPString subString(pp_uint32 leftIndex, pp_uint32 rightIndex) const
    {
        PPString newString;
        for (pp_uint32 i = leftIndex; i < rightIndex && i < length(); i++)
            newString.append(charAt(i));
        
        return newString;
    }

    void replace(const PPString& str)
    {
        delete[] strBuffer;
        strBuffer = new char[str.allocatedSize];
        memcpy(strBuffer, str.strBuffer, str.allocatedSize);
        allocatedSize = str.allocatedSize;
    }

    pp_int32 getIntValue() const
    {
        pp_uint32 v; 
        sscanf(strBuffer, "%d", &v);
        return v;
    }
    
    pp_int32 countLines()
    {
        pp_int32 numLines = 1;
        pp_int32 len = this->length();
        for (pp_int32 i = 0; i < len; i++)
        {
            if (strBuffer[i] == '\n' && i != len-1)
                numLines++;
        }
        
        return numLines;
    }

    void toUpper()
    {
        for (pp_uint32 i = 0; i < length(); i++)
            if (strBuffer[i] >= 'a' && 
                strBuffer[i] <= 'z')
                strBuffer[i] -= 'a'-'A';
    }

    void toLower()
    {
        for (pp_uint32 i = 0; i < length(); i++)
            if (strBuffer[i] >= 'A' && 
                strBuffer[i] <= 'Z')
                strBuffer[i] += 'a'-'A';
    }

    PPString stripPath() const
    {
        char* ptr = strBuffer+strlen(strBuffer);
        
        while (ptr > strBuffer && *ptr != '/' && *ptr != '\\')
            ptr--;
            
        if (ptr != strBuffer)
            ptr++;
            
        PPString str = ptr;
        return str;
    }

    PPString stripExtension() const
    {
        char* ptr = strBuffer+strlen(strBuffer);
        
        while (ptr > strBuffer && *ptr != '.' && *ptr != '/' && *ptr != '\\')
            ptr--;
        
        if (*ptr == '/' || *ptr == '\\')
            return strBuffer;
            
        if (ptr != strBuffer)
        {    
            PPString str;
        
            delete[] str.strBuffer;
            str.allocatedSize = (pp_uint32)((ptr-strBuffer)+1);
            str.strBuffer = new char[str.allocatedSize];
            memcpy(str.strBuffer, strBuffer, (ptr-strBuffer));
            str.strBuffer[(ptr-strBuffer)] = '\0';
        
            return str;
        }
        else
        {
            return ptr;
        }
    }

    PPString getExtension() const
    {
        char* ptr = strBuffer+strlen(strBuffer);
        
        while (ptr > strBuffer && *ptr != '.' && *ptr != '/' && *ptr != '\\')
            ptr--;
        
        if (*ptr != '.')
            return "";
            
        return ptr;
    }

    pp_int32 compareExtensions(const PPString& str) const    
    {
        char* ptrSrc = strBuffer+strlen(strBuffer);
        
        while (ptrSrc > strBuffer && *ptrSrc != '.' && *ptrSrc != '/')
            ptrSrc--;
        
        bool noExt1 = false;
        
        if (*ptrSrc != '.')
            noExt1 = true;

        ptrSrc++;
        if (*ptrSrc == '\0')
            noExt1 = true;

        char* ptrDst = str.strBuffer+strlen(str.strBuffer);
        
        while (ptrDst > str.strBuffer && *ptrDst != '.' && *ptrDst != '/')
            ptrDst--;
        
        if (*ptrDst != '.')
            return noExt1 ? 0 : 1;

        ptrDst++;
        if (*ptrDst == '\0')
            return noExt1 ? 0 : 1;

        return STRINGCOMPARE_NOCASE(ptrSrc, ptrDst);
    }

    bool compareToExtension(const PPString& extension) const    
    {
        char* ptrSrc = strBuffer+strlen(strBuffer);
        
        while (ptrSrc > strBuffer && *ptrSrc != '.' && *ptrSrc != '/')
            ptrSrc--;
        
        if (*ptrSrc != '.')
            return false;

        ptrSrc++;
        if (*ptrSrc == '\0')
            return false;

        return STRINGCOMPARE_NOCASE(ptrSrc, extension.strBuffer) == 0;
    }

    void ensureTrailingCharacter(char chr)
    {
        pp_uint32 len = length();
        if (len)
        {
            char* ptr = strBuffer+(len-1);
            if (*ptr != chr)
                append(chr);
        }
    }
    
    // Delete this pointer after usage
    char* toASCIIZ() const
    {
        char* newStr = new char[length() + 1];
        strcpy(newStr, strBuffer);
        return newStr;
    }
};

#endif 