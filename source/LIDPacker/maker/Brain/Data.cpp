/*!
********************************************************
* 
*   @file   Data.cpp
*   @author Kalikin D.M.
*   @date   Декабрь  08/12/2022
*   @brief  Реализация методов Data.h
* 
**********************************************************
*/
#include "LIDPacker/maker/Brain/Data.h"
#include <qexception.h>
namespace lid {

Data::Data()
    : Num(0)
    , description_of_file(" ")
    , name_table_data(" ")
    , fill(0)
{

}
Data::~Data()
{
}

void Data::set_datax1(const sreal_t d) {
    ndataq.push_back(d);
}
void Data::set_datax1(const sreal_t* d, const int size) {
    for (int i = 0; i < size; ++i)
        ndataq.push_back(d[i]);
}
void Data::set_datax1(const std::vector<sreal_t>& d)
{
    ndataq = QVector<sreal_t>(d.begin(), d.end());
}
void Data::set_datax2(std::vector<std::vector<sreal_t>> d)
{
    int si = d.size();
    int sj = d[0].size();
    ndatax2q.clear();
    ndatax2q.resize(si);
    for (int i = 0; i < si; ++i)
        for (int j = 0; j < sj; ++j)
            ndatax2q[i].push_back(d[i][j]);
}

const std::vector<sreal_t> Data::get_datax1_v() const
{
    return std::vector<sreal_t>(ndataq.begin(), ndataq.end());
}
const std::vector<std::vector<sreal_t>> Data::get_dataX2v()
{
    std::vector<std::vector<sreal_t>> v;
    int si = ndatax2q.size();
    int sj = ndatax2q[0].size();
    v.resize(si);
    for (int i = 0; i < si; ++i)
        for (int j = 0; j < sj; ++j)
            v[i].push_back(ndatax2q[i][j]);
    return v;
}

void Data::convert_n1_to_n2(int size_of_A1)
{
    ndatax2q.clear();
    int k = 0;
    int s = ndataq.size() / size_of_A1;
    ndatax2q.resize(s);
    for (int i = 0; i < s; ++i)
        for (int j = 0; j < size_of_A1; ++j)
        {
            ndatax2q[i].push_back(ndataq[k]);
            ++k;
        }
}
void Data::convert_n2_to_n1(int size_of_A1)
{
    ndataq.clear();
    int k = 0;
    int s = ndatax2q.size();
    for (int i = 0; i < s; ++i)
        for (int j = 0; j < size_of_A1; ++j)
        {
            ndataq.push_back(ndatax2q[i][j]);
        }
}
void Data::clear_data()
{
    ndataq.clear();
    ndatax2q.clear();
}
void Data::clear()
{
    clear_data();
    description_of_file.clear();
    name_table_data.clear();
    Num = 0;
}
void Data::add_data_by_A1(int size_of_A1)
{
    ndatax2q.resize(1);
    for (int i = 0; i < 1; ++i)
        for (int j = 0; j < size_of_A1; ++j)
                ndatax2q[i].push_back(fill.toDouble());
}
void Data::add_data_by_AN(int pos, int size_of_AN, Dimensions* dem)
{
    QVector<QVector<sreal_t>>::iterator it;
    QVector<sreal_t> tmp_vector;
    unsigned int AF;
    std::vector<int> DF;


    int ord = pos;
    int advnc = 0;
    int advnc_count = 0;
    int itmp = ndatax2q.size() * size_of_AN;
    int jtmp = ndatax2q[0].size();
    bool was = false;

    for (size_t i = 0; i < itmp; ++i) {
        it = ndatax2q.begin();
        for (size_t j = 0; j < jtmp; ++j) {
            DF = dem->ArgsByXY(j, i);
            if (DF[ord]) {
                tmp_vector.push_back(fill.toDouble());
                was = true;
            }
        }
        if (was) {
            std::advance(it, advnc_count);
            ndatax2q.insert(it, tmp_vector);
        }

        advnc_count++;
        tmp_vector.clear();
        was = false;
    }
}
void Data::resize_data_by_A1(int size_of_A1, QVector<int> pos_s)
{
    int MainSize = ndatax2q.size();
    int k = 0;
    QVector<sreal_t>::iterator it;
    /**/
    //std::vector<int> pos_ = pos_s.toStdVector();
    /**/
    for (int i = 0; i < MainSize; ++i)
    {
        k = 0;
        for (int j = 0; j < size_of_A1; ++j)
        {
            if (pos_s.at(k) == j)
            {
                it = ndatax2q[i].begin();
                std::advance(it, j);
                ndatax2q[i].insert(it, fill.toDouble());
                ++k;
            }
            if (k == pos_s.size())
                break;
        }
    }
}
void Data::resize_data_by_AN(int pos, int size_of_AN, QVector<int> pos_s, Dimensions* dem)
{
    QVector<QVector<sreal_t>>::iterator it;
    QVector<sreal_t> tmp_vector;
    QVector<int> AF = pos_s;
    std::vector<int> DF;


    int ord = pos;
    int advnc = 0;
    int advnc_count = 0;
    int arg_count = 0;
    int itmp = size_of_AN;
    int jtmp = ndatax2q[0].size();
    bool was = false;
    bool avoidF = false;

    for (int i = 0; i < itmp; ++i)
    {
        for (int j = 0; j < jtmp; ++j)
        {
            DF = dem->ArgsByXY(j, i);
            for (int k = 0; k < AF.size(); ++k)
            {
                if (AF.at(k) == DF[ord])
                {
                    avoidF = true;
                    break;
                }
                else
                    avoidF = false;
            }

            if (avoidF) 
            {
                tmp_vector.push_back(fill.toDouble());
                was = true;
            }
        }
        if (was) 
        {
            it = ndatax2q.begin();
            std::advance(it, advnc_count);
            ndatax2q.insert(it, tmp_vector);
            ++advnc_count;
        }
        else
            ++advnc_count;

        tmp_vector.clear();
        was = false;
    }
}
void Data::resize_data_by_A1_d(QVector<int> pos_s)
{
    int MainSize = ndatax2q.size();
    int size_of_A1 = ndatax2q[0].size();
    QVector<sreal_t>::iterator it;
    unsigned int k = 0;
    for (int i = 0; i < MainSize; ++i) {
        k = 0;
        for (int j = 0; j < size_of_A1; ++j) {
            if (pos_s.at(k) == j) {
                it = ndatax2q[i].begin();
                std::advance(it, j - k);
                ndatax2q[i].erase(it);
                ++k;
            }
            if (k == pos_s.size())
                break;
        }
    }
}
void Data::resize_data_by_AN_d(int pos, QVector<int> pos_s, Dimensions* dem)
{
    QVector<QVector<sreal_t>>::iterator it;
    QVector<sreal_t> tmp_vector;
    QVector<int> AF = pos_s;
    std::vector<int> DF;

    int ord = pos;
    int advnc = 0;
    int advnc_count = 0;
    int arg_count = 0;
    int itmp = ndatax2q.size();
    int jtmp = ndatax2q[0].size();
    bool was = false;
    bool avoidF = false;

    for (int i = 0; i < itmp; ++i) 
    {
        it = ndatax2q.begin();
        for (int j = 0; j < jtmp; ++j) 
        {
            DF = dem->ArgsByXY(j, i);
            for (int k = 0; k < AF.size(); ++k)
            {
                if (AF.at(k) == DF[ord]) 
                {
                    avoidF = true;
                    break;
                }
                else 
                    avoidF = false;
            }
            if (avoidF)
                was = true;
        }
        if (was) 
        {
            std::advance(it, advnc_count);
            ndatax2q.erase(it);
        }
        else
            ++advnc_count;

        was = false;
    }

}
void Data::remove_data_by_A1(int size_of_A1)
{
    /*PRO*/
}
void Data::remove_data_by_AN(int pos, int size_of_AN, int plain, Dimensions* dem)
{
    QVector<QVector<sreal_t>>::iterator it;
    std::vector<int> DF;
    int ord = pos;
    int advnc_count = 0;
    int itmp = ndatax2q.size();
    int jtmp = ndatax2q[0].size();
    bool was = false;
    bool avoidF = false;
    int k = 0;

    for (int i = 0; i < itmp; ++i) 
    {
        it = ndatax2q.begin();
        for (int j = 0; j < jtmp; ++j) 
        {
            DF = dem->ArgsByXY(j, i);

            if (DF[ord] != plain)
                avoidF = true;
            else 
                avoidF = false;

            if (avoidF) 
                was = true;

        }
        if (was) 
        {
            std::advance(it, advnc_count);
            ndatax2q.erase(it);
            k++;
        }
        else
            ++advnc_count;

        was = false;
    }
}
/* PRIVATE */
}//end namespace lid