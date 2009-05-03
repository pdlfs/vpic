#ifndef _v4_altivec_hxx_
#define _v4_altivec_hxx_

#ifndef IN_v4_h
#error "Do not include v4_altivec.hxx directly; use v4.h"
#endif

#define V4_ACCELERATION
#define V4_ALTIVEC_ACCELERATION

#ifndef ALIGNED
#define ALIGNED(n)
#endif

#include <math.h>
#include <altivec.h>

namespace v4 {

  class v4;
  class v4int;
  class v4float;

# define _v4_int    __vector int
# define _v4_uint   __vector unsigned int
# define _v4_float  __vector float

# define P(i0,i1,i2,i3) { 4*i0, 4*i0+1, 4*i0+2, 4*i0+3, \
                          4*i1, 4*i1+1, 4*i1+2, 4*i1+3, \
                          4*i2, 4*i2+1, 4*i2+2, 4*i2+3, \
                          4*i3, 4*i3+1, 4*i3+2, 4*i3+3 }

  const __vector unsigned char _perm[256] = {
    P(0,0,0,0), P(1,0,0,0), P(2,0,0,0), P(3,0,0,0),
    P(0,1,0,0), P(1,1,0,0), P(2,1,0,0), P(3,1,0,0),
    P(0,2,0,0), P(1,2,0,0), P(2,2,0,0), P(3,2,0,0),
    P(0,3,0,0), P(1,3,0,0), P(2,3,0,0), P(3,3,0,0),
    P(0,0,1,0), P(1,0,1,0), P(2,0,1,0), P(3,0,1,0),
    P(0,1,1,0), P(1,1,1,0), P(2,1,1,0), P(3,1,1,0),
    P(0,2,1,0), P(1,2,1,0), P(2,2,1,0), P(3,2,1,0),
    P(0,3,1,0), P(1,3,1,0), P(2,3,1,0), P(3,3,1,0),
    P(0,0,2,0), P(1,0,2,0), P(2,0,2,0), P(3,0,2,0),
    P(0,1,2,0), P(1,1,2,0), P(2,1,2,0), P(3,1,2,0),
    P(0,2,2,0), P(1,2,2,0), P(2,2,2,0), P(3,2,2,0),
    P(0,3,2,0), P(1,3,2,0), P(2,3,2,0), P(3,3,2,0),
    P(0,0,3,0), P(1,0,3,0), P(2,0,3,0), P(3,0,3,0),
    P(0,1,3,0), P(1,1,3,0), P(2,1,3,0), P(3,1,3,0),
    P(0,2,3,0), P(1,2,3,0), P(2,2,3,0), P(3,2,3,0),
    P(0,3,3,0), P(1,3,3,0), P(2,3,3,0), P(3,3,3,0),

    P(0,0,0,1), P(1,0,0,1), P(2,0,0,1), P(3,0,0,1),
    P(0,1,0,1), P(1,1,0,1), P(2,1,0,1), P(3,1,0,1),
    P(0,2,0,1), P(1,2,0,1), P(2,2,0,1), P(3,2,0,1),
    P(0,3,0,1), P(1,3,0,1), P(2,3,0,1), P(3,3,0,1),
    P(0,0,1,1), P(1,0,1,1), P(2,0,1,1), P(3,0,1,1),
    P(0,1,1,1), P(1,1,1,1), P(2,1,1,1), P(3,1,1,1),
    P(0,2,1,1), P(1,2,1,1), P(2,2,1,1), P(3,2,1,1),
    P(0,3,1,1), P(1,3,1,1), P(2,3,1,1), P(3,3,1,1),
    P(0,0,2,1), P(1,0,2,1), P(2,0,2,1), P(3,0,2,1),
    P(0,1,2,1), P(1,1,2,1), P(2,1,2,1), P(3,1,2,1),
    P(0,2,2,1), P(1,2,2,1), P(2,2,2,1), P(3,2,2,1),
    P(0,3,2,1), P(1,3,2,1), P(2,3,2,1), P(3,3,2,1),
    P(0,0,3,1), P(1,0,3,1), P(2,0,3,1), P(3,0,3,1),
    P(0,1,3,1), P(1,1,3,1), P(2,1,3,1), P(3,1,3,1),
    P(0,2,3,1), P(1,2,3,1), P(2,2,3,1), P(3,2,3,1),
    P(0,3,3,1), P(1,3,3,1), P(2,3,3,1), P(3,3,3,1),

    P(0,0,0,2), P(1,0,0,2), P(2,0,0,2), P(3,0,0,2),
    P(0,1,0,2), P(1,1,0,2), P(2,1,0,2), P(3,1,0,2),
    P(0,2,0,2), P(1,2,0,2), P(2,2,0,2), P(3,2,0,2),
    P(0,3,0,2), P(1,3,0,2), P(2,3,0,2), P(3,3,0,2),
    P(0,0,1,2), P(1,0,1,2), P(2,0,1,2), P(3,0,1,2),
    P(0,1,1,2), P(1,1,1,2), P(2,1,1,2), P(3,1,1,2),
    P(0,2,1,2), P(1,2,1,2), P(2,2,1,2), P(3,2,1,2),
    P(0,3,1,2), P(1,3,1,2), P(2,3,1,2), P(3,3,1,2),
    P(0,0,2,2), P(1,0,2,2), P(2,0,2,2), P(3,0,2,2),
    P(0,1,2,2), P(1,1,2,2), P(2,1,2,2), P(3,1,2,2),
    P(0,2,2,2), P(1,2,2,2), P(2,2,2,2), P(3,2,2,2),
    P(0,3,2,2), P(1,3,2,2), P(2,3,2,2), P(3,3,2,2),
    P(0,0,3,2), P(1,0,3,2), P(2,0,3,2), P(3,0,3,2),
    P(0,1,3,2), P(1,1,3,2), P(2,1,3,2), P(3,1,3,2),
    P(0,2,3,2), P(1,2,3,2), P(2,2,3,2), P(3,2,3,2),
    P(0,3,3,2), P(1,3,3,2), P(2,3,3,2), P(3,3,3,2),

    P(0,0,0,3), P(1,0,0,3), P(2,0,0,3), P(3,0,0,3),
    P(0,1,0,3), P(1,1,0,3), P(2,1,0,3), P(3,1,0,3),
    P(0,2,0,3), P(1,2,0,3), P(2,2,0,3), P(3,2,0,3),
    P(0,3,0,3), P(1,3,0,3), P(2,3,0,3), P(3,3,0,3),
    P(0,0,1,3), P(1,0,1,3), P(2,0,1,3), P(3,0,1,3),
    P(0,1,1,3), P(1,1,1,3), P(2,1,1,3), P(3,1,1,3),
    P(0,2,1,3), P(1,2,1,3), P(2,2,1,3), P(3,2,1,3),
    P(0,3,1,3), P(1,3,1,3), P(2,3,1,3), P(3,3,1,3),
    P(0,0,2,3), P(1,0,2,3), P(2,0,2,3), P(3,0,2,3),
    P(0,1,2,3), P(1,1,2,3), P(2,1,2,3), P(3,1,2,3),
    P(0,2,2,3), P(1,2,2,3), P(2,2,2,3), P(3,2,2,3),
    P(0,3,2,3), P(1,3,2,3), P(2,3,2,3), P(3,3,2,3),
    P(0,0,3,3), P(1,0,3,3), P(2,0,3,3), P(3,0,3,3),
    P(0,1,3,3), P(1,1,3,3), P(2,1,3,3), P(3,1,3,3),
    P(0,2,3,3), P(1,2,3,3), P(2,2,3,3), P(3,2,3,3),
    P(0,3,3,3), P(1,3,3,3), P(2,3,3,3), P(3,3,3,3) };

