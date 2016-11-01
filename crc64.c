#include <intrin.h>
#include <stdint.h>

// Poly = 0x42F0E1EBA9EA3693
static const uint64_t crcTable[256] = {
	0x0000000000000000, 0xB32E4CBE03A75F6F, 0xF4843657A840A05B, 0x47AA7AE9ABE7FF34,
	0x7BD0C384FF8F5E33, 0xC8FE8F3AFC28015C, 0x8F54F5D357CFFE68, 0x3C7AB96D5468A107,
	0xF7A18709FF1EBC66, 0x448FCBB7FCB9E309, 0x0325B15E575E1C3D, 0xB00BFDE054F94352,
	0x8C71448D0091E255, 0x3F5F08330336BD3A, 0x78F572DAA8D1420E, 0xCBDB3E64AB761D61,
	0x7D9BA13851336649, 0xCEB5ED8652943926, 0x891F976FF973C612, 0x3A31DBD1FAD4997D,
	0x064B62BCAEBC387A, 0xB5652E02AD1B6715, 0xF2CF54EB06FC9821, 0x41E11855055BC74E,
	0x8A3A2631AE2DDA2F, 0x39146A8FAD8A8540, 0x7EBE1066066D7A74, 0xCD905CD805CA251B,
	0xF1EAE5B551A2841C, 0x42C4A90B5205DB73, 0x056ED3E2F9E22447, 0xB6409F5CFA457B28,
	0xFB374270A266CC92, 0x48190ECEA1C193FD, 0x0FB374270A266CC9, 0xBC9D3899098133A6,
	0x80E781F45DE992A1, 0x33C9CD4A5E4ECDCE, 0x7463B7A3F5A932FA, 0xC74DFB1DF60E6D95,
	0x0C96C5795D7870F4, 0xBFB889C75EDF2F9B, 0xF812F32EF538D0AF, 0x4B3CBF90F69F8FC0,
	0x774606FDA2F72EC7, 0xC4684A43A15071A8, 0x83C230AA0AB78E9C, 0x30EC7C140910D1F3,
	0x86ACE348F355AADB, 0x3582AFF6F0F2F5B4, 0x7228D51F5B150A80, 0xC10699A158B255EF,
	0xFD7C20CC0CDAF4E8, 0x4E526C720F7DAB87, 0x09F8169BA49A54B3, 0xBAD65A25A73D0BDC,
	0x710D64410C4B16BD, 0xC22328FF0FEC49D2, 0x85895216A40BB6E6, 0x36A71EA8A7ACE989,
	0x0ADDA7C5F3C4488E, 0xB9F3EB7BF06317E1, 0xFE5991925B84E8D5, 0x4D77DD2C5823B7BA,
	0x64B62BCAEBC387A1, 0xD7986774E864D8CE, 0x90321D9D438327FA, 0x231C512340247895,
	0x1F66E84E144CD992, 0xAC48A4F017EB86FD, 0xEBE2DE19BC0C79C9, 0x58CC92A7BFAB26A6,
	0x9317ACC314DD3BC7, 0x2039E07D177A64A8, 0x67939A94BC9D9B9C, 0xD4BDD62ABF3AC4F3,
	0xE8C76F47EB5265F4, 0x5BE923F9E8F53A9B, 0x1C4359104312C5AF, 0xAF6D15AE40B59AC0,
	0x192D8AF2BAF0E1E8, 0xAA03C64CB957BE87, 0xEDA9BCA512B041B3, 0x5E87F01B11171EDC,
	0x62FD4976457FBFDB, 0xD1D305C846D8E0B4, 0x96797F21ED3F1F80, 0x2557339FEE9840EF,
	0xEE8C0DFB45EE5D8E, 0x5DA24145464902E1, 0x1A083BACEDAEFDD5, 0xA9267712EE09A2BA,
	0x955CCE7FBA6103BD, 0x267282C1B9C65CD2, 0x61D8F8281221A3E6, 0xD2F6B4961186FC89,
	0x9F8169BA49A54B33, 0x2CAF25044A02145C, 0x6B055FEDE1E5EB68, 0xD82B1353E242B407,
	0xE451AA3EB62A1500, 0x577FE680B58D4A6F, 0x10D59C691E6AB55B, 0xA3FBD0D71DCDEA34,
	0x6820EEB3B6BBF755, 0xDB0EA20DB51CA83A, 0x9CA4D8E41EFB570E, 0x2F8A945A1D5C0861,
	0x13F02D374934A966, 0xA0DE61894A93F609, 0xE7741B60E174093D, 0x545A57DEE2D35652,
	0xE21AC88218962D7A, 0x5134843C1B317215, 0x169EFED5B0D68D21, 0xA5B0B26BB371D24E,
	0x99CA0B06E7197349, 0x2AE447B8E4BE2C26, 0x6D4E3D514F59D312, 0xDE6071EF4CFE8C7D,
	0x15BB4F8BE788911C, 0xA6950335E42FCE73, 0xE13F79DC4FC83147, 0x521135624C6F6E28,
	0x6E6B8C0F1807CF2F, 0xDD45C0B11BA09040, 0x9AEFBA58B0476F74, 0x29C1F6E6B3E0301B,
	0xC96C5795D7870F42, 0x7A421B2BD420502D, 0x3DE861C27FC7AF19, 0x8EC62D7C7C60F076,
	0xB2BC941128085171, 0x0192D8AF2BAF0E1E, 0x4638A2468048F12A, 0xF516EEF883EFAE45,
	0x3ECDD09C2899B324, 0x8DE39C222B3EEC4B, 0xCA49E6CB80D9137F, 0x7967AA75837E4C10,
	0x451D1318D716ED17, 0xF6335FA6D4B1B278, 0xB199254F7F564D4C, 0x02B769F17CF11223,
	0xB4F7F6AD86B4690B, 0x07D9BA1385133664, 0x4073C0FA2EF4C950, 0xF35D8C442D53963F,
	0xCF273529793B3738, 0x7C0979977A9C6857, 0x3BA3037ED17B9763, 0x888D4FC0D2DCC80C,
	0x435671A479AAD56D, 0xF0783D1A7A0D8A02, 0xB7D247F3D1EA7536, 0x04FC0B4DD24D2A59,
	0x3886B22086258B5E, 0x8BA8FE9E8582D431, 0xCC0284772E652B05, 0x7F2CC8C92DC2746A,
	0x325B15E575E1C3D0, 0x8175595B76469CBF, 0xC6DF23B2DDA1638B, 0x75F16F0CDE063CE4,
	0x498BD6618A6E9DE3, 0xFAA59ADF89C9C28C, 0xBD0FE036222E3DB8, 0x0E21AC88218962D7,
	0xC5FA92EC8AFF7FB6, 0x76D4DE52895820D9, 0x317EA4BB22BFDFED, 0x8250E80521188082,
	0xBE2A516875702185, 0x0D041DD676D77EEA, 0x4AAE673FDD3081DE, 0xF9802B81DE97DEB1,
	0x4FC0B4DD24D2A599, 0xFCEEF8632775FAF6, 0xBB44828A8C9205C2, 0x086ACE348F355AAD,
	0x34107759DB5DFBAA, 0x873E3BE7D8FAA4C5, 0xC094410E731D5BF1, 0x73BA0DB070BA049E,
	0xB86133D4DBCC19FF, 0x0B4F7F6AD86B4690, 0x4CE50583738CB9A4, 0xFFCB493D702BE6CB,
	0xC3B1F050244347CC, 0x709FBCEE27E418A3, 0x3735C6078C03E797, 0x841B8AB98FA4B8F8,
	0xADDA7C5F3C4488E3, 0x1EF430E13FE3D78C, 0x595E4A08940428B8, 0xEA7006B697A377D7,
	0xD60ABFDBC3CBD6D0, 0x6524F365C06C89BF, 0x228E898C6B8B768B, 0x91A0C532682C29E4,
	0x5A7BFB56C35A3485, 0xE955B7E8C0FD6BEA, 0xAEFFCD016B1A94DE, 0x1DD181BF68BDCBB1,
	0x21AB38D23CD56AB6, 0x9285746C3F7235D9, 0xD52F0E859495CAED, 0x6601423B97329582,
	0xD041DD676D77EEAA, 0x636F91D96ED0B1C5, 0x24C5EB30C5374EF1, 0x97EBA78EC690119E,
	0xAB911EE392F8B099, 0x18BF525D915FEFF6, 0x5F1528B43AB810C2, 0xEC3B640A391F4FAD,
	0x27E05A6E926952CC, 0x94CE16D091CE0DA3, 0xD3646C393A29F297, 0x604A2087398EADF8,
	0x5C3099EA6DE60CFF, 0xEF1ED5546E415390, 0xA8B4AFBDC5A6ACA4, 0x1B9AE303C601F3CB,
	0x56ED3E2F9E224471, 0xE5C372919D851B1E, 0xA26908783662E42A, 0x114744C635C5BB45,
	0x2D3DFDAB61AD1A42, 0x9E13B115620A452D, 0xD9B9CBFCC9EDBA19, 0x6A978742CA4AE576,
	0xA14CB926613CF817, 0x1262F598629BA778, 0x55C88F71C97C584C, 0xE6E6C3CFCADB0723,
	0xDA9C7AA29EB3A624, 0x69B2361C9D14F94B, 0x2E184CF536F3067F, 0x9D36004B35545910,
	0x2B769F17CF112238, 0x9858D3A9CCB67D57, 0xDFF2A94067518263, 0x6CDCE5FE64F6DD0C,
	0x50A65C93309E7C0B, 0xE388102D33392364, 0xA4226AC498DEDC50, 0x170C267A9B79833F,
	0xDCD7181E300F9E5E, 0x6FF954A033A8C131, 0x28532E49984F3E05, 0x9B7D62F79BE8616A,
	0xA707DB9ACF80C06D, 0x14299724CC279F02, 0x5383EDCD67C06036, 0xE0ADA17364673F59\
};


