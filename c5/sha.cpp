// sha.cpp - modified by Wei Dai from Steve Reid's public domain sha1.c

// Steve Reid implemented SHA-1. Wei Dai implemented SHA-2.
// Both are in the public domain.

#include "pch.h"

#ifndef CRYPTOPP_IMPORTS

#include "sha.h"
#include "misc.h"

NAMESPACE_BEGIN(CryptoPP)

// start of Steve Reid's code

#define blk0(i) (W[i] = data[i])
#define blk1(i) (W[i&15] = rotlFixed(W[(i+13)&15]^W[(i+8)&15]^W[(i+2)&15]^W[i&15],1))

void SHA::InitState(HashWordType *state)
{
	state[0] = 0x67452301L;
	state[1] = 0xEFCDAB89L;
	state[2] = 0x98BADCFEL;
	state[3] = 0x10325476L;
	state[4] = 0xC3D2E1F0L;
}

#define f1(x,y,z) (z^(x&(y^z)))
#define f2(x,y,z) (x^y^z)
#define f3(x,y,z) ((x&y)|(z&(x|y)))
#define f4(x,y,z) (x^y^z)

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=f1(w,x,y)+blk0(i)+0x5A827999+rotlFixed(v,5);w=rotlFixed(w,30);
#define R1(v,w,x,y,z,i) z+=f1(w,x,y)+blk1(i)+0x5A827999+rotlFixed(v,5);w=rotlFixed(w,30);
#define R2(v,w,x,y,z,i) z+=f2(w,x,y)+blk1(i)+0x6ED9EBA1+rotlFixed(v,5);w=rotlFixed(w,30);
#define R3(v,w,x,y,z,i) z+=f3(w,x,y)+blk1(i)+0x8F1BBCDC+rotlFixed(v,5);w=rotlFixed(w,30);
#define R4(v,w,x,y,z,i) z+=f4(w,x,y)+blk1(i)+0xCA62C1D6+rotlFixed(v,5);w=rotlFixed(w,30);

void SHA::Transform(word32 *state, const word32 *data)
{
	word32 W[16];
    /* Copy context->state[] to working vars */
    word32 a = state[0];
    word32 b = state[1];
    word32 c = state[2];
    word32 d = state[3];
    word32 e = state[4];
    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
    R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
    R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
    R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
    R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);
    R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
    R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
    R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
    R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
    R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);
    R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
    R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
    R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
    R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
    R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);
    R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
    R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
    R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
    R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
    R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
	memset(W, 0, sizeof(W));
}

// end of Steve Reid's code

// *************************************************************

void SHA256::InitState(HashWordType *state)
{
	state[0] = 0x6a09e667;
	state[1] = 0xbb67ae85;
	state[2] = 0x3c6ef372;
	state[3] = 0xa54ff53a;
	state[4] = 0x510e527f;
	state[5] = 0x9b05688c;
	state[6] = 0x1f83d9ab;
	state[7] = 0x5be0cd19;
}

#define blk2(i) (W[i&15]+=s1(W[(i-2)&15])+W[(i-7)&15]+s0(W[(i-15)&15]))

#define Ch(x,y,z) (z^(x&(y^z)))
#define Maj(x,y,z) ((x&y)|(z&(x|y)))

#define a(i) T[(0-i)&7]
#define b(i) T[(1-i)&7]
#define c(i) T[(2-i)&7]
#define d(i) T[(3-i)&7]
#define e(i) T[(4-i)&7]
#define f(i) T[(5-i)&7]
#define g(i) T[(6-i)&7]
#define h(i) T[(7-i)&7]

#define R(i) h(i)+=S1(e(i))+Ch(e(i),f(i),g(i))+K[i+j]+(j?blk2(i):blk0(i));\
	d(i)+=h(i);h(i)+=S0(a(i))+Maj(a(i),b(i),c(i))

// for SHA256
#define S0(x) (rotrFixed(x,2)^rotrFixed(x,13)^rotrFixed(x,22))
#define S1(x) (rotrFixed(x,6)^rotrFixed(x,11)^rotrFixed(x,25))
#define s0(x) (rotrFixed(x,7)^rotrFixed(x,18)^(x>>3))
#define s1(x) (rotrFixed(x,17)^rotrFixed(x,19)^(x>>10))

