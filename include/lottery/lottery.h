#include "../headers/struct.h"
#include <QtWidgets/QWidget>


class QVBoxLayout;
class QLineEdit;
class QPushButton;
class QHBoxLayout;




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