# undef P

  // FIXME: IS IT FASTER TO SPLAT THESE ON THE FLY

  const _v4_int   _false = {  0,  0,  0,  0 };
  const _v4_int   _true  = { -1, -1, -1, -1 };
  const _v4_int   _ione  = {  1,  1,  1,  1 };

  const _v4_float _zero  = { 0.0f, 0.0f, 0.0f, 0.0f };
  const _v4_float _half  = { 0.5f, 0.5f, 0.5f, 0.5f };
  const _v4_float _one   = { 1.0f, 1.0f, 1.0f, 1.0f };
  const _v4_float _sign  = (_v4_float)
    ((_v4_int){ 1<<31, 1<<31, 1<<31, 1<<31 });

  ////////////////
  // v4 base class
  
  class v4 {
    
    friend class v4int;
    friend class v4float;
      
    // v4 miscellenous friends

    friend inline int any( const v4 &a );
    friend inline int all( const v4 &a );
    friend inline v4 splat( const v4 &a, const int n );
    friend inline v4 shuffle( const v4 &a,
                              int i0, int i1, int i2, int i3 );
    friend inline void swap( v4 &a, v4 &b );
    friend inline void transpose( v4 &a0, v4 &a1, v4 &a2, v4 &a3 );

    // v4int miscellaneous friends

    friend inline v4 czero(    const v4int &c, const v4 &a );
    friend inline v4 notczero( const v4int &c, const v4 &a );
    friend inline v4 merge(    const v4int &c, const v4 &a, const v4 &b );

    // v4 memory manipulation friends
        
    friend inline void load_4x1( const void * ALIGNED(16) p, v4 &a );
    friend inline void store_4x1( const v4 &a, void * ALIGNED(16) p );
    friend inline void stream_4x1( const v4 &a, void * ALIGNED(16) p );
    friend inline void copy_4x1( void * ALIGNED(16) dst,
                                 const void * ALIGNED(16) src );
    friend inline void swap_4x1( void * ALIGNED(16) a, void * ALIGNED(16) b );

    // v4 transposed memory manipulation friends
    // Note: Half aligned values are permissible in the 4x2_tr variants!

    friend inline void load_4x1_tr( const void *a0, const void *a1,
                                    const void *a2, const void *a3,
                                    v4 &a );
    friend inline void load_4x2_tr( const void * ALIGNED(8) a0,
                                    const void * ALIGNED(8) a1,
                                    const void * ALIGNED(8) a2,
                                    const void * ALIGNED(8) a3,
                                    v4 &a, v4 &b );
    friend inline void load_4x3_tr( const void * ALIGNED(16) a0,
                                    const void * ALIGNED(16) a1,
                                    const void * ALIGNED(16) a2,
                                    const void * ALIGNED(16) a3,
                                    v4 &a, v4 &b, v4 &c );
    friend inline void load_4x4_tr( const void * ALIGNED(16) a0,
                                    const void * ALIGNED(16) a1,
                                    const void * ALIGNED(16) a2,
                                    const void * ALIGNED(16) a3,
                                    v4 &a, v4 &b, v4 &c, v4 &d );
    
    friend inline void store_4x1_tr( const v4 &a,
                                     void *a0, void *a1, void *a2, void *a3 );
    friend inline void store_4x2_tr( const v4 &a, const v4 &b,
                                     void * ALIGNED(8) a0,
                                     void * ALIGNED(8) a1,
                                     void * ALIGNED(8) a2,
                                     void * ALIGNED(8) a3 );
    friend inline void store_4x3_tr( const v4 &a, const v4 &b, const v4 &c,
                                     void * ALIGNED(16) a0,
                                     void * ALIGNED(16) a1,
                                     void * ALIGNED(16) a2,
                                     void * ALIGNED(16) a3 );
    friend inline void store_4x4_tr( const v4 &a, const v4 &b,
                                     const v4 &c, const v4 &d,
                                     void * ALIGNED(16) a0,
                                     void * ALIGNED(16) a1,
                                     void * ALIGNED(16) a2,
                                     void * ALIGNED(16) a3 );

  protected:

    _v4_float v;
    
  public:

    v4() {}                    // Default constructor
    v4(const v4 &a) {          // Copy constructor
      v = a.v;
    }
    ~v4() {}                   // Default destructor

  };
  
  // v4 miscellaneous functions

  inline int any( const v4 &a ) {
    return vec_any_ne( (_v4_int)a.v, _false );
  }
  
  inline int all( const v4 &a ) {
    return vec_all_ne( (_v4_int)a.v, _false );
  }
  
  inline v4 splat( const v4 & a, const int n ) {
    v4 b;
    b.v = vec_splat( a.v, n );
    return b;
  }

  inline v4 shuffle( const v4 & a,
                     int i0, int i1, int i2, int i3 ) {
    _v4_float a_v = a.v;
    v4 b;
    b.v = vec_perm( a_v, a_v, _perm[i0 + i1*4 + i2*16 + i3*64] );
    return b;
  }

  inline void swap( v4 &a, v4 &b ) { 
    _v4_float t;
    t   = a.v;
    a.v = b.v;
    b.v = t;
  }

  inline void transpose( v4 &a, v4 &b, v4 &c, v4 &d ) {
    _v4_float a0 = a.v;                  // a0 =  0  1  2  3
    _v4_float b0 = b.v;                  // b0 =  4  5  6  7
    _v4_float c1 = c.v;                  // c1 =  8  9 10 11
    _v4_float d1 = d.v;                  // d1 = 12 13 14 15

    // Step 1: Interleave top and bottom half

    _v4_float a1 = vec_mergeh( a0, c1 ); // a1 =  0  8  1  9
    _v4_float b1 = vec_mergeh( b0, d1 ); // b1 =  4 12  5 13
    c1           = vec_mergel( a0, c1 ); // c1 =  2 10  3 11
    d1           = vec_mergel( b0, d1 ); // d1 =  6 14  7 15

    // Step 2: Interleave even and odd rows

    a.v          = vec_mergeh( a1, b1 ); // a  =  0  4  8 12
    b.v          = vec_mergel( a1, b1 ); // b  =  1  5  9 13
    c.v          = vec_mergeh( c1, d1 ); // c  =  2  6 10 14
    d.v          = vec_mergel( c1, d1 ); // d  =  3  7 11 15
  }

  // v4 memory manipulation functions
  
  inline void load_4x1( const void * ALIGNED(16) p, v4 &a ) {
    a.v = vec_ld( 0, (const float *)p );
  }

  inline void store_4x1( const v4 &a, void * ALIGNED(16) p ) {
    vec_st( a.v, 0, (float *)p );
  }

  inline void stream_4x1( const v4 &a, void * ALIGNED(16) p ) {
    vec_stl( a.v, 0, (float *)p );
  }

  // FIXME: Ordering semantics
  inline void copy_4x1( void * ALIGNED(16) d, const void * ALIGNED(16) s ) {
    vec_st( vec_ld( 0, (const float *)s ), 0, (float *)d );
  }

  inline void swap_4x1( void * ALIGNED(16) a, void * ALIGNED(16) b ) {
    _v4_float va = vec_ld( 0, (float *)a );
    _v4_float vb = vec_ld( 0, (float *)b );
    vec_st( vb, 0, (float *)a );
    vec_st( va, 0, (float *)b );
  }

  // v4 transposed memory manipulation functions

  inline void load_4x1_tr( const void *pa,
                           const void *pb,
                           const void *pc,
                           const void *pd,
                           v4 &a ) {
    a.v = (_v4_float){ ((const float *)pa)[0],
                       ((const float *)pb)[0],
                       ((const float *)pc)[0],
                       ((const float *)pd)[0] };
  }

  inline void load_4x2_tr( const void * ALIGNED(8) pa,
                           const void * ALIGNED(8) pb,
                           const void * ALIGNED(8) pc,
                           const void * ALIGNED(8) pd,
                           v4 &a, v4 &b ) { // FIXME: UGLY!!
    a.v = (_v4_float){ ((const float *)pa)[0],
                       ((const float *)pb)[0],
                       ((const float *)pc)[0],
                       ((const float *)pd)[0] };
    b.v = (_v4_float){ ((const float *)pa)[1],
                       ((const float *)pb)[1],
                       ((const float *)pc)[1],
                       ((const float *)pd)[1] };
  }
  
  inline void load_4x3_tr( const void * ALIGNED(16) pa,
                           const void * ALIGNED(16) pb,
                           const void * ALIGNED(16) pc,
                           const void * ALIGNED(16) pd,
                           v4 &a, v4 &b, v4 &c ) {
    _v4_float a0 = vec_ld( 0, (const float *)pa ); // a0 =  0  1  2  x
    _v4_float b0 = vec_ld( 0, (const float *)pb ); // b0 =  4  5  6  x
    _v4_float c1 = vec_ld( 0, (const float *)pc ); // c1 =  8  9 10  x
    _v4_float d1 = vec_ld( 0, (const float *)pd ); // d1 = 12 13 14  x

    // Step 1: Interleave top and bottom half

    _v4_float a1 = vec_mergeh( a0, c1 );           // a1 =  0  8  1  9
    _v4_float b1 = vec_mergeh( b0, d1 );           // b1 =  4 12  5 13
    c1           = vec_mergel( a0, c1 );           // c1 =  2 10  x  x
    d1           = vec_mergel( b0, d1 );           // d1 =  6 14  x  x

    // Step 2: Interleave even and odd rows

    a.v          = vec_mergeh( a1, b1 );           // a  =  0  4  8 12
    b.v          = vec_mergel( a1, b1 );           // b  =  1  5  9 13
    c.v          = vec_mergeh( c1, d1 );           // c  =  2  6 10 14
  }

  inline void load_4x4_tr( const void * ALIGNED(16) pa,
                           const void * ALIGNED(16) pb,
                           const void * ALIGNED(16) pc,
                           const void * ALIGNED(16) pd,
                           v4 &a, v4 &b, v4 &c, v4 &d ) {
    _v4_float a0 = vec_ld( 0, (const float *)pa ); // a0 =  0  1  2  3
    _v4_float b0 = vec_ld( 0, (const float *)pb ); // b0 =  4  5  6  7
    _v4_float c1 = vec_ld( 0, (const float *)pc ); // c1 =  8  9 10 11
    _v4_float d1 = vec_ld( 0, (const float *)pd ); // d1 = 12 13 14 15

    // Step 1: Interleave top and bottom half

    _v4_float a1 = vec_mergeh( a0, c1 );           // a1 =  0  8  1  9
    _v4_float b1 = vec_mergeh( b0, d1 );           // b1 =  4 12  5 13
    c1           = vec_mergel( a0, c1 );           // c1 =  2 10  3 11
    d1           = vec_mergel( b0, d1 );           // d1 =  6 14  7 15

    // Step 2: Interleave even and odd rows

    a.v          = vec_mergeh( a1, b1 );           // a  =  0  4  8 12
    b.v          = vec_mergel( a1, b1 );           // b  =  1  5  9 13
    c.v          = vec_mergeh( c1, d1 );           // c  =  2  6 10 14
    d.v          = vec_mergel( c1, d1 );           // d  =  3  7 11 15
  }

  inline void store_4x1_tr( const v4 &a,
                            void * pa,
                            void * pb,
                            void * pc,
                            void * pd ) {
    union { float f[4]; _v4_float v; } t;
    t.v = a.v;
    ((float *)pa)[0] = t.f[0];
    ((float *)pb)[0] = t.f[1];
    ((float *)pc)[0] = t.f[2];
    ((float *)pd)[0] = t.f[3];
  }

  inline void store_4x2_tr( const v4 &a, const v4 &b,
                            void * ALIGNED(8) pa,
                            void * ALIGNED(8) pb,
                            void * ALIGNED(8) pc,
                            void * ALIGNED(8) pd ) { // FIXME: UGLY!
    union { float f[4]; _v4_float v; } t;
    t.v = a.v;
    ((float *)pa)[0] = t.f[0];
    ((float *)pb)[0] = t.f[1];
    ((float *)pc)[0] = t.f[2];
    ((float *)pd)[0] = t.f[3];
    t.v = b.v;
    ((float *)pa)[1] = t.f[0];
    ((float *)pb)[1] = t.f[1];
    ((float *)pc)[1] = t.f[2];
    ((float *)pd)[1] = t.f[3];
  }

  inline void store_4x3_tr( const v4 &a, const v4 &b, const v4 &c,
                            void * ALIGNED(16) pa,
                            void * ALIGNED(16) pb,
                            void * ALIGNED(16) pc,
                            void * ALIGNED(16) pd ) { // FIXME: UGLY!
    union { float f[4]; _v4_float v; } t;
    t.v = a.v;
    ((float *)pa)[0] = t.f[0];
    ((float *)pb)[0] = t.f[1];
    ((float *)pc)[0] = t.f[2];
    ((float *)pd)[0] = t.f[3];
    t.v = b.v;
    ((float *)pa)[1] = t.f[0];
    ((float *)pb)[1] = t.f[1];
    ((float *)pc)[1] = t.f[2];
    ((float *)pd)[1] = t.f[3];
    t.v = c.v;
    ((float *)pa)[2] = t.f[0];
    ((float *)pb)[2] = t.f[1];
    ((float *)pc)[2] = t.f[2];
    ((float *)pd)[2] = t.f[3];
  }
  
  inline void store_4x4_tr( const v4 &a, const v4 &b, const v4 &c, const v4 &d,
                            void * ALIGNED(16) pa,
                            void * ALIGNED(16) pb,
                            void * ALIGNED(16) pc,
                            void * ALIGNED(16) pd ) {
    _v4_float a0 = a.v;                             // a0 =  0  1  2  3
    _v4_float b0 = b.v;                             // b0 =  4  5  6  7
    _v4_float c1 = c.v;                             // c1 =  8  9 10 11
    _v4_float d1 = d.v;                             // d1 = 12 13 14 15

    // Step 1: Interleave top and bottom half

    _v4_float a1 = vec_mergeh( a0, c1 );            // a1 =  0  8  1  9
    _v4_float b1 = vec_mergeh( b0, d1 );            // b1 =  4 12  5 13
    c1           = vec_mergel( a0, c1 );            // c1 =  2 10  3 11
    d1           = vec_mergel( b0, d1 );            // d1 =  6 14  7 15

    // Step 2: Interleave even and odd rows

    vec_st( vec_mergeh( a1, b1 ), 0, (float *)pa ); // a  =  0  4  8 12
    vec_st( vec_mergel( a1, b1 ), 0, (float *)pb ); // b  =  1  5  9 13
    vec_st( vec_mergeh( c1, d1 ), 0, (float *)pc ); // c  =  2  6 10 14
    vec_st( vec_mergel( c1, d1 ), 0, (float *)pd ); // d  =  3  7 11 15
  }

  //////////////
  // v4int class

  class v4int : public v4 {

    // v4int prefix unary operator friends

    friend inline v4int operator  +( const v4int & a );
    friend inline v4int operator  -( const v4int & a );
    friend inline v4int operator  ~( const v4int & a );
    friend inline v4int operator  !( const v4int & a );
    // Note: Referencing (*) and dereferencing (&) apply to the whole vector

    // v4int prefix increment / decrement operator friends

    friend inline v4int operator ++( v4int & a );
    friend inline v4int operator --( v4int & a );

    // v4int postfix increment / decrement operator friends

    friend inline v4int operator ++( v4int & a, int );
    friend inline v4int operator --( v4int & a, int );

    // v4int binary operator friends

    friend inline v4int operator  +( const v4int &a, const v4int &b );
    friend inline v4int operator  -( const v4int &a, const v4int &b );
    friend inline v4int operator  *( const v4int &a, const v4int &b );
    friend inline v4int operator  /( const v4int &a, const v4int &b );
    friend inline v4int operator  %( const v4int &a, const v4int &b );
    friend inline v4int operator  ^( const v4int &a, const v4int &b );
    friend inline v4int operator  &( const v4int &a, const v4int &b );
    friend inline v4int operator  |( const v4int &a, const v4int &b );
    friend inline v4int operator <<( const v4int &a, const v4int &b );
    friend inline v4int operator >>( const v4int &a, const v4int &b );

    // v4int logical operator friends

    friend inline v4int operator  <( const v4int &a, const v4int &b );
    friend inline v4int operator  >( const v4int &a, const v4int &b );
    friend inline v4int operator ==( const v4int &a, const v4int &b );
    friend inline v4int operator !=( const v4int &a, const v4int &b );
    friend inline v4int operator <=( const v4int &a, const v4int &b );
    friend inline v4int operator >=( const v4int &a, const v4int &b );
    friend inline v4int operator &&( const v4int &a, const v4int &b );
    friend inline v4int operator ||( const v4int &a, const v4int &b );

    // v4int miscellaneous friends

    friend inline v4int abs( const v4int &a );
    friend inline v4    czero( const v4int &c, const v4 &a );
    friend inline v4 notczero( const v4int &c, const v4 &a );
    // FIXME: cswap, notcswap!
    friend inline v4 merge( const v4int &c, const v4 &t, const v4 &f );

    // v4float unary operator friends

    friend inline v4int operator  !( const v4float & a ); 

    // v4float logical operator friends

    friend inline v4int operator  <( const v4float &a, const v4float &b );
    friend inline v4int operator  >( const v4float &a, const v4float &b );
    friend inline v4int operator ==( const v4float &a, const v4float &b );
    friend inline v4int operator !=( const v4float &a, const v4float &b );
    friend inline v4int operator <=( const v4float &a, const v4float &b );
    friend inline v4int operator >=( const v4float &a, const v4float &b );
    friend inline v4int operator &&( const v4float &a, const v4float &b );
    friend inline v4int operator ||( const v4float &a, const v4float &b );

    // v4float miscellaneous friends

    friend inline v4float clear_bits(  const v4int &m, const v4float &a );
    friend inline v4float set_bits(    const v4int &m, const v4float &a );
    friend inline v4float toggle_bits( const v4int &m, const v4float &a );

  public:

    // v4int constructors / destructors
    
    v4int() {}                              // Default constructor
    v4int( const v4int &a ) {               // Copy constructor
      v = a.v;
    }
    v4int( const v4 &a ) {                  // Initialize from mixed
      v = a.v;
    }
    v4int( const int &a ) {                 // Initialize from scalar
      v = (_v4_float)((_v4_int){ a, a, a, a });
    }
    v4int( const int &i0, const int &i1,
           const int &i2, const int &i3 ) { // Initialize from scalars
      v = (_v4_float)((_v4_int){ i0, i1, i2, i3 });
    }
    ~v4int() {}                             // Destructor
    
    // v4int assignment operators
  
#   define ASSIGN(op,instr)			  \
    inline v4int &operator op( const v4int &b ) { \
      instr;                                      \
      return *this;                               \
    }

    ASSIGN(=,   v = b.v )
    ASSIGN(+=,  v = (_v4_float)vec_add( (_v4_int)v, (_v4_int)b.v ) )
    ASSIGN(-=,  v = (_v4_float)vec_sub( (_v4_int)v, (_v4_int)b.v ) )
    ASSIGN(*=,  union { int i[4]; _v4_float v; } t;
                union { int i[4]; _v4_float v; } u;
                t.v = v; u.v = b.v;
                v = (_v4_float)((_v4_int){ t.i[0]*u.i[0],
                                           t.i[1]*u.i[1],
                                           t.i[2]*u.i[2],
                                           t.i[3]*u.i[3] }) ) // FIXME: Sigh ...
    ASSIGN(/=,  union { int i[4]; _v4_float v; } t;
                union { int i[4]; _v4_float v; } u;
                t.v = v; u.v = b.v;
                v = (_v4_float)((_v4_int){ t.i[0]/u.i[0],
                                           t.i[1]/u.i[1],
                                           t.i[2]/u.i[2],
                                           t.i[3]/u.i[3] }) ) // FIXME: Sigh ...
    ASSIGN(%=,  union { int i[4]; _v4_float v; } t;
                union { int i[4]; _v4_float v; } u;
                t.v = v; u.v = b.v;
                v = (_v4_float)((_v4_int){ t.i[0]%u.i[0],
                                           t.i[1]%u.i[1],
                                           t.i[2]%u.i[2],
                                           t.i[3]%u.i[3] }) ) // FIXME: Sigh ...
    ASSIGN(^=,  v = (_v4_float)vec_xor( (_v4_int)v, (_v4_int) b.v ) )
    ASSIGN(&=,  v = (_v4_float)vec_and( (_v4_int)v, (_v4_int) b.v ) )
    ASSIGN(|=,  v = (_v4_float)vec_or(  (_v4_int)v, (_v4_int) b.v ) )
    ASSIGN(<<=, v = (_v4_float)vec_sl(  (_v4_int)v, (_v4_uint)b.v ) )
    ASSIGN(>>=, v = (_v4_float)vec_sr(  (_v4_int)v, (_v4_uint)b.v ) )

#   undef ASSIGN

    // v4int member access operator
    
    // FIXME: [] operation probably breaks the compiler if used to modify
    // a vector!

    inline int &operator []( const int n ) { return ((int *)&v)[n]; }
    inline int  operator ()( const int n ) {
      union { int i[4]; _v4_float v; } t; t.v = v; return t.i[n];
    }

  };

  // v4int prefix unary operators

