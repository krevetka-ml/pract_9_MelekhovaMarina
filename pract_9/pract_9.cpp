#include <iostream>

const int size = 10;
double data[size];
double original[size];

void reduce_time(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] *= 0.8; // -20%
    }
}

void increase_time(double* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] *= 1.2; // +20%
    }
}

void limit_max_time(double* data, int size)
{
    double max_time;
    std::cout << "Введите максимальное время задачи: ";
    std::cin >> max_time;
    for (int i = 0; i < size; i++)
    {
        if (data[i] > max_time)
        {
            data[i] = max_time;
        }
    }
}

void zero_long_tasks(double* data, int size)
{
    double x;
    std::cout << "Введите порог: ";
    std::cin >> x;
    for (int i = 0; i < size; i++)
    {
        if (data[i] > x)
        {
            data[i] = 0.0;
        }
    }
}

void (*processors[])(double*, int) =
{
    reduce_time,
    increase_time,
    limit_max_time,
    zero_long_tasks
};

const int count = 4;

void applyProcessing(double* data, int size, void (*processor)(double*, int))
{
    if (processor != nullptr)
    {
        processor(data, size);
    }
}

void print_array(const double* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void fill_random()
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        data[i] = rand() % 1000 / 10.0;
    }

    for (int i = 0; i < size; i++)
    {
        original[i] = data[i];
    }
    std::cout << "Массив заполнен случайными значениями\n";
}

void show_menu()
{
    std::cout << "\nМеню:\n";
    std::cout << "1.Ввести данные\n";
    std::cout << "2.Показать данные\n"; 
    std::cout << "3.Выбрать и выполнить обработку\n";
    std::cout << "4.Восстановить исходные данные\n";
    std::cout << "5.Выход\n";
    std::cout << "Выберите пункт: ";
}

void choose_process()
{
    std::cout << "\nВыберите обработку:\n";
    std::cout << "1.Уменьшить время выполнения на 20%\n";
    std::cout << "2.Увеличить время выполнения на 20%\n";
    std::cout << "3.Ограничить максимальное время задачи\n";
    std::cout << "4.Слишком долгие задачи заменить на 0\n";
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= count)
    {
        void (*processor)(double*, int) = processors[choice - 1];
        if (processor != nullptr)
        {
            applyProcessing(data, size, processor);
            std::cout << "Обработка выполнена\n";
        }
        else
        {
            std::cout << "Ошибка: указатель на функцию равен nullptr\n";
        }
    }
    else 
    {
        std::cout << "Неверный номер обработки\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;

    do 
    {
        show_menu();
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
            fill_random();
            break;

        case 2:
            std::cout << "Текущие данные:\n";
            print_array(data, size);
            break;

        case 3:
            std::cout << "Данные до обработки:\n";
            print_array(data, size);

            choose_process();

            std::cout << "Данные после обработки:\n";
            print_array(data, size);
            break;

        case 4:
        { 
            bool changed = false;
            for (int i = 0; i < size; i++)
            {
                if (data[i] != original[i])
                {
                    changed = true;
                    break;
                }
            }

            for (int i = 0; i < size; i++)
            {
                data[i] = original[i];
            }

            if (changed)
                std::cout << "Исходные данные восстановлены\n"; 
            else 
                std::cout << "Данные уже соответствуют исходным\n";
            break;
        }
        case 5:
            std::cout << "Выход из программы\n";
            break;

        default:
            std::cout << "Неверный пункт меню\n";
        }

    } while (choice != 5);

    return 0;
}