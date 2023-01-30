#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>
#include <QtAlgorithms>

class Function {
 private:

    // Имя
    QString name = "";
    // Тип
    QString type = "";
    // Количество аргументов
    int n_arguments = 0;
    // Аргументы
    QString *arguments = nullptr;
    // Комментарий к функции
    QString comment = "";

 public:

    // Конструктор по умолчанию
    Function();

    // Конструктор
    explicit Function(QString name, QString type, QString comment, int n);

    // Конструктор копирования
    Function(const Function &da);

    // Оператор копирования
    Function &operator=(const Function &da);

    // Конструктор перемещения
    Function(Function &&da) noexcept;

    // Оператор перемещения
    Function &operator=(Function &&da) noexcept;

    // Деструктор
    virtual ~Function();

    // Оператор получения элемента по индексу I
    QString &operator[](int i);

    // Очистка массива
    void clear();

    // Оператор приведения к типу bool
    explicit operator bool();

    // Установка имени
    void setName(QString arg);

    // Получение имени
    const QString &getName();

    // Установка типа
    void setType(QString arg);

    // Получение имени
    const QString &getType();

    // Установка комментария
    void setComment(QString arg);

    // Получение комментария
    const QString &getComment();

    // Получение количества аргументов
    const int &getNArguments();

    // Установка числа аргументов
    void setNArguments(int n);

    friend void swap(Function &first, Function &second) noexcept;

    // Класс итератора по аргументам
    class iterator {
     public:
        QString *i;
        typedef std::random_access_iterator_tag  iterator_category;
        typedef ptrdiff_t  difference_type;
        typedef QString value_type;
        typedef QString *pointer;
        typedef QString &reference;

        inline iterator() : i(nullptr) {}
        inline explicit iterator(QString *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline QString &operator*() const { return *i; }
        inline QString *operator->() const { return i; }
        inline QString &operator[](int j) const { return i[j]; }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline const iterator operator++(int) { QString *n = i; ++i; return iterator(n); }
        inline iterator &operator--() { i--; return *this; }
        inline const iterator operator--(int) { QString *n = i; i--; return iterator(n); }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return int(i - j.i); }
    };

    inline typename Function::iterator begin() { return iterator(&arguments[0]); }
    inline typename Function::iterator end() { return iterator(&arguments[n_arguments]); }
};

#endif // FUNCTION_H
