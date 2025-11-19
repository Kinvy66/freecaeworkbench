/******************************************************************************
 * File     : FCUniqueIDGenerater.h
 * Brief    : id生成器
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-19
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCUNIQUEIDGENERATER_H
#define FCUNIQUEIDGENERATER_H
#include "FCUtilsAPI.h"
#include <cstdint>


namespace FC 
{
class FCUTILS_API FCUniqueIDGenerater
{
public:
    FCUniqueIDGenerater();
    /**
     * @brief 生成当前进程唯一uint64_t类型的id
	 * @return
	 */
    static uint64_t id_uint64();
};
} // namespace FC


#endif // FCUNIQUEIDGENERATER_H
