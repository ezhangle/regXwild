
**[regXwild](https://github.com/3F/regXwild)** - Fast and powerful wildcards ! `*,|,?,^,$,+,#,>` in addition to slow regex engine and more...

Unique algorithms that implemented in native C++ & optional .NET support (via [Conari engine](https://github.com/3F/Conari)).

[![Build status](https://ci.appveyor.com/api/projects/status/92y03ofto5fbb60a/branch/master?svg=true)](https://ci.appveyor.com/project/3Fs/regxwild/branch/master)
[![release-src](https://img.shields.io/github/release/3F/regXwild.svg)](https://github.com/3F/regXwild/releases/latest)
[![License](https://img.shields.io/badge/License-MIT-74A5C2.svg)](https://github.com/3F/regXwild/blob/master/LICENSE)
[![NuGet package](https://img.shields.io/nuget/v/regXwild.svg)](https://www.nuget.org/packages/regXwild/) 

## Native C/C++ API

The regXwild library exports the following functions (C-linkage):

```cpp
    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchEssC(const TCHAR* data, const TCHAR* filter, bool ignoreCase);
    
    REGXWILD_API bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase);

    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchExtC(const TCHAR* data, const TCHAR* filter, bool ignoreCase);
    
    REGXWILD_API bool searchExt(const tstring& data, const tstring& filter, bool ignoreCase);
```

Calling Convention: **__cdecl**


## .NET Platform & C# ##

The regXwild library was written on **native C++**, but you can also use it flexibly in .NET world via [Conari](https://github.com/3F/Conari) engine !

For .NET users, use [this](https://github.com/3F/Conari) for work as you like:

```csharp
using(var l = new ConariL("regXwild.dll")) {
...
    if(l.DLR.searchEssC<bool>((WCharPtr)data, (WCharPtr)filter, false)) {
        // ...
    }
}
```

## Easy to start even for C++

v1.1+ also distributed via NuGet package (*How to Get* - below).

For this method you can add this library **for both type** of your projects (Native projects ~ C/C++ and for .NET projects like C# etc.) in one click.

```cpp
#include "regXwildAPI.h"

using namespace net::r_eg::regXwild;

...
if(searchEssC(_T("regXwild"), _T("reg?wild"), true)) {
    // ...
}
```

## Meta symbols

ESS version (improvement of EXT version):

```cpp
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
```


EXT version (initial, more simplified):

```cpp
enum MetaSymbols {
    MS_ANY      = _T('*'),
    MS_ANYSP    = _T('>'), //as [^/\\]+
    MS_SPLIT    = _T('|'),
    MS_ONE      = _T('?'),
};
```

## Features & Unit-Tests

All features of regXwild you can see with Unit-Tests - regXwildTest subproject.

```cpp
searchEss(data, _T("^main*is ok$"));
searchEss(data, _T("^new*pro?ection"));
searchEss(data, _T("pro*system"));
searchEss(data, _T("sys###s"));
searchEss(data, _T("new+7+system"));
searchEss(data, _T("some project|open*and*star|system"));
...
```

## License

The [MIT License (MIT)](https://github.com/3F/regXwild/blob/master/LICENSE)

```
Copyright (c) 2013, 2014, 2016, 2017  Denis Kuzmin <entry.reg@gmail.com>
```

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=entry%2ereg%40gmail%2ecom&lc=US&item_name=3F%2dOpenSource%20%5b%20github%2ecom%2f3F&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted)

##

### How to Get

Available variants:

* NuGet PM: `Install-Package regXwild`
* [GetNuTool](https://github.com/3F/GetNuTool): `msbuild gnt.core /p:ngpackages="regXwild"` or [gnt](https://github.com/3F/GetNuTool/releases/download/v1.6/gnt.bat) /p:ngpackages="regXwild"
* NuGet Commandline: `nuget install regXwild`
* [/releases](https://github.com/3F/regXwild/releases) ( [latest](https://github.com/3F/regXwild/releases/latest) )
* [Nightly builds](https://ci.appveyor.com/project/3Fs/regxwild/history) (`/artifacts` page). But remember: It can be unstable or not work at all. Use this for tests of latest changes.


## Speed comparison

**Please note:** 

* **+icase** means that a search engine should ignore case sensitivity when matching the filter(pattern) within the searched string, i.e. `ignoreCase = true`. Without this, all below would be much more faster, and final algorithms EXT & ESS should be **< 1ms** (see table below)
* All results below can be different for other machines and you should look only difference (in milliseconds) between algorithms for specific target.
    * To calculate data as in table below you should run - `algo.exe`
    
### Procedure of testing

* Used the `algo` subproject as tester of main algorithms (*Release cfg - x32 & x64*)
* Mainly, calculation is simple and also uses average as `i = (t2 - t1); (sum(i) / n)` where:
    * **i** - one iteration for searching by filter. Represents a delta of time `t2 - t1`
    * **n** - the number of repeats of searching to get average.

e.g.:

```cpp
{
    Meter meter;
    int results = 0;

    for(int total = 0; total < average; ++total)
    {
        meter.start();
        for(int i = 0; i < iterations; ++i)
        {
            if((alg.*method)(data, filter)) {
                //...
            }
        }
        results += meter.delta();
    }

    TRACE((results / average) << "ms");
}
```

for regex it also prepares additional `basic_regex` from filter - one for all iterations:

```cpp
meter.start();

auto rfilter = tregex(
    filter,
    regex_constants::icase | regex_constants::optimize
);

results += meter.delta();
...
```

### Sample of speed

Test Data:

* 340 Symbols of Unicode, 10000 iterations, Filter: `L"nime**haru*02*Magica"`


 algorithms (see impl. from `algo`)       | +icase [x32]| +icase [x64]
------------------------------------------|-------------|-------------
Find + Find                               | ~58ms       | ~44ms       
Iterator + Find                           | ~57ms       | ~46ms       
Getline + Find                            | ~59ms       | ~54ms       
Iterator + Substr                         | ~165ms      | ~132ms      
Iterator + Iterator                       | ~136ms      | ~118ms      
main :: based on Iterator + Find          | ~53ms       | ~45ms       
                                          |             |             
**Final algorithm - EXT version:**        | **~50ms**   | **~26ms**   
**Final algorithm - ESS version:**        | **~50ms**   | **~27ms**   
                                          |             |             
regexp-c++11(regex_search)                | ~59309ms    | ~53334ms    
regexp-c++11(only as ^match$ like a '==') | ~12ms       | ~5ms        
regexp-c++11(regex_match with endings .*) | ~59503ms    | ~53817ms    


**ESS vs EXT**

* 350 Symbols of Unicode, 10000 iterations

Operation (+icase)    | EXT  [x32] | ESS  [x32] | EXT  [x64] | ESS  [x64] 
----------------------|------------|------------|------------|------------
ANY                   | ~54ms      | ~55ms      | ~32ms      | ~34ms
ANYSP                 | ~60ms      | ~59ms      | ~37ms      | ~38ms
ONE                   | ~56ms      | ~56ms      | ~33ms      | ~35ms
SPLIT                 | ~92ms      | ~94ms      | ~58ms      | ~63ms
BEGIN                 | ---        | ~38ms      | ---        | ~19ms
END                   | ---        | ~39ms      | ---        | ~21ms
MORE                  | ---        | ~44ms      | ---        | ~23ms
SINGLE                | ---        | ~43ms      | ---        | ~22ms


**For .NET users via [Conari](https://github.com/3F/Conari) engine:** 

*Same test Data & Filter: 10000 iterations* 

*x32 or x64 regXwild (Unicode)*

* Updated with new improved speed via [Conari engine - v1.3](https://github.com/3F/Conari/commit/4f14cecbcea75895a510954c2cd402ee0e9e3521)

 algorithms  (see impl. from `snet`)        | +icase [x32]*| +icase [x64]*| .
--------------------------------------------|--------------|--------------|---
regXwild via Conari v1.2 (Lambda) - ESS     | **~1032ms**  | **~1418ms**  |
regXwild via Conari v1.2 (DLR) - ESS        | ~1238ms      | ~1609ms      |
regXwild via Conari v1.2 (Lambda) - EXT     | **~1117ms**  | **~1457ms**  |
regXwild via Conari v1.2 (DLR) - EXT        | ~1246ms      | ~1601ms      |
                                            |              |              |
regXwild via Conari **v1.3** (Lambda) - ESS | **~58ms**    | **~42ms**    | `<<`
regXwild via Conari **v1.3** (DLR) - ESS    | ~218ms       | ~234ms       |
regXwild via Conari **v1.3** (Lambda) - EXT | **~54ms**    | **~35ms**    | `<<`
regXwild via Conari **v1.3** (DLR) - EXT    | ~214ms       | ~226ms       |
                                            |              |              |
.NET Regex engine [Compiled]                | ~38310ms     | ~37242ms     |
.NET Regex engine [Compiled]{only ^match$}  | < 1ms        | ~3ms         |
.NET Regex engine                           | ~31565ms     | ~30975ms     |
.NET Regex engine {only ^match$}            | < 1ms        | ~1ms         |
