// __BEGIN_LICENSE__
// 
// Copyright (C) 2006 United States Government as represented by the
// Administrator of the National Aeronautics and Space Administration
// (NASA).  All Rights Reserved.
// 
// Copyright 2006 Carnegie Mellon University. All rights reserved.
// 
// This software is distributed under the NASA Open Source Agreement
// (NOSA), version 1.3.  The NOSA has been approved by the Open Source
// Initiative.  See the file COPYING at the top of the distribution
// directory tree for the complete NOSA document.
// 
// THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF ANY
// KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
// LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
// SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
// A PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT
// THE SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT
// DOCUMENTATION, IF PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE.
// 
// __END_LICENSE__

//! \file Quaternion.h
//!
//! Provides the core Quaternion<> template class.
//! Depends on the BOOST quaternion<> class for much of the implementation.
//!
//! Currently I believe we support:
//!   Element access via q(i), q[i], and q.w(),q.x(),q.y(),q.z()
//!   Quaternion addition, subtraction, multiplication, division, and negation
//!   Scalar addition, subtraction, multiplication, and division
//!   Construction from axis vector + angle
//!   Construction from a rotation matrix
//!   Conversion to matrix via rotation_matrix() and rotation_matrix_4()
//!   Rotation of individual 3-vectors via rotate()
//!   Conjugation and inverse via conj() and inverse()
//!   exp, sin, cos, tan, sinh, cosh, tanh, and pow with integer powers
//!   Norms via norm_1(), norm_2(), and norm_inf()
//!   Extraction of real and imaginary-vector parts via real() and imag()
//!
#ifndef __VW_QUATERNION_H__
#define __VW_QUATERNION_H__

#include <boost/math/quaternion.hpp>

#include <vw/Core/Exception.h>

#include <vw/Math/Vector.h>
#include <vw/Math/Matrix.h>

namespace vw {
namespace math {

  class QuaternionImplementation {
  public:

    template <class QuaternionT, class OStreamT>
    static inline OStreamT& quaternion_to_stream( QuaternionT const& q, OStreamT& os ) {
      return os << "[Q]" << q.core_;
    }

    template <class QuaternionT>
    static inline typename QuaternionT::value_type quaternion_real( QuaternionT const& q ) {
      return real( q.core_ );
    }

