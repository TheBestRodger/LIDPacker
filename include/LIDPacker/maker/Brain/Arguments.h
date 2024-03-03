/*!
********************************************************
* 
*   @file   Arguments.cpp
*   @author Kalikin D.M. - dep.106
*   @date   Декабрь  28/06/2023
*   @brief  ~~~~~~~~~~
* 
**********************************************************
*/
#ifndef __LIST_H__
#define __LIST_H__
#include "Argument.h"
/*
===============================================================================

	List template
	Does not allocate memory until the first item is added.

===============================================================================
*/

namespace {
	/*
	================
	idListSortCompare<type>
	================
	*/
#ifdef __INTEL_COMPILER
	// the intel compiler doesn't do the right thing here
	template< class type >
	ID_INLINE int idListSortCompare(const type* a, const type* b) {
		assert(0);
		return 0;
	}
#else
	template< class type >
	ID_INLINE int idListSortCompare(const type* a, const type* b) {
		return *a - *b;
	}
#endif

	/*
	================
	idListNewElement<type>
	================
	*/
	template< class type >
	ID_INLINE type* idListNewElement(void) {
		return new type;
	}

	/*
	================
	idSwap<type>
	================
	*/
	template< class type >
	ID_INLINE void idSwap(type& a, type& b) {
		type c = a;
		a = b;
		b = c;
	}
}
namespace lid {
	/*!*****************************************************************************
		@brief Удобный и быстрый контейнер типа список
		@author ...
	*******************************************************************************/
template< class type >
class idList {
public:

	typedef int		cmp_t(const type*, const type*);
	typedef type	new_t(void);

					idList(int newgranularity = 16);
					~idList(void);

	void			Clear(void);									// clear the list
	int				Num(void) const;								// returns number of elements in list
	int				NumAllocated(void) const;						// returns number of elements allocated for

	void			SetGranularity(int newgranularity);				// set new granularity
	int				GetGranularity(void) const;						// get the current granularity

	size_t			Allocated(void) const;							// returns total size of allocated memory
	size_t			Size(void) const;								// returns total size of allocated memory including size of list type
	size_t			MemoryUsed(void) const;							// returns size of the used elements in the list

	idList<type>& operator=(const idList<type>& other);
	const type& operator[](int index) const;
	type& operator[](int index);

	void			Condense(void);									// resizes list to exactly the number of elements it contains
	void			Resize(int newsize);							// resizes list to the given number of elements
	void			Resize(int newsize, int newgranularity);		// resizes list and sets new granularity
	void			SetNum(int newnum, bool resize = true);			// set number of elements in list and resize to exactly this number if necessary
	void			AssureSize(int newSize);						// assure list has given number of elements, but leave them uninitialized
	void			AssureSize(int newSize, const type& initValue);	// assure list has given number of elements and initialize any new elements
	void			AssureSizeAlloc(int newSize, new_t* allocator);	// assure the pointer list has the given number of elements and allocate any new elements


