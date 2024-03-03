/*!*****************************************************************************
	@file struct.hpp				               
	@author Kuslya A.M.
	@date 2023/05/31
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief ������, ���������� ��������������� ��������� ��� ��������������� ��������
*******************************************************************************/


#ifndef __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__
#define __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__


#include <science/core/type.hpp>


/** \brief science - Common utilities library */
namespace science {


/*!*****************************************************************************
	@brief ����������� ��������� ��������
	@author Kuslya A.M.
	@version 1.0
	@date 2023/05/31
	
	�������� �������� ��� ��������, ��� ����������� ���������. ����������� � 
	��������, ��������� � �������������, �������� saturate().
*******************************************************************************/
struct Limits
{
    sreal_t min;		/**< ������ ������� ��������� */
    sreal_t max;		/**< ������� ������� ��������� */
};

} /* namespace science */


#endif // __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__