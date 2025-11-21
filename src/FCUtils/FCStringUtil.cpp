/******************************************************************************
 * File     : FCStringUtil.h
 * Brief    : 字符串相关的工具方法
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-20
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCStringUtil.h"
#include <stdexcept>
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <QTextCodec>
#include <QByteArray>

#pragma warning(disable : 4819)

#ifndef FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP
#define FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(type, qstringCastFun)                                                 \
type fromQString(const QString& str, type defaultValue)                                                            \
{                                                                                                                  \
        bool ok(false);                                                                                                \
        auto v = str.qstringCastFun(&ok);                                                                              \
        return (ok ? v : defaultValue);                                                                                \
}
#endif
#ifndef FC_STRING_CAST_QSTRINGINNER_CPP
#define FC_STRING_CAST_QSTRINGINNER_CPP(type, qstringCastFun)                                                          \
type fromQString(const QString& str, const type& defaultValue)                                                     \
{                                                                                                                  \
        Q_UNUSED(defaultValue);                                                                                        \
        return str.qstringCastFun();                                                                                   \
}
#endif

namespace FC 
{
/**
 * @brief 生成一个唯一的字符串
 *
 * 如果str在stringSet出现过，将会在这个字符串后面加上_1，并继续判断是否在stringSet出现过出现过，直到没有为止
 *
 * 这个函数常用于生成一个唯一的名字
 * @param stringSet 字符串数组
 * @param str 待检测的字符串
 * @param split 分隔符，分隔符后面将加入数字
 * @return 返回一个不会出现在stringSet的字符串
 */
QString makeUniqueString(const QSet< QString >& stringSet, const QString& str, const QString& split)
{
    if (!stringSet.contains(str)) {
        return str;
    }
    QString n = str;
    int index = -1;
    do {
        index = n.lastIndexOf(split);
        if (index <= 0) {  // 等于0也要包含
            n = (n + split + "1");
        } else if (index != 0) {
            if (index == n.size() - 1) {
                // 以split结尾
                n = n + "1";
            } else {
                // 说明有{split}xx,但要确认这个xx是数字
                QString suf = n.mid(index + 1);
                bool isnum  = false;
                int num     = suf.toInt(&isnum);
                if (isnum) {
                    // 说明是_num结尾
                    n = (n.mid(0, index) + split + QString::number(++num));
                } else {
                    n = (n + split + "1");
                }
            }
        }
    } while (stringSet.contains(n));
    return n;
}

int getSystemCodePage()
{
    // Windows平台
    // 获取系统编码的 QTextCodec
    QTextCodec* codec = QTextCodec::codecForLocale();
    if (!codec) {
        // 如果无法获取系统编码的 codec，则使用 UTF-8 作为备选
        codec = QTextCodec::codecForName("UTF-8");
    }
    return codec->mibEnum();
}

std::wstring qstringToSystemWString(const QString& qstr)
{
#ifdef Q_OS_WIN
    // Windows平台
    // 获取系统编码的 QTextCodec
    QTextCodec* codec = QTextCodec::codecForLocale();
    if (!codec) {
        // 如果无法获取系统编码的 codec，则使用 UTF-8 作为备选
        codec = QTextCodec::codecForName("UTF-8");
    }
    
    // 将 QString 转换为系统编码的 QByteArray
    QByteArray encodedBytes = codec->fromUnicode(qstr);
    
    // 计算转换为 wchar_t 数组所需的字符数
    int wcharCount = MultiByteToWideChar(codec->mibEnum(), 0, encodedBytes.constData(), -1, nullptr, 0);
    if (wcharCount == 0) {
        // 如果转换失败，则返回一个空的 std::wstring
        return std::wstring();
    }
    
    // 分配 wchar_t 数组并转换
    std::wstring result(wcharCount - 1, 0);
    MultiByteToWideChar(codec->mibEnum(), 0, encodedBytes.constData(), -1, &result[ 0 ], wcharCount);
    
    return result;
#else
    // Linux平台（或其他非Windows平台）
    // 假设系统使用 UTF-8 编码
    std::wstring result;
    result.assign(qstr.toStdWString());
    return result;
#endif
}

std::wstring stringToSystemWString(const std::string& str)
{
    // 获取系统的本地编码（ANSI编码）的QTextCodec
    QTextCodec* codec = QTextCodec::codecForLocale();
    if (!codec) {
        throw std::runtime_error("Failed to get locale codec");
    }
    
    // 将std::string转换为QString，使用系统编码
    QString qstr = codec->toUnicode(QByteArray(str.c_str(), static_cast< int >(str.size())));
    
    // 将QString转换为std::wstring
    return qstr.toStdWString();
}

#ifdef Q_OS_WIN
std::string convertToUtf8(const std::string& str, unsigned int codePage)
{
    // 首先转换为宽字符
    int wcharCount = MultiByteToWideChar(codePage, 0, str.c_str(), -1, nullptr, 0);
    if (wcharCount == 0) {
        throw std::runtime_error("MultiByteToWideChar failed");
    }
    std::vector< wchar_t > wcharBuffer(wcharCount);
    MultiByteToWideChar(codePage, 0, str.c_str(), -1, wcharBuffer.data(), wcharCount);
    
    // 然后将宽字符转换为 UTF-8
    int utf8Count = WideCharToMultiByte(CP_UTF8, 0, wcharBuffer.data(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Count == 0) {
        throw std::runtime_error("WideCharToMultiByte failed");
    }
    std::vector< char > utf8Buffer(utf8Count);
    WideCharToMultiByte(CP_UTF8, 0, wcharBuffer.data(), -1, utf8Buffer.data(), utf8Count, nullptr, nullptr);
    
    // 返回 UTF-8 编码的字符串
    return std::string(utf8Buffer.data(), utf8Count - 1);  // 减去1以排除终止null字符
}

#endif
/**
 * @brief 字符串转换为值
 * @param str 字符串
 * @param defaultValue 默认参数，如果转换失败，将返回默认参数
 * @return 转换的结果
 */

FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(short, toShort)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(unsigned short, toUShort)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(int, toInt)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(unsigned int, toUInt)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(long, toLong)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(unsigned long, toULong)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(long long, toLongLong)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(unsigned long long, toULongLong)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(float, toFloat)
FC_STRING_CAST_QSTRINGINNER_WITHBOOL_CPP(double, toDouble)
FC_STRING_CAST_QSTRINGINNER_CPP(std::string, toStdString)
FC_STRING_CAST_QSTRINGINNER_CPP(std::u16string, toStdU16String)
FC_STRING_CAST_QSTRINGINNER_CPP(std::u32string, toStdU32String)
FC_STRING_CAST_QSTRINGINNER_CPP(std::wstring, toStdWString)

} // namespace FC