	int				Append(const type& obj);						// append element
	int				Insert(const type& obj, int index = 0);			// insert the element at the given index
	int				FindIndex(const type& obj) const;				// find the index for the given element
	type*			Find(type const& obj) const;					// find pointer to the given element
	int				FindNull(void) const;							// find the index for the first NULL pointer in the list
	int				IndexOf(const type* obj) const;					// returns the index for the pointer to an element in the list
	bool			RemoveIndex(int index);							// remove the element at the given index
	bool			Remove(const type& obj);						// remove the element
	virtual void	Swap(idList<type>& other);						// swap the contents of the lists
	void			DeleteContents(bool clear);						// delete the contents of the list

private:;
		int				num;
		int				size;
		int				granularity;
protected:
	type* list;
};
#pragma region meth_idList
/*
================
idList<type>::idList( int )
================
*/
template< class type >
ID_INLINE idList<type>::idList(int newgranularity) {
	assert(newgranularity > 0);

	list = NULL;
	granularity = newgranularity;
	Clear();
}

/*
================
idList<type>::~idList<type>
================
*/
template< class type >
ID_INLINE idList<type>::~idList(void) {
	Clear();
}

/*
================
idList<type>::Clear

Frees up the memory allocated by the list.  Assumes that type automatically handles freeing up memory.
================
*/
template< class type >
ID_INLINE void idList<type>::Clear(void) {
	if (list) {
		delete[] list;
	}

	list = nullptr;
	num  = 0;
	size = 0;
}

/*
================
idList<type>::DeleteContents
================
*/
template< class type >
ID_INLINE void idList<type>::DeleteContents(bool clear) {
	int i;

	for (i = 0; i < num; i++) {
		delete list[i];
		list[i] = NULL;
	}

	if (clear) {
		Clear();
	}
	else {
		memset(list, 0, size * sizeof(type));
	}
}

/*
================
idList<type>::Allocated
================
*/
template< class type >
ID_INLINE size_t idList<type>::Allocated(void) const {
	return size * sizeof(type);
}

/*
================
idList<type>::Size
================
*/
template< class type >
ID_INLINE size_t idList<type>::Size(void) const {
	return sizeof(idList<type>) + Allocated();
}

/*
================
idList<type>::MemoryUsed
================
*/
template< class type >
ID_INLINE size_t idList<type>::MemoryUsed(void) const {
	return num * sizeof(*list);
}

/*
================
idList<type>::Num
================
*/
template< class type >
ID_INLINE int idList<type>::Num(void) const {
	return num;
}

/*
================
idList<type>::NumAllocated
================
*/
template< class type >
ID_INLINE int idList<type>::NumAllocated(void) const {
	return size;
}

/*
================
idList<type>::SetNum
================
*/
template< class type >
ID_INLINE void idList<type>::SetNum(int newnum, bool resize) {
	assert(newnum >= 0);
	if (resize || newnum > size) {
		Resize(newnum);
	}
	num = newnum;
}

/*
================
idList<type>::SetGranularity
================
*/
template< class type >
ID_INLINE void idList<type>::SetGranularity(int newgranularity) {
	int newsize;

	assert(newgranularity > 0);
	granularity = newgranularity;

	if (list) {
		// resize it to the closest level of granularity
		newsize = num + granularity - 1;
		newsize -= newsize % granularity;
		if (newsize != size) {
			Resize(newsize);
		}
	}
}

/*
================
idList<type>::GetGranularity
================
*/
template< class type >
ID_INLINE int idList<type>::GetGranularity(void) const {
	return granularity;
}

/*
================
idList<type>::Condense
================
*/
template< class type >
ID_INLINE void idList<type>::Condense(void) {
	if (list) {
		if (num) {
			Resize(num);
		}
		else {
			Clear();
		}
	}
}

/*
================
idList<type>::Resize
================
*/
template< class type >
ID_INLINE void idList<type>::Resize(int newsize) {
	type* temp;
	int		i;

	assert(newsize >= 0);

	// free up the list if no data is being reserved
	if (newsize <= 0) {
		Clear();
		return;
	}

	if (newsize == size) {
		// not changing the size, so just exit
		return;
	}

	temp = list;
	size = newsize;
	if (size < num) {
		num = size;
	}

	// copy the old list into our new one
	list = new type[size];
	for (i = 0; i < num; i++) {
		list[i] = temp[i];
	}

	// delete the old list if it exists
	if (temp) {
		delete[] temp;
	}
}

/*
================
idList<type>::Resize
================
*/
template< class type >
ID_INLINE void idList<type>::Resize(int newsize, int newgranularity) {
	type* temp;
	int		i;

	assert(newsize >= 0);

	assert(newgranularity > 0);
	granularity = newgranularity;

	// free up the list if no data is being reserved
	if (newsize <= 0) {
		Clear();
		return;
	}

	temp = list;
	size = newsize;
	if (size < num) {
		num = size;
	}

	// copy the old list into our new one
	list = new type[size];
	for (i = 0; i < num; i++) {
		list[i] = temp[i];
	}

	// delete the old list if it exists
	if (temp) {
		delete[] temp;
	}
}

/*
================
idList<type>::AssureSize
================
*/
template< class type >
ID_INLINE void idList<type>::AssureSize(int newSize) {
	int newNum = newSize;

	if (newSize > size) {

		if (granularity == 0) {	// this is a hack to fix our memset classes
			granularity = 16;
		}

		newSize += granularity - 1;
		newSize -= newSize % granularity;
		Resize(newSize);
	}

	num = newNum;
}

/*
================
idList<type>::AssureSize
================
*/
template< class type >
ID_INLINE void idList<type>::AssureSize(int newSize, const type& initValue) {
	int newNum = newSize;

	if (newSize > size) {

		if (granularity == 0) {	// this is a hack to fix our memset classes
			granularity = 16;
		}

		newSize += granularity - 1;
		newSize -= newSize % granularity;
		num = size;
		Resize(newSize);

		for (int i = num; i < newSize; i++) {
			list[i] = initValue;
		}
	}

	num = newNum;
}

/*
================
idList<type>::AssureSizeAlloc
================
*/
template< class type >
ID_INLINE void idList<type>::AssureSizeAlloc(int newSize, new_t* allocator) {
	int newNum = newSize;

	if (newSize > size) {

		if (granularity == 0) {	// this is a hack to fix our memset classes
			granularity = 16;
		}

		newSize += granularity - 1;
		newSize -= newSize % granularity;
		num = size;
		Resize(newSize);

		for (int i = num; i < newSize; i++) {
			list[i] = (*allocator)();
		}
	}

	num = newNum;
}

/*
================
idList<type>::operator=
================
*/
template< class type >
ID_INLINE idList<type>& idList<type>::operator=(const idList<type>& other) {
	int	i;

	Clear();

	num = other.num;
	size = other.size;
	granularity = other.granularity;

	if (size) {
		list = new type[size];
		for (i = 0; i < num; i++) {
			list[i] = other.list[i];
		}
	}

	return *this;
}

/*
================
idList<type>::operator[] const
================
*/
template< class type >
ID_INLINE const type& idList<type>::operator[](int index) const {
	assert(index >= 0);
	assert(index < num);

	return list[index];
}

/*
================
idList<type>::operator[]
================
*/
template< class type >
ID_INLINE type& idList<type>::operator[](int index) {
	assert(index >= 0);
	assert(index < num);

	return list[index];
}

/*
================
idList<type>::Append
================
*/
template< class type >
ID_INLINE int idList<type>::Append(type const& obj) {
	if (!list) {
		Resize(granularity);
	}

	if (num == size) {
		int newsize;

		if (granularity == 0) {	// this is a hack to fix our memset classes
			granularity = 16;
		}
		newsize = size + granularity;
		Resize(newsize - newsize % granularity);
	}

	list[num] = obj;
	num++;

	return num - 1;
}


/*
================
idList<type>::Insert
================
*/
template< class type >
ID_INLINE int idList<type>::Insert(type const& obj, int index) {
	if (!list) {
		Resize(granularity);
	}

	if (num == size) {
		int newsize;

		if (granularity == 0) {	// this is a hack to fix our memset classes
			granularity = 16;
		}
		newsize = size + granularity;
		Resize(newsize - newsize % granularity);
	}

	if (index < 0) {
		index = 0;
	}
	else if (index > num) {
		index = num;
	}
	for (int i = num; i > index; --i) {
		list[i] = list[i - 1];
	}
	num++;
	list[index] = obj;
	return index;
}


/*
================
idList<type>::FindIndex
================
*/
template< class type >
ID_INLINE int idList<type>::FindIndex(type const& obj) const {
	int i;

	for (i = 0; i < num; i++) {
		if (list[i] == obj) {
			return i;
		}
	}

	// Not found
	return -1;
}

/*
================
idList<type>::Find
================
*/
template< class type >
ID_INLINE type* idList<type>::Find(type const& obj) const {
	int i;

	i = FindIndex(obj);
	if (i >= 0) {
		return &list[i];
	}

	return NULL;
}

/*
================
idList<type>::FindNull
================
*/
template< class type >
ID_INLINE int idList<type>::FindNull(void) const {
	int i;

	for (i = 0; i < num; i++) {
		if (list[i] == NULL) {
			return i;
		}
	}

	// Not found
	return -1;
}

/*
================
idList<type>::IndexOf
================
*/
template< class type >
ID_INLINE int idList<type>::IndexOf(type const* objptr) const {
	int index;

	index = objptr - list;

	assert(index >= 0);
	assert(index < num);

	return index;
}

/*
================
idList<type>::RemoveIndex
================
*/
template< class type >
ID_INLINE bool idList<type>::RemoveIndex(int index) {
	int i;

	assert(list != NULL);
	assert(index >= 0);
	assert(index < num);

	if ((index < 0) || (index >= num)) {
		return false;
	}

	
	for (i = index; i < num; i++) {
		list[i] = list[i + 1];
	}
	num--;
	return true;
}

/*
================
idList<type>::Remove
================
*/
template< class type >
ID_INLINE bool idList<type>::Remove(type const& obj) {
	int index;

	index = FindIndex(obj);
	if (index >= 0) {
		return RemoveIndex(index);
	}

	return false;
}

/*
================
idList<type>::Swap

Swaps the contents of two lists
================
*/
template< class type >
ID_INLINE void idList<type>::Swap(idList<type>& other) {
	idSwap(num, other.num);
	idSwap(size, other.size);
	idSwap(granularity, other.granularity);
	idSwap(list, other.list);
}
#pragma endregion
/*!*****************************************************************************
	@brief Контейнер аргументов
	@author Kalikin D.M.
	@version 1.0
	@date 2023/06/28

	Нужен для удобной работы с аргументами, унаследован от списка
*******************************************************************************/
class idArguments : public idList<Argument>
{
public:
	/* @brief Конструктор по умолчанию, инициализирует sum = 1. */
									idArguments();

