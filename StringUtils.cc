#include "StringUtils.h"

using namespace std;
using namespace oir;

void oir::split(const string &delimiters, const string &source,
        vector<string> &result)
{
    size_t prev_pos = 0, pos = 0;
    result.resize(0);
    pos = source.find_first_of(delimiters, pos);
    while (pos != string::npos)
    {
        result.push_back(source.substr(prev_pos, pos - prev_pos));
        prev_pos = ++ pos;
        pos = source.find_first_of(delimiters, pos);
    }
    result.push_back(source.substr(prev_pos));
}

void oir::split(char delimiter, const string &source,
        vector<string> &result, int32_t reqSize)
{
    size_t prev_pos = 0, pos = 0;

    result.resize(0);
    pos = source.find(delimiter, pos);
    int32_t index  = 0;
    while (pos != string::npos)
    {
        result.push_back(source.substr(prev_pos, pos - prev_pos));
        if( reqSize != 0 && ++index >= reqSize ) {
            return;
        }
        prev_pos = ++ pos;
        pos = source.find(delimiter, pos);
    }
    result.push_back(source.substr(prev_pos));
}

const vector<string> oir::split(char delimiter, const string &source)
{
    size_t prev_pos = 0, pos = 0;

    vector<string> result;
    result.reserve(count(source.begin(), source.end(), delimiter) + 1);
    pos = source.find(delimiter, pos);
    while (pos != string::npos) {
        result.push_back(source.substr(prev_pos, pos - prev_pos));
        prev_pos = ++ pos;
        pos = source.find(delimiter, pos);
    }
    result.push_back(source.substr(prev_pos));

    return result;
}

const string oir::strip(string &source)
{
    static const string trims = " \t\r\n";
    string::size_type pos1, pos2;

    pos1 = source.find_first_not_of(trims);
    pos2 = source.find_last_not_of(trims);

    if (pos1 != string::npos)
        return source.substr(pos1, pos2 - pos1 + 1);
    return "";
}
