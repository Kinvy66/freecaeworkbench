/**
 * @file FCUniqueIDGenerater.h
 * @brief id生成器
 * @date 2025-11-19
 * @version V0.0.1
 * @details 生成当前进程唯一uint64_t类型的id
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