# define PREFIX_UNARY(op,instr)                 \
  inline v4int operator op( const v4int & a ) { \
    v4int b;                                    \
    instr;                                      \
    return b;                                   \
  }

  PREFIX_UNARY(+, b.v = a.v )
  PREFIX_UNARY(-, b.v = (_v4_float)vec_sub(   _false, (_v4_int)a.v ) )
  PREFIX_UNARY(!, b.v = (_v4_float)vec_cmpeq( _false, (_v4_int)a.v ) )
  PREFIX_UNARY(~, b.v = (_v4_float)vec_xor(   _true,  (_v4_int)a.v ) )
  
# undef PREFIX_UNARY

  // v4int prefix increment / decrement operators

  inline v4int operator ++( v4int &a ) {
    _v4_float a_v = (_v4_float)vec_add( (_v4_int)a.v, _ione );
    v4int b;
    a.v = a_v;
    b.v = a_v;
    return b;
  }

  inline v4int operator --( v4int &a ) {
    _v4_float a_v = (_v4_float)vec_sub( (_v4_int)a.v, _ione );
    v4int b;
    a.v = a_v;
    b.v = a_v;
    return b;
  }

  // v4int postfix increment / decrement operators

  inline v4int operator ++( v4int &a, int ) {
    _v4_float a_v = a.v;
    v4int b;
    a.v = (_v4_float)vec_add( (_v4_int)a_v, _ione );
    b.v = a_v;
    return b;
  }

  inline v4int operator --( v4int &a, int ) {
    _v4_float a_v = a.v;
    v4int b;
    a.v = (_v4_float)vec_sub( (_v4_int)a_v, _ione );
    b.v = a_v;
    return b;
  }

  // v4int binary operators
  
