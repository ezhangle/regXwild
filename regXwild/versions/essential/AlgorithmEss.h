/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef WILDCARDS_VERSIONS_ESSENTIAL_ALGORITHM_ESS__H
#define WILDCARDS_VERSIONS_ESSENTIAL_ALGORITHM_ESS__H

#include "../../common/typedefs.h"

namespace net { namespace r_eg { namespace regXwild {

    class AlgorithmEss
    {
    public:

        enum MetaOperation
        {
            NONE    = 0x000,
            BOL     = 0x001,
            ANY     = 0x002,
            SPLIT   = 0x004,
            ONE     = 0x008,
            BEGIN   = 0x010,
            END     = 0x020,
            MORE    = 0x040,
            SINGLE  = 0x080,
            ANYSP   = 0x100,
            EOL     = 0x200,
        };

        enum MetaSymbols
        {
            MS_ANY      = _T('*'), // {0, ~}
            MS_SPLIT    = _T('|'), // str1 or str2 or ...
            MS_ONE      = _T('?'), // {0, 1}, ??? - {0, 3}, ...
            MS_BEGIN    = _T('^'), // [str... or [str1... |[str2...
            MS_END      = _T('$'), // ...str] or ...str1]| ...str2]
            MS_MORE     = _T('+'), // {1, ~}
            MS_SINGLE   = _T('#'), // {1}
            MS_ANYSP    = _T('>'), // as [^/]*  //TODO: >\>/ i.e. '>' + {symbol}
        };

        /**
         * default symbol for special case
         * regexp equivalent search is a [^/]* (EXT version: [^/\\]+)
         */
        const static TCHAR ANYSP_CMP_DEFAULT = _T('/');

        /** entry for match cases */
        bool search(const tstring& text, const tstring& filter, bool ignoreCase = true);

    protected:

        struct Mask
        {
            MetaOperation curr;
            MetaOperation prev;
            Mask(): curr(BOL), prev(BOL){};
        };

        /**
         * to wildcards
         */
        struct Item
        {
            tstring curr;
            size_t pos;
            size_t left;
            size_t delta;
            Mask mask;
            unsigned short int overlay;

            /** enough of this.. */
            tstring prev;

            void reset()
            {
                pos = left = delta = overlay = 0;
                mask.curr = mask.prev = BOL;
                curr.clear();
                prev.clear();
            };
            Item(): pos(0), left(0), delta(0), overlay(0){};
        } item;

        /**
         * to words
         */
        struct Words
        {
            size_t found;
            size_t left;

            void reset()
            {
                found   = tstring::npos;
                left    = 0;
            };
            Words(): left(0){};
        } words;

        /**
         * Working with an interval:
         *      _______
         * {word} ... {word}
         */
        size_t interval();

        /** rewind to next SPLIT-block */
        bool rewindToNextBlock(tstring::const_iterator& it, bool delta = true);

    private:

        /** work with the target sequence (subject) */
        tstring _text;

        /** work with the pattern */
        tstring _filter;

        inline tstring _lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towlower);
            return str;
        };
    };

    class AlgorithmEssTestCase
    {
    public:

        /** verify MetaOperation::ANY */
        void assertsAny();
        /** verify MetaOperation::SPLIT */
        void assertsSplit();
        /** verify MetaOperation::ONE */
        void assertsOne();
        /** verify MetaOperation::ANYSP */
        void assertsAnySP();
        /** verify MetaOperation::BEGIN */
        void assertsBegin();
        /** verify MetaOperation::END */
        void assertsEnd();
        /** verify MetaOperation::MORE */
        void assertsMore();
        /** verify MetaOperation::SINGLE */
        void assertsSingle();
        /** wrapper */
        void asserts();

    protected:
        AlgorithmEss alg;

    private:
        /** Stub with a MS combination for current version - END */
        void _stubENDCombination();
        /** Stub with a MS combination for current version - SINGLE */
        void _stubSINGLECombination();
    };

}}}

#endif // WILDCARDS_VERSIONS_ESSENTIAL_ALGORITHM_ESS__H