    template <class QuaternionT>
    static inline Vector<typename QuaternionT::value_type,3> quaternion_imaj( QuaternionT const& q ) {
      return Vector<typename QuaternionT::value_type,3>( q[1], q[2], q[3] );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_conj( QuaternionT const& q ) {
      return conj( q.core_ );
    }

    template <class QuaternionT>
    static inline typename QuaternionT::value_type quaternion_norm_1( QuaternionT const& q ) {
      return l1( q.core_ );
    }

    template <class QuaternionT>
    static inline typename QuaternionT::value_type quaternion_norm_2( QuaternionT const& q ) {
      return abs( q.core_ );
    }

    template <class QuaternionT>
    static inline typename QuaternionT::value_type quaternion_norm_inf( QuaternionT const& q ) {
      return sup( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_inverse( QuaternionT const& q ) {
      return conj( q.core_ ) / norm( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_negation( QuaternionT const& q ) {
      return - q.core_;
    }

    template <class QuaternionT, class ScalarT>
    static inline QuaternionT quaternion_scalar_sum( QuaternionT const& q, ScalarT s ) {
      return q.core_ + typename QuaternionT::value_type(s);
    }

    template <class QuaternionT, class ScalarT>
    static inline QuaternionT quaternion_scalar_difference( QuaternionT const& q, ScalarT s ) {
      return q.core_ - typename QuaternionT::value_type(s);
    }

    template <class QuaternionT, class ScalarT>
    static inline QuaternionT quaternion_scalar_product( QuaternionT const& q, ScalarT s ) {
      return q.core_ * typename QuaternionT::value_type(s);
    }

    template <class QuaternionT, class ScalarT>
    static inline QuaternionT quaternion_scalar_quotient( QuaternionT const& q, ScalarT s ) {
      return q.core_ / typename QuaternionT::value_type(s);
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_quaternion_sum( QuaternionT const& q1, QuaternionT const& q2 ) {
      return q1.core_ + q2.core_;
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_quaternion_difference( QuaternionT const& q1, QuaternionT const& q2 ) {
      return q1.core_ - q2.core_;
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_quaternion_product( QuaternionT const& q1, QuaternionT const& q2 ) {
      return q1.core_ * q2.core_;
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_quaternion_quotient( QuaternionT const& q1, QuaternionT const& q2 ) {
      return q1.core_ / q2.core_;
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_exp( QuaternionT const& q ) {
      return exp( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_sin( QuaternionT const& q ) {
      return sin( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_cos( QuaternionT const& q ) {
      return cos( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_tan( QuaternionT const& q ) {
      return tan( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_sinh( QuaternionT const& q ) {
      return sinh( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_cosh( QuaternionT const& q ) {
      return cosh( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_tanh( QuaternionT const& q ) {
      return tanh( q.core_ );
    }

    template <class QuaternionT>
    static inline QuaternionT quaternion_int_pow( QuaternionT const& q, int n ) {
      return pow( q.core_, n );
    }

  };


  // This is just a placeholder for now, so that we're ready if we 
  // ever want to add any expression templating.
  template <class QuaternionT>
  class QuaternionBase {
  public:
    //! Returns the derived implementation type.
    QuaternionT& impl() { return *static_cast<QuaternionT*>(this); }

    //! Returns the derived implementation type.
    QuaternionT const& impl() const { return *static_cast<QuaternionT const*>(this); }    
  };


  template <class ElemT>
  class Quaternion : public QuaternionBase<Quaternion<ElemT> >
  {
    typedef boost::math::quaternion<ElemT> core_type;
    core_type core_;
    friend class QuaternionImplementation;
    Quaternion( core_type const& q ) : core_(q) {}
  public:
    typedef ElemT value_type;

    Quaternion() {}

    Quaternion( ElemT w, ElemT x, ElemT y, ElemT z ) : core_( w, x, y, z ) {}

    ElemT& operator[]( unsigned i ) {
      return *(reinterpret_cast<ElemT*>(this)+i);
    }

    ElemT const& operator[]( unsigned i ) const {
      return *(reinterpret_cast<ElemT const*>(this)+i);
    }

    ElemT& operator()( unsigned i ) {
      return *(reinterpret_cast<ElemT*>(this)+i);
    }

    ElemT const& operator()( unsigned i ) const {
      return *(reinterpret_cast<ElemT const*>(this)+i);
    }

    ElemT& w() {
      return operator[](0);
    }

    ElemT const& w() const {
      return operator[](0);
    }
    
    ElemT& x() {
      return operator[](1);
    }

    ElemT const& x() const {
      return operator[](1);
    }
    
    ElemT& y() {
      return operator[](2);
    }

    ElemT const& y() const {
      return operator[](2);
    }
    
    ElemT& z() {
      return operator[](3);
    }

    ElemT const& z() const {
      return operator[](3);
    }
    
    template <class MatrixT>
    explicit Quaternion( MatrixBase<MatrixT> const& matrix ) {
      MatrixT const& rot = matrix.impl();
      ElemT d0 = rot(0,0), d1 = rot(1,1), d2 = rot(2,2);
      ElemT ww = 1.0 + d0 + d1 + d2;
      ElemT xx = 1.0 + d0 - d1 - d2;
      ElemT yy = 1.0 - d0 + d1 - d2;
      ElemT zz = 1.0 - d0 - d1 + d2;

      ElemT max = ww;
      if (xx > max) max = xx;
      if (yy > max) max = yy;
      if (zz > max) max = zz;

      if (ww == max) {
        ElemT w4 = ElemT(sqrt(ww * 4.0));
        w() = w4 / 4;
        x() = (rot(2,1) - rot(1,2)) / w4;
        y() = (rot(0,2) - rot(2,0)) / w4;
        z() = (rot(1,0) - rot(0,1)) / w4;
      } else if (xx == max) {
        ElemT x4 = ElemT(sqrt(xx * 4.0));
        w() = (rot(2,1) - rot(1,2)) / x4;
        x() = x4 / 4;
        y() = (rot(0,1) + rot(1,0)) / x4;
        z() = (rot(0,2) + rot(2,0)) / x4;
      } else if (yy == max) {
        ElemT y4 = ElemT(sqrt(yy * 4.0));
        w() = (rot(0,2) - rot(2,0)) / y4;
        x() = (rot(0,1) + rot(1,0)) / y4;
        y() =  y4 / 4;
        z() = (rot(1,2) + rot(2,1)) / y4;
      } else {
        ElemT z4 = ElemT(sqrt(zz * 4.0));
        w() = (rot(1,0) - rot(0,1)) / z4;
        x() = (rot(0,2) + rot(2,0)) / z4;
        y() = (rot(1,2) + rot(2,1)) / z4;
        z() =  z4 / 4;
      }
    }

    template <class VectorT>
    explicit Quaternion( VectorBase<VectorT> const& vec ) {
      for( unsigned i=0; i<4; ++i ) operator[](i) = vec.impl()[i];
    }

    template <class VectorT>
    Quaternion( VectorBase<VectorT> const& axis, ElemT angle ) {
      double ha = angle * 0.5;
      w() = ElemT(cos(ha));
      ElemT s = ElemT(sin(ha));
      for (unsigned i = 0; i < 3; i++)
        operator[](i+1) = s * axis.impl()[i];
    }

    template <class VectorT>
    void axis_angle( VectorBase<VectorT> &axis_, ElemT &angle ) {
      VectorT & axis = axis_.impl();

      Vector<ElemT,3> imag_part = imag(*this);
      ElemT imag_norm_2 = norm_2(imag_part);
      angle = 2 * atan2(imag_norm_2, real(*this));
      // What's the better way to do this?
      // For rotation of 0 or 180, axis does not matter
      if (fabs(imag_norm_2) < 1e-10) {
        axis = Vector<ElemT,3>(1,0,0);
      } else {
        axis = imag_part / norm_2(imag_part);
      }
    }

    template <class MatrixT>
    void rotation_matrix( MatrixBase<MatrixT>& rot_ ) const {
      MatrixT& rot = rot_.impl();
      ElemT w2 = w()*w(), x2 = x()*x(), y2 = y()*y(), z2 = z()*z();
      ElemT wx = w()*x(), wy = w()*y(), wz = w()*z();
      ElemT xy = x()*y(), yz = y()*z(), zx = z()*x();
      rot(0,0) = w2 + x2 - y2 - z2;
      rot(1,1) = w2 - x2 + y2 - z2;
      rot(2,2) = w2 - x2 - y2 + z2;
      rot(0,1) = 2 * (xy - wz);
      rot(0,2) = 2 * (zx + wy);
      rot(1,2) = 2 * (yz - wx);
      rot(1,0) = 2 * (xy + wz);
      rot(2,0) = 2 * (zx - wy);
      rot(2,1) = 2 * (yz + wx);
    }

    Matrix<ElemT,3,3> rotation_matrix() const {
      Matrix<ElemT,3,3> rot;
      rotation_matrix( rot );
      return rot;
    }

    Matrix<ElemT,4,4> rotation_matrix_4() const {
      Matrix<ElemT,4,4> rot;
      rot.set_identity();
      rotation_matrix( rot );
      return rot;
    }

    template <class VectorT>
    VectorT rotate( VectorBase<VectorT> const& v_ ) const {
      VectorT const& v = v_.impl();
      return imag( *this * Quaternion(0,v[0],v[1],v[2]) / *this );
    }
  };


  //! Dumps a quaternion to a std::ostream
  template <class QuaternionT>
  inline std::ostream& operator<<( std::ostream& os, QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_to_stream( q.impl(), os );
  }

  template <class QuaternionT>
  inline typename QuaternionT::value_type real( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_real( q.impl() );
  }

  template <class QuaternionT>
  inline Vector<typename QuaternionT::value_type,3> imag( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_imaj( q.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT conj( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_conj( q.impl() );
  }

  template <class QuaternionT>
  inline typename QuaternionT::value_type norm_1( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_norm_1( q.impl() );
  }

  template <class QuaternionT>
  inline typename QuaternionT::value_type norm_2( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_norm_2( q.impl() );
  }

  template <class QuaternionT>
  inline typename QuaternionT::value_type norm_inf( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_norm_inf( q.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT inverse( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_inverse( q.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT operator-( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_negation( q.impl() );
  }

  template <class QuaternionT, class ScalarT>
  typename boost::enable_if< IsScalar<ScalarT>, QuaternionT >::type
  inline operator+( QuaternionBase<QuaternionT> const& q, ScalarT s ) {
    return QuaternionImplementation::quaternion_scalar_sum( q.impl(), s );
  }

  template <class QuaternionT, class ScalarT>
  typename boost::enable_if< IsScalar<ScalarT>, QuaternionT >::type
  inline operator-( QuaternionBase<QuaternionT> const& q, ScalarT s ) {
    return QuaternionImplementation::quaternion_scalar_difference( q.impl(), s );
  }

  template <class QuaternionT, class ScalarT>
  typename boost::enable_if< IsScalar<ScalarT>, QuaternionT >::type
  inline operator*( QuaternionBase<QuaternionT> const& q, ScalarT s ) {
    return QuaternionImplementation::quaternion_scalar_product( q.impl(), s );
  }

  template <class QuaternionT, class ScalarT>
  typename boost::enable_if< IsScalar<ScalarT>, QuaternionT >::type
  inline operator/( QuaternionBase<QuaternionT> const& q, ScalarT s ) {
    return QuaternionImplementation::quaternion_scalar_quotient( q.impl(), s );
  }

  template <class QuaternionT>
  inline QuaternionT operator+( QuaternionBase<QuaternionT> const& q1, QuaternionBase<QuaternionT> const& q2 ) {
    return QuaternionImplementation::quaternion_quaternion_sum( q1.impl(), q2.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT operator-( QuaternionBase<QuaternionT> const& q1, QuaternionBase<QuaternionT> const& q2 ) {
    return QuaternionImplementation::quaternion_quaternion_difference( q1.impl(), q2.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT operator*( QuaternionBase<QuaternionT> const& q1, QuaternionBase<QuaternionT> const& q2 ) {
    return QuaternionImplementation::quaternion_quaternion_product( q1.impl(), q2.impl() );
  }

  template <class QuaternionT>
  inline QuaternionT operator/( QuaternionBase<QuaternionT> const& q1, QuaternionBase<QuaternionT> const& q2 ) {
    return QuaternionImplementation::quaternion_quaternion_quotient( q1.impl(), q2.impl() );
  }

  using ::exp;
  template <class QuaternionT>
  inline QuaternionT exp( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_exp( q.impl() );
  }

  using ::sin;
  template <class QuaternionT>
  inline QuaternionT sin( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_sin( q.impl() );
  }

  using ::cos;
  template <class QuaternionT>
  inline QuaternionT cos( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_cos( q.impl() );
  }

  using ::tan;
  template <class QuaternionT>
  inline QuaternionT tan( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_tan( q.impl() );
  }

  using ::sinh;
  template <class QuaternionT>
  inline QuaternionT sinh( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_sinh( q.impl() );
  }

  using ::cosh;
  template <class QuaternionT>
  inline QuaternionT cosh( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_cosh( q.impl() );
  }

  using ::tanh;
  template <class QuaternionT>
  inline QuaternionT tanh( QuaternionBase<QuaternionT> const& q ) {
    return QuaternionImplementation::quaternion_tanh( q.impl() );
  }

  using ::pow;
  template <class QuaternionT>
  inline QuaternionT pow( QuaternionBase<QuaternionT> const& q, int n ) {
    return QuaternionImplementation::quaternion_int_pow( q.impl(), n );
  }

} // namespace math
  using math::Quaternion;
  typedef Quaternion<double> Quat;
  typedef Quaternion<float> Quatf;
} // namespace vw

#endif // __VW_QUATERNION_H__
