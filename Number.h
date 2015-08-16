/*
* Interval.h
*
*  Created on: 03-04-2015
*  Author: Jakub Kuderski
*/

#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <type_traits>
#include <stdexcept>

#include "ErrorCode.h"

# define M_PI          3.141592653589793238462643383279502884L /* pi */
#define M_SQRT2   1.41421356237309504880 /* sqrt(2) */
namespace ean
{
	template<typename T>
	class Number final
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
	public:
		Number() = default;
		Number(const std::string& value) 
			: m_value(std::stold(value))
		{}

		explicit Number(T value) 
			: m_value(value)
		{}

		T getWidth() const  { return T(0); }

		Number& operator+=(const Number& rhs) 
		{
			m_value += rhs.m_value;
			return *this;
		}

		Number operator+(const Number& rhs) const 
		{
			Number temp = *this;
			temp += rhs;
			return temp;
		}

		Number& operator-=(const Number& rhs) 
		{
			m_value -= rhs.m_value;
			return *this;
		}
		Number operator-(const Number& rhs) const 
		{
			Number temp = *this;
			temp -= rhs;
			return temp;
		}

		Number& operator*=(const Number& rhs) 
		{
			m_value *= rhs.m_value;
			return *this;
		}

		Number operator*(const Number& rhs) const 
		{
			Number temp = *this;
			temp *= rhs;
			return temp;
		}

		Number& operator/=(const Number& rhs)
		{
			if (rhs.m_value == T(0)) // abs(x-y) < eps?
			{
				throw std::runtime_error("Division by 0");
			}

			m_value /= rhs.m_value;
			return *this;
		}

		Number operator/(const Number& rhs) const
		{
			Number temp = *this;
			temp /= rhs;
			return temp;
		}

		bool operator==(const Number& rhs) const
		{
			return std::fabs(m_value - rhs.m_value) < T(LDBL_EPSILON);
		}

        bool operator<(const T& rhs) const
        {
            return m_value < rhs;
        }

        bool operator<(const Number& rhs) const
        {
            return m_value < rhs.m_value;
        }
//zero
        bool isZero(){
            return m_value==0;
        }

        Number& opposite()
		{
			m_value = -m_value;
			return *this;
		}

		Number getOpposite() const 
		{
			return Number{-m_value};
		}
//abs
        Number abs() const
        {
            if(m_value<0)return Number(-m_value);
            return Number(m_value);
        }
        Number& invert()
		{
			m_value = 1 / m_value;
			return *this;
		}

		Number getInverse() const 
		{
			Number temp = *this;
			temp.invert();
			return temp;
		}

		ErrorCode<Number> sin() const 
		{
			return {Number{std::sin(m_value)}};
		}
		
		ErrorCode<Number> cos() const 
		{
			return {Number{std::cos(m_value)}};
		}
		
		ErrorCode<Number> exp() const 
		{
			return {Number{std::exp(m_value)}};
		}
		
		ErrorCode<Number> sqr() const 
		{
			return {Number{m_value * m_value}};
		}

		static Number sqrt2() { return Number{T(M_SQRT2)}; }
		static Number sqrt3() { return Number{T(std::sqrt(3.0l))}; }
		static Number pi() { return Number{T(M_PI)}; }

		std::string to_string() const 
		{
			std::ostringstream oss;
            oss << std::scientific << std::setprecision(15) << m_value;
			return oss.str();
        }
    T getM_value(){return m_value;}
	private:
		T m_value = 0;
	};
	
	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Number<T>& value)
	{
		return os << value.to_string();
	}

	using Extended = Number<long double>;

} // namespace ean
