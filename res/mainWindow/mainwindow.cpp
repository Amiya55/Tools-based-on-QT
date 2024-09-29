#include "../include/mainWindow/mainwindow.h"
#include "../include/lottery/lottery.h"

#ifdef DEBUG
#include <iostream>
#endif

#include <QMessageBox>
// #include <ctime>
#include <cstdlib>
#include <QScreen>
#include <QDir>
#include <QFileDialog>
#include <QTimer>
#include <QPushButton>
#include <QMenu>
#include <QGridLayout>
#include <QMenuBar>



Application_Window::Application_Window(QMainWindow* parent)
    : QMainWindow(parent)
    , _menu_bar(this->menuBar())  // 每个继承自QMainWindow类的类都自带一个菜单栏，而menuBar()方法是直接获取这个自带的菜单栏的指针

    , _menu_edit(new QMenu(QStringLiteral("Edit(&E)")))
    , _action_file(new QAction("file(&F)"))

    , _menu_tools(new QMenu(QStringLiteral("Tools(&T)")))
    , _sub_menu_language(new QMenu("Language(&L)"))
    , _lang_english(new QAction("English"))
    , _lang_chinese(new QAction("chinese"))
    , _action_screenshot(new QAction("ScreenShot(&C)"))

    , _menu_help(new QMenu(QStringLiteral("Help(&H)")))
    , _action_guide(new QAction("Guide(&G"))

    , _menu_settings(new QMenu(QStringLiteral("Settings(&S)")))
    , _action_simple_settings(new QAction("simple settings"))

    , _central_widget(new QWidget(this))
    , _main_layout(new QGridLayout(this))

    , _lottery_machine(new QPushButton("摇号器"))
    , _game_machine(new QPushButton("游戏"))
    , _file_send(new QPushButton("文件传输"))
    , _spider(new QPushButton("爬虫"))
    , _translation(new QPushButton("翻译工具"))
    , _AI_chat(new QPushButton("AI聊天"))
{}


void Application_Window::build_top_menu()
{
    this->setMenuBar(_menu_bar);

    _menu_bar->addMenu(_menu_edit);
    _menu_edit->addAction(_action_file);

    _menu_bar->addMenu(_menu_tools);
    _menu_tools->addMenu(_sub_menu_language);
    _sub_menu_language->addAction(_lang_english);
    _sub_menu_language->addSeparator();
    _sub_menu_language->addAction(_lang_chinese);
    _menu_tools->addSeparator();  // 添加菜单项分隔符
    _menu_tools->addAction(_action_screenshot);

    _menu_bar->addMenu(_menu_help);
    _menu_help->addAction(_action_guide);

    _menu_bar->addMenu(_menu_settings);
    _menu_settings->addAction(_action_simple_settings);

    QObject::connect(_action_screenshot, &QAction::triggered, this, &Application_Window::screen_shot);
}


void Application_Window::build_widgets()
{
    QObject::connect(_lottery_machine, &QPushButton::clicked, this, &Application_Window::lottery_machine);
}


void Application_Window::build_layout()
{
    this->setCentralWidget(_central_widget);
    _central_widget->setLayout(_main_layout);

    _main_layout->addWidget(_lottery_machine);
    _main_layout->addWidget(_game_machine);
    _main_layout->addWidget(_file_send);
    _main_layout->addWidget(_spider);
    _main_layout->addWidget(_translation);
    _main_layout->addWidget(_AI_chat);
}


void Application_Window::build_window()
{
    this->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    this->build_layout();

    this->build_top_menu();

    this->build_widgets();


    this->show();
}

void Application_Window::screen_shot()
{
    this->hide();

    QTimer::singleShot(200, this, [this]() {
        QScreen* screen = QGuiApplication::primaryScreen();

        if(screen)
        {
            QImage screenShot = screen->grabWindow(0).toImage();

            QString saveFormat = ".png";
            QString defaultPath = QDir::currentPath() + "\\untitled" + saveFormat;
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                            defaultPath,
                                                            tr("%1 Files (*.%2);;All Files (*)")
                                                                .arg(saveFormat.toUpper())
                                                                .arg(saveFormat));

            if (!filePath.isEmpty())
            {


                if(screenShot.save(filePath))
                {
                    QString info = "截图保存成功\n保存路径为:" + filePath;
                    // QMessageBox::information(NULL, "info", info);


                }
                else
                {
                    QMessageBox::warning(NULL, "error", "截图保存失败");
                }
            }
        }

        this->show();
    });
}

void Application_Window::lottery_machine()
{
    Lottery_Main_Window* lottery = new Lottery_Main_Window(this);
    lottery->build_window();
}

void game_machine()
{

}

void file_send()
{

}

void spider()
{

}

void translation()
{

}

void AI_chat()
{

}


Application_Window::~Application_Window()
{
    delete _menu_help;
    delete _action_file;

    delete _menu_tools;
    delete _sub_menu_language;
    delete _lang_english;
    delete _lang_chinese;
    delete _action_screenshot;

    delete _menu_edit;
    delete _action_guide;

    delete _menu_settings;
    delete _action_simple_settings;

    delete _central_widget;
    delete _main_layout;

    delete _lottery_machine;
    delete _game_machine;
    delete _file_send;
    delete _spider;
    delete _translation;
    delete _AI_chat;
}





