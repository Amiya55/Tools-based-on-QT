#include "../../include/lottery/lottery.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <regex>


Lottery_Main_Window::Lottery_Main_Window(QWidget *parent)
    : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(windowFlags() | Qt::Window);

    _main_lay = new QVBoxLayout(this);
    _button_layout = new QHBoxLayout(this);
    _input_layout = new QVBoxLayout(this);


    _quit = new QPushButton("quit");
    _start = new QPushButton("start");

    _begin_input = new QLineEdit;
    _end_input = new QLineEdit;

    _lottery_count = new QLineEdit;

    _skip_num_input = new QLineEdit;
    _group_input = new QLineEdit;

    _skip_num = new Lottery_Skip_Num;

}


void Lottery_Main_Window::build_window()
{
    // 因为Lottery_Main_Window类继承自QWidget类，所以这个this压根不用写
    // 不过为了可读性，我带上了this
    this->setWindowTitle("摇号器2.0");
    this->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 这里的操作是开辟三个Layout对象，两个垂直分布的，一个水平分布的
    // 其中main_lay是背板，input_box_lay是输入框的布局，为垂直分布，button_lay是按钮的布局，为水平分布
    // 最后我们吧input_box_lay和button_lay全都添加到背板main_lay上就可以了
    creat_input_box();
    creat_button();

    _main_lay->addLayout(_input_layout);
    _main_lay->addLayout(_button_layout);

    this->setLayout(_main_lay);
    this->show();

}


void Lottery_Main_Window::creat_button()
{

    // 设置按钮控件的尺寸
    set_widget_size<QPushButton>(_quit, BUTTON_SIZE);
    set_widget_size<QPushButton>(_start, BUTTON_SIZE);

    // 为两个button控件添加对应的槽函数
    // QObject::connect(_quit, &QPushButton::clicked, \
    //     QCoreApplication::instance(), &QApplication::quit);

    QObject::connect(_quit, &QPushButton::clicked, \
                     this, &Lottery_Main_Window::close);
    QObject::connect(_start, &QPushButton::clicked, \
                     this, &Lottery_Main_Window::get_lottery_data);

    _button_layout->addWidget(_quit);
    _button_layout->addWidget(_start);
}


void Lottery_Main_Window::creat_input_box()
{

    // 设置文本输入框的大小
    set_widget_size<QLineEdit>(_begin_input, INPUT_BOX_SIZE);
    set_widget_size<QLineEdit>(_end_input, INPUT_BOX_SIZE);
    set_widget_size<QLineEdit>(_lottery_count, INPUT_BOX_SIZE);
    set_widget_size<QLineEdit>(_group_input, INPUT_BOX_SIZE);
    set_widget_size<QLineEdit>(_skip_num_input, INPUT_BOX_SIZE);

    // 设置提示文本
    _begin_input->setPlaceholderText("输入起始号码:");
    _end_input->setPlaceholderText("输入结束号码:");
    _lottery_count->setPlaceholderText("(选填，不填默认抽全部) 输入抽取的个数:");
    _skip_num_input->setPlaceholderText("(选填) 输入指定跳过的号码，空格隔开:");
    _group_input->setPlaceholderText("(选填) 指定分组抽号:");

    // 将控件添加到布局上
    _input_layout->addWidget(_begin_input, 2, Qt::AlignCenter);
    _input_layout->addWidget(_end_input, 2, Qt::AlignCenter);
    _input_layout->addWidget(_lottery_count, 2, Qt::AlignCenter);
    _input_layout->addWidget(_skip_num_input, 2, Qt::AlignCenter);
    _input_layout->addWidget(_group_input, 2, Qt::AlignCenter);

}

template<class T>
void Lottery_Main_Window::set_widget_size(T* widget, const Widgets_Size& size)
{
    widget->setFixedWidth(size._width);
    widget->setFixedHeight(size._height);
}