	/* @brief Установка конкретному аргументу (pos) его имя. */
	void							set_name(const int pos, const char* name);
	/* @brief Установка конкретному аргументу (pos) его имя. */
	void							set_name(const int pos, const QString name);
	/* @brief Установка конкретному аргументу (pos) его имя. */
	void							set_name(const int pos, const std::string name);

	/* @brief Установка конкретному аргументу (pos) его описание. */
	void							set_description(const int pos, const char* desc);
	/* @brief Установка конкретному аргументу (pos) его описание. */
	void							set_description(const int pos, const std::string desc);
	/* @brief Установка конкретному аргументу (pos) его описание. */
	void							set_description(const int pos, const QString desc);

	/* @brief Установка конкретному аргументу (pos), одно значение в конец других. */
	void							set_scale(const int pos, const sreal_t arg);

	/* @brief Установка\Изменение конкретному аргументу (pos), его плоскость. */
	void							set_plain(const int pos, const int p);

	/* @brief Тип сортировки аргумента возраст./убыв. */
	void							set_sort_policy(const int pos, const bool p);


	/* @brief Удаление у конкретного аргумента (pos), последнее значение. */
	void							remove_last_scale(const int pos);

	/* @brief Удаление у конкретного аргумента (pos), все значения */
	void							remove_scales(const int pos);