# define BINARY(op,instr)                                       \
  inline v4int operator op( const v4int &a, const v4int &b ) {	\
    v4int c;                                                    \
    instr;                                                      \
    return c;                                                   \
  }

  BINARY(+,  c.v = (_v4_float)vec_add( (_v4_int)a.v, (_v4_int) b.v ) )
  BINARY(-,  c.v = (_v4_float)vec_sub( (_v4_int)a.v, (_v4_int) b.v ) )
  BINARY(*,  union { int i[4]; _v4_float v; } t;
             union { int i[4]; _v4_float v; } u;
             t.v = a.v; u.v = b.v;
             c.v = (_v4_float)((_v4_int){ t.i[0]*u.i[0],
                                          t.i[1]*u.i[1],
                                          t.i[2]*u.i[2],
                                          t.i[3]*u.i[3] }) ) // FIXME: Sigh ...
  BINARY(/,  union { int i[4]; _v4_float v; } t;
             union { int i[4]; _v4_float v; } u;
             t.v = a.v; u.v = b.v;
             c.v = (_v4_float)((_v4_int){ t.i[0]/u.i[0],
                                          t.i[1]/u.i[1],
                                          t.i[2]/u.i[2],
                                          t.i[3]/u.i[3] }) ) // FIXME: Sigh ...
  BINARY(%,  union { int i[4]; _v4_float v; } t;
             union { int i[4]; _v4_float v; } u;
             t.v = a.v; u.v = b.v;
             c.v = (_v4_float)((_v4_int){ t.i[0]%u.i[0],
                                          t.i[1]%u.i[1],
                                          t.i[2]%u.i[2],
                                          t.i[3]%u.i[3] }) ) // FIXME: Sigh ...
  BINARY(^,  c.v = (_v4_float)vec_xor( (_v4_int)a.v, (_v4_int) b.v ) )
  BINARY(&,  c.v = (_v4_float)vec_and( (_v4_int)a.v, (_v4_int) b.v ) )
  BINARY(|,  c.v = (_v4_float)vec_or(  (_v4_int)a.v, (_v4_int) b.v ) )
  BINARY(<<, c.v = (_v4_float)vec_sl(  (_v4_int)a.v, (_v4_uint)b.v ) )
  BINARY(>>, c.v = (_v4_float)vec_sr(  (_v4_int)a.v, (_v4_uint)b.v ) )

