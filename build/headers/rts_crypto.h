#ifndef __RTS_CRYPTO_H__
#define __RTS_CRYPTO_H__

#include <stdint.h>

#define RTS_CIPHER_ENCRYPT_LEN_MAX	(1024 * 1024) /* byte */

enum RTS_CIPHER_ERRNO {
	RTS_OK = 0,
	RTS_FAIL,
	RTS_E_CIPHER_NOT_INITIALIZED,
	RTS_E_CIPHER_INVALID_ARG,
	RTS_E_CIPHER_NULL_POINT,
	RTS_E_CIPHER_NO_MEMORY,
	RTS_E_CIPHER_NOT_SUPPORT,
};

enum RTS_CIPHER_KEYSIZE {
	RTS_CIPHER_AES_KEYSIZE_128 = 16,
	RTS_CIPHER_AES_KEYSIZE_192 = 24,
	RTS_CIPHER_AES_KEYSIZE_256 = 32,
	RTS_CIPHER_DES_KEYSIZE_1KEY = 8,
	RTS_CIPHER_DES_KEYSIZE_3KEY = 24,
};

enum RTS_CIPHER_PADDING_MODE {
	RTS_CIPHER_PADDING_NONE = 0,
	RTS_CIPHER_PADDING_PKCS7
};

struct rts_cipher_handle;

/**
 * Initialize cipher handle
 *
 * @param[out] handle - return cipher handle
 * @param[in]  name   - cipher name (ex: cbc(aes))
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_init(struct rts_cipher_handle **handle, const char *name);

/**
 * Destroy cipher handle and release resources
 *
 * @param[in] handle - cipher handle
 *
 */
void rts_cipher_destroy(struct rts_cipher_handle *handle);

/**
 * Set cipher key
 *
 * @param[in] handle  - cipher handle
 * @param[in] key     - key buffer
 * @param[in] keysize - length of key buffer
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_setkey(struct rts_cipher_handle *handle,
			const uint8_t *key, uint32_t keysize);

/**
 * Get size of one block of the cipher
 *
 * @param[in]  handle - cipher handle
 * @param[out] bksize - return size of one block
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_get_blocksize(struct rts_cipher_handle *handle,
			uint32_t *bksize);

/**
 * Get size of IV required for cipher
 *
 * @param[in]  handle - cipher handle
 * @param[out] ivsize - return size of IV required
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_get_ivsize(struct rts_cipher_handle *handle, uint32_t *ivsize);

/**
 * Set cipher iv
 *
 * @param[in] handle - cipher handle
 * @param[in] iv     - iv buffer
 * @param[in] ivsize - length of iv buffer
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_setiv(struct rts_cipher_handle *handle,
			const uint8_t *iv, uint32_t ivsize);

/**
 * Start to encrypt
 *
 * @param[in]     handle - cipher handle
 * @param[in]     in     - plaintext buffer
 * @param[in]     inlen  - length of in buffer, <= 1MB
 *                         padding mode:
 *                         RTS_CIPHER_PADDING_NONE && need padding:
 *                                    must be multiple of block size
 * @param[out]    out    - ciphertext buffer
 * @param[in,out] outlen - in: length of out buffer
 *                         padding mode:
 *                         RTS_CIPHER_PADDING_NONE: >= inlen
 *                         RTS_CIPHER_PADDING_PKCS7:
 *                                    >= (inlen / blocksize + 1) * blocksize
 *                         out: actual length of the ciphertext
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_encrypt(struct rts_cipher_handle *handle,
			const uint8_t *in, uint32_t inlen,
			uint8_t *out, uint32_t *outlen);

/**
 * Start to decrypt
 *
 * @param[in]     handle - cipher handle
 * @param[in]     in     - ciphertext buffer
 * @param[in]     inlen  - length of in buffer
 *                         RTS_CIPHER_PADDING_NONE:
 *                              <= 1MB
 *                              need padding: must be multiple of block size
 *                         RTS_CIPHER_PADDING_PKCS7:
 *                              <= 1MB + block size
 *                              must be multiple of block size
 * @param[out]    out    - plaintext buffer
 * @param[in,out] outlen - in: length of out buffer. >= inlen
 *                         out: actual length of the plaintext
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_decrypt(struct rts_cipher_handle *handle,
			const uint8_t *in, uint32_t inlen,
			uint8_t *out, uint32_t *outlen);

/**
 * set padding mode
 *
 * @param[in] handle - cipher handle
 * @param[in] mode   - padding mode. default: RTS_CIPHER_PADDING_NONE
 *
 * @return =0 - success
 *	   <0 - fail
 */
int rts_cipher_set_padding(struct rts_cipher_handle *handle,
			enum RTS_CIPHER_PADDING_MODE mode);


#endif