	/* @brief Удаление у конкретного аргумента (pos), конкретное значение*/
	void							remove_scale(const int pos, const int pos_scale);

	/* @brief Установка конкретному аргументу (pos), все значения */
	void							set_full_scale(const int pos, const sreal_t* arg, const int size);

	/* @brief Установка конкретному аргументу (pos), все значения */
	void							set_full_scale_v(const int pos, const QVector<sreal_t>& arg);

	/* @brief Перестановка двух аргументов по имени */
	void							swap_by_name(const QString f, const QString s);

	/* @brief Перестановка двух аргументов по имени */
	void							swap(const int A1, const int A2);;

	/* @brief Перемещение аргумнтов откуда и куда */
	void							move_to(int what_move, int where);

	/* @brief Соритировка аргумента */
	void							sort_argument(const int pos);

	/* @brief Получение имя конкретного аргумента */
	const QString					get_name(const int pos) const;

	/* @brief Получение описания конкретного аргумента */
	const QString					get_description(const int pos) const;

	/* @brief Получение всех значений конкретного аргумента */
	const QVector<sreal_t>			get_full_scale_v(const int pos) const;

	/* @brief Получение плоскости аргумента */
	const int						get_plain(const int pos) const;

	/* @brief Тип сортировки аргумента возраст./убыв. */
	const bool						get_sort_policy(const int pos) const;

