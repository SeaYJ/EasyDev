#ifndef EASYDEV_H
#define EASYDEV_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMap>
#include <QShowEvent>
#include <QThread>
#include "deps/framelesswindow/framelesswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EasyDev;
}
QT_END_NAMESPACE

class EasyDev : public CFramelessWindow {
    Q_OBJECT

public:
    EasyDev(QWidget* parent = nullptr);
    ~EasyDev();

protected:

signals:
    void showMainWindow();

private slots:
    void showEvent(QShowEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void on_BtnMin_clicked();

    void on_BtnMax_clicked();

    void on_BtnClose_clicked();

    void on_SidebarMenu_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_SettingsBtn_clicked();

private:
    Ui::EasyDev* ui;

    const QFont _FontAwesome;

    QMap<QWidget*, QAbstractAnimation*> _AnimationBox;

    void setWindowIcons() const;
    void setWindowLogo();
    void connectInit();
    void animationInit();
    void flowLayoutInit();

    void singleItemExpansion(QTreeWidgetItem* item);

};
#endif // EASYDEV_H
