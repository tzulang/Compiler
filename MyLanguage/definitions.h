#pragma once

#ifdef PARSE_WSTRING

    #define WIDEN(x) L ## x
    #define S(x) WIDEN(x)

    namespace compiler {
        using strType= std::wstring;
    }

#elif defined(PARSE_U8)

    #define WIDEN(x) u ## x
    #define S(x) WIDEN(x)

    namespace compiler {
        using strType= std::u8string;
    }

#elif defined(PARSE_U16)

    #define WIDEN(x) u ## x
    #define S(x) WIDEN(x)

    namespace compiler {
        using strType= std::u16string;
    }


#elif defined(PARSE_U32)

    #define WIDEN(x) U ## x
    #define S(x) WIDEN(x)

    namespace compiler {
        using strType= std::u32string ;
    }

#else

    #define S(x) x

    namespace compiler {
        using strType= std::string;
    }
#endif
