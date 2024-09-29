#include <cstring>


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