# undef BINARY

  // v4int logical operators

# define LOGICAL(op,instr)                                     \
  inline v4int operator op( const v4int &a, const v4int &b ) { \
    v4int c;                                                   \
    instr;                                                     \
    return c;                                                  \
  }

  LOGICAL(<,  c.v = (_v4_float)vec_cmplt( (_v4_int)a.v, (_v4_int)b.v ) )
  LOGICAL(>,  c.v = (_v4_float)vec_cmpgt( (_v4_int)a.v, (_v4_int)b.v ) )
  LOGICAL(==, c.v = (_v4_float)vec_cmpeq( (_v4_int)a.v, (_v4_int)b.v ) )
  LOGICAL(!=, c.v = (_v4_float)vec_xor( _true, vec_cmpeq( (_v4_int)a.v, 
                                                          (_v4_int)b.v ) ) )
  LOGICAL(<=, c.v = (_v4_float)vec_xor( _true, vec_cmpgt( (_v4_int)a.v, 
                                                          (_v4_int)b.v ) ) )
  LOGICAL(>=, c.v = (_v4_float)vec_xor( _true, vec_cmplt( (_v4_int)a.v,
                                                          (_v4_int)b.v ) ) )
  LOGICAL(&&, c.v = (_v4_float)vec_xor( _true,
                                        vec_or( vec_cmpeq( (_v4_int)a.v,
                                                           _false ),
                                                vec_cmpeq( (_v4_int)b.v,
                                                           _false ) ) ) )
  LOGICAL(||, c.v = (_v4_float)vec_xor( _true,
                                        vec_and( vec_cmpeq( (_v4_int)a.v,
                                                            _false ),
                                                 vec_cmpeq( (_v4_int)b.v,
                                                            _false ) ) ) )
  
