// Практика 9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

void increaseBrightness(double* data, int size) 
{
    double delta;
    cout << "Введите величину увеличения яркости: ";
    cin >> delta;
    for (int i = 0; i < size; i++) 
    {
        data[i] += delta;
    }
    cout << "Яркость увеличена на " << delta << ".\n";
}

void decreaseBrightness(double* data, int size) 
{
    double delta;
    cout << "Введите величину уменьшения яркости: ";
    cin >> delta;
    for (int i = 0; i < size; i++) 
    {
        data[i] -= delta;
    }
    cout << "Яркость уменьшена на " << delta << ".\n";
}

void invertBrightness(double* data, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        data[i] = 255.0 - data[i];
    }
    cout << "Яркость инвертирована по формуле 255 - value.\n";
}

void thresholdProcessing(double* data, int size) 
{
    double threshold;
    cout << "Введите порог: ";
    cin >> threshold;
    for (int i = 0; i < size; i++) 
    {
        if (data[i] < threshold) 
        {
            data[i] = 0.0;
        }
        else 
        {
            data[i] = 255.0;
        }
    }
    cout << "Выполнена пороговая обработка с порогом " << threshold << ".\n";
}

void applyProcessing(double* data, int size, void (*processor)(double*, int)) 
{
    if (processor != nullptr) 
    {
        processor(data, size);
    }
    else 
    {
        cout << "Ошибка: указатель на функцию равен nullptr!\n";
    }
}

void printArray(double* data, int size, const char* title) 
{
    cout << title << ":\n";
    for (int i = 0; i < size; i++) 
    {
        cout << data[i] << "  ";
        if ((i + 1) % 5 == 0) cout << "\n";
    }
    if (size % 5 != 0) cout << "\n";
    cout << "\n";
}

void inputArray(double* data, int size) 
{
    cout << "Введите " << size << " значений яркости (0..255):\n";
    for (int i = 0; i < size; i++) 
    {
        cout << "data[" << i << "] = ";
        cin >> data[i];
    }
}

void copyArray(double* source, double* dest, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        dest[i] = source[i];
    }
}

int main()
{
    setlocale(NULL, "Russian");

    const int SIZE = 15;

    double originalData[SIZE] =
    {
         10.0,  50.0, 120.0, 200.0, 240.0,
         30.0,  80.0, 160.0, 255.0,   0.0,
         95.0, 175.0, 220.0,  45.0, 130.0
    };

    double data[SIZE];
    copyArray(originalData, data, SIZE);

    void (*processors[])(double*, int)
    {
        increaseBrightness,
            decreaseBrightness,
            invertBrightness,
            thresholdProcessing
    };
    const int PROCESSOR_COUNT = 4;

    int choice = 0;

    while (true)
    {
        cout << "\nМеню яркости:\n";
        cout << "1. Ввести данные\n";
        cout << "2. Показать данные\n";
        cout << "3. Выбрать и выполнить обработку\n";
        cout << "4. Восстановить исходные данные\n";
        cout << "5. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            inputArray(data, SIZE);
            copyArray(data, originalData, SIZE);
            cout << "Данные введены.\n";
            printArray(data, SIZE, "Текущий массив");
            break;
        }

        case 2:
        {
            printArray(data, SIZE, "Текущий массив");
            break;
        }

        case 3:
        {
            cout << "\nДоступные обработки\n";
            cout << "1. Увеличить яркость\n";
            cout << "2. Уменьшить яркость\n";
            cout << "3. Инвертировать яркость (255 - value)\n";
            cout << "4. Пороговая обработка (ниже порога - 0, иначе - 255)\n";
            cout << "Выберите обработку: ";

            int opChoice;
            cin >> opChoice;

            if (opChoice < 1 || opChoice > PROCESSOR_COUNT)
            {
                cout << "Неверный номер обработки!\n";
                break;
            }

            void (*selectedProcessor)(double*, int) = processors[opChoice - 1];

            printArray(data, SIZE, "Массив ДО обработки");

            applyProcessing(data, SIZE, selectedProcessor);

            printArray(data, SIZE, "Массив ПОСЛЕ обработки");
            break;
        }

        case 4:
        {
            copyArray(originalData, data, SIZE);
            cout << "Исходные данные восстановлены.\n";
            printArray(data, SIZE, "Текущий массив");
            break;
        }

        case 5:
        {
            cout << "Выход из программы.\n";
            return 0;
        }

        default:
        {
            cout << "Неверный пункт меню!\n";
            break;
        }
        }
    }
        return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