// Reference implementation
uint64_t crc64_reference(uint64_t crc, const unsigned char* data, size_t length)
{
	crc = ~crc;
	for (size_t j = 0; j < length; j++)
	{
		crc = crcTable[(crc ^ data[j]) & 0xff] ^ (crc >> 8);
	}
	return ~crc;
}

// Reverses bits
static uint64_t bitReflect(uint64_t v)
{
	v = ((v >> 1) & 0x5555555555555555) | ((v & 0x5555555555555555) << 1);
	v = ((v >> 2) & 0x3333333333333333) | ((v & 0x3333333333333333) << 2);
	v = ((v >> 4) & 0x0F0F0F0F0F0F0F0F) | ((v & 0x0F0F0F0F0F0F0F0F) << 4);
	v = ((v >> 8) & 0x00FF00FF00FF00FF) | ((v & 0x00FF00FF00FF00FF) << 8);
	v = ((v >> 16) & 0x0000FFFF0000FFFF) | ((v & 0x0000FFFF0000FFFF) << 16);
	v = (v >> 32) | (v << 32);
	return v;
}

// Computes r*x^N mod p(x)
static uint64_t expMod65(uint32_t n, uint64_t p, uint64_t r)
{
	return n == 0 ? r : expMod65(n - 1, p, (r << 1) ^ (p & ((int64_t)r >> 63)));
}