# undef LOGICAL

  // v4int miscellaneous functions

  inline v4int abs( const v4int &a ) {
    v4int b;
    b.v = (_v4_float)vec_abs( (_v4_int)a.v );
    return b;
  }

  inline v4 czero( const v4int &c, const v4 &a ) {
    v4 b;
    b.v = vec_andc( a.v, c.v );
    return b;
  }

  inline v4 notczero( const v4int &c, const v4 &a ) {
    v4 b;
    b.v = vec_and( a.v, c.v );
    return b;
  }
  
  inline v4 merge( const v4int &c, const v4 &t, const v4 &f ) {
    v4 m;
    m.v = vec_sel( f.v, t.v, (_v4_uint)c.v );
    return m;
  }

  ////////////////
  // v4float class

  class v4float : public v4 {

    // v4float prefix unary operator friends

    friend inline v4float operator  +( const v4float &a );
    friend inline v4float operator  -( const v4float &a );
    friend inline v4float operator  ~( const v4float &a );
    friend inline v4int   operator  !( const v4float &a );
    // Note: Referencing (*) and dereferencing (&) apply to the whole vector

    // v4float prefix increment / decrement operator friends

    friend inline v4float operator ++( v4float &a );
    friend inline v4float operator --( v4float &a );

    // v4float postfix increment / decrement operator friends

    friend inline v4float operator ++( v4float &a, int );
    friend inline v4float operator --( v4float &a, int );

    // v4float binary operator friends

    friend inline v4float operator  +( const v4float &a, const v4float &b );
    friend inline v4float operator  -( const v4float &a, const v4float &b );
    friend inline v4float operator  *( const v4float &a, const v4float &b );
    friend inline v4float operator  /( const v4float &a, const v4float &b );

    // v4float logical operator friends

    friend inline v4int operator  <( const v4float &a, const v4float &b );
    friend inline v4int operator  >( const v4float &a, const v4float &b );
    friend inline v4int operator ==( const v4float &a, const v4float &b );
    friend inline v4int operator !=( const v4float &a, const v4float &b );
    friend inline v4int operator <=( const v4float &a, const v4float &b );
    friend inline v4int operator >=( const v4float &a, const v4float &b );
    friend inline v4int operator &&( const v4float &a, const v4float &b );
    friend inline v4int operator ||( const v4float &a, const v4float &b );

    // v4float math library friends

#   define CMATH_FR1(fn) friend inline v4float fn( const v4float &a )
#   define CMATH_FR2(fn) friend inline v4float fn( const v4float &a,  \
                                                   const v4float &b )

    CMATH_FR1(acos);  CMATH_FR1(asin);  CMATH_FR1(atan); CMATH_FR2(atan2);
    CMATH_FR1(ceil);  CMATH_FR1(cos);   CMATH_FR1(cosh); CMATH_FR1(exp);
    CMATH_FR1(fabs);  CMATH_FR1(floor); CMATH_FR2(fmod); CMATH_FR1(log);
    CMATH_FR1(log10); CMATH_FR2(pow);   CMATH_FR1(sin);  CMATH_FR1(sinh);
    CMATH_FR1(sqrt);  CMATH_FR1(tan);   CMATH_FR1(tanh);

    CMATH_FR2(copysign);

#   undef CMATH_FR1
#   undef CMATH_FR2

    // v4float miscellaneous friends

    friend inline v4float rsqrt_approx( const v4float &a );
    friend inline v4float rsqrt( const v4float &a );
    friend inline v4float rcp_approx( const v4float &a );
    friend inline v4float rcp( const v4float &a );
    friend inline v4float fma(  const v4float &a, const v4float &b, const v4float &c );
    friend inline v4float fms(  const v4float &a, const v4float &b, const v4float &c );
    friend inline v4float fnms( const v4float &a, const v4float &b, const v4float &c );
    friend inline v4float clear_bits(  const v4int &m, const v4float &a );
    friend inline v4float set_bits(    const v4int &m, const v4float &a );
    friend inline v4float toggle_bits( const v4int &m, const v4float &a );
    friend inline void increment_4x1( float * ALIGNED(16) p, const v4float &a );
    friend inline void decrement_4x1( float * ALIGNED(16) p, const v4float &a );
    friend inline void scale_4x1(     float * ALIGNED(16) p, const v4float &a );
    // FIXME: crack
    
  public:

    // v4float constructors / destructors
    
    v4float() {}                                  // Default constructor
    v4float( const v4float &a ) {                 // Copy constructor
      v = a.v;
    }
    v4float( const v4 &a ) {                      // Initialize from mixed
      v = a.v;
    }
    v4float( const float &a ) {                   // Initialize from scalar
      v = (_v4_float){ a, a, a, a };
    }
    v4float( const float &f0, const float &f1,
             const float &f2, const float &f3 ) { // Initialize from scalars
      v = (_v4_float){ f0, f1, f2, f3 };
    }
    ~v4float() {}                                 // Destructor

    // v4float assignment operators

