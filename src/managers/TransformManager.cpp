//
// Created by Sp4rk on 08-12-17.
//

#include "managers/TransformManager.h"

TransformManager::TransformManager(InstanceData *data)
{
    data_ = data;
}

bool TransformManager::isValid(size_t id)
{
    return id > -1;
}
//
//int TransformManager::setDirty(size_t instance)
//{
//    data_->dirty[instance] = true;
//
//    return data_->entity[instance].id;
//}
//
//Matrix4x4 TransformManager::matrix4x4_identity()
//{
//    Matrix4x4 matrix_identity;
//    return matrix_identity;
//}
//
//int TransformManager::setClean(size_t instance)
//{
//    data_->dirty[instance] = false;
//
//    return data_->entity[instance].id;
//}
//
//bool TransformManager::isDirty(size_t instance)
//{
//    return data_->dirty[instance];
//}