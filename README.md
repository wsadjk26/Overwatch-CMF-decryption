# Overwatch CMF decryption
**Algorithm**: AES  
**Mode**: CBC  
**Encrypted data offset**: sizeof(CMFHeader)

### Notes:
* CMFHeader is different for each CMF version. 
* GenerateKey takes a buffer of 32 bytes.  
* GenerateIV takes a buffer of 16 bytes.  
* CMF V20 is for clients version < 1.14  
* CMF V21 is for clients version >= 1.14  
