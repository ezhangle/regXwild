/*
* The MIT License (MIT)
*
* Copyright (c) 2013, 2014, 2016  Denis Kuzmin <entry.reg@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild {

void AlgorithmExtTestCase::assertsAny()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    /* should be found: */
    assert(alg.main(data, _T("protection of various")) == true);      // __ __ __
    assert(alg.main(data, _T("pro*system")) == true);                 // __ * __
    assert(alg.main(data, _T("*pro*system*")) == true);               // * __ * __ *
    assert(alg.main(data, _T("project**various")) == true);           // __ ** __
    assert(alg.main(data, _T("new*7*systems")) == true);              // __ * __ * __
    assert(alg.main(data, _T("")) == true);                           // empty

    /* should not be found: */
    assert(alg.main(data, _T("project 12 and")) == false);            // __ _x_ __
    assert(alg.main(data, _T("new*express")) == false);               // __ * _x_
    assert(alg.main(data, _T("tes*ting*project")) == false);          // __ * _x_ * __
    assert(alg.main(data, _T("testing*project*and")) == false);       // _x_ * __ * __
    assert(alg.main(data, _T("now*is*completely")) == false);         // _x_ * _x_ * _x_
    assert(alg.main(data, _T("protection*project*new")) == false);    // backwards __ * __ * __
    assert(alg.main(data, _T("**open**close")) == false);             // ** _x_ ** _x_
}

void AlgorithmExtTestCase::assertsSplit()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    /* should be found: */
    assert(alg.main(data, _T("protection of|new tes")) == true);       // __ __ | __ __
    assert(alg.main(data, _T("some project|of various")) == true);     // _x_ __ | __ __
    assert(alg.main(data, _T("various systems|new 237")) == true);     // __ __ | __ _x_
    assert(alg.main(data, _T("pro*12|new*system")) == true);           // __ * __ | __ *__
    assert(alg.main(data, _T("ject*new|pro*tems")) == true);           // __ * _x_ | __ * __
    assert(alg.main(data, _T("pro*tems|seems*and")) == true);          // __ * __ | _x_ * __
    assert(alg.main(data, _T("project*|new")) == true);                // __ *| __
    assert(alg.main(data, _T("various*|zeep")) == true);               // __ * | _x_
    assert(alg.main(data, _T("goo*|systems")) == true);                // _x_ * | __
    assert(alg.main(data, _T("project||protect")) == true);            // __ || __
    assert(alg.main(data, _T("|new||and|")) == true);                  // | __ || __ |
    assert(alg.main(data, _T("|fail|system")) == true);                // | _x_ | __
    assert(alg.main(data, _T("|12||true||")) == true);                 // | __ || _x_ ||
    assert(alg.main(data, _T("above|new|with")) == true);              // _x_ | __ | _x_
    assert(alg.main(data, _T("project**|new")) == true);               // __ **| __
    assert(alg.main(data, _T("zoom|*pro")) == true);                   // _x_ | * __
    assert(alg.main(data, _T("zoom|*pro**")) == true);                 // _x_ | *__ **
    assert(alg.main(data, _T("||")) == true);                          //empty
    assert(alg.main(data, _T("")) == true);                            //empty
    assert(alg.main(data, _T("||zoom||out||")) == true);               // ||_x_ || _x_ ||
    assert(alg.main(data, _T("|*|")) == true);                         // |*|
    assert(alg.main(data, _T("|long-term")) == true);                  // | _x_
    assert(alg.main(data, _T("long-term|")) == true);                  // _x_ |
    assert(alg.main(data, _T("*|*")) == true);                         // *|*
    assert(alg.main(data, _T("*|")) == true);                          // *|
    assert(alg.main(data, _T("|*")) == true);                          // |*
    assert(alg.main(data, _T("seems|open*and*star|*system")) == true); // _x_ | _x_ * __ * _x_ | * __

    /* should not be found: */
    assert(alg.main(data, _T("above|fails|with")) == false);           // _x_ | _x_ | _x_
    assert(alg.main(data, _T("let*proj|project*deep")) == false);      // _x_ * __ | __ * _x_
    assert(alg.main(data, _T("operator*|*zeep")) == false);            // _x_ *|* _x_
    assert(alg.main(data, _T("some project|let*various")) == false);   // _x_ __ | _x_* __
    assert(alg.main(data, _T("some project|various*zoom")) == false);  // _x_ __ | __ * _x_
    assert(alg.main(data, _T("be|pen*and*star|*my*system")) == false); // _x_ | _x_ * __ * _x_ | * _x_ * __
}

void AlgorithmExtTestCase::assertsOne()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    /* should be found: */
    assert(alg.main(data, _T("new*pro?ection")) == true);              // __ * [pro]ject ... [pro]t[ection]
    assert(alg.main(data, _T("????")) == true);
    assert(alg.main(data, _T("project?12")) == true);
    assert(alg.main(_T("system-17 fee also offers protection"), _T("system?17")) == true);

    /* should not be found: */
    assert(alg.main(data, _T("?pro?12?|seems?7")) == false);
    assert(alg.main(_T("system, installments range from 2 to 17"), _T("system?17")) == false);
    assert(alg.main(_T("system17 fee also"), _T("system?17")) == false);
    assert(alg.main(_T("my system17 fee also"), _T("system?17")) == false);
    assert(alg.main(_T("system_-17 fee also"), _T("system?17")) == false);
}

void AlgorithmExtTestCase::assertsAnySP()
{
    /* should be found: */
    assert(alg.main(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")) == true);   // __...___
    assert(alg.main(_T("/new/user_myhid_test.bzip2"), _T("myhid>")) == true);       // __...EOL
    assert(alg.main(_T("/new/user_myhid"), _T("myhid>")) == true);                  // __EOL
        
    /* with other metasymbols: */
    {
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>*")) == true);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>***")) == true);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>?")) == true);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>?*")) == true);
    }

    /* should not be found: */
    assert(alg.main(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")) == false);     // __.../...__
    assert(alg.main(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")) == false);     // __/...__
    assert(alg.main(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")) == false);     // __.../__
    assert(alg.main(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")) == false);         // __.../...EOL
    assert(alg.main(_T("/new/user_myhid_te/"), _T("myhid>")) == false);                 // __.../EOL
    assert(alg.main(_T("/new/user_myhid_t\\est.bzip2"), _T("myhid>bzip")) == false);    //  "\" & "//"
        
    /* with other metasymbols: */
    {
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")) == false);
        //-
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")) == false);
        assert(alg.main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")) == false);
        //-
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>*txt")) == false);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>***txt")) == false);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>?txt")) == false);
        assert(alg.main(_T("/new/user_myhid"), _T("myhid>?*??txt")) == false);
    }
}

void AlgorithmExtTestCase::asserts()
{
    assertsAny();
    assertsSplit();
    assertsOne();
    assertsAnySP();
}

}}}
