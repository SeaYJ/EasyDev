#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QPropertyAnimation>
#include "easydev.h"
#include "ui_easydev.h"
#include "modules/flowlayout.h"
#include "utils/fontawesome.h"

EasyDev::EasyDev(QWidget* parent)
    : CFramelessWindow(parent)
    , ui(new Ui::EasyDev)
    , _FontAwesome(FontAwesome::Instance().getFont()) {
    ui->setupUi(this);

    // 程序自定义标题栏指定
    setTitleBar(ui->WindowTitleBar);

    // 设置程序 Logo
    setWindowLogo();

    // 设置软件所有 ICON 图标
    setWindowIcons();

    // 信号连接
    connectInit();

    // 流式布局初始化
    flowLayoutInit();
}

EasyDev::~EasyDev() {
    delete ui;

    // 清除所有动画
    for (QMap<QWidget*, QAbstractAnimation*>::iterator animation = _AnimationBox.begin();
            animation != _AnimationBox.end();
            animation++) {
        (animation.value())->stop();
        delete (animation.value());
    }

    _AnimationBox.clear();
}

void EasyDev::showEvent(QShowEvent* event) {
    // 动画初始化
    // 因为很多动画都需要使用控件参数进行初始化,
    // 为了确保控件已经完全被初始化，
    // 获取到正确的参数，
    // 所以要放在这里
    animationInit();

    emit showMainWindow();
    event->accept();
}

void EasyDev::resizeEvent(QResizeEvent* event) {
    event->accept();
}

void EasyDev::on_BtnMin_clicked() {
    showMinimized();
}


void EasyDev::on_BtnMax_clicked() {
    if (isMaximized()) {
        showNormal();
        ui->BtnMax->setIcon(QIcon(":/svg/FluentMaximize24Regular.svg"));
        ui->BtnMax->setIconSize(QSize(18, 18));
    } else {
        showMaximized();
        ui->BtnMax->setIcon(QIcon(":/svg/FluentSquareMultiple24Regular.svg"));
        ui->BtnMax->setIconSize(QSize(17, 17));
    }
}


void EasyDev::on_BtnClose_clicked() {
    close();
}

void EasyDev::setWindowIcons() const {
    // WindowBtn
    ui->BtnMin->setIcon(QIcon(":/svg/FluentMinimize24Regular.svg"));
    ui->BtnMax->setIcon(QIcon(":/svg/FluentMaximize24Regular.svg"));
    ui->BtnClose->setIcon(QIcon(":/svg/FluentDismiss24Regular.svg"));

    ui->BtnMin->setIconSize(QSize(20, 20));
    ui->BtnMax->setIconSize(QSize(18, 18));
    ui->BtnClose->setIconSize(QSize(20, 20));
}

void EasyDev::setWindowLogo() {
    // WindowLogo In TitleBar
    QPixmap EasyDevPNG(":/imgs/EasyDev.png");
    EasyDevPNG = EasyDevPNG.scaled(
                     ui->Logo->size(),
                     Qt::KeepAspectRatio,
                     Qt::SmoothTransformation); // 图片放缩
    ui->Logo->setAlignment(Qt::AlignCenter); // Logo 居中
    ui->Logo->setPixmap(EasyDevPNG); // 添加 Logo
    ui->Logo->setMinimumWidth(ui->Logo->width()); // 防止宽度过低导致 Logo 显示不全

    // WindowLogo in System
    setWindowIcon(QIcon(":/imgs/ED.png"));
}

void EasyDev::connectInit() {
    // 确保侧边栏只有一个展开项(OnlyOneTopItemExpansion)
    connect(ui->SidebarMenu, &QTreeWidget::itemExpanded, this, &EasyDev::singleItemExpansion);

    // 连接 itemClicked 信号来实现单击展开的效果
    connect(ui->SidebarMenu, &QTreeWidget::itemClicked, this, [ =](QTreeWidgetItem * item) {
        if (item->childCount() > 0) {
            if (item->isExpanded()) {
                ui->SidebarMenu->collapseItem(item);
            } else {
                ui->SidebarMenu->expandItem(item);
            }
        }
    });


    // 动画事件绑定
    // ==========·==========
    // 程序 showMainWindow（自定义信号）时触发
    connect(this, &EasyDev::showMainWindow, this, [ =]() {
        _AnimationBox.value(ui->SidebarMenu)->start();
        // _AnimationBox.value(ui->MenuItemPages)->start();
    });
}

