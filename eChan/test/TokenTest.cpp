#include <iostream>
#include <string>

#include "MsgTokenizer.h"

using std::string;
using std::cout;
using std::endl;
using eNetworks::MsgTokenizer;

int main()
{

   MsgTokenizer eToken("#evilnet 1067533780 +tncC ABACk,ABACi,ABACh,ABACf,AZAAE:o,ABABu,AUAAC,AUAAE,AUAAF,A0AAA,ABAAL,ABAAn :%*!*@202.69.51.204 blablabla lb sdf sdf   ");


   // MsgTokenizer eToken("AIAAB,AIAAA:v,AZAAA:o", ',');

   for (int i = 0; i < eToken.size(); i++)
    cout <<  "eToken[" << i << "]: " << eToken[i] << endl;

return 0;
}