void SHA256::Transform(word32 *state, const word32 *data)
{
	word32 W[16];
	word32 T[8];
    /* Copy context->state[] to working vars */
	memcpy(T, state, sizeof(T));
    /* 64 operations, partially loop unrolled */
	for (unsigned int j=0; j<64; j+=16)
	{
		R( 0); R( 1); R( 2); R( 3);
		R( 4); R( 5); R( 6); R( 7);
		R( 8); R( 9); R(10); R(11);
		R(12); R(13); R(14); R(15);
	}
    /* Add the working vars back into context.state[] */
    state[0] += a(0);
    state[1] += b(0);
    state[2] += c(0);
    state[3] += d(0);
    state[4] += e(0);
    state[5] += f(0);
    state[6] += g(0);
    state[7] += h(0);
    /* Wipe variables */
	memset(W, 0, sizeof(W));
	memset(T, 0, sizeof(T));
}

#undef S0
#undef S1
#undef s0
#undef s1

const word32 SHA256::K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void SHA224::InitState(HashWordType *state)
{
	state[0] = 0xc1059ed8;
	state[1] = 0x367cd507;
	state[2] = 0x3070dd17;
	state[3] = 0xf70e5939;
	state[4] = 0xffc00b31;
	state[5] = 0x68581511;
	state[6] = 0x64f98fa7;
	state[7] = 0xbefa4fa4;
}

// *************************************************************

#ifdef WORD64_AVAILABLE

void SHA512::InitState(HashWordType *state)
{
	state[0] = W64LIT(0x6a09e667f3bcc908);
	state[1] = W64LIT(0xbb67ae8584caa73b);
	state[2] = W64LIT(0x3c6ef372fe94f82b);
	state[3] = W64LIT(0xa54ff53a5f1d36f1);
	state[4] = W64LIT(0x510e527fade682d1);
	state[5] = W64LIT(0x9b05688c2b3e6c1f);
	state[6] = W64LIT(0x1f83d9abfb41bd6b);
	state[7] = W64LIT(0x5be0cd19137e2179);
}

// for SHA512
#define S0(x) (rotrFixed(x,28)^rotrFixed(x,34)^rotrFixed(x,39))
#define S1(x) (rotrFixed(x,14)^rotrFixed(x,18)^rotrFixed(x,41))
#define s0(x) (rotrFixed(x,1)^rotrFixed(x,8)^(x>>7))
#define s1(x) (rotrFixed(x,19)^rotrFixed(x,61)^(x>>6))

void SHA512::Transform(word64 *state, const word64 *data)
{
	word64 W[16];
	word64 T[8];
    /* Copy context->state[] to working vars */
	memcpy(T, state, sizeof(T));
    /* 80 operations, partially loop unrolled */
	for (unsigned int j=0; j<80; j+=16)
	{
		R( 0); R( 1); R( 2); R( 3);
		R( 4); R( 5); R( 6); R( 7);
		R( 8); R( 9); R(10); R(11);
		R(12); R(13); R(14); R(15);
	}
    /* Add the working vars back into context.state[] */
    state[0] += a(0);
    state[1] += b(0);
    state[2] += c(0);
    state[3] += d(0);
    state[4] += e(0);
    state[5] += f(0);
    state[6] += g(0);
    state[7] += h(0);
    /* Wipe variables */
	memset(W, 0, sizeof(W));
	memset(T, 0, sizeof(T));
}

