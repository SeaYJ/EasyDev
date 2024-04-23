#include "easydev.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QScreen>
#include <QFont>
#include <QFontDatabase>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for(const QString& locale : uiLanguages) {
        const QString baseName = "EasyDev_" + QLocale(locale).name();
        if(translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // 设置默认字体
    int fontId = QFontDatabase::addApplicationFont(":/fonts/HarmonyOS_Sans_SC/HarmonyOS_Sans_SC_Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if(!fontFamilies.isEmpty()) {
        app.setFont(QFont(fontFamilies.at(0), 12, QFont::Weight::Normal, QFont::Style::StyleNormal));
    } else {
        app.setFont(QFont("Microsoft YaHei", 12, QFont::Weight::Normal, QFont::Style::StyleNormal));
    }

    EasyDev mainWindow;

    // 获取屏幕的尺寸和中心点
    const QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - mainWindow.width()) / 2;
    int y = (screenGeometry.height() - mainWindow.height()) / 2;
    // 将程序移动到屏幕正中心
    mainWindow.move(x, y);

    mainWindow.show();

    return app.exec();
}
