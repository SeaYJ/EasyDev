#include <QFontDatabase>
#include <QStringList>
#include "fontawesome.h"
#include "qdebug.h"

FontAwesome& FontAwesome::Instance() {
    static FontAwesome _instance; // 局部静态变量
    return _instance;
}

QFont FontAwesome::getFont() {
    return _font;
}

QChar FontAwesome::getIcon(Identity& icon_name) {
    return QChar(static_cast<int>(icon_name));
}

FontAwesome::FontAwesome() {
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Font Awesome 6 Free Solid.ttf");
    if(fontId == -1) {
        qWarning() << "Failed to load font file.";
        return ;
    }

    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if(fontFamilies.isEmpty()) {
        qWarning() << "Font loaded but no families found.";
        return ;
    }

    _font.setFamily(fontFamilies.at(0));
}


