/**
 * @file FCMessageLogViewWidget.cpp
 * @brief 日志窗口，用于显示全局的消息
 * @date 2025-10-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMessageLogViewWidget.h"
#include "ui_FCMessageLogViewWidget.h"
#include <QDebug>
#include <QMenu>
#include <QItemSelectionModel>
#include <QClipboard>
#include <QApplication>
#include <QKeyEvent>
#include "Models/FCMessageLogsModel.h"

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

FCMessageLogViewWidget::FCMessageLogViewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMessageLogViewWidget)
{
    ui->setupUi(this);
    // 创建action
    _actionMessageLogShowInfo     = createAction("actionMessageLogShowInfo",
                                             ":/FCGui/MessageType/icon/messageType/messageTypeInfo.svg",
                                             true,
                                             true);
    _actionMessageLogShowWarning  = createAction("actionMessageLogShowWarning",
                                                ":/FCGui/MessageType/icon/messageType/messageTypeWarning.svg",
                                                true,
                                                true);
    _actionMessageLogShowCritical = createAction("actionMessageLogShowCritical",
                                                 ":/FCGui/MessageType/icon/messageType/messageTypeError.svg",
                                                 true,
                                                 true);
    _actionMessageLogShowDebug = createAction("actionMessageLogShowCritical",
                                                 ":/FCGui/MessageType/icon/messageType/messageTypeDebug.svg",
                                                 true,
                                                 true);
    _actionMessageLogClear        = createAction("actionMessageLogClear", ":/FCGui/MessageType/icon/messageType/clear-message.svg");
    _actionCopySelectMessage      = createAction("actionCopySelectMessage", ":/FCGui/icon/copy.svg");
    // 构建菜单
    
    //
    _model           = new FCMessageLogsModel(this);
    _sortFilterModel = new FCMessageLogsSortFilterProxyModel(this);
    _sortFilterModel->setSourceModel(_model);
    ui->tableView->setModel(_sortFilterModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    
    QFontMetrics fm = ui->tableView->fontMetrics();
    // 高度为行高的1.2
    ui->tableView->verticalHeader()->setDefaultSectionSize(fm.lineSpacing() * 1.2);
    
    //
    ui->toolButtonInfo->setDefaultAction(_actionMessageLogShowInfo);
    ui->toolButtonWarning->setDefaultAction(_actionMessageLogShowWarning);
    ui->toolButtonCritial->setDefaultAction(_actionMessageLogShowCritical);
    ui->toolButtonDebug->setDefaultAction(_actionMessageLogShowDebug);
    ui->toolButtonClear->setDefaultAction(_actionMessageLogClear);
    //
    connect(_actionMessageLogShowInfo, &QAction::triggered, this, &FCMessageLogViewWidget::setEnableShowInfoMsg);
    connect(_actionMessageLogShowWarning, &QAction::triggered, this, &FCMessageLogViewWidget::setEnableShowWarningMsg);
    connect(_actionMessageLogShowCritical, &QAction::triggered, this, &FCMessageLogViewWidget::setEnableShowCriticalMsg);
    connect(_actionMessageLogShowDebug, &QAction::triggered, this, &FCMessageLogViewWidget::setEnableShowDebugMsg);    
    connect(_actionMessageLogClear, &QAction::triggered, this, &FCMessageLogViewWidget::clearAll);
    connect(_actionCopySelectMessage, &QAction::triggered, this, &FCMessageLogViewWidget::copySelectionMessageToClipBoard);
    connect(this, &FCMessageLogViewWidget::customContextMenuRequested, this, &FCMessageLogViewWidget::onCustomContextMenuRequested);
    ui->tableView->setWordWrap(true);
    connect(ui->tableView, &QTableView::clicked, this, &FCMessageLogViewWidget::onTableViewItemClicked);
    FCMessageQueueProxy* messageQueue = &(_model->messageQueueProxy());
    connect(messageQueue, &FCMessageQueueProxy::messageQueueAppended, this, &FCMessageLogViewWidget::onMessageAppended);

    
    retranslateUi();
}

FCMessageLogViewWidget::~FCMessageLogViewWidget()
{
    delete ui;
}

QAction* FCMessageLogViewWidget::createAction(const char* objname, const char* iconpath, bool checkable, bool checked)
{
    QAction* act = new QAction(this);
    act->setObjectName(QString::fromUtf8(objname));
    QIcon icon(iconpath);
    act->setIcon(icon);
    act->setCheckable(checkable);
    if (checkable) {
        act->setChecked(checked);
    }
    return act;
}

void FCMessageLogViewWidget::onCustomContextMenuRequested(const QPoint& pos)
{
    if (ui->tableView->underMouse()) {
        if (nullptr == _menu) {
            buildMenu();
        }
        _menu->exec(mapToGlobal(pos));
    }
}

void FCMessageLogViewWidget::onMessageAppended()
{
    if (isAutoScrollToButtom()) {
        ui->tableView->scrollToBottom();
    }
}

void FCMessageLogViewWidget::buildMenu()
{
    _menu = new QMenu(this);
    _menu->addAction(_actionCopySelectMessage);
    _menu->addSeparator();
    _menu->addAction(_actionMessageLogShowInfo);
    _menu->addAction(_actionMessageLogShowWarning);
    _menu->addAction(_actionMessageLogShowCritical);
    _menu->addAction(_actionMessageLogShowDebug);    
    _menu->addSeparator();
    _menu->addAction(_actionMessageLogClear);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

bool FCMessageLogViewWidget::isAutoScrollToButtom() const
{
    return mIsAutoScrollToButtom;
}

void FCMessageLogViewWidget::setAutoScrollToButtom(bool isAutoScrollToButtom)
{
    mIsAutoScrollToButtom = isAutoScrollToButtom;
}
/**
 * @brief 设置是否允许DebugMsg的显示
 * @param on
 */
