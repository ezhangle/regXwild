#include "stdafx.h"
#include "regXwild.h"
#include "regXwildAPI.h"
#include "core\ESS\AlgorithmEss.h"
#include "core\EXT\AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild 
{

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase)
    {
        core::ESS::AlgorithmEss alg;

        return alg.search(data, filter, ignoreCase);
    }
    
    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchExt(const tstring& data, const tstring& filter, bool ignoreCase)
    {
        core::EXT::AlgorithmExt alg;

        return alg.main(data, filter, ignoreCase);
    }

    /**
    * To get current version of regXwild library as a string.
    * @return Returns version as Major.Minor [.Revision] etc.
    */
    REGXWILD_API const TCHAR* versionString()
    {
        // Please use '.version' file. It will be automatically updated by vssbe script.
        return /*vsSBE*/_T("0.0.1"); //TODO: additional structure etc. of version data.
    }

}}}