#   define ASSIGN(op,instr)                             \
    inline v4float &operator op( const v4float &b ) {	\
      instr;                                            \
      return *this;                                     \
    }

    ASSIGN(=,  v = b.v );
    ASSIGN(+=, v = vec_add(v,b.v) );
    ASSIGN(-=, v = vec_sub(v,b.v) );
    ASSIGN(*=, v = vec_madd(v,b.v,_zero) );

    inline v4float &operator /=( const v4float &a ) {
      _v4_float a_v = a.v, b_v;

      // Compute an estimate of the reciprocal of a (??-bit accurate)

      b_v = vec_re( a_v );

      // FIXME: CHECK NUMERICS ... HOW MANY N-R STEPS TO USE?  APPLE'S
      // ALTIVEC WEB PAGE SUGGESTS TWO STEPS AND GIVES THE BELOW
      // IMPLEMENTATION FOR THE REFINEMENT.

      // FIXME: IS THIS THE MOST ACCURATE FORM FOR THE REFINEMENT?
      // THE SPU IMPLEMENTATION HAS AN ALTERNATE THAT MAY BE MORE
      // ACCURATE (OR AT LEAST USES FEWER CONSTANTS).

      b_v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );
      b_v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );

      // Compute n * refined( (1/a)_estimate ) to get result n/a

      v = vec_madd( v, b_v, _zero );

      return *this;
    }

#   undef ASSIGN

    // v4float member access operator

    // FIXME: [] operation probably breaks the compiler if used to modify
    // a vector!

    inline float &operator []( const int n ) { return ((float *)&v)[n]; }
    inline float  operator ()( const int n ) {
      union { float f[4]; _v4_float v; } t; t.v = v; return t.f[n];
    }

  };

  // v4float prefix unary operators

  inline v4float operator +( const v4float &a ) {
    v4float b;
    b.v = a.v;
    return b;
  }

  inline v4float operator -( const v4float &a ) {
    v4float b;
    b.v = vec_sub( _zero, a.v );
    return b;
  }

  inline v4int operator !( const v4float &a ) {
    v4int b;
    b.v = (_v4_float)vec_cmpeq( a.v, _zero );
    return b;
  }

  // v4float prefix increment / decrement operators

  inline v4float operator ++( v4float &a ) {
    _v4_float a_v = vec_add( a.v, _one );
    v4float b;
    a.v = a_v;
    b.v = a_v;
    return b;
  }

  inline v4float operator --( v4float &a ) {
    _v4_float a_v = vec_sub( a.v, _one );
    v4float b;
    a.v = a_v;
    b.v = a_v;
    return b;
  }

  // v4float postfix increment / decrement operators

  inline v4float operator ++( v4float &a, int ) {
    _v4_float a_v = a.v;
    v4float b;
    a.v = vec_add( a_v, _one );
    b.v = a_v;
    return b;
  }

  inline v4float operator --( v4float &a, int ) {
    _v4_float a_v = a.v;
    v4float b;
    a.v = vec_sub( a_v, _one );
    b.v = a_v;
    return b;
  }

  // v4float binary operators
    
# define BINARY(op,instr)                                            \
  inline v4float operator op( const v4float &a, const v4float &b ) { \
    v4float c;                                                       \
    instr;                                                           \
    return c;                                                        \
  }

  BINARY(+, c.v = vec_add( a.v, b.v ) )
  BINARY(-, c.v = vec_sub( a.v, b.v ) )
  BINARY(*, c.v = vec_madd( a.v, b.v, _zero ) )

  inline v4float operator /( const v4float &n, const v4float &a ) {
    _v4_float a_v = a.v, b_v;
    v4float c;

    // Compute an estimate of the reciprocal of a (??-bit accurate)

    b_v = vec_re( a_v );

    // FIXME: CHECK NUMERICS ... HOW MANY N-R STEPS TO USE?  APPLE'S
    // ALTIVEC WEB PAGE SUGGESTS TWO STEPS AND GIVES THE BELOW
    // IMPLEMENTATION FOR THE REFINEMENT.

    // FIXME: IS THIS THE MOST ACCURATE FORM FOR THE REFINEMENT?
    // THE SPU IMPLEMENTATION HAS AN ALTERNATE THAT MAY BE MORE
    // ACCURATE (OR AT LEAST USES FEWER CONSTANTS).

    b_v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );
    b_v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );

    // Compute n * refined( (1/a)_estimate ) to get result n/a
    
    c.v = vec_madd( n.v, b_v, _zero );

    return c;
  }

# undef BINARY

  // v4float logical operators

# define LOGICAL(op,instr)                                         \
  inline v4int operator op( const v4float &a, const v4float &b ) { \
    v4int c;                                                       \
    instr;                                                         \
    return c;                                                      \
  }

  LOGICAL(<,  c.v = (_v4_float)vec_cmplt( a.v, b.v ) )
  LOGICAL(>,  c.v = (_v4_float)vec_cmpgt( a.v, b.v ) )
  LOGICAL(==, c.v = (_v4_float)vec_cmpeq( a.v, b.v ) )
  LOGICAL(!=, c.v = (_v4_float)vec_xor( vec_cmpeq( a.v, b.v ), _true ) )
  LOGICAL(<=, c.v = (_v4_float)vec_cmple( a.v, b.v ) )
  LOGICAL(>=, c.v = (_v4_float)vec_cmpge( a.v, b.v ) )
  LOGICAL(&&, c.v = (_v4_float)vec_xor( vec_or( vec_cmpeq( a.v, _zero ),
                                                vec_cmpeq( b.v, _zero ) ),
                                        _true ) )
  LOGICAL(||, c.v = (_v4_float)vec_xor( vec_and( vec_cmpeq( a.v, _zero ),
                                                 vec_cmpeq( b.v, _zero ) ),
                                        _true ) )

# undef LOGICAL

  // v4float math library functions

# define CMATH_FR1(fn)                    \
  inline v4float fn( const v4float &a ) { \
    union { float f[4]; _v4_float v; } t; \
    v4float b;                            \
    t.v = a.v;                            \
    b.v = (_v4_float){ ::fn( t.f[0] ),    \
                       ::fn( t.f[1] ),    \
                       ::fn( t.f[2] ),    \
                       ::fn( t.f[3] ) };  \
    return b;                             \
  }
  
