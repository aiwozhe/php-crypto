/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jakub Zelenka <jakub.php@gmail.com>                          |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_CRYPTO_EVP_H
#define PHP_CRYPTO_EVP_H

#include "php.h"
#include "php_crypto.h"

#include <openssl/evp.h>

typedef enum {
	PHP_CRYPTO_ALG_NONE = 0,
	PHP_CRYPTO_ALG_CIPHER,
	PHP_CRYPTO_ALG_DIGEST
} php_crypto_algorithm_type;

typedef enum {
	PHP_CRYPTO_ALG_STATUS_CLEAR,
	PHP_CRYPTO_ALG_STATUS_DIGEST,
	PHP_CRYPTO_ALG_STATUS_ENCRYPT,
	PHP_CRYPTO_ALG_STATUS_DECRYPT
} php_crypto_algorithm_status;

typedef struct {
	zend_object zo;
	php_crypto_algorithm_type type;
	php_crypto_algorithm_status status;
	union {
		struct {
			const EVP_CIPHER *alg;
			EVP_CIPHER_CTX *ctx;
		} cipher;
		struct {
			const EVP_MD *alg;
			EVP_MD_CTX *ctx;
		} digest;
	};
} php_crypto_algorithm_object;

/* Algorithm exceptions macros */
#define PHP_CRYPTO_ALG_E(code) PHP_CRYPTO_ALGORITHM_ERROR_##code
#define PHP_CRYPTO_THROW_ALGORITHM_EXCEPTION(code, msg) \
	PHP_CRYPTO_THROW_EXCEPTION(php_crypto_algorithm_exception_ce, PHP_CRYPTO_ALG_E(code), msg)
#define PHP_CRYPTO_THROW_ALGORITHM_EXCEPTION_EX(code, msg, ...) \
	PHP_CRYPTO_THROW_EXCEPTION_EX(php_crypto_algorithm_exception_ce, PHP_CRYPTO_ALG_E(code), msg, ##__VA_ARGS__)

/* Algorithm exception error codes */
typedef enum {
	PHP_CRYPTO_ALG_E(CIPHER_NOT_FOUND) = 1,
	PHP_CRYPTO_ALG_E(CIPHER_KEY_LENGTH),
	PHP_CRYPTO_ALG_E(CIPHER_IV_LENGTH),
	PHP_CRYPTO_ALG_E(CIPHER_INIT_FAILED),
	PHP_CRYPTO_ALG_E(CIPHER_UPDATE_FAILED),
	PHP_CRYPTO_ALG_E(CIPHER_FINAL_FAILED),
	PHP_CRYPTO_ALG_E(ENCRYPT_INIT_STATUS),
	PHP_CRYPTO_ALG_E(ENCRYPT_UPDATE_STATUS),
	PHP_CRYPTO_ALG_E(ENCRYPT_FINAL_STATUS),
	PHP_CRYPTO_ALG_E(DECRYPT_INIT_STATUS),
	PHP_CRYPTO_ALG_E(DECRYPT_UPDATE_STATUS),
	PHP_CRYPTO_ALG_E(DECRYPT_FINAL_STATUS),
	PHP_CRYPTO_ALG_E(DIGEST_NOT_FOUND),
	PHP_CRYPTO_ALG_E(DIGEST_INIT_FAILED),
	PHP_CRYPTO_ALG_E(DIGEST_UPDATE_FAILED),
	PHP_CRYPTO_ALG_E(DIGEST_FINAL_FAILED),
	PHP_CRYPTO_ALG_E(DIGEST_UPDATE_STATUS),
	PHP_CRYPTO_ALG_E(DIGEST_FINAL_STATUS)
} php_crypto_algorithm_error_code;

/* Class entries */
extern PHP_CRYPTO_API zend_class_entry *php_crypto_algorithm_ce;
extern PHP_CRYPTO_API zend_class_entry *php_crypto_digest_ce;
extern PHP_CRYPTO_API zend_class_entry *php_crypto_cipher_ce;
extern PHP_CRYPTO_API zend_class_entry *php_crypto_algorithm_exception_ce;

/* Methods definitions */
PHP_MINIT_FUNCTION(crypto_evp);
PHP_CRYPTO_METHOD(Algorithm, getAlgorithm);
PHP_CRYPTO_METHOD(Cipher, hasAlgorithm);
PHP_CRYPTO_METHOD(Cipher, __construct);
PHP_CRYPTO_METHOD(Cipher, encryptInit);
PHP_CRYPTO_METHOD(Cipher, encryptUpdate);
PHP_CRYPTO_METHOD(Cipher, encryptFinal);
PHP_CRYPTO_METHOD(Cipher, encrypt);
PHP_CRYPTO_METHOD(Cipher, decryptInit);
PHP_CRYPTO_METHOD(Cipher, decryptUpdate);
PHP_CRYPTO_METHOD(Cipher, decryptFinal);
PHP_CRYPTO_METHOD(Cipher, decrypt);
PHP_CRYPTO_METHOD(Cipher, getBlockSize);
PHP_CRYPTO_METHOD(Cipher, getKeyLength);
PHP_CRYPTO_METHOD(Cipher, getIVLength);
PHP_CRYPTO_METHOD(Digest, hasAlgorithm);
PHP_CRYPTO_METHOD(Digest, __construct);
PHP_CRYPTO_METHOD(Digest, init);
PHP_CRYPTO_METHOD(Digest, update);
PHP_CRYPTO_METHOD(Digest, final);
PHP_CRYPTO_METHOD(Digest, make);
PHP_CRYPTO_METHOD(Digest, getSize);
PHP_CRYPTO_METHOD(Digest, getBlockSize);

#endif	/* PHP_CRYPTO_EVP_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
