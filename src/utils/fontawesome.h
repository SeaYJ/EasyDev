#ifndef FONTAWESOME_H
#define FONTAWESOME_H

#include <QFont>
#include <QChar>

class FontAwesome {
  public:
    enum class Identity : int {
        Glass = 0xf000,
        Zero = 0x0030,
        One = 0x0031,
        Two = 0x0032
    };

    static FontAwesome& Instance();

    // 返回字体
    QFont getFont();
    QChar getIcon(FontAwesome::Identity& icon_name);

  protected:
    // 私有构造函数和赋值操作符确保不会被外部构造或复制
    explicit FontAwesome();
    explicit FontAwesome(const FontAwesome&) = delete;
    FontAwesome& operator=(const FontAwesome&) = delete;

  private:
    QFont _font;
};

#endif // FONTAWESOME_H
