/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Written (W) 2013 Soumyajit De
 */

#include <shogun/lib/common.h>

#ifdef HAVE_EIGEN3

#include <shogun/base/Parameter.h>
#include <shogun/mathematics/logdet/IterativeLinearSolver.h>

namespace shogun
{

template <class T, class ST>
CIterativeLinearSolver<T, ST>::CIterativeLinearSolver()
	: CLinearSolver<T, ST>()
	{
		init();

		SG_SGCDEBUG("%s created (%p)\n", this->get_name(), this);
	}

template <class T, class ST>
void CIterativeLinearSolver<T, ST>::init()
	{
		m_max_iteration_limit=1000;
		m_relative_tolerence=1E-5;
		m_absolute_tolerence=1E-5;

		CSGObject::m_parameters->add(&m_max_iteration_limit, "max_iteration_limit",
			"Maximum number of iteration for the solver");

		CSGObject::m_parameters->add(&m_relative_tolerence, "relative_tolerence",
			"Relative tolerence of solver");

		CSGObject::m_parameters->add(&m_absolute_tolerence, "absolute_tolerence",
			"Absolute tolerence of solver");
	}

template <class T, class ST>
CIterativeLinearSolver<T, ST>::~CIterativeLinearSolver()
	{
		SG_SGCDEBUG("%s destroyed (%p)\n", this->get_name(), this);
	}

template class CIterativeLinearSolver<bool>;
template class CIterativeLinearSolver<char>;
template class CIterativeLinearSolver<int8_t>;
template class CIterativeLinearSolver<uint8_t>;
template class CIterativeLinearSolver<int16_t>;
template class CIterativeLinearSolver<uint16_t>;
template class CIterativeLinearSolver<int32_t>;
template class CIterativeLinearSolver<uint32_t>;
template class CIterativeLinearSolver<int64_t>;
template class CIterativeLinearSolver<uint64_t>;
template class CIterativeLinearSolver<float32_t>;
template class CIterativeLinearSolver<float64_t>;
template class CIterativeLinearSolver<floatmax_t>;
template class CIterativeLinearSolver<complex64_t>;
template class CIterativeLinearSolver<complex64_t, float64_t>;
}
#endif // HAVE_EIGEN3