void Lottery_Main_Window::get_lottery_data()
{
    // ----------获取跳过的号码------------

    // 这一步很重要，假如用户重复抽取，只有将_size值清零才能实现_arr数组的复用
    _skip_num->_size = 0;

    if(!(_skip_num_input->text().isEmpty()))
    {
        QString get_qstr = _skip_num_input->text();
        std::string result_str = get_qstr.toStdString();

        std::smatch match;
        std::regex pattern("(\\d+)");

        std::string::const_iterator iter = result_str.begin();

        int num = 0;
        while(std::regex_search(iter, result_str.cend(), match, pattern))
        {
            iter = match[0].second;
            for(size_t i = 1; i < match.size(); ++i)
            {
                num = std::stoi(match[i].str());

                _skip_num->push_data(num);
            }
        }
    }
    // -------------------------


    if((_begin_input->text().isEmpty()) ||\
        (_end_input->text().isEmpty()))
    {
        QMessageBox::warning(NULL, "Error","你还有选项没有输入");
        return;
    }
    else
    {
        bool success_1, success_2, success_3, success_4;
        _data._begin = _begin_input->text().toInt(&success_1);
        _data._end = _end_input->text().toInt(&success_2);
        _data._count = _lottery_count->text().toInt(&success_3);
        _data._group_num = _group_input->text().toInt(&success_4);


        if(!success_4)
            _data._group_num = 1;

        if(success_1 && success_2)
        {
            // 判断抽取个数需不需要缺省
            if(!success_3)
            {
                _data._count = _data._end - _data._begin + 1 - _skip_num->_size;
            }

            if(_data._count < _data._group_num)
            {
                QMessageBox::warning(NULL, "Error", "不是吧，分组数量比总人数还多？\n我上哪去给你造人？");
                return;
            }

            // ----------判断指定跳过的号码是否合法------------
            for(int i = 0; i < _skip_num->_size; ++i)
            {
                if(_skip_num->_arr[i] > _data._end || \
                                                           _skip_num->_arr[i] < _data._begin)
                {
                    QMessageBox::warning(NULL, "Error", \
                                         "你确定你指定跳过的号码比结束号码还大\n或者比起始号码还小？\n何必多此一举？");
                    return;
                }
            }
            // --------------------------------------------

            if(_data._begin > _data._end)
            {
                QMessageBox::warning(NULL, "Error", "你确定你的起始号码比结束号码还大？");
            }
            else if(_data._count < 1)
            {
                QMessageBox::warning(NULL, "Error", "你确定要抽的人数没问题？\n这我抽个毛啊！");
            }
            else if(_data._end - _data._begin + 1 - _skip_num->_size < _data._count)
            {
                QMessageBox::warning(NULL, "Error", "抽的人数比总数还多...\n你这不亚于在鸡蛋里面挑石子！");
            }
            else
            {
                Lottery(_data._begin, _data._end, _data._count, _skip_num, _data._group_num).start_lottery();
            }
        }
        else
        {
            QMessageBox::warning(NULL, "Error", "输入戳啦！\n只能输入整数！");
        }
    }

}


Lottery_Main_Window::~Lottery_Main_Window()
{
    delete _quit;
    delete _start;

    delete _begin_input;
    delete _end_input;
    delete _lottery_count;
    delete _group_input;
    delete _skip_num_input;

    delete _skip_num;

    delete _input_layout;
    delete _button_layout;
}




Lottery::Lottery(int begin, int end, int count, \
                 Lottery_Skip_Num* skip_num, int group)
    : _arr(nullptr)
    , _begin(begin)
    , _end(end)
    , _count(count)
    , _skip_num(skip_num)
    , _group(group)
{
    _arr = new int[_count];
}


void Lottery::start_lottery()
{
    srand((unsigned int)time(NULL));

    int index = 0;
    int value = 0;
    bool flag = 1;

    for(index = 0; index < _count;)
    {
        flag = 1;

        value = rand() % (_end - _begin + 1) + _begin;

        for(int i = 0; i < _skip_num->_size; ++i)  // 看看抽到的号码是不是指定要跳过的号码
        {
            if(_skip_num->_arr[i] == value)
            {
                flag = 0;
                break;
            }
        }

        if(flag)  // 看看抽到的号码是不是已经抽到过了
        {
            for(int i = 0; i < index; ++i)
            {
                if(_arr[i] == value)
                {
                    flag = 0;
                    break;
                }
            }
        }

        if(flag)
        {
            _arr[index] = value;
            ++index;
        }
    }

    if(_group == 1)
        show_result();
    else
        show_group_result();
}


void Lottery::show_result()
{
    std::string result = "";
    char* str = new char[100];

    for(int i = 0; i < _count; i++)
    {
        sprintf(str, "第%d个同学：%d号同学\n", i + 1, _arr[i]);
        result += str;
    }

    QString qstr = QString::fromStdString(result);
    QMessageBox::information(NULL, "抽号结果", qstr);

    delete[] str;
}


void Lottery::show_group_result()
{

    int* size_of_each_group = new int[_group];
    int total_num = _count;

    int average = total_num / _group;
    for(int i = 0; i < _group; ++i)
    {
        size_of_each_group[i] = average;
    }

    int num_left = total_num % _group;
    while(num_left)
    {
        for(int i = 0; num_left && i < _count; ++i)
        {
            (size_of_each_group[i])++;
            num_left--;
        }
    }

    std::string return_str = "";

    int count = 0;
    char* str = new char[100];

    int _arr_index = 0;
    for(int i = _group; i > 0; --i)
    {
        std::string result = "";
        sprintf(str, "第%d组的号码有：", count + 1);
        result += str;

        while((size_of_each_group[count])--)
        {
            sprintf(str, "%d, ", _arr[_arr_index]);
            result += str;
            _arr_index++;
        }

        return_str += result + "\n";
        count++;
    }

    QString ret = QString::fromStdString(return_str);
    QMessageBox::information(NULL, "result", ret);

    delete[] size_of_each_group;
}


Lottery::~Lottery()
{
    delete[] _arr;
}

