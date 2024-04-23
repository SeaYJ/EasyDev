#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QWidget>  // 包含 QWidget 头文件，用于类的声明
#include <QSize>  // 包含 QSize 头文件，用于尺寸定义
#include <QLayout>  // 包含 QLayout 头文件，用于布局管理
#include <QLayoutItem>  // 包含 QLayoutItem 头文件，用于布局项
#include <QStyle>  // 包含 QStyle 头文件，用于样式定义
#include <QRect>  // 包含 QRect 头文件，用于矩形定义
#include <QList>  // 包含 QList 头文件，用于列表定义

class FlowLayout : public QLayout { // 声明 FlowLayout 类，继承自 QLayout
  public:
    explicit FlowLayout(QWidget* parent,
                        int margin = -1,
                        int hSpacing = -1,
                        int vSpacing = -1); // 声明带参数的构造函数
    explicit FlowLayout(int margin = -1,
                        int hSpacing = -1,
                        int vSpacing = -1); // 声明带参数的构造函数
    ~FlowLayout(); // 声明析构函数

    void addItem(QLayoutItem* item) override; // 声明添加布局项的函数，override 用于覆盖基类方法
    int horizontalSpacing() const; // 声明获取水平间距的函数
    int verticalSpacing() const; // 声明获取垂直间距的函数
    Qt::Orientations expandingDirections() const override; // 声明获取扩展方向的函数，override 用于覆盖基类方法
    bool hasHeightForWidth() const override; // 声明是否具有宽度相关高度的函数，override 用于覆盖基类方法
    int heightForWidth(int) const override; // 声明获取给定宽度的高度的函数，override 用于覆盖基类方法
    int count() const override; // 声明获取布局项数量的函数，override 用于覆盖基类方法
    QLayoutItem* itemAt(int index) const override; // 声明获取指定索引处的布局项的函数，override 用于覆盖基类方法
    QSize minimumSize() const override; // 声明获取最小尺寸的函数，override 用于覆盖基类方法
    void setGeometry(const QRect& rect) override; // 声明设置几何属性的函数，override 用于覆盖基类方法
    QSize sizeHint() const override; // 声明获取尺寸提示的函数，override 用于覆盖基类方法
    QLayoutItem* takeAt(int index) override; // 声明移除指定索引处的布局项的函数，override 用于覆盖基类方法

  private:
    int doLayout(const QRect& rect,
                 bool testOnly) const; // 声明执行布局的函数，testOnly 参数表示是否为测试模式
    int smartSpacing(QStyle::PixelMetric pm) const; // 声明获取智能间距的函数

    QList<QLayoutItem*> itemList; // 使用 QList 存储布局项的列表
    int m_hSpace; // 水平间距
    int m_vSpace; // 垂直间距
};

#endif // FLOWLAYOUT_H