const word64 SHA512::K[80] = {
	W64LIT(0x428a2f98d728ae22), W64LIT(0x7137449123ef65cd),
	W64LIT(0xb5c0fbcfec4d3b2f), W64LIT(0xe9b5dba58189dbbc),
	W64LIT(0x3956c25bf348b538), W64LIT(0x59f111f1b605d019),
	W64LIT(0x923f82a4af194f9b), W64LIT(0xab1c5ed5da6d8118),
	W64LIT(0xd807aa98a3030242), W64LIT(0x12835b0145706fbe),
	W64LIT(0x243185be4ee4b28c), W64LIT(0x550c7dc3d5ffb4e2),
	W64LIT(0x72be5d74f27b896f), W64LIT(0x80deb1fe3b1696b1),
	W64LIT(0x9bdc06a725c71235), W64LIT(0xc19bf174cf692694),
	W64LIT(0xe49b69c19ef14ad2), W64LIT(0xefbe4786384f25e3),
	W64LIT(0x0fc19dc68b8cd5b5), W64LIT(0x240ca1cc77ac9c65),
	W64LIT(0x2de92c6f592b0275), W64LIT(0x4a7484aa6ea6e483),
	W64LIT(0x5cb0a9dcbd41fbd4), W64LIT(0x76f988da831153b5),
	W64LIT(0x983e5152ee66dfab), W64LIT(0xa831c66d2db43210),
	W64LIT(0xb00327c898fb213f), W64LIT(0xbf597fc7beef0ee4),
	W64LIT(0xc6e00bf33da88fc2), W64LIT(0xd5a79147930aa725),
	W64LIT(0x06ca6351e003826f), W64LIT(0x142929670a0e6e70),
	W64LIT(0x27b70a8546d22ffc), W64LIT(0x2e1b21385c26c926),
	W64LIT(0x4d2c6dfc5ac42aed), W64LIT(0x53380d139d95b3df),
	W64LIT(0x650a73548baf63de), W64LIT(0x766a0abb3c77b2a8),
	W64LIT(0x81c2c92e47edaee6), W64LIT(0x92722c851482353b),
	W64LIT(0xa2bfe8a14cf10364), W64LIT(0xa81a664bbc423001),
	W64LIT(0xc24b8b70d0f89791), W64LIT(0xc76c51a30654be30),
	W64LIT(0xd192e819d6ef5218), W64LIT(0xd69906245565a910),
	W64LIT(0xf40e35855771202a), W64LIT(0x106aa07032bbd1b8),
	W64LIT(0x19a4c116b8d2d0c8), W64LIT(0x1e376c085141ab53),
	W64LIT(0x2748774cdf8eeb99), W64LIT(0x34b0bcb5e19b48a8),
	W64LIT(0x391c0cb3c5c95a63), W64LIT(0x4ed8aa4ae3418acb),
	W64LIT(0x5b9cca4f7763e373), W64LIT(0x682e6ff3d6b2b8a3),
	W64LIT(0x748f82ee5defb2fc), W64LIT(0x78a5636f43172f60),
	W64LIT(0x84c87814a1f0ab72), W64LIT(0x8cc702081a6439ec),
	W64LIT(0x90befffa23631e28), W64LIT(0xa4506cebde82bde9),
	W64LIT(0xbef9a3f7b2c67915), W64LIT(0xc67178f2e372532b),
	W64LIT(0xca273eceea26619c), W64LIT(0xd186b8c721c0c207),
	W64LIT(0xeada7dd6cde0eb1e), W64LIT(0xf57d4f7fee6ed178),
	W64LIT(0x06f067aa72176fba), W64LIT(0x0a637dc5a2c898a6),
	W64LIT(0x113f9804bef90dae), W64LIT(0x1b710b35131c471b),
	W64LIT(0x28db77f523047d84), W64LIT(0x32caab7b40c72493),
	W64LIT(0x3c9ebe0a15c9bebc), W64LIT(0x431d67c49c100d4c),
	W64LIT(0x4cc5d4becb3e42b6), W64LIT(0x597f299cfc657e2a),
	W64LIT(0x5fcb6fab3ad6faec), W64LIT(0x6c44198c4a475817)
};

void SHA384::InitState(HashWordType *state)
{
	state[0] = W64LIT(0xcbbb9d5dc1059ed8);
	state[1] = W64LIT(0x629a292a367cd507);
	state[2] = W64LIT(0x9159015a3070dd17);
	state[3] = W64LIT(0x152fecd8f70e5939);
	state[4] = W64LIT(0x67332667ffc00b31);
	state[5] = W64LIT(0x8eb44a8768581511);
	state[6] = W64LIT(0xdb0c2e0d64f98fa7);
	state[7] = W64LIT(0x47b5481dbefa4fa4);
}

#endif

NAMESPACE_END

#endif	// #ifndef CRYPTOPP_IMPORTS