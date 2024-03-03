#pragma once
/*!********************************************************
*   @file Data.h
*   @author Dmitry
*   @date Декабрь  08/12/2022
*   @brief
***********************************************************/
#include "LIDPacker/maker/predefine.h"
#include "LIDPacker/maker/Brain/Dimensions.h"

#include "science/core/type.hpp"

#include <QByteArray>
#include <QVector>
#include <QMap>
#include <qvariant.h>
/*!***********************************************************
*    @brief
*    @author Dmitry
*    @version 2.0
*    @date Декабрь  08.12.2022
******************************************************************/
namespace lid {
class Data {
    /* @brief  Вся таблица в виде одномерного вектора */
    QVector<sreal_t>            ndataq;
    /* @brief  Вся таблица в виде двумерного вектора */
    QVector<QVector<sreal_t>>   ndatax2q;
    /* @brief Описание файла */
    QString	                    description_of_file;
    /* @brief  Описание таблицы */
    QString                     name_table_data;
    /* @brief  Количество данных в таблице */
    int                         Num;

public:    
    QVariant fill;

    /* @brief  Конструктор по умолчанию */
                                Data();
    /* @brief  Деструктор по умолчанию */
                                ~Data();
    /* @brief  Получения одного значения для табличных данных в конец массива */
    void                        set_datax1(const sreal_t d);
    /* @brief  Получения списка всех аргументов в виде одномерного вектора */
    void                        set_datax1(const std::vector<sreal_t>& d);
    /* @brief  Получения списка всех аргументов в виде одномерного Qвектора */
    void                        set_datax1(const QVector<sreal_t>& d);
    /* @brief  Получения списка всех аргументов в виде одномерного массива и его размер */
    void                        set_datax1(const sreal_t* d, const int size);
    /* @brief  Получения списка всех аргументов в виде одномерного массива и его размер */
    void                        set_datax2(std::vector<std::vector<sreal_t>> d);
    /* @brief  Изменение конкретного элемента массива  */
    void                        set_data(int x, int y, double d);
    /* @brief  Получение описание всего файла */
    void                        set_desc_file(const QString&);
    /* @brief Получение описания таблицы */
    void                        set_name_tdata(const QString&);
    /* @brief  Получение описание всего файла */
    void                        set_desc_file(const wchar_t*);
    /* @brief  Получение описания таблицы */
    void                        set_name_tdata(const wchar_t*);
    /* @brief  Получение конкретного элемента массива  */
    const sreal_t                   get_data(int x, int y) const;
    /* @brief  Возращение одномерного вектора с данными о таблице */
    const std::vector<sreal_t>  get_datax1_v()          const;
    /* @brief  Возращение одномерного Qвектора с данными о таблице */
    const QVector<sreal_t>      get_datax1_qv()         const;
    /* @brief  Возращение описания файла */
    const QString&              get_desc_file()          const;
    /* @brief  Возращение описание таблицы */
    const QString&              get_name_tdata()         const;
    /* @brief Возращение количество данных в таблице */
    const int                   size_datax1()            const;
    /* @brief  Возращение двумерного Qвектора с данными таблицы */
    const QVector<QVector<sreal_t>>& get_dataX2q() const;
    /* @brief  Возращение двумерного вектора с данными таблицы */
    const std::vector<std::vector<sreal_t>> get_dataX2v();
    /* @brief  Конвертакия с одномерного вектора в двумерный, нужен размер первого аргумента */
    void                        convert_n1_to_n2(int size_of_A1);
    /* @brief Конвертация с двумерного в одномерный, нужен размер первого аргумента */
    void                        convert_n2_to_n1(int size_of_A1);
    /* @brief Удаление данных */
    void                        clear_data();
    /* @brief Удаление всех данных */
    void                        clear();
    /**********************************************************/
    /* @brief Добавление по первому аргументу */
    void add_data_by_A1(int size_of_A1);
    /* @brief Добавление по АN аргументу */
    void add_data_by_AN(int pos, int size_of_AN, Dimensions* dem);
    /* @brief Изменение размера данных  в большую сторону по мервому аргументу */
    void resize_data_by_A1(int size_of_A1, QVector<int> pos_s);
    /* @brief Изменение размера данных в большую сторону по по AN аргументу*/
    void resize_data_by_AN(int pos, int size_of_AN, QVector<int> pos_s, Dimensions* dem);
    /* @brief Изменение размера данных в меньшую сторону по мервому аргументу */
    void resize_data_by_A1_d(QVector<int> pos_s);
    /* @brief Изменение размера данных в меньшую сторону по по AN аргументу*/
    void resize_data_by_AN_d(int pos, QVector<int> pos_s, Dimensions* dem);
    /* @brief Удаление данных первого аргумента */
    void remove_data_by_A1(int size_of_A1);
    /* @brief Удаление данных AN аргумента */
    void remove_data_by_AN(int pos, int size_of_AN, int plain, Dimensions* dem);
    /**********************************************************/

};
}//end namespace lid
ID_INLINE void lid::Data::set_datax1(const QVector<sreal_t>& d)
{
    ndataq = d;
}
ID_INLINE void lid::Data::set_desc_file(const QString& s )
{
    description_of_file = s;
}
ID_INLINE void lid::Data::set_name_tdata(const QString& s )
{
    name_table_data = s;
}
ID_INLINE void lid::Data::set_desc_file(const wchar_t * s)
{
    description_of_file = QString::fromWCharArray(s);
}
ID_INLINE void lid::Data::set_name_tdata(const wchar_t * s)
{
    name_table_data = QString::fromWCharArray(s);
}
ID_INLINE void lid::Data::set_data(int x, int y, double d)
{
    ndatax2q[x][y] = (sreal_t)d;
}
ID_INLINE const QString& lid::Data::get_desc_file() const
{
    return description_of_file;
}
ID_INLINE const QString& lid::Data::get_name_tdata() const
{
    return name_table_data;
}
ID_INLINE const sreal_t lid::Data::get_data(int x, int y) const
{
    return  ndatax2q[x][y];
}
ID_INLINE const QVector<sreal_t> lid::Data::get_datax1_qv() const
{
    return ndataq;
}
ID_INLINE const int lid::Data::size_datax1() const
{
    return ndataq.size();
}
ID_INLINE const QVector<QVector<sreal_t>>& lid::Data::get_dataX2q() const
{
    return ndatax2q;
}
