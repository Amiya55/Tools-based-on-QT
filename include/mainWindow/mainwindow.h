#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QObject>

// #define DEBUG


class QMenuBar;
class QMenu;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QGridLayout;


class Application_Window : public QMainWindow
{
public:
    Application_Window(QMainWindow* parent = nullptr);

    void build_window();

    void lottery_machine();

    void game_machine();

    void file_send();

    void spider();

    void translation();

    void AI_chat();

    ~Application_Window();
private:

    void build_top_menu();

    void build_widgets();

    void build_layout();

    void screen_shot();


    // --------------顶部菜单栏相关-------------
    QMenuBar* _menu_bar;

    QMenu* _menu_edit;
    QAction* _action_file;

    QMenu* _menu_tools;
    QMenu* _sub_menu_language;  // 这是个二级菜单项
    QAction* _lang_english;
    QAction* _lang_chinese;
    QAction* _action_screenshot;

    QMenu* _menu_help;
    QAction* _action_guide;

    QMenu* _menu_settings;
    QAction* _action_simple_settings;
    // -----------------------------------------

    // ---------------布局相关-------------------
    QWidget* _central_widget;
    QGridLayout* _main_layout;
    // -----------------------------------------

    // ---------------各种软件启动按钮--------------
    QPushButton* _lottery_machine;

    QPushButton* _game_machine;

    QPushButton* _file_send;

    QPushButton* _spider;

    QPushButton* _translation;

    QPushButton* _AI_chat;

    // -------------------------------------------

};