void FCMessageLogViewWidget::setEnableShowDebugMsg(bool on)
{
    _sortFilterModel->setAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptDebugMsg, on);
    ui->tableView->update();
}
/**
 * @brief 检测是否允许DebugMsg的显示
 * @return
 */
bool FCMessageLogViewWidget::isEnableShowDebugMsg() const
{
    return _sortFilterModel->testAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptDebugMsg);
}
/**
 * @brief 设置是否允许WarningMsg的显示
 * @param on
 */
void FCMessageLogViewWidget::setEnableShowWarningMsg(bool on)
{
    _sortFilterModel->setAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptWarningMsg, on);
    ui->tableView->update();
}
/**
 * @brief 检测是否允许WarningMsg的显示
 * @return
 */
bool FCMessageLogViewWidget::isEnableShowWarningMsg() const
{
    return _sortFilterModel->testAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptWarningMsg);
}
/**
 * @brief 设置是否允许CriticalMsg的显示
 * @param on
 */
void FCMessageLogViewWidget::setEnableShowCriticalMsg(bool on)
{
    _sortFilterModel->setAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptCriticalMsg, on);
    ui->tableView->update();
}
/**
 * @brief 检测是否允许CriticalMsg的显示
 * @return
 */
bool FCMessageLogViewWidget::isEnableShowCriticalMsg() const
{
    return _sortFilterModel->testAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptCriticalMsg);
}
/**
 * @brief 设置是否允许FatalMsg的显示
 * @param on
 */
void FCMessageLogViewWidget::setEnableShowFatalMsg(bool on)
{
    _sortFilterModel->setAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptFatalMsg, on);
    ui->tableView->update();
}
/**
 * @brief 检测是否允许FatalMsg的显示
 * @return
 */
bool FCMessageLogViewWidget::isEnableShowFatalMsg() const
{
    return _sortFilterModel->testAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptFatalMsg);
}
/**
 * @brief 设置是否允许InfoMsg的显示
 * @param on
 */
void FCMessageLogViewWidget::setEnableShowInfoMsg(bool on)
{
    _sortFilterModel->setAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptInfoMsg, on);
    ui->tableView->update();
}

/**
 * @brief 点击后自动适应尺寸
 * @param index
 */
void FCMessageLogViewWidget::onTableViewItemClicked(const QModelIndex& index)
{
    QHeaderView* vh = ui->tableView->verticalHeader();
    if (vh && index.isValid()) {
        if (index.row() < vh->count()) {
            vh->setSectionResizeMode(index.row(), QHeaderView::ResizeToContents);
        }
    }
}