void EasyDev::animationInit() {
    // Animation of SidebarMenu
    QParallelAnimationGroup* sidebarMenuAnimationGroup
        = new QParallelAnimationGroup(this);

    QPropertyAnimation* smfPos
        = new QPropertyAnimation(ui->SidebarMenuFrame, "pos");

    QPoint smfStartPoint(-(ui->SidebarMenuFrame->width() + ui->SidebarMenuFrame->x()),
                         ui->SidebarMenuFrame->y());
    QPoint smfEndPoint(ui->SidebarMenuFrame->x(), ui->SidebarMenuFrame->y());

    smfPos->setDuration(400);
    smfPos->setStartValue(smfStartPoint);
    smfPos->setEndValue(smfEndPoint);
    smfPos->setEasingCurve(QEasingCurve::OutBack);

    sidebarMenuAnimationGroup->addAnimation(smfPos);

    // Animation of SettingsBtn(按理说应该归属于 SidebarMenu，所以放在一起)
    QPropertyAnimation* sbPos
        = new QPropertyAnimation(ui->SettingsBtn, "pos");

    QPoint sbStartPoint(-(ui->SidebarMenu->width() + ui->SidebarMenu->x()), ui->SettingsBtn->y());
    QPoint sbEndPoint(ui->SettingsBtn->x(), ui->SettingsBtn->y());

    sbPos->setDuration(400);
    sbPos->setStartValue(sbStartPoint);
    sbPos->setEndValue(sbEndPoint);
    sbPos->setEasingCurve(QEasingCurve::OutBack);

    sidebarMenuAnimationGroup->addAnimation(sbPos);

    // Animation of MenuItemPages
    QParallelAnimationGroup* menuItemPagesAnimationGroup
        = new QParallelAnimationGroup(this);

    QPropertyAnimation* mipPos
        = new QPropertyAnimation(ui->MenuItemPages, "pos");

    QPoint mipStartPonit((ui->MenuItemPages->x() + ui->MenuItemPages->width()), ui->MenuItemPages->y());
    QPoint mipEndPoint(ui->MenuItemPages->x(), ui->MenuItemPages->y());

    mipPos->setDuration(400);
    mipPos->setStartValue(mipStartPonit);
    mipPos->setEndValue(mipEndPoint);

    menuItemPagesAnimationGroup->addAnimation(mipPos);

    // Save Animation Group
    _AnimationBox[ui->SidebarMenu] = sidebarMenuAnimationGroup;
    _AnimationBox[ui->MenuItemPages] = menuItemPagesAnimationGroup;

}

void EasyDev::flowLayoutInit() {}

void EasyDev::singleItemExpansion(QTreeWidgetItem* item) {
    // 遍历所有项，将除当前展开项外的所有项折叠
    int topLevelItemCount = ui->SidebarMenu->topLevelItemCount();

    for (int i = 0; i < topLevelItemCount; ++i) {
        QTreeWidgetItem* currentItem = ui->SidebarMenu->topLevelItem(i);

        if (currentItem != item) {
            ui->SidebarMenu->collapseItem(currentItem);
        }
    }
}


void EasyDev::on_SidebarMenu_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    // 这里简化处理：假设每个子项名称唯一
    if (current && !current->parent()) return; // 忽略顶级项的选择

    QString currentItemText = current->text(0);
    if (currentItemText == "Number Base") {
        ui->MenuItemPages->setCurrentWidget(ui->NumberBasePage);
    } else if (currentItemText == "Timestamp") {
        ui->MenuItemPages->setCurrentWidget(ui->TimestampPage);
    } else if (currentItemText == "Image") {
        ui->MenuItemPages->setCurrentWidget(ui->ImageConverterPage);
    } else if (currentItemText == "Video") {
        ui->MenuItemPages->setCurrentWidget(ui->VideoConverterPage);
    } else if (currentItemText == "Audio") {
        ui->MenuItemPages->setCurrentWidget(ui->AudioConverterPage);
    } else if (currentItemText == "URL") {
        ui->MenuItemPages->setCurrentWidget(ui->EDCoderURLPage);
    } else if (currentItemText == "HTML") {
        ui->MenuItemPages->setCurrentWidget(ui->EDCoderHTMLPage);
    } else if (currentItemText == "Base64 Text") {
        ui->MenuItemPages->setCurrentWidget(ui->Base64TextPage);
    } else if (currentItemText == "Base64 Image") {
        ui->MenuItemPages->setCurrentWidget(ui->Base64ImagePage);
    } else if (currentItemText == "JSON") {
        ui->MenuItemPages->setCurrentWidget(ui->FormatterJSONPage);
    } else if (currentItemText == "SQL") {
        ui->MenuItemPages->setCurrentWidget(ui->FormatterSQLPage);
    } else if (currentItemText == "C++") {
        ui->MenuItemPages->setCurrentWidget(ui->FormatterCPPPage);
    } else if (currentItemText == "XML") {
        ui->MenuItemPages->setCurrentWidget(ui->FormatterXMLPage);
    } else if (currentItemText == "Lorem Ipsum") {
        ui->MenuItemPages->setCurrentWidget(ui->LoremIpsumPage);
    } else if (currentItemText == "Markdown Preview") {
        ui->MenuItemPages->setCurrentWidget(ui->MarkdownPreviewPage);
    } else if (currentItemText == "Color Picker & Contrast") {
        ui->MenuItemPages->setCurrentWidget(ui->ColorPickerContrastPage);
    }

    ui->MenuItemPageTitle->setText(currentItemText);
}


void EasyDev::on_SettingsBtn_clicked() {
    ui->MenuItemPages->setCurrentWidget(ui->SettingsPage);
    ui->MenuItemPageTitle->setText(tr("Settings"));
}

