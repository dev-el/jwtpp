// The MIT License (MIT)
//
// Copyright (c) 2023 Jesiel Emerim Schardosim
// Copyright (c) 2016-2020 Artur Troian
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <gtest/gtest.h>

#include <jwtpp/jwtpp.hh>

#include <openssl/err.h>

TEST(jwtpp, rsa_gen_invalid_size) {
	jwtpp::sp_rsa_key key;

	EXPECT_THROW(key = jwtpp::rsa::gen(1023), std::exception);
}

TEST(jwtpp, create_close_rsa_crypto) {
	jwtpp::sp_rsa_key key;

	EXPECT_NO_THROW(key = jwtpp::rsa::gen(1024));

	EXPECT_NO_THROW(std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS512));

	EXPECT_THROW(std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::HS256), std::exception);
	EXPECT_THROW(std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::ES384), std::exception);
}

TEST(jwtpp, sign_verify_rsa256) {
	jwtpp::claims cl;

	jwtpp::sp_rsa_key key;
	jwtpp::sp_rsa_key pubkey;
	jwtpp::sp_crypto r256;
	jwtpp::sp_crypto r256_pub;
	jwtpp::sp_crypto r384;
	jwtpp::sp_crypto r384_pub;
	jwtpp::sp_crypto r512;
	jwtpp::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jwtpp::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jwtpp::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r384 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r512 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS512));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS512));

	std::string bearer = jwtpp::jws::sign_bearer(cl, r256);

	jwtpp::sp_jws jws;

	EXPECT_NO_THROW(jws = jwtpp::jws::parse(bearer, true));

	EXPECT_TRUE(jws->verify(r256_pub));

	auto vf = [](jwtpp::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r256_pub, vf));
	EXPECT_THROW(jws->verify(r384_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r512_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);
}

TEST(jwtpp, sign_verify_rsa384) {
	jwtpp::claims cl;

	jwtpp::sp_rsa_key key;
	jwtpp::sp_rsa_key pubkey;
	jwtpp::sp_crypto r256;
	jwtpp::sp_crypto r256_pub;
	jwtpp::sp_crypto r384;
	jwtpp::sp_crypto r384_pub;
	jwtpp::sp_crypto r512;
	jwtpp::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jwtpp::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jwtpp::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r384 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r512 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS512));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS512));

	std::string bearer = jwtpp::jws::sign_bearer(cl, r384);

	jwtpp::sp_jws jws;

	EXPECT_NO_THROW(jws = jwtpp::jws::parse(bearer, true));

	EXPECT_TRUE(jws->verify(r384_pub));

	auto vf = [](jwtpp::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r384_pub, vf));
	EXPECT_THROW(jws->verify(r256_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r512_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);
}

TEST(jwtpp, sign_verify_rsa512) {
	jwtpp::claims cl;

	jwtpp::sp_rsa_key key;
	jwtpp::sp_rsa_key pubkey;
	jwtpp::sp_crypto r256;
	jwtpp::sp_crypto r256_pub;
	jwtpp::sp_crypto r384;
	jwtpp::sp_crypto r384_pub;
	jwtpp::sp_crypto r512;
	jwtpp::sp_crypto r512_pub;

	EXPECT_NO_THROW(key = jwtpp::rsa::gen(1024));
	EXPECT_NO_THROW(pubkey = jwtpp::sp_rsa_key(RSAPublicKey_dup(key.get()), ::RSA_free));
	EXPECT_NO_THROW(r256 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r256_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS256));
	EXPECT_NO_THROW(r384 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r384_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS384));
	EXPECT_NO_THROW(r512 = std::make_shared<jwtpp::rsa>(key, jwtpp::alg_t::RS512));
	EXPECT_NO_THROW(r512_pub = std::make_shared<jwtpp::rsa>(pubkey, jwtpp::alg_t::RS512));

	std::string bearer = jwtpp::jws::sign_bearer(cl, r512);

	jwtpp::sp_jws jws;

	EXPECT_NO_THROW(jws = jwtpp::jws::parse(bearer, true));

	EXPECT_TRUE(jws->verify(r512_pub));

	auto vf = [](jwtpp::sp_claims cl) {
		return !cl->check().iss("troian");
	};

	EXPECT_TRUE(jws->verify(r512_pub, vf));
	EXPECT_THROW(jws->verify(r384_pub, vf), std::exception);
	EXPECT_THROW(jws->verify(r256_pub, vf), std::exception);

	bearer = "ghdfgddf";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer ";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);

	bearer = "Bearer bla.bla.bla";
	EXPECT_THROW(jws = jwtpp::jws::parse(bearer, true), std::exception);
}

TEST(jwtpp, load_rsa_from_file) {
	jwtpp::sp_rsa_key key;

	EXPECT_NO_THROW(key = jwtpp::rsa::load_from_file(TEST_RSA_KEY_PATH, [](jwtpp::secure_string &pass, int rwflag) {
		pass.assign("12345");
	}));

	EXPECT_THROW(key = jwtpp::rsa::load_from_file(TEST_RSA_KEY_PATH), std::exception);
}
