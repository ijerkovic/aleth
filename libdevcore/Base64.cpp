/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
	  claim that you wrote the original source code. If you use this source code
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/
/// Adapted from code found on http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
/// Originally by René Nyffenegger, modified by some other guy and then devified by Gav Wood.

#include "Base64.h"

#include <algorithm>
#include <cryptopp/base64.h>

using namespace std;
using namespace dev;

//static inline bool is_base64(byte cs)
//{
//	char c = std::to_integer(cs);
//	return (isalnum(c) || (c == '+') || (c == '/'));
//}

string dev::toBase64(bytesConstRef _in)
{
	string encoded;

	CryptoPP::ArraySource ss(&_in[0], sizeof(_in), true,
			    new CryptoPP::Base64Encoder(
				            new CryptoPP::StringSink(encoded)
					        ) // Base64Encoder
	); // StringSource
	return encoded;
}

bytes dev::fromBase64(string const& encoded_string)
{
	bytes values(encoded_string.size() + 1);
	//TODO(mhala) put bytes sink intead ArraySink
	CryptoPP::StringSource ss(encoded_string, true,
			    new CryptoPP::Base64Decoder(
				            new CryptoPP::ArraySink(&values[0], sizeof(values))
					        ) // Base64Decoder
		       ); // StringSource

        //std::transform(decoded.begin(), decoded.end(), values.begin(),
	//		                       [] (char c) { return c; });

	return values; 

}
