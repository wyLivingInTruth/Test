#ifndef TALK_UTILS_URL_H_
#define TALK_UTILS_URL_H_
#include <string>

namespace mtalk{
namespace utils{

    typedef unsigned char BYTE;
 
    inline BYTE toHex(const BYTE &x)
    {
        return x > 9 ? x -10 + 'A': x + '0';
    }

    inline BYTE fromHex(const BYTE &x)
    {
        return isdigit(x) ? x-'0' : x-'A'+10;
    }
 
    inline std::string urlEncode(const std::string &sIn)
    {
        std::string sOut;
        for( size_t ix = 0; ix < sIn.size(); ix++ )
        {      
            BYTE buf[4];
            memset( buf, 0, 4 );
            if( isalnum( (BYTE)sIn[ix] ) )
            {      
                buf[0] = sIn[ix];
            }
            //else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
            //{
            //    buf[0] = '+';
            //}
            else
            {
                buf[0] = '%';
                buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
                buf[2] = toHex( (BYTE)sIn[ix] % 16);
            }
            sOut += (char *)buf;
        }
        return sOut;
    };

    inline std::string urlDecode(const std::string &sIn)
    {
        std::string sOut;
        for( size_t ix = 0; ix < sIn.size(); ix++ )
        {
            BYTE ch = 0;
            if(sIn[ix]=='%')
            {
                ch = (fromHex(sIn[ix+1])<<4);
                ch |= fromHex(sIn[ix+2]);
                ix += 2;
            }
            else if(sIn[ix] == '+')
            {
                ch = ' ';
            }
            else
            {
                ch = sIn[ix];
            }
            sOut += (char)ch;
        }
        return sOut;
    }
};
};
#endif //TALK_UTILS_URL_H_