#include "StringUtil.h"
#include <sstream>

using namespace std;

string StringUtil::intToString(int value){

	ostringstream valueString;

	valueString << value;

	return valueString.str();
}