// Computes x^129 / p(x); the result has an implicit 65th bit.
static uint64_t div129by65(uint64_t poly)
{
	uint64_t q = 0;
	uint64_t h = poly;
	for (uint32_t i = 0; i < 64; ++i)
	{
		q |= (h & (1ull << 63)) >> i;
		h = (h << 1) ^ (poly & ((int64_t)h >> 63));
	}
	return q;
}

static const uint8_t shuffleMasks[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80,
};

static void shiftRight128(__m128i in, size_t n, __m128i* outLeft, __m128i* outRight)
{
	const __m128i maskA = _mm_loadu_si128((const __m128i*)(shuffleMasks + (16 - n)));
	const __m128i maskB = _mm_xor_si128(maskA, _mm_cmpeq_epi8(_mm_setzero_si128(), _mm_setzero_si128()));

	*outLeft = _mm_shuffle_epi8(in, maskB);
	*outRight = _mm_shuffle_epi8(in, maskA);
}

static __m128i fold(__m128i in, __m128i foldConstants)
{
	return _mm_xor_si128(_mm_clmulepi64_si128(in, foldConstants, 0x00), _mm_clmulepi64_si128(in, foldConstants, 0x11));
}

uint64_t crc64(uint64_t crc, const uint8_t *data, size_t length)
{
	const uint64_t k1 = 0xe05dd497ca393ae4; // bitReflect(expMod65(128 + 64, poly, 1)) << 1;
	const uint64_t k2 = 0xdabe95afc7875f40; // bitReflect(expMod65(128, poly, 1)) << 1;
	const uint64_t mu = 0x9c3e466c172963d5; // (bitReflect(div129by65(poly)) << 1) | 1;
	const uint64_t p  = 0x92d8af2baf0e1e85; // (bitReflect(poly) << 1) | 1;

	const __m128i foldConstants1 = _mm_set_epi64x(k2, k1);
	const __m128i foldConstants2 = _mm_set_epi64x(p, mu);

	const uint8_t* end = data + length;

	// Align pointers
	const __m128i* alignedData = (const __m128i*)((uintptr_t)data & ~(uintptr_t)15);
	const __m128i* alignedEnd = (const __m128i*)(((uintptr_t)end + 15) & ~(uintptr_t)15);

	const size_t leadInSize = data - (const uint8_t*)alignedData;
	const size_t leadOutSize = (const uint8_t*)alignedEnd - end;

	const size_t alignedLength = alignedEnd - alignedData;

	const __m128i leadInMask = _mm_loadu_si128((const __m128i*)(shuffleMasks + (16 - leadInSize)));
	const __m128i data0 = _mm_blendv_epi8(_mm_setzero_si128(), _mm_load_si128(alignedData), leadInMask);

#if defined(_WIN64)
	const __m128i initialCrc = _mm_cvtsi64x_si128(~crc);
#else
	const __m128i initialCrc = _mm_set_epi64x(0, ~crc);
#endif

	__m128i R;
	if (alignedLength == 1)
	{
		// Single data block, initial CRC possibly bleeds into zero padding
		__m128i crc0, crc1;
		shiftRight128(initialCrc, 16 - length, &crc0, &crc1);

		__m128i A, B;
		shiftRight128(data0, leadOutSize, &A, &B);

		const __m128i P = _mm_xor_si128(A, crc0);
		R = _mm_xor_si128(_mm_clmulepi64_si128(P, foldConstants1, 0x10), _mm_xor_si128(_mm_srli_si128(P, 8), _mm_slli_si128(crc1, 8)));
	}
	else if (alignedLength == 2)
	{
		const __m128i data1 = _mm_load_si128(alignedData + 1);

		if (length < 8)
		{
			// Initial CRC bleeds into the zero padding
			__m128i crc0, crc1;
			shiftRight128(initialCrc, 16 - length, &crc0, &crc1);

			__m128i A, B, C, D;
			shiftRight128(data0, leadOutSize, &A, &B);
			shiftRight128(data1, leadOutSize, &C, &D);

			const __m128i P = _mm_xor_si128(_mm_xor_si128(B, C), crc0);
			R = _mm_xor_si128(_mm_clmulepi64_si128(P, foldConstants1, 0x10), _mm_xor_si128(_mm_srli_si128(P, 8), _mm_slli_si128(crc1, 8)));
		}
		else
		{
			// We can fit the initial CRC into the data without bleeding into the zero padding
			__m128i crc0, crc1;
			shiftRight128(initialCrc, leadInSize, &crc0, &crc1);

			__m128i A, B, C, D;
			shiftRight128(_mm_xor_si128(data0, crc0), leadOutSize, &A, &B);
			shiftRight128(_mm_xor_si128(data1, crc1), leadOutSize, &C, &D);

			const __m128i P = _mm_xor_si128(fold(A, foldConstants1), _mm_xor_si128(B, C));
			R = _mm_xor_si128(_mm_clmulepi64_si128(P, foldConstants1, 0x10), _mm_srli_si128(P, 8));
		}
	}
	else
	{
		alignedData++;
		length -= 16 - leadInSize;

		// Initial CRC can simply be added to data
		__m128i crc0, crc1;
		shiftRight128(initialCrc, leadInSize, &crc0, &crc1);

		__m128i accumulator = _mm_xor_si128(fold(_mm_xor_si128(crc0, data0), foldConstants1), crc1);

		while (length >= 32)
		{
			accumulator = fold(_mm_xor_si128(_mm_load_si128(alignedData), accumulator), foldConstants1);

			length -= 16;
			alignedData++;
		}

		__m128i P;
		if (length == 16)
		{
			P = _mm_xor_si128(accumulator, _mm_load_si128(alignedData));
		}
		else
		{
			const __m128i end0 = _mm_xor_si128(accumulator, _mm_load_si128(alignedData));
			const __m128i end1 = _mm_load_si128(alignedData + 1);

			__m128i A, B, C, D;
			shiftRight128(end0, leadOutSize, &A, &B);
			shiftRight128(end1, leadOutSize, &C, &D);

			P = _mm_xor_si128(fold(A, foldConstants1), _mm_or_si128(B, C));
		}

		R = _mm_xor_si128(_mm_clmulepi64_si128(P, foldConstants1, 0x10), _mm_srli_si128(P, 8));
	}

	// Final Barrett reduction
	const __m128i T1 = _mm_clmulepi64_si128(R, foldConstants2, 0x00);
	const __m128i T2 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(T1, foldConstants2, 0x10), _mm_slli_si128(T1, 8)), R);

#if defined(_WIN64)
	return ~_mm_extract_epi64(T2, 1);
#else
	return ~(((uint64_t)(uint32_t)_mm_extract_epi32(T2, 3) << 32) | (uint64_t)(uint32_t)_mm_extract_epi32(T2, 2));
#endif
}