# define CMATH_FR2(fn)                                      \
  inline v4float fn( const v4float &a, const v4float &b ) { \
    union { float f[4]; _v4_float v; } t;                   \
    union { float f[4]; _v4_float v; } u;                   \
    v4float c;                                              \
    t.v = a.v;                                              \
    u.v = b.v;                                              \
    c.v = (_v4_float){ ::fn( t.f[0], u.f[0] ),              \
                       ::fn( t.f[1], u.f[1] ),              \
                       ::fn( t.f[2], u.f[2] ),              \
                       ::fn( t.f[3], u.f[3] ) };            \
    return c;                                               \
  }

  CMATH_FR1(acos)     CMATH_FR1(asin)  CMATH_FR1(atan) CMATH_FR2(atan2)
  CMATH_FR1(ceil)     CMATH_FR1(cos)   CMATH_FR1(cosh) CMATH_FR1(exp)
  /*CMATH_FR1(fabs)*/ CMATH_FR1(floor) CMATH_FR2(fmod) CMATH_FR1(log)
  CMATH_FR1(log10)    CMATH_FR2(pow)   CMATH_FR1(sin)  CMATH_FR1(sinh)
  /*CMATH_FR1(sqrt)*/ CMATH_FR1(tan)   CMATH_FR1(tanh)

  inline v4float fabs( const v4float &a ) {
    v4float b;
    b.v = vec_andc( a.v, _sign );
    return b;
  }

  inline v4float sqrt( const v4float &a ) {
    _v4_float a_v = a.v, b_v;
    v4float b;

    // Compute an estimate of the rsqrt (??-bit accurate)

    b_v = vec_rsqrte( a_v );

    // FIXME: CHECK NUMERICS.  HOW MANY N-R STEPS NECESSARY?
    // APPLE'S ALTIVEC PAGE SUGGESTS TWO.

    b_v = vec_madd( vec_nmsub( vec_madd( b_v, b_v,   _zero ), a_v, _one ),
                    vec_madd( b_v, _half, _zero ),
                    b_v );
    b_v = vec_madd( vec_nmsub( vec_madd( b_v, b_v,   _zero ), a_v, _one ),
                    vec_madd( b_v, _half, _zero ),
                    b_v );

    // Compute the sqrt(a) via a*refined_rsqrt_estimate(a) ~ sqrt(a)

    b.v = vec_madd( a_v, b_v, _zero );

    return b;
  }

  inline v4float copysign( const v4float &a, const v4float &b ) {
    v4float c;
    c.v = vec_or( vec_andc( a.v, _sign ), vec_and( b.v, _sign ) );
    return c;
  }

# undef CMATH_FR1
# undef CMATH_FR2

  // v4float miscelleanous functions
  
  inline v4float rsqrt_approx( const v4float &a ) {
    v4float b;
    b.v = vec_rsqrte( a.v );
    return b;
  }
  
  inline v4float rsqrt( const v4float &a ) {
    _v4_float a_v = a.v, b_v;
    v4float b;

    // Compute an estimate of the rsqrt (??-bit accurate)

    b_v = vec_rsqrte( a_v );

    // FIXME: CHECK NUMERICS.  HOW MANY N-R STEPS NECESSARY?
    // APPLE'S ALTIVEC PAGE SUGGESTS TWO.

    b_v = vec_madd( vec_nmsub( vec_madd( b_v, b_v,   _zero ), a_v, _one ),
                    vec_madd( b_v, _half, _zero ),
                    b_v );
    b.v = vec_madd( vec_nmsub( vec_madd( b_v, b_v,   _zero ), a_v, _one ),
                    vec_madd( b_v, _half, _zero ),
                    b_v );

    return b;
  }

  inline v4float rcp_approx( const v4float &a ) {
    v4float b;
    b.v = vec_re( a.v );
    return b;
  }
  
  inline v4float rcp( const v4float &a ) {
    _v4_float a_v = a.v, b_v;
    v4float b;

    // Compute an estimate of the reciprocal of a (??-bit accurate)

    b_v = vec_re( a_v );

    // FIXME: CHECK NUMERICS ... HOW MANY N-R STEPS TO USE?  APPLE'S
    // ALTIVEC WEB PAGE SUGGESTS TWO STEPS AND GIVES THE BELOW
    // IMPLEMENTATION FOR THE REFINEMENT.

    // FIXME: IS THIS THE MOST ACCURATE FORM FOR THE REFINEMENT?
    // THE SPU IMPLEMENTATION HAS AN ALTERNATE THAT MAY BE MORE
    // ACCURATE (OR AT LEAST USES FEWER CONSTANTS).

    b_v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );
    b.v = vec_madd( vec_nmsub( b_v, a_v, _one ), b_v, b_v );

    return b;
  }

  inline v4float fma(  const v4float &a, const v4float &b, const v4float &c ) {
    v4float d;
    d.v = vec_madd( a.v, b.v, c.v );
    return d;
  }

  inline v4float fms(  const v4float &a, const v4float &b, const v4float &c ) {
    v4float d;
    d.v = vec_sub( _zero, vec_nmsub( a.v, b.v, c.v ) ); // FIXME: Sigh ...
    return d;
  }

  inline v4float fnms( const v4float &a, const v4float &b, const v4float &c ) {
    v4float d;
    d.v = vec_nmsub( a.v, b.v, c.v );
    return d;
  }

  inline v4float clear_bits(  const v4int &m, const v4float &a ) {
    v4float b;
    b.v = vec_andc( a.v, m.v );
    return b;
  }

  inline v4float set_bits(    const v4int &m, const v4float &a ) {
    v4float b;
    b.v = vec_or( a.v, m.v );
    return b;
  }

  inline v4float toggle_bits( const v4int &m, const v4float &a ) {
    v4float b;
    b.v = vec_xor( a.v, m.v );
    return b;
  }
  
  inline void increment_4x1( float * ALIGNED(16) p, const v4float &a ) {
    vec_st( vec_add( vec_ld( 0, p ), a.v ), 0, p );
  }

  inline void decrement_4x1( float * ALIGNED(16) p, const v4float &a ) {
    vec_st( vec_sub( vec_ld( 0, p ), a.v ), 0, p );
  }

  inline void scale_4x1( float * ALIGNED(16) p, const v4float &a ) {
    vec_st( vec_madd( vec_ld( 0, p ), a.v, _zero ), 0, p );
  }

# undef _v4_int
# undef _v4_uint
# undef _v4_float

} // namespace v4

#endif // _v4_altivec_hxx_
