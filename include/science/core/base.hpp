/*!*****************************************************************************
	@file base.hpp				               
	@author Kuslya A.M.
	@date 2023/05/31
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief ������ ��������������� ������� �������
	
	������ �������� � ���� ����� ��������������� ������� � ��������, �������
	����� ���� ������������ ������������� ��� ����������� ������ ����������
	������������ ����.
*******************************************************************************/


/** \brief science - Common utilities library */
namespace science {


/*!*****************************************************************************
	@brief ��������������� �����, ��������������� ��� ������� �����������
	@author Kuslya A.M.
	@version 1.0
	@date 2023/05/31
	
	��� ������������ �� ������ NonCopyable ��� ���� ������� ����������� �����
	������� ���������� ������������� ������������ ����������� � ��������� 
	�����������.
*******************************************************************************/
class NonCopyable
{
protected:
	/** \brief ����������� ��-��������� */
	NonCopyable() = default;

	/** \brief ���������� ��-��������� */
	~NonCopyable() = default;

private:
	NonCopyable(NonCopyable const&) = default;
	NonCopyable& operator = (NonCopyable const&) = default;
};



/*!*****************************************************************************
	@brief ��������������� ������� ����� ��� ������� �������� �����������
	@author Kuslya A.M.
	@version 1.0
	@date 2023/05/31
	
	��� ������������ �� ������ NonCreatable ��� ���� ������� ����������� �����
	������� ����������� �������� ����������� ������
*******************************************************************************/
class NonCreatable
{
	NonCreatable() = default;
};


} /* namespace science */