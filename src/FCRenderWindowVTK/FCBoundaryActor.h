/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 *
 * @file FCBoundaryActor.h
 * @brief 边界范围actor，用于渲染对象的边界范围
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-05-05
 *
 */
#ifndef __FCBOUNDARYACTOR_H___
#define __FCBOUNDARYACTOR_H___

class vtkActor;
class vtkUnstructuredGrid;

namespace FC
{
    /**
     * @brief 边界范围actor，用于渲染对象的边界范围
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-05-05
     */
    class FCBoundaryActor
    {
    public:
        /**
         * @brief Construct a new FCBoundaryActor object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-05
         */
        explicit FCBoundaryActor();
        /**
         * @brief Destroy the FCBoundaryActor object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-05
         */
        virtual ~FCBoundaryActor();
        /**
         * @brief 获取边界范围actor
         * @return vtkActor*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-05
         */
        vtkActor* getActor();
        /**
         * @brief 更新边界范围
         * @param bound   6个分量 minx maxX minY maxY minZ maxZ
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-05
         */
        void updateBoundary(double* bound);

    private:
        /**
         * @brief 边界范围actor
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-05
         */
        vtkActor* _boundaryActor{};
    };
}

#endif
