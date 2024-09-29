#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <cstring>

#define DEBUG

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct Widgets_Size
{
    Widgets_Size(int width = 10, int height = 10)
        : _width(width)
        , _height(height)
    {}

    int _width;
    int _height;
};


const Widgets_Size BUTTON_SIZE(150, 40);
const Widgets_Size INPUT_BOX_SIZE(300, 40);


struct Lottery_Data
{
    Lottery_Data()
        : _begin(0)
        , _end(0)
        , _count(0)
    {}

    int _begin;
    int _end;
    int _count;
    int _group_num;
};



struct Lottery_Skip_Num
{
    Lottery_Skip_Num(int init_size = 5)
        : _arr(nullptr)
        , _size(0)
        , _capacity(init_size)
    {
        _arr = new int[init_size];
    }

    void capacity_expansion()
    {
        if(_size >= _capacity)
        {
            int* temp = new int[_capacity * 2];
            memcpy(temp, _arr, _size * sizeof(int));

            delete[] _arr;
            _arr = temp;

            _capacity *= 2;
        }
    }

    void push_data(int num)
    {
        capacity_expansion();

        _arr[_size] = num;
        _size++;
    }

    ~Lottery_Skip_Num()
    {
        delete[] _arr;
    }

    int* _arr;
    int _size;
    int _capacity;
};



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



class Lottery_Main_Window : public QWidget
{
    Q_OBJECT

public:
    Lottery_Main_Window(QWidget *parent = nullptr);

    void build_window();  // 初始化创建窗口

    void creat_button();  // 创建按钮控件

    void creat_input_box();  // 创建文本输入框

    void get_lottery_data();  // 开始抽号

    template<class T>
    void set_widget_size(T* widget, const Widgets_Size& size);  // 设置控件尺寸

    ~Lottery_Main_Window();

private:

    QVBoxLayout* _main_lay;
    QHBoxLayout* _button_layout;
    QVBoxLayout* _input_layout;

    QPushButton* _quit;  // 结束程序
    QPushButton* _start;  // 开始抽号

    QLineEdit* _begin_input;  // 起始号码
    QLineEdit* _end_input;  // 结束号码
    QLineEdit* _skip_num_input;  // 跳过号码
    QLineEdit* _group_input;  // 分组组数
    QLineEdit* _lottery_count;  // 抽号个数

    // 从文本框获取到的几个个抽号基准信息
    Lottery_Data _data;
    Lottery_Skip_Num* _skip_num;

    // 跳过的号码无论是获取还是存储都跟普通的抽奖参数不同，所以就不放在_data中了
};


class Lottery
{
public:
    Lottery(int begin = 0, int end = 0, int count = 0, \
            Lottery_Skip_Num* skip_num = nullptr, int group = 1);

    void start_lottery();

    void show_group_result();

    void show_result();

    ~Lottery();
private:
    int* _arr;

    int _begin;
    int _end;
    int _count;

    Lottery_Skip_Num* _skip_num;

    int _group;
};













