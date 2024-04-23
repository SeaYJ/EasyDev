#include "flowlayout.h"  // 包含流式布局头文件

// 使用样例如下
// delete ui->ConvertersPage->layout();
// FlowLayout* convertersPageFlowLayout
//     = new FlowLayout(ui->ConvertersPage, 20, 20, 30);
// convertersPageFlowLayout->addWidget(ui->ConvertersNumberBaseIndexBtn);
// convertersPageFlowLayout->addWidget(ui->ConvertersTimestampIndexBtn);
// convertersPageFlowLayout->addWidget(ui->ConvertersImageIndexBtn);
// convertersPageFlowLayout->addWidget(ui->ConvertersVideoIndexBtn);
// convertersPageFlowLayout->addWidget(ui->ConvertersAudioIndexBtn);
// ui->ConvertersPage->setLayout(convertersPageFlowLayout);

FlowLayout::FlowLayout(QWidget* parent, int margin, int hSpacing,
                       int vSpacing) // 构造函数实现
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing) { // 初始化列表
    setContentsMargins(margin, margin, margin, margin); // 设置边距
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing) // 构造函数实现
    : m_hSpace(hSpacing), m_vSpace(vSpacing) { // 初始化列表
    setContentsMargins(margin, margin, margin, margin); // 设置边距
}

FlowLayout::~FlowLayout() { // 析构函数实现
    QLayoutItem* item; // 声明布局项指针

    while ((item = takeAt(0))) { // 循环移除布局项，直到为空
        delete item;    // 删除布局项
    }
}

void FlowLayout::addItem(QLayoutItem* item) { // 添加布局项函数实现
    itemList.append(item); // 将布局项添加到列表中
}

int FlowLayout::horizontalSpacing() const { // 获取水平间距函数实现
    if (m_hSpace >= 0) { // 如果水平间距大于等于0
        return m_hSpace; // 返回水平间距
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing); // 否则返回智能水平间距
    }
}

int FlowLayout::verticalSpacing() const { // 获取垂直间距函数实现
    if (m_vSpace >= 0) { // 如果垂直间距大于等于0
        return m_vSpace; // 返回垂直间距
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing); // 否则返回智能垂直间距
    }
}

Qt::Orientations FlowLayout::expandingDirections() const { // 获取扩展方向函数实现
    return {}; // 返回空方向，表示不扩展
}

bool FlowLayout::hasHeightForWidth() const { // 是否具有宽度相关高度函数实现
    return true; // 返回 true，表示具有宽度相关高度
}

int FlowLayout::heightForWidth(int width) const { // 获取给定宽度的高度函数实现
    int height = doLayout(QRect(0, 0, width, 0), true); // 执行布局并获取高度
    return height; // 返回高度
}

int FlowLayout::count() const { // 获取布局项数量函数实现
    return itemList.size(); // 返回布局项列表的大小
}

QLayoutItem* FlowLayout::itemAt(int index) const { // 获取指定索引处的布局项函数实现
    return itemList.value(index); // 返回指定索引处的布局项
}

QLayoutItem* FlowLayout::takeAt(int index) { // 移除指定索引处的布局项函数实现
    if (index >= 0 && index < itemList.size()) { // 如果索引有效
        return itemList.takeAt(index);    // 移除并返回布局项
    }

    return nullptr; // 否则返回空指针
}

QSize FlowLayout::minimumSize() const { // 获取最小尺寸函数实现
    QSize size; // 声明尺寸变量

    for (const QLayoutItem* item : std::as_const(itemList)) { // 遍历布局项列表
        size = size.expandedTo(item->minimumSize());    // 获取布局项的最小尺寸并扩展到总尺寸
    }

    const QMargins margins = contentsMargins(); // 获取边距
    size += QSize(margins.left() + margins.right(),
                  margins.top() + margins.bottom()); // 将边距添加到总尺寸
    return size; // 返回总尺寸
}

void FlowLayout::setGeometry(const QRect& rect) { // 设置几何属性函数实现
    QLayout::setGeometry(rect); // 调用基类方法设置几何属性
    doLayout(rect, false); // 执行布局
}

QSize FlowLayout::sizeHint() const { // 获取尺寸提示函数实现
    return minimumSize(); // 返回最小尺寸作为尺寸提示
}

int FlowLayout::doLayout(const QRect& rect, bool testOnly) const { // 执行布局函数实现
    int left, top, right, bottom; // 声明边距变量
    getContentsMargins(&left, &top, &right, &bottom); // 获取边距
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom); // 调整有效矩形
    int x = effectiveRect.x(); // 初始化 x 坐标
    int y = effectiveRect.y(); // 初始化 y 坐标
    int lineHeight = 0; // 初始化行高

    for (QLayoutItem* item : std::as_const(itemList)) { // 遍历布局项列表
        const QWidget* wid = item->widget(); // 获取布局项对应的窗口部件
        int spaceX = horizontalSpacing(); // 获取水平间距

        if (spaceX == -1) // 如果水平间距为无效值
            spaceX = wid->style()->layoutSpacing( // 获取窗口部件样式定义的水平间距
                         QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);

        int spaceY = verticalSpacing(); // 获取垂直间距

        if (spaceY == -1) // 如果垂直间距为无效值
            spaceY = wid->style()->layoutSpacing( // 获取窗口部件样式定义的垂直间距
                         QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);

        int nextX = x + item->sizeHint().width() + spaceX; // 计算下一个布局项的 x 坐标

        if (nextX - spaceX > effectiveRect.right()
                && lineHeight > 0) { // 如果下一个布局项超出右侧且当前行有高度
            x = effectiveRect.x(); // 重置 x 坐标
            y = y + lineHeight + spaceY; // 更新 y 坐标
            nextX = x + item->sizeHint().width() + spaceX; // 计算下一个布局项的 x 坐标
            lineHeight = 0; // 重置行高
        }

        if (!testOnly) { // 如果不是测试模式
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));    // 设置布局项的几何属性
        }

        x = nextX; // 更新 x 坐标
        lineHeight = qMax(lineHeight,
                          item->sizeHint().height()); // 更新行高为当前布局项高度的最大值
    }

    return y + lineHeight - rect.y() + bottom; // 返回布局的总高度
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const { // 获取智能间距函数实现
    QObject* parent = this->parent(); // 获取父对象

    if (!parent) { // 如果没有父对象
        return -1; // 返回无效值
    } else if (parent->isWidgetType()) { // 如果父对象是窗口部件类型
        QWidget* pw = static_cast<QWidget*>(parent); // 转换为窗口部件指针
        return pw->style()->pixelMetric(pm, nullptr,
                                        pw); // 返回窗口部件样式定义的像素度量值
    } else { // 否则
        return static_cast<QLayout*>(parent)->spacing(); // 返回父布局的间距值
    }
}
