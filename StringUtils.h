#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace oir {

/** 切分字符串（多个切分字符）
 *
 * 如果只需要一个切分字符，请使用速度更快的：
 * @code
 * void split(char delimiter, const std::string &source,
 *     std::vector<std::string> &result);
 * @endcode
 *
 * @param  delimiters 切分字符列表，匹配任意一个。
 * @param  source     源字符串。
 * @param  result     输出切分结果。
 */
void split(const std::string &delimiters, const std::string &source,
        std::vector<std::string> &result);

/** 切分字符串（单个切分字符）
 *
 * 最佳使用方式是：
 * @code
 * vector<string> fields;
 * for (int i = 0; i < 1000; i ++)
 *   split(' ', source, fields);
 * @endcode
 *
 * @param  delimiter 切分字符。
 * @param  source    源字符串。
 * @param  result    输出切分结果。
 */
void split(char delimiter, const std::string &source,
        std::vector<std::string> &result, int32_t reqSize = 0);

/** 切分字符串（单个切分字符）
 *
 * 最佳使用方式是：
 * @code
 * for (int i = 0; i < 1000; i ++)
 *   vector<string> fields = split(' ', source);
 * @endcode
 *
 * @param  delimiter 切分字符。
 * @param  source    源字符串。
 * @return           返回切分结果。
 */
const std::vector<std::string> split(char delimiter, const std::string &source);

/** 去除字符串头尾的空白字符（空格、制表符、换行）
 *
 * @param  source 源字符串。
 * @return        返回结果。
 */
const std::string strip(std::string &source);

template<typename T>
const std::string castToS(const T &a)
{
    std::stringstream s;
    s << a;
    return s.str();
}

template<typename T>
const T castFromS(const std::string &a)
{
    T ret;
    std::stringstream s;
    s << a;
    s >> ret;
    return ret;
}

} // namespace goldfinger

#endif /* __STRING_UTILS_H__ */
