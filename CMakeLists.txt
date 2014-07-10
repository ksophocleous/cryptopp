cmake_minimum_required(VERSION 2.6)

project(cryptopp)

option(INCLUDE_NETWORK "Include networking component" OFF)
option(BUILD_SHARED "Build shared version of the library" OFF)

set(libtype STATIC)

set(extras
#	bench.cpp
#	bench2.cpp
#	datatest.cpp
#	test.cpp
#	validat1.cpp
#	validat2.cpp
#	validat3.cpp
#	dlltest.cpp
#	bench.h
#	validate.h
#	regtest.cpp
)

set(src
	3way.cpp
	adhoc.cpp.proto
	adler32.cpp
	algebra.cpp
	algparam.cpp
	arc4.cpp
	asn.cpp
	authenc.cpp
	base32.cpp
	base64.cpp
	basecode.cpp
	bfinit.cpp
	blowfish.cpp
	blumshub.cpp
	camellia.cpp
	cast.cpp
	casts.cpp
	cbcmac.cpp
	ccm.cpp
	channels.cpp
	cmac.cpp
	cpu.cpp
	crc.cpp
	cryptlib.cpp
	default.cpp
	des.cpp
	dessp.cpp
	dh.cpp
	dh2.cpp
	dll.cpp
	dsa.cpp
	eax.cpp
	ec2n.cpp
	eccrypto.cpp
	ecp.cpp
	elgamal.cpp
	emsa2.cpp
	eprecomp.cpp
	esign.cpp
	files.cpp
	filters.cpp
	fips140.cpp
	fipsalgt.cpp
	fipstest.cpp
	gcm.cpp
	gf256.cpp
	gf2_32.cpp
	gf2n.cpp
	gfpcrypt.cpp
	gost.cpp
	gzip.cpp
	hex.cpp
	hmac.cpp
	hrtimer.cpp
	ida.cpp
	idea.cpp
	integer.cpp
	iterhash.cpp
	luc.cpp
	mars.cpp
	marss.cpp
	md2.cpp
	md4.cpp
	md5.cpp
	misc.cpp
	modes.cpp
	mqueue.cpp
	mqv.cpp
	nbtheory.cpp
	oaep.cpp
	osrng.cpp
	panama.cpp
	pch.cpp
	pkcspad.cpp
	polynomi.cpp
	pssr.cpp
	pubkey.cpp
	queue.cpp
	rabin.cpp
	randpool.cpp
	rc2.cpp
	rc5.cpp
	rc6.cpp
	rdtables.cpp
	rijndael.cpp
	ripemd.cpp
	rng.cpp
	rsa.cpp
	rw.cpp
	safer.cpp
	salsa.cpp
	seal.cpp
	seed.cpp
	serpent.cpp
	sha.cpp
	shacal2.cpp
	shark.cpp
	sharkbox.cpp
	simple.cpp
	skipjack.cpp
	sosemanuk.cpp
	square.cpp
	squaretb.cpp
	stdcpp.h
	strciphr.cpp
	tea.cpp
	tftables.cpp
	tiger.cpp
	tigertab.cpp
	trdlocal.cpp
	ttmac.cpp
	twofish.cpp
	vmac.cpp
	wait.cpp
	wake.cpp
	whrlpool.cpp
	winpipes.cpp
	xtr.cpp
	xtrcrypt.cpp
	zdeflate.cpp
	zinflate.cpp
	zlib.cpp
	sha3.cpp)

set(public_hdr
	sha3.h
	3way.h
	adler32.h
	aes.h
	algebra.h
	algparam.h
	arc4.h
	argnames.h
	asn.h
	authenc.h
	base32.h
	base64.h
	basecode.h
	blowfish.h
	blumshub.h
	camellia.h
	cast.h
	cbcmac.h
	ccm.h
	channels.h
	cmac.h
	config.h
	cpu.h
	crc.h
	cryptlib.h
	default.h
	des.h
	dh.h
	dh2.h
	dll.h
	dmac.h
	dsa.h
	eax.h
	ec2n.h
	eccrypto.h
	ecp.h
	elgamal.h
	emsa2.h
	eprecomp.h
	esign.h
	factory.h
	files.h
	filters.h
	fips140.h
	fltrimpl.h
	gcm.h
	gf256.h
	gf2_32.h
	gf2n.h
	gfpcrypt.h
	gost.h
	gzip.h
	hex.h
	hmac.h
	hrtimer.h
	ida.h
	idea.h
	integer.h
	iterhash.h
	lubyrack.h
	luc.h
	mars.h
	md2.h
	md4.h
	md5.h
	mdc.h
	misc.h
	modarith.h
	modes.h
	modexppc.h
	mqueue.h
	mqv.h
	nbtheory.h
	nr.h
	oaep.h
	oids.h
	osrng.h
	panama.h
	pch.h
	pkcspad.h
	polynomi.h
	pssr.h
	pubkey.h
	pwdbased.h
	queue.h
	rabin.h
	randpool.h
	rc2.h
	rc5.h
	rc6.h
	resource.h
	rijndael.h
	ripemd.h
	rng.h
	rsa.h
	rw.h
	safer.h
	salsa.h
	seal.h
	secblock.h
	seckey.h
	seed.h
	serpent.h
	serpentp.h
	sha.h
	shacal2.h
	shark.h
	simple.h
	skipjack.h
	smartptr.h
	sosemanuk.h
	square.h
	stdcpp.h
	strciphr.h
	tea.h
	tiger.h
	trdlocal.h
	trunhash.h
	ttmac.h
	twofish.h
	vmac.h
	wait.h
	wake.h
	whrlpool.h
	winpipes.h
	words.h
	xtr.h
	xtrcrypt.h
	zdeflate.h
	zinflate.h
	zlib.h)

if(INCLUDE_NETWORK)
	list(APPEND src "socketft.cpp" "network.cpp")
	list(APPEND public_hdr "socketft.h" "network.h")
endif()

set(public_hdr_loc "${CMAKE_CURRENT_SOURCE_DIR}/")
set(libname "cryptopp")
set(version "5.6.2")

# -- Shared library?
if (BUILD_SHARED)
	set(libtype SHARED)
	set(cryptopp_def "CRYPTOPP_EXPORTS")
endif()

add_library(${libname} ${libtype} ${src} ${public_hdr})

if(WIN32)
	list(APPEND platformlibs "wsock32.lib")
	list(APPEND platformlibs "shlwapi.lib")
endif()

target_link_libraries(${libname} ${platformlibs})

set_target_properties(${libname} PROPERTIES 
	INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/."
	PUBLIC_HEADER "${public_hdr}"
	INTERFACE_INCLUDE_DIRECTORIES "${public_hdr_loc}"
	COMPILE_DEFINITIONS "${cryptopp_def}"
	VERSION ${version}
	LIBFILENAME "cryptopp"
	)