	/* @brief Получение произведение всех аргументов */
	const int						get_sum()	const;

	/* @brief Получения максимального значения шкалы у аргумента  */
	const sreal_t					get_max_scale(int pos)	const;

	/* @brief Получения минимальноьго значения шкалы у аргумента  */
	const sreal_t					get_min_scale(int pos)	const;

	/* @brief Получегтя всех длинн аргументов по порядку*/
	const std::vector<int>			get_Sizes() const;

	/* @brief Получение позиции по имени */
	const int						get_pos(const QString nm) const;

	/* @brief Получение всех аргументов с их значениями */
	const QMap<int, QVector<sreal_t>>	get_AllValues() const;

	/* @brief Вовзращает максимальную длинну аргумента */
	const int						max_length_arg() const;

	/* @brief Получение произведение аргументов без первого */
	const int						amount_rows() const;

	/* @brief Позиция аргумента по имени */
	const int						position_by_name(QString nameofargument);

};
ID_INLINE void  idArguments::set_name(const int pos, const char* name)
{
	list[pos].set_name(name);
}
ID_INLINE void	idArguments::set_name(const int pos, const std::string name)
{
	list[pos].set_description(name);
}
ID_INLINE void	idArguments::set_name(const int pos, const QString name)
{
	list[pos].set_description(name);
}
ID_INLINE void	idArguments::set_description(const int pos, const std::string desc)
{
	list[pos].set_description(desc);
}
ID_INLINE void	idArguments::set_description(const int pos, const QString desc)
{
	list[pos].set_description(desc);
}
ID_INLINE void  idArguments::set_description(const int pos, const char* desc)
{
	list[pos].set_description(desc);
}
ID_INLINE void  idArguments::set_scale(const int pos, const sreal_t arg)
{
	list[pos].set_scale(arg);
}
ID_INLINE void idArguments::set_plain(const int pos, const int p)
{
	list[pos].set_plain(p);
}
ID_INLINE void idArguments::set_sort_policy(const int pos, const bool p)
{
	list[pos].set_policy_sort(p);
}
ID_INLINE void  idArguments::remove_last_scale(const int pos)
{
	list[pos].remove_last_scale();
}
ID_INLINE void  idArguments::remove_scales(const int pos)
{
	list[pos].remove_scales();
}
ID_INLINE void  idArguments::remove_scale(const int pos, const int pos_scale)
{
	list[pos].remove_scale(pos_scale);
}
ID_INLINE void  idArguments::set_full_scale(const int pos, const sreal_t* arg, const int size)
{
	list[pos].set_full_scale(arg, size);
}
ID_INLINE void  idArguments::set_full_scale_v(const int pos, const QVector<sreal_t>& arg)
{
	list[pos].set_full_scale_v(arg);
}
ID_INLINE void idArguments::sort_argument(const int pos)
{
	list[pos].sort_argument();
}
ID_INLINE const QString   idArguments::get_name(const int pos) const
{
	return list[pos].get_name();
}
ID_INLINE const QString   idArguments::get_description(const int pos) const
{
	return list[pos].get_description();
}
ID_INLINE const QVector<sreal_t> idArguments::get_full_scale_v(const int pos) const
{
	return list[pos].get_full_scale_v();
}
ID_INLINE const int idArguments::get_plain(const int pos) const
{
	return list[pos].get_plain();
}
ID_INLINE const bool idArguments::get_sort_policy(const int pos) const
{
	return list[pos].get_policy_sort();
}


ID_INLINE const sreal_t idArguments::get_max_scale(int pos)	const
{
	return list[pos].get_max_scale();
}


ID_INLINE const sreal_t idArguments::get_min_scale(int pos)	const
{
	return list[pos].get_min_scale();
}
}//end namespace lid
#endif /* !__LIST_H__ *//* PRIVATE */