/**
 * @brief 清空所有消息
 */
void FCMessageLogViewWidget::clearAll()
{
    _model->clearAll();
}

/**
 * @brief 把选中的文本复制到剪切板
 */
void FCMessageLogViewWidget::copySelectionMessageToClipBoard()
{
    QItemSelectionModel* sm = ui->tableView->selectionModel();
    if (nullptr == sm) {
        return;
    }
    int cc = _sortFilterModel->columnCount();
    QSet< int > rowIndexs;
    QModelIndexList indexs = sm->selectedIndexes();
    QString text;
    for (const QModelIndex& i : qAsConst(indexs)) {
        if (!rowIndexs.contains(i.row())) {
            if (!rowIndexs.isEmpty()) {
                text += "\n";
            }
            rowIndexs.insert(i.row());
            QString line;
            for (int c = 0; c < cc; ++c) {
                line += _sortFilterModel->data(_sortFilterModel->index(i.row(), c)).toString();
                if (c != cc - 1) {
                    line += "\t";
                }
            }
            text += line;
        }
    }
    if (text.isEmpty()) {
        qDebug() << "copy nothing to clipboard";
        return;
    }
    QClipboard* appclip = QApplication::clipboard();
    if (appclip) {
        appclip->setText(text);
    }
    qDebug() << "copy to clipboard:" << text;
}

/**
 * @brief 选中所有
 */
void FCMessageLogViewWidget::selectAll()
{
    ui->tableView->selectAll();
}

/**
 * @brief 事件改变捕获
 * @param event
 */
void FCMessageLogViewWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}

/**
 * @brief 设置文本
 */
void FCMessageLogViewWidget::retranslateUi()
{
    _actionMessageLogShowInfo->setText(tr("Info"));
    _actionMessageLogShowInfo->setToolTip(tr("Show Info Message"));
    _actionMessageLogShowWarning->setText(tr("Warning"));
    _actionMessageLogShowWarning->setToolTip(tr("Show Warning Message"));
    _actionMessageLogShowCritical->setText(tr("Critical"));
    _actionMessageLogShowCritical->setToolTip(tr("Show Critical Message"));
    _actionMessageLogShowDebug->setText(tr("Debug"));
    _actionMessageLogShowDebug->setToolTip(tr("Show Debug Message"));
    _actionMessageLogClear->setText(tr("Clear"));                  // cn:清空
    _actionMessageLogClear->setToolTip(tr("Clear All Messages"));  // cn:清空所有消息
    _actionCopySelectMessage->setText(tr("Copy"));                 // 复制
    _actionCopySelectMessage->setToolTip(tr("Copy Select Message"));
}

/**
 * @brief 处理快捷键
 * @param event
 */
void FCMessageLogViewWidget::keyPressEvent(QKeyEvent* event)
{
    if (event) {
        if (Qt::ControlModifier == event->modifiers()) {
            if (Qt::Key_C == event->key()) {
                // 复制
                copySelectionMessageToClipBoard();
                event->accept();
            } else if (Qt::Key_A == event->key()) {
                selectAll();
                event->accept();
            }
        }
    }
    QWidget::keyPressEvent(event);
}

/**
 * @brief 获取内部的action
 * @param ac
 * @return
 */
QAction* FCMessageLogViewWidget::getAction(FCMessageLogViewWidget::MessageLogActions ac) const
{
    switch (ac) {
    case ActionInfo:
        return _actionMessageLogShowInfo;
    case ActionWarning:
        return _actionMessageLogShowWarning;
    case ActionCritial:
        return _actionMessageLogShowCritical;
    case ActionDebug:
        return _actionMessageLogShowDebug;
    case ActionClear:
        return _actionMessageLogClear;
    case ActionCopy:
        return _actionCopySelectMessage;
    default:
        break;
    }
    return nullptr;
}
/**
 * @brief 检测是否允许InfoMsg的显示
 * @return
 */
bool FCMessageLogViewWidget::isEnableShowInfoMsg() const
{
    return _sortFilterModel->testAcceptMessageTypeFlag(FCMessageLogsSortFilterProxyModel::AcceptInfoMsg);
}
