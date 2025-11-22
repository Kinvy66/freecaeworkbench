#ifndef FCDATABASE_H
#define FCDATABASE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include "FCDataAPI.h"

class QDomDocument;
class QDomElement;

namespace FC 
{
class FCDATA_API FCDataBase : public QObject
{
    Q_OBJECT
public:
    
    FCDataBase() = default;
    ~FCDataBase() = default;
    
    /**
     * @brief 拷贝数据
     * @param data
     */
    virtual void copy(FCDataBase *data);
    
    /**
     * @brief 设置数据的ID值
     * @param id ID值
     */
    virtual void setID(uint64_t id);
    
    /**
     * @brief 获取数据的ID值
     * @return int 返回ID值
     */
    int64_t getID() const;
    
    /**
     * @brief 设置数据的名称
     * @param name 名称
     */
    virtual void setName(const QString &name);
    
    /**
     * @brief 获取数据的名称
     * @return QString 返回名称
     */
    QString getName() const;
    
    /**
		 * @brief 将参数列表转换为二进制流
		 * @param datas 转换后的二进制流
		 * @since 2.5.0
		 */
    virtual void dataToStream(QDataStream *datas);
    ///数据写入工程文件
    virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent);
    ///从工程文件读入数据
    virtual void readDataFromProjectFile(QDomElement *e);
    //读取参数
    virtual void readParameters(QDomElement *ele);
    //写出参数
    virtual void writeParameters(QDomDocument *doc, QDomElement *parent);
    ///根据名称获取参数
    // ParameterBase *getParameterByName(QString name) override;
    QString getName();
    
protected:
    uint64_t mId{0};
    // int MIndex{-1};
    QString mName{"FFFFFF"};
    
};

} // namespace FC


#endif // FCDATABASE_H
