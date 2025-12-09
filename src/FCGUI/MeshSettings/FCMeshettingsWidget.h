#ifndef FCMESHETTINGSWIDGET_H
#define FCMESHETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class FCMeshettingsWidget;
}

class FCMeshettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FCMeshettingsWidget(QWidget *parent = nullptr);
    ~FCMeshettingsWidget();

private:
    Ui::FCMeshettingsWidget *ui;
};

#endif // FCMESHETTINGSWIDGET_H
