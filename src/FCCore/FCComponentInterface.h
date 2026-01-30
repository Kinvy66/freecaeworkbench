#ifndef FCCOMPONENTINTERFACE_H
#define FCCOMPONENTINTERFACE_H

#include "FCCoreAPI.h"
#include <functional>
#include <QString>
#include <QWidget>
#include <QVariant>
#include <QHash>


//定义回调函数，参数为void*，返回值为int
typedef std::function<int(void*)> CallBackFuns;

namespace FC 
{

class  FCCORE_API FCComponentInterface
{
public:
    
    /**
     * @brief Construct a new FCComponentInterface object
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    explicit FCComponentInterface() = default;
    /**
     * @brief Destroy the FCComponentInterface object
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    virtual ~FCComponentInterface() = 0;
    
    /**
     * @brief 初始化，创建完成之后自动化调用
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    virtual void init();
    /**
     * @brief 获取组件中的界面
     * @param[i]  indexPort     抽象定义接口
     * @return QWidget*
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    virtual QWidget* getWidget(const int indexPort);
    /**
     * @brief 获取部件名称，不能重复
     * @return QString
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    virtual QString getComponentName() = 0;
    /**
     * @brief 执行组件
     * @param[i]  indexPort      抽象接口定义
     * @return true
     * @return false
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-07
     */
    virtual bool exec(const int indexPort);
    /**
     * @brief 设置名称
     * @param[i]  name           名称
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-30
     */
    void setComponentObjName(const QString & name);
    /**
     * @brief 获取名称
     * @return QString
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-30
     */
    QString getComponentObjName() const;
    /**
     * @brief 获取回调函数
     * @param[i]  key            键
     * @return CallBackFuns
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-25
     */
    CallBackFuns getCallBackFuns(int key);
    /**
     * @brief 设置回调函数，键相同的会覆盖
     * @param[i]  k              键
     * @param[i]  f              回调函数
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-25
     */
    void setCallBackFuns(int k, CallBackFuns f);
    /**
     * @brief 移除回调函数
     * @param[i]  k              键
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-25
     */
    void removeCallBackFun(int k);
    /**
     * @brief 设置数据对象
     * @param[i]  name           数据对象标记
     * @param[i]  data           数据对象指针
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-10
     */
    void setDataObject(const QString& name, QObject* data);
    /**
     * @brief 获取数据对象
     * @param[i]  name           数据对象标记
     * @return Core::FCAbstractDataobject* 
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-10
     */
    QObject* getDataObject(const QString& name);
    
    template <class T>
    /**
     * @brief 获取数据对象并进行强制类型转换
     * @param[i]  name           名称
     * @return T* 
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-10
     */
    T* getDataObjectT(const QString& name)
    {
        return dynamic_cast<T*>(this->getDataObject(name));
    }
    
    /**
     * @brief 重置全部数据对象
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-10
     */
    void resetDataObjects();
    
    /**
     * @brief 获取打开工程文件不释放的数据对象
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2025-08-18
     */
    virtual QList<int> getUnResetDataObj();
protected:
    /**
     * @brief 名称
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-30
     */
    QString _compObjName{};
    /**
     * @brief 回调函数
     * @author LiBaojun (libaojunqd@foxmail.com) 
     * @date 2024-04-25
     */
    QHash<int, CallBackFuns> _callBackFuns{};
    /**
     * @brief 数据对象hash
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-10
     */
    QHash<QString, QObject*> _dataObjects{};
};

} // namespace FC



#endif // FCCOMPONENTINTERFACE_H
