#include <iostream>
using namespace std;

//задание 1

//функция распределения динамической памяти
int* allocateMemory(int size) {
    return new int[size];  //выделяем память в куче
}

//функция инициализации динамического массива
void initializeArray(int* arr, int size) {
    cout << "Введите " << size << " элементов массива: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
}

//функция печати динамического массива
void printArray(int* arr, int size) {
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }

    cout << "Массив [" << size << "]: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//функция удаления динамического массива
void deleteArray(int* arr) {
    delete[] arr;
}

//функция добавления элемента в конец массива
int* addElement(int* arr, int& size, int element) {
    int* newArr = new int[size + 1];

    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    newArr[size] = element;
    size++;

    delete[] arr;
    return newArr;
}

//функция вставки элемента по указанному индексу
int* insertElement(int* arr, int& size, int index, int element) {
    if (index < 0 || index > size) {
        cout << "Некорректный индекс!" << endl;
        return arr;
    }

    int* newArr = new int[size + 1];

    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }

    newArr[index] = element;

    for (int i = index; i < size; i++) {
        newArr[i + 1] = arr[i];
    }

    size++;
    delete[] arr;
    return newArr;
}

//функция удаления элемента по указанному индексу
int* removeElement(int* arr, int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "Некорректный индекс!" << endl;
        return arr;
    }

    int* newArr = new int[size - 1];

    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }

    for (int i = index + 1; i < size; i++) {
        newArr[i - 1] = arr[i];
    }

    size--;
    delete[] arr;
    return newArr;
}

//задание 2

//функция проверяет, является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//функция удаления всех простых чисел из массива
int* removePrimes(int* arr, int size, int& newSize) {
    //считаем количество непростых чисел
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (!isPrime(arr[i])) {
            count++;
        }
    }

    newSize = count;

    int* newArr = new int[count];
    int index = 0;

    for (int i = 0; i < size; i++) {
        if (!isPrime(arr[i])) {
            newArr[index] = arr[i];
            index++;
        }
    }

    return newArr;
}

//задание 3

//функция разделения статического массива на три динамических массива
void separateArray(int* staticArr, int size,
    int*& positive, int& posCount,
    int*& negative, int& negCount,
    int*& zero, int& zeroCount) {

    // 1.подсчет количества элементов каждого типа
    posCount = 0;
    negCount = 0;
    zeroCount = 0;

    for (int i = 0; i < size; i++) {
        if (staticArr[i] > 0) {
            posCount++;
        }
        else if (staticArr[i] < 0) {
            negCount++;
        }
        else {
            zeroCount++;
        }
    }

    // 2.выделение памяти для каждого массива
    positive = new int[posCount];
    negative = new int[negCount];
    zero = new int[zeroCount];

    // 3.заполнение массивов
    int posIdx = 0, negIdx = 0, zeroIdx = 0;

    for (int i = 0; i < size; i++) {
        if (staticArr[i] > 0) {
            positive[posIdx] = staticArr[i];
            posIdx++;
        }
        else if (staticArr[i] < 0) {
            negative[negIdx] = staticArr[i];
            negIdx++;
        }
        else {
            zero[zeroIdx] = staticArr[i];
            zeroIdx++;
        }
    }
}

//основ. программа

int main() {
    setlocale(LC_ALL, "ru");
    cout << "задание 1" << endl;

    //динамический массив 
    int size = 5;
    int* arr = allocateMemory(size);

    cout << "Инициализация массива:" << endl;
    initializeArray(arr, size);
    printArray(arr, size);

    cout << "\nДобавление элемента 99 в конец:" << endl;
    arr = addElement(arr, size, 99);
    printArray(arr, size);

    cout << "\nВставка элемента 777 на позицию 2:" << endl;
    arr = insertElement(arr, size, 2, 777);
    printArray(arr, size);

    cout << "\nУдаление элемента на позиции 3:" << endl;
    arr = removeElement(arr, size, 3);
    printArray(arr, size);

    cout << "\nзадание 2" << endl;

    int testSize = 8;
    int* testArr = new int[testSize] {1, 2, 3, 4, 5, 6, 7, 8};

    cout << "Исходный массив: ";
    printArray(testArr, testSize);

    int newSize;  //переменная для хранения размера нового массива
    int* noPrimesArr = removePrimes(testArr, testSize, newSize);

    cout << "Массив без простых чисел: ";
    printArray(noPrimesArr, newSize);

    //память
    delete[] testArr;
    delete[] noPrimesArr;

    cout << "\nзадание 3" << endl;

    int staticArr[] = { 5, -3, 0, 8, -1, 0, 2, -7, 4 };
    int staticSize = sizeof(staticArr) / sizeof(staticArr[0]);

    cout << "Исходный статический массив: ";
    for (int i = 0; i < staticSize; i++) {
        cout << staticArr[i] << " ";
    }
    cout << endl;

    int* positiveArr;
    int* negativeArr;
    int* zeroArr;
    int posCount, negCount, zeroCount;

    //функция разделения
    separateArray(staticArr, staticSize,
        positiveArr, posCount,
        negativeArr, negCount,
        zeroArr, zeroCount);

    //результаты
    cout << "Положительные элементы [" << posCount << "]: ";
    for (int i = 0; i < posCount; i++) {
        cout << positiveArr[i] << " ";
    }
    cout << endl;

    cout << "Отрицательные элементы [" << negCount << "]: ";
    for (int i = 0; i < negCount; i++) {
        cout << negativeArr[i] << " ";
    }
    cout << endl;

    cout << "Нулевые элементы [" << zeroCount << "]: ";
    for (int i = 0; i < zeroCount; i++) {
        cout << zeroArr[i] << " ";
    }
    cout << endl;

    //очистка
    deleteArray(arr);
    delete[] positiveArr;
    delete[] negativeArr;
    delete[] zeroArr;

    cout << "\nПрограмма закончена" << endl;
    return 0